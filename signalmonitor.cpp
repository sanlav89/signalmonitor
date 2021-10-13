#include "signalmonitor.h"
#include <QGridLayout>

SignalMonitor::SignalMonitor(QWidget *parent)
    : QWidget(parent)
{
    m_graph = new GraphBase(this);
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_graph);
    setLayout(mainLayout);

    int n = 100;
    QVector<QPointF> testData(n);
    for (int i = 0; i < n; i++) {
        testData[i] = QPointF(i, rand());
    }
    m_graph->setValues(testData);
}

SignalMonitor::~SignalMonitor()
{
}

