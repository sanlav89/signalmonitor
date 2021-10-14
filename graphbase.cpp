#include "graphbase.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <qwt_picker_machine.h>
#include <qwt_symbol.h>
#include "myscaledraw.h"

GraphBase::GraphBase(QWidget *parent)
    : QwtPlot(parent)
    , m_xLeft(0)
    , m_xRight(0)
    , m_yBottom(0)
    , m_yTop(0)
    , m_xValues({})
    , m_yValues({})
    , m_generalFont(QFont("Helvetica", 10))
{
    // Основное
    QwtText axisTitle = QwtText("Амплитуда [В]");
    QFont axisTitleFont = QFont("Consolas", 20);
    axisTitle.setFont(axisTitleFont);
    setAxisTitle(QwtPlot::yLeft, axisTitle);
    axisTitle.setText("Время [сек]");
    setAxisTitle(QwtPlot::xBottom, axisTitle);
    setAxisScaleDraw(QwtPlot::yLeft, new MyScaleDraw());
    setAxisScaleDraw(QwtPlot::xBottom, new MyScaleDraw("%.6f"));

    // Шрифт осей
    setAxisFont(QwtPlot::xBottom,  m_generalFont);
    setAxisFont(QwtPlot::yLeft, m_generalFont);

    // Фон
    QPalette pal;
//    pal.setBrush(QPalette::Window, QBrush(QColor(50, 50, 100)));
    pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
    setPalette(pal);

    // Сетка
    m_grid = new QwtPlotGrid;
    m_grid->enableXMin(true);
    m_grid->enableYMin(true);
    m_grid->enableX(false);
    m_grid->enableY(false);
    m_grid->attach(this);
    setGrid(true, true, QPen(Qt::black, 0.25, Qt::DashLine));

    // Зумер
    m_zoomer = new MyZoomer(this->canvas());
    m_zoomer->setRubberBandPen(QPen(Qt::white));
    m_zoomer->setTrackerPen(QPen(Qt::white));
    m_zoomer->setTrackerFont(m_generalFont);
    m_zoomer->setMousePattern(QwtEventPattern::MouseSelect1, Qt::LeftButton, Qt::ShiftModifier);
    m_zoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::NoButton);
    m_zoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::NoButton);

    // Курсор мыши
    m_picker = new MyPlotPicker(canvas());
    m_picker->setStateMachine(new QwtPickerDragLineMachine);
    m_picker->setRubberBand(QwtPicker::VLineRubberBand);
    m_picker->setRubberBandPen(QPen(Qt::white));
    m_picker->setTrackerMode(QwtPicker::AlwaysOn);
    m_picker->setTrackerPen(QPen(Qt::black));
    m_picker->setTrackerFont(QFont("Consolas", 18, QFont::Normal));

    // Левый маркер выделения
    m_markerLeft = new QwtPlotMarker();
    m_markerLeft->setLineStyle(QwtPlotMarker::VLine);
    m_markerLeft->setLinePen(Qt::white, 2, Qt::SolidLine);
    m_markerLeft->attach(this);
    m_markerLeft->setLabelAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_markerLeft->setVisible(false);

    // Правый маркер выделения
    m_markerRight = new QwtPlotMarker();
    m_markerRight->setLineStyle(QwtPlotMarker::VLine);
    m_markerRight->setLinePen(Qt::darkGray, 2, Qt::SolidLine);
    m_markerRight->attach(this);
    m_markerRight->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
    m_markerRight->setVisible(false);

    // Маркер со значением в точке
    m_markerValue = new QwtPlotMarker();
    m_markerValue->setLineStyle(QwtPlotMarker::VLine);
    m_markerValue->setLinePen(Qt::black, 0.5, Qt::SolidLine);
    m_markerValue->attach(this);
    m_markerValue->setLabelAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_markerValue->setSymbol(new QwtSymbol(
                                   QwtSymbol::Diamond,
                                   QBrush(Qt::gray),
                                   QPen(Qt::black, 1.5),
                                   QSize(20, 20)
                                   ));
    m_markerValue->setLabelAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_markerValue->setVisible(false);

    // Кривая
    m_curve = new QwtPlotCurve;
    m_curve->setBrush(QBrush());
    m_curve->setStyle(QwtPlotCurve::Lines);
    m_curve->setPen(QPen(Qt::green));
    m_curve->attach(this);

    // Зоны выделения
    m_zoomZone = new QwtPlotZoneItem();
    m_zoomZone->setBrush(Qt::darkRed);
    m_zoomZone->attach(this);
    m_zoomZone->setVisible(false);

    // Коннекты
    connect(m_picker, SIGNAL(appended(const QPointF &)),
            this, SLOT(pickerAppended(const QPointF &)));
    connect(m_picker, SIGNAL(selected(const QVector<QPointF> &)),
            this, SLOT(pickerSelected(const QVector<QPointF> &)));
    connect(m_picker, SIGNAL(moved(const QPointF &)),
            this, SLOT(pickerMoved(const QPointF &)));

    replot();
}

