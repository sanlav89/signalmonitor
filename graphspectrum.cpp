#include "graphspectrum.h"
#include "fftengine.h"

GraphSpectrum::GraphSpectrum(QWidget *parent)
    : GraphBase(parent)
{
}

void GraphSpectrum::setYValues(const QVector<qreal> &yValues)
{
    if (yValues.size() > 0 && yValues.size() == m_yValues.size()) {
        qDebug() << Q_FUNC_INFO << "here";
        m_yValues = yValues;
        qDebug() << Q_FUNC_INFO << "here";
        FftEngine::spectrumRealDb(m_yValues.data(), m_yValues.size());
        qDebug() << Q_FUNC_INFO << "here";
        m_curve->setSamples(m_xValues.data(), m_yValues.data(), yValues.size());
        qDebug() << Q_FUNC_INFO << "here";
        replot();
        qDebug() << Q_FUNC_INFO << "here";
    }
}
