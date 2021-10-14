#ifndef SIGNALMONITOR_H
#define SIGNALMONITOR_H

#include <QWidget>
#include "graphspectrum.h"
#include "datasource.h"

class SignalMonitor : public QWidget
{
    Q_OBJECT

public:
    SignalMonitor(QWidget *parent = nullptr);
    ~SignalMonitor();

    GraphBase *m_graph;
    GraphSpectrum *m_spectrum;
    DataSource *m_dataSource;

};
#endif // SIGNALMONITOR_H
