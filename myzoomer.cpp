#include "myzoomer.h"
#include <qwt_plot.h>
#include <qwt_scale_div.h>

MyZoomer::MyZoomer(
        QWidget *canvas,
        bool doReplot
        ) :
    QwtPlotZoomer(canvas, doReplot)
{
}

void MyZoomer::rescale()
{
    QwtPlot *plt = plot();
    if ( !plt ) {
        return;
    }

    const QRectF &rect = zoomStack()[zoomRectIndex()];

    if ( rect != scaleRect() ) {
        const bool doReplot = plt->autoReplot();
        plt->setAutoReplot( false );

        double xmin = plt->axisScaleDiv(QwtPlot::xBottom).lowerBound();
        double xmax = plt->axisScaleDiv(QwtPlot::xBottom).upperBound();

        double x1 = rect.left();
        double x2 = rect.right();
        if (x1 < xmin) {
            x1 = xmin;
        }
        if (x2 > xmax) {
            x2 = xmax;
        }
        if ( !plt->axisScaleDiv( xAxis() ).isIncreasing() ) {
            qSwap( x1, x2 );
        }

        plt->setAxisScale( xAxis(), x1, x2 );

        double y1 = rect.top();
        double y2 = rect.bottom();
        if ( !plt->axisScaleDiv( yAxis() ).isIncreasing() ) {
            qSwap( y1, y2 );
        }

        plt->setAxisScale( yAxis(), y1, y2 );

        plt->setAutoReplot( doReplot );

        plt->replot();
    }

}
