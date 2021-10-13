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
    text.setText(QString::asprintf("Aмп.: %.3f В\r\n T: %.6f с", pos.y(), pos.x()));
    return text;
}
