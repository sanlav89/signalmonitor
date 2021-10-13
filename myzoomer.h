#ifndef MYZOOMER_H
#define MYZOOMER_H

#include <qwt_plot_zoomer.h>

class MyZoomer : public QwtPlotZoomer
{
    Q_OBJECT
public:
    explicit MyZoomer(QWidget *canvas,
            bool doReplot = true
            );

private:
    void rescale() override;
};

#endif // MYZOOMER_H
