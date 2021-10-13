#include "graphbase.h"

GraphBase::GraphBase(QWidget *parent)
    : QwtPlot(parent)
{

}

void GraphBase::setTitle(const QString &title)
{

}

void GraphBase::setGrid(bool xEnabled, bool yEnabled, const QPen &pen)
{

}

void GraphBase::setXLabel(const QString &label)
{

}

void GraphBase::setYLabel(const QString &label)
{

}

void GraphBase::setXValues(const QVector<qreal> &xValues)
{

}

void GraphBase::setYValues(const QVector<qreal> &yValues)
{

}

void GraphBase::setValues(const QVector<QPointF> &values)
{

}

void GraphBase::wheelEvent(QWheelEvent *e)
{

}

void GraphBase::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void GraphBase::updateXValues(const QVector<qreal> &xValues)
{

}

void GraphBase::updateYValues(const QVector<qreal> &yValues)
{

}

void GraphBase::updateValues(const QVector<QPointF> &values)
{

}

void GraphBase::pickerSelected(const QVector<QPointF> &pa)
{

}

void GraphBase::pickerAppended(const QPointF &pos)
{

}

void GraphBase::pickerMoved(const QPointF &pos)
{

}
