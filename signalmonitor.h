#ifndef SIGNALMONITOR_H
#define SIGNALMONITOR_H

#include <QWidget>

class SignalMonitor : public QWidget
{
    Q_OBJECT

public:
    SignalMonitor(QWidget *parent = nullptr);
    ~SignalMonitor();
};
#endif // SIGNALMONITOR_H
