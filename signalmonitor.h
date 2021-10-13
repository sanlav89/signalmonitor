#ifndef SIGNALMONITOR_H
#define SIGNALMONITOR_H

#include <QWidget>
#include "graphbase.h"

class SignalMonitor : public QWidget
{
    Q_OBJECT

public:
    SignalMonitor(QWidget *parent = nullptr);
    ~SignalMonitor();

    GraphBase *m_graph;

};
#endif // SIGNALMONITOR_H