void GraphBase::setTitle(const QString &title)
{
    setTitle(title);
    replot();
}

void GraphBase::setGrid(bool xEnabled, bool yEnabled, const QPen &pen)
{
    m_grid->enableX(xEnabled);
    m_grid->enableY(yEnabled);
    m_grid->setPen(pen);
    replot();
}

void GraphBase::setXLabel(const QString &label)
{
    QwtText t;
    t.setText(label);
    t.setFont(m_generalFont);
    setAxisTitle(QwtPlot::xBottom, t);
}

void GraphBase::setYLabel(const QString &label)
{
    QwtText t;
    t.setText(label);
    t.setFont(m_generalFont);
    setAxisTitle(QwtPlot::yLeft, t);
}

void GraphBase::setXValues(const QVector<qreal> &xValues)
{
    if (xValues.size() == m_yValues.size()) {
        m_xValues = xValues;
        m_curve->setSamples(m_xValues.data(), m_yValues.data(), xValues.size());
        replot();
    }
}

void GraphBase::setYValues(const QVector<qreal> &yValues)
{
    if (yValues.size() == m_xValues.size()) {
        qDebug() << Q_FUNC_INFO << "here";
        m_yValues = yValues;
        qDebug() << Q_FUNC_INFO << "here";
        m_curve->setSamples(m_xValues.data(), m_yValues.data(), yValues.size());
        qDebug() << Q_FUNC_INFO << "here";
        replot();
        qDebug() << Q_FUNC_INFO << "here";
    }
}

void GraphBase::setValues(const QVector<QPointF> &values)
{
    m_xValues = QVector<qreal>(values.size());
    m_yValues = QVector<qreal>(values.size());
    for (int i = 0; i < values.size(); i++) {
        m_xValues[i] = values[i].x();
        m_yValues[i] = values[i].y();
    }
    m_curve->setSamples(m_xValues.data(), m_yValues.data(), values.size());
    replot();
}

void GraphBase::wheelEvent(QWheelEvent *e)
{
    double xmin = axisScaleDiv(QwtPlot::xBottom).lowerBound();
    double xmax = axisScaleDiv(QwtPlot::xBottom).upperBound();
    double ymin = axisScaleDiv(QwtPlot::yLeft).lowerBound();
    double ymax = axisScaleDiv(QwtPlot::yLeft).upperBound();
    double delta;

    if (e->modifiers() == Qt::ShiftModifier) {
        delta = (xmax - xmin) * 0.001 * e->angleDelta().y();
        xmin += delta;
        xmax += delta;
        if (xmin < minXValue()) {
            xmax -= delta;
            xmin = minXValue();
        }
        if (xmax > maxXValue()) {
            xmin -= delta;
            xmax = maxXValue();
        }
    } else if (e->modifiers() == Qt::ControlModifier) {
        delta = (xmax - xmin) * 0.001 * e->angleDelta().y();
        xmin += delta;
        xmax -= delta;
        if (xmin < minXValue()) {
            xmin = minXValue();
        }
        if (xmax > maxXValue()) {
            xmax = maxXValue();
        }
    } else if (e->modifiers() == Qt::AltModifier) {
        delta = (ymax - ymin) * 0.001 * e->angleDelta().x();
        ymax += delta;
        ymin += delta;
        if (ymin < minYValue()) {
            ymax -= delta;
            ymin = minYValue();
        }
        if (ymax > maxYValue()) {
            ymin -= delta;
            ymax = maxYValue();
        }
    } else {
        delta = -(ymax - ymin) * 0.001 * e->angleDelta().y();
        ymax += delta;
        ymin -= delta;
        if (ymin < minYValue()) {
            ymin = minYValue();
        }
        if (ymax > maxYValue()) {
            ymax = maxYValue();
        }
    }

    m_xLeft = xmin;
    m_xRight = xmax;
    m_yBottom = ymin;
    m_yTop = ymax;
    setAxisScale(QwtPlot::xBottom, m_xLeft, m_xRight);
    setAxisScale(QwtPlot::yLeft, m_yBottom, m_yTop);
    replot();
}

