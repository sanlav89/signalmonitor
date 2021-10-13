#include "signalmonitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SignalMonitor w;
    w.show();
    return a.exec();
}
