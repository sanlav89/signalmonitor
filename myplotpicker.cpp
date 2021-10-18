#include "myplotpicker.h"

MyPlotPicker::MyPlotPicker(QWidget *canvas) : QwtPlotPicker(canvas)
{
}

QPointF MyPlotPicker::position()
{
    return invTransform(trackerPosition());
}

QwtText MyPlotPicker::trackerTextF(const QPointF &pos) const
{
    QwtText text;
    text.setText(QString::asprintf("%.3f\r\n%.3f", pos.y(), pos.x()));
    return text;
}
