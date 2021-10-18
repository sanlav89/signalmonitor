#ifndef SIGNALMONITOR_H
#define SIGNALMONITOR_H

#include <QWidget>
#include <QTreeWidget>
#include <QRadioButton>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QTimer>
#include <QSharedMemory>
#include "graphspectrum.h"
#include "sortedtreewidgetitem.h"
#include "statistic.h"

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
//    DataSource *m_dataSource;
    QPushButton *m_startStopBtn;

    bool m_isStarted;
    QMap<int, SortedTreeWidgetItem *> m_itemsMap;

    QTimer *m_testTimer;
    QSharedMemory m_shmem;
    statistic_t *statistic;
    QVector<qreal> m_yValues;

    bool initSharedMemory();
    void detach();

public slots:
    void addStatisticItem(int id, int cycle);
    void updateYValues(const QVector<qreal> &yValues);

private slots:
    void onStartStopBtn();
    void onTimeout();

};
#endif // SIGNALMONITOR_H
