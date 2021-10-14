#include "datasource.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

DataSource::DataSource(QObject *parent)
    : QObject(parent)
{
    m_yValues.reserve(SignalLen);
    m_yValues = QVector<qreal>(SignalLen);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &DataSource::onTimeout);
}

void DataSource::loadData(const QString &fileName)
{
//    QFile fin("id_09.dat.save");
    QFile fin(fileName);
    QDataStream ds(&fin);
    if (fin.open(QIODevice::ReadOnly)) {
        m_data.reserve(fin.size());
        m_data = fin.readAll();
//        quint8 tmp;
//        for (int i = 0; i < 100; i++) {
//            ds >> tmp;
//            qDebug("0x%02X", tmp);
//        }
        fin.close();
        m_timer->start(1000);
//        parsePortion();
    } else {
        qDebug() << Q_FUNC_INFO << "Can't open() file" << fileName;
    }
}

void DataSource::parsePortion()
{
    qDebug() << Q_FUNC_INFO << m_data.size();
    static int packetNum = 0;
    static int currentPos = 0;
    int ETH_HDR_LEN = 14;
    int IP_HDR_LEN = 20;
    int UDP_HDR_LEN = 8;
    int ADC_HDR_LEN = 16;
    int PAYLOAD_LEN = packetNum % 19 == 18 ? 288 : 1408;
    int UNDEFINED_PRE_SIZE = 198 + ETH_HDR_LEN + IP_HDR_LEN + UDP_HDR_LEN + ADC_HDR_LEN;

    int i = 0;
    while (i < SignalLen) {
        PAYLOAD_LEN = packetNum % 19 == 18 ? 288 : 1408;
//        PAYLOAD_LEN -= UNDEFINED_PRE_SIZE;
        int udpPacketLen = ETH_HDR_LEN + IP_HDR_LEN + UDP_HDR_LEN + ADC_HDR_LEN + PAYLOAD_LEN;
        int current = currentPos + ETH_HDR_LEN + IP_HDR_LEN + UDP_HDR_LEN + ADC_HDR_LEN + UNDEFINED_PRE_SIZE;
        int end = current + PAYLOAD_LEN - UNDEFINED_PRE_SIZE;
        int offset = 0;
        qint16 *data = (qint16 *)&m_data.data()[current];
//        qDebug() << i << current << end << packetNum << PAYLOAD_LEN
//                    ;
//                 << quint8(m_data.data()[0])
//                 << quint8(m_data.data()[currentPos])
//                 << quint8(m_data.data()[currentPos + 200])
//                 << quint8(m_data.data()[currentPos + ETH_HDR_LEN + IP_HDR_LEN + UDP_HDR_LEN + 198])
//                 << quint8(m_data.data()[currentPos + ETH_HDR_LEN + IP_HDR_LEN + UDP_HDR_LEN + 197]);
        qDebug() << m_data.mid(currentPos + UNDEFINED_PRE_SIZE, 6).toHex() << udpPacketLen << end - current;
//        for (int i = 0; i < 20; i++) {
//        qDebug("0x%02X, 0x%02X, 0x%02X, 0x%02X",
//               quint8(m_data.at(0 + i * 4)), quint8(m_data.data()[1 + i * 4]),
//                quint8(m_data.data()[2 + i * 4]), quint8(m_data.data()[3 + i * 4]));
//        }
        while (current < end && i < SignalLen) {
//            qDebug() << "before";
            m_yValues[i++] = qreal(data[offset]);
            qDebug() << i << m_yValues[i - 1];
//            qDebug() << "after";
            offset += 4;
            current += sizeof(qint16) * 4;
        }
        packetNum++;
        currentPos += ETH_HDR_LEN + IP_HDR_LEN + UDP_HDR_LEN + ADC_HDR_LEN + PAYLOAD_LEN;

    }
    qDebug() << Q_FUNC_INFO << "here" << i;
    emit yValuesChanged(m_yValues);
    qDebug() << Q_FUNC_INFO << "here";
    m_timer->stop();
    qDebug() << Q_FUNC_INFO << "here";
}

void DataSource::onTimeout()
{
    parsePortion();
}
