#ifndef MYPLOTPICKER_H
#define MYPLOTPICKER_H

#include <qwt_plot_picker.h>

class MyPlotPicker : public QwtPlotPicker
{
    Q_OBJECT
public:
    explicit MyPlotPicker(QWidget *canvas);
    QPointF position();

private:
    QwtText trackerTextF(const QPointF &pos) const;
};

#endif // MYPLOTPICKER_H