void GraphBase::mouseDoubleClickEvent(QMouseEvent *e)
{
    if ( e->button() == Qt::LeftButton ) {
        setAxisScale(QwtPlot::xBottom, minXValue(), maxXValue());
        setAxisAutoScale(QwtPlot::yLeft, true);
        replot();
    }
}

void GraphBase::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_1 && event->modifiers() == Qt::ControlModifier) {
        QwtText text;
        QPointF pos = m_picker->position();
        text.setText(QString::asprintf("Aмп.: %.3f В\r\n T: %.6f с", pos.y(), pos.x()));
        text.setColor(Qt::black);
        text.setFont(QFont("Consolas", 18, QFont::Normal));
        m_markerValue->setLabel(text);
        m_markerValue->setValue(pos);
        m_markerValue->setVisible(!m_markerValue->isVisible());
        replot();
    }
}

qreal GraphBase::minXValue() const
{
    return m_curve->minXValue();
}

qreal GraphBase::maxXValue() const
{
    return m_curve->maxXValue();
}

qreal GraphBase::minYValue() const
{
    return m_curve->minYValue();
}

qreal GraphBase::maxYValue() const
{
    return m_curve->maxYValue();
}

void GraphBase::updateXValues(const QVector<qreal> &xValues)
{
    setXValues(xValues);
}

void GraphBase::updateYValues(const QVector<qreal> &yValues)
{
    setYValues(yValues);
}

void GraphBase::updateValues(const QVector<QPointF> &values)
{
    setValues(values);
}

void GraphBase::pickerSelected(const QVector<QPointF> &pa)
{
    Q_UNUSED(pa);
    m_zoomZone->setVisible(false);
    m_markerLeft->setVisible(false);
    m_markerRight->setVisible(false);
    m_xLeft = m_markerLeft->value().x();
    if (m_xLeft < minXValue()) {
        m_xLeft = minXValue();
    }
    m_xRight = m_markerRight->value().x();
    if (m_xRight > maxXValue()) {
        m_xRight = maxXValue();
    }
    setAxisScale(QwtPlot::xBottom, m_xLeft, m_xRight);
    replot();
}

void GraphBase::pickerAppended(const QPointF &pos)
{
    m_markerLeft->setValue(pos);
    m_markerRight->setValue(pos);
    m_markerLeft->setVisible(true);
    m_markerRight->setVisible(true);
    replot();
}

void GraphBase::pickerMoved(const QPointF &pos)
{
    m_zoomZone->setVisible(true);

    QPointF posLeft = m_markerLeft->value();
    QPointF posRight = m_markerRight->value();

    if (pos.x() < m_markerLeft->value().x()) {
        posLeft = pos;
    } else if (pos.x() > m_markerRight->value().x()) {
        posRight = pos;
    } else if (fabs(pos.x() - m_markerLeft->value().x())
               < fabs(pos.x() - m_markerRight->value().x())) {
        posLeft = pos;
    } else {
        posRight = pos;
    }

    if (posLeft.x() < minXValue()) {
        posLeft.setX(minXValue());
    }

    if (posLeft.x() > maxXValue()) {
        posLeft.setX(maxXValue());
    }

    m_markerLeft->setValue(posLeft);
    m_markerRight->setValue(posRight);

    m_zoomZone->setInterval(posLeft.x(), posRight.x());
    replot();
}
