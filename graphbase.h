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
#include "myscaledraw.h"

class GraphBase : public QwtPlot
{
    Q_OBJECT
public:
    GraphBase(QWidget *parent = nullptr);

    void setGrid(bool xEnabled, bool yEnabled, const QPen &pen);
    void setXLabel(const QString &label);
    void setYLabel(const QString &label);
    virtual void setYValues(const QVector<qreal> &yValues);

protected:
    virtual void wheelEvent(QWheelEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

    qreal m_xLeft;
    qreal m_xRight;
    qreal m_yBottom;
    qreal m_yTop;
    qreal m_fs;
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
    bool m_wasMoved;

    qreal minXValue() const;
    qreal maxXValue() const;
    qreal minYValue() const;
    qreal maxYValue() const;

public slots:
    void updateYValues(const QVector<qreal> &yValues);

private slots:
    void pickerSelected(const QVector<QPointF> &pa);
    void pickerAppended(const QPointF &pos);
    void pickerMoved(const QPointF &pos);


};

#endif // GRAPHBASE_H
