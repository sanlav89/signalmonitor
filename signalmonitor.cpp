#include "signalmonitor.h"
#include <QGridLayout>

SignalMonitor::SignalMonitor(QWidget *parent)
    : QWidget(parent)
{
    m_graph = new GraphBase(this);
    m_spectrum = new GraphSpectrum(this);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_graph, 0, 0, 1, 1);
    mainLayout->addWidget(m_spectrum, 1, 0, 1, 1);
    setLayout(mainLayout);

    int n = 16384;
    QVector<QPointF> nullData(n);
    QVector<qreal> testData(n);
    for (int i = 0; i < n; i++) {
        testData[i] = rand();
        nullData[i] = QPointF(i, 0);
    }

    m_graph->setValues(nullData);
    m_spectrum->setValues(nullData);

    m_graph->setYValues(testData);
    m_spectrum->setYValues(testData);
}

SignalMonitor::~SignalMonitor()
{
}

