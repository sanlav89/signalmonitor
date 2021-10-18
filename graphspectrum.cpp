#include "graphspectrum.h"
#include "fftengine.h"

GraphSpectrum::GraphSpectrum(QWidget *parent)
    : GraphBase(parent)
{
}

void GraphSpectrum::setYValues(const QVector<qreal> &yValues)
{
    if (yValues.size() > 0 && yValues.size() == m_yValues.size()) {
        m_yValues = yValues;
        FftEngine::spectrumRealDb(m_yValues.data(), m_yValues.size());
        m_curve->setSamples(m_xValues.data(), m_yValues.data(), yValues.size());
        replot();
    }
}
