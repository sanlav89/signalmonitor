#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QTimer>

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);
    void loadData(const QString &fileName);

    static const int SignalLen = 128;

private:
    QByteArray m_data;
    QTimer *m_timer;
    QVector<qreal> m_yValues;

    void parsePortion();

private slots:
    void onTimeout();

signals:
    void yValuesChanged(const QVector<qreal> &);



};

#endif // DATASOURCE_H
