#ifndef SIGNALMONITOR_H
#define SIGNALMONITOR_H

#include <QWidget>
#include "graphspectrum.h"

class SignalMonitor : public QWidget
{
    Q_OBJECT

public:
    SignalMonitor(QWidget *parent = nullptr);
    ~SignalMonitor();

    GraphBase *m_graph;
    GraphSpectrum *m_spectrum;

};
#endif // SIGNALMONITOR_H
