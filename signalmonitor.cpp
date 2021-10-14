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

    int n = DataSource::SignalLen;
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


    m_dataSource = new DataSource(this);
    m_dataSource->loadData("id_09.dat.save");

    connect(m_dataSource, &DataSource::yValuesChanged, m_graph, &GraphBase::updateYValues);
    connect(m_dataSource, &DataSource::yValuesChanged, m_spectrum, &GraphSpectrum::updateYValues);

}

SignalMonitor::~SignalMonitor()
{
}

