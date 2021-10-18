#include "signalmonitor.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>

SignalMonitor::SignalMonitor(QWidget *parent)
    : QWidget(parent)
    , m_isStarted(false)
    , m_shmem("SHMEM")
{
    m_graph = new GraphBase(this);
    m_spectrum = new GraphSpectrum(this);
    m_modulesTw = new QTreeWidget(this);
    m_modulesTw->setColumnCount(2);
    m_modulesTw->setHeaderLabels(QStringList() << "ID" << "№ цикла");
    m_modulesTw->header()->resizeSections(QHeaderView::ResizeToContents);
    m_modulesTw->setSortingEnabled(true);
    m_modulesTw->setSelectionMode(QAbstractItemView::SingleSelection);
    m_startStopBtn = new QPushButton("Старт", this);

    QGroupBox *channelsGb = new QGroupBox("Канал", this);
    QHBoxLayout *channelsLayout = new QHBoxLayout(channelsGb);
    for (int i = 0; i < NUMBER_OF_CHANNELS; i++) {
        m_channelRaB[i] = new QRadioButton(QString::asprintf("%d", i + 1), this);
        channelsLayout->addWidget(m_channelRaB[i]);
    }
    m_channelRaB[0]->setChecked(true);

    QGroupBox *modulesGb = new QGroupBox("Статистика", this);
    QVBoxLayout *modulesLayout = new QVBoxLayout(modulesGb);
    modulesLayout->addWidget(m_modulesTw);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_graph, 0, 0, 10, 9);
    mainLayout->addWidget(m_spectrum, 10, 0, 10, 9);
    mainLayout->addWidget(modulesGb, 0, 9, 18, 1);
    mainLayout->addWidget(channelsGb, 18, 9, 1, 1);
    mainLayout->addWidget(m_startStopBtn, 19, 9, 1, 1);
    for (int i = 0; i < 10; i++) {
        mainLayout->setColumnStretch(i, 1);
    }
    setLayout(mainLayout);

    // Тестовые данные
    int n = MAX_SAMPLES;
    QVector<qreal> testData(n);
    for (int i = 0; i < n; i++) {
        testData[i] = rand();
    }
    m_graph->setYValues(testData);
    m_spectrum->setYValues(testData);

    connect(m_startStopBtn, &QPushButton::clicked, this, &SignalMonitor::onStartStopBtn);

    m_testTimer = new QTimer(this);
    m_testTimer->start(500);
    connect(m_testTimer, &QTimer::timeout, this, &SignalMonitor::onTimeout);

    m_yValues.reserve(MAX_SAMPLES);
    m_yValues = QVector<qreal>(MAX_SAMPLES);

    initSharedMemory();

}

SignalMonitor::~SignalMonitor()
{
}

bool SignalMonitor::isStarted() const
{
    return m_isStarted;
}

int SignalMonitor::selectedId() const
{
    if (m_modulesTw->selectedItems().size() > 0) {
        SortedTreeWidgetItem *item = static_cast<SortedTreeWidgetItem *>(m_modulesTw->selectedItems()[0]);
        return m_itemsMap.key(item);
    }
    return 0;
}

int SignalMonitor::selectedChannel() const
{
    for (int i = 0; i < NUMBER_OF_CHANNELS; i++) {
        if (m_channelRaB[i]->isChecked()) {
            return i;
        }
    }
    return 0;
}

bool SignalMonitor::initSharedMemory()
{
    if (m_shmem.isAttached()) {
        detach();
    }

    if (!m_shmem.attach()) {
        qDebug() << Q_FUNC_INFO << "Unable to attach to shared memory segment.";
        return false;
    }

    statistic = static_cast<statistic_t *>(m_shmem.data());

    return true;
}

void SignalMonitor::detach()
{
    if (!m_shmem.detach()) {
        qDebug() << Q_FUNC_INFO << "Unable to detach from shared memory.";
    }
}

void SignalMonitor::addStatisticItem(int id, int cycle)
{
    if (m_itemsMap.contains(id)) {
        m_itemsMap[id]->setText(1, QString::asprintf("%d", cycle));
    } else {
        SortedTreeWidgetItem *item = new SortedTreeWidgetItem;
        item->setText(0, QString::asprintf("%d", id));
        item->setText(1, QString::asprintf("%d", cycle));
        item->setTextAlignment(0, Qt::AlignCenter);
        item->setTextAlignment(1, Qt::AlignCenter);
        m_itemsMap.insert(id, item);
        m_modulesTw->addTopLevelItem(item);
        m_modulesTw->header()->resizeSections(QHeaderView::ResizeToContents);
    }
}

void SignalMonitor::updateYValues(const QVector<qreal> &yValues)
{
    m_graph->setYValues(yValues);
    m_spectrum->setYValues(yValues);
}

void SignalMonitor::onStartStopBtn()
{
    m_isStarted = !m_isStarted;
    m_startStopBtn->setText(m_isStarted ? "Стоп" : "Старт");
}

void SignalMonitor::onTimeout()
{
//    qDebug() << selectedChannel() << selectedId() << isStarted();
    if (m_shmem.isAttached()) {

//        qDebug() << "m_shmem.isAttached()";

        // Список id-шек
        for (int i = 0; i < MAX_MODULES; i++) {
            if (statistic->ids[i].id > 0 && statistic->ids[i].cycles > 0) {
                addStatisticItem(statistic->ids[i].id, statistic->ids[i].cycles);
            }
        }

        m_shmem.lock();

        // Выбранные id и channel
        statistic->id_channel.channel = selectedChannel();
        statistic->id_channel.id = selectedId();

        // Show samples
        for (int i = 0; i < MAX_SAMPLES; i++) {
            m_yValues[i] = statistic->samples[i] >> 4;
        }
        m_shmem.unlock();

        updateYValues(m_yValues);
    }
}

