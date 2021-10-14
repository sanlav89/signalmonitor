#ifndef SIGNALMONITOR_H
#define SIGNALMONITOR_H

#include <QWidget>
#include <QTreeWidget>
#include <QRadioButton>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QTimer>
#include "graphspectrum.h"
#include "datasource.h"
#include "sortedtreewidgetitem.h"

class SignalMonitor : public QWidget
{
    Q_OBJECT

public:
    SignalMonitor(QWidget *parent = nullptr);
    ~SignalMonitor();

    bool isStarted() const;
    int selectedId() const;
    int selectedChannel() const;

private:

    static const int NUMBER_OF_CHANNELS = 4;

    GraphBase *m_graph;
    GraphSpectrum *m_spectrum;
    QTreeWidget *m_modulesTw;
    QRadioButton *m_channelRaB[NUMBER_OF_CHANNELS];
    DataSource *m_dataSource;
    QPushButton *m_startStopBtn;

    bool m_isStarted;
    QMap<int, SortedTreeWidgetItem *> m_itemsMap;

    QTimer *m_testTimer;

public slots:
    void addStatisticItem(int id, int cycle);
    void updateYValues(const QVector<qreal> &yValues);

private slots:
    void onStartStopBtn();
    void onTimeout();

};
#endif // SIGNALMONITOR_H
