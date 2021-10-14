#include "signalmonitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SignalMonitor w;
    w.show();

    w.addStatisticItem(9, 10);
    w.addStatisticItem(1, 10);
    w.addStatisticItem(97, 10);
    w.addStatisticItem(90, 10);
    w.addStatisticItem(11, 10);
    w.addStatisticItem(12, 10);
    w.addStatisticItem(9, 10);
    w.addStatisticItem(9, 10);
    w.addStatisticItem(10, 10);

    return a.exec();
}
