#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_textlabel.h>
#include <qwt_plot_zoneitem.h>
#include <qwt_plot_grid.h>

#include "myzoomer.h"
#include "myplotpicker.h"

class GraphBase : public QwtPlot
{
    Q_OBJECT
public:
    GraphBase(QWidget *parent = nullptr);

    void setTitle(const QString &title);
    void setGrid(bool xEnabled, bool yEnabled, const QPen &pen);
    void setXLabel(const QString &label);
    void setYLabel(const QString &label);
    void setXValues(const QVector<qreal> &xValues);
    void setYValues(const QVector<qreal> &yValues);
    void setValues(const QVector<QPointF> &values);

protected:
    virtual void wheelEvent(QWheelEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    qreal m_xLeft;
    qreal m_xRight;
    qreal m_yBottom;
    qreal m_yTop;
    QVector<qreal> m_xValues;
    QVector<qreal> m_yValues;
    QFont m_generalFont;
    QwtPlotGrid *m_grid;
    MyZoomer *m_zoomer;

    QwtPlotCurve *m_curve;
    QwtPlotMarker *m_markerValue;
    QwtPlotMarker *m_markerLeft;
    QwtPlotMarker *m_markerRight;
    QwtPlotZoneItem *m_zoomZone;
    MyPlotPicker *m_picker;

    qreal minXValue() const;
    qreal maxXValue() const;
    qreal minYValue() const;
    qreal maxYValue() const;

public slots:
    void updateXValues(const QVector<qreal> &xValues);
    void updateYValues(const QVector<qreal> &yValues);
    void updateValues(const QVector<QPointF> &values);

private slots:
    void pickerSelected(const QVector<QPointF> &pa);
    void pickerAppended(const QPointF &pos);
    void pickerMoved(const QPointF &pos);


};

#endif // GRAPHBASE_H
