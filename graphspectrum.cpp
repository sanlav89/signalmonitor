#include "graphspectrum.h"
#include "fftengine.h"

GraphSpectrum::GraphSpectrum(QWidget *parent)
    : GraphBase(parent)
{
    QwtText axisTitle = QwtText("Амплитуда [дБ]");
    QFont axisTitleFont = QFont("Helvetica", 12);
    axisTitle.setFont(axisTitleFont);
    setAxisTitle(QwtPlot::yLeft, axisTitle);
    axisTitle.setText("Частота [кГц]");
    setAxisTitle(QwtPlot::xBottom, axisTitle);
    setAxisScaleDraw(QwtPlot::yLeft, new MyScaleDraw());
    setAxisScaleDraw(QwtPlot::xBottom, new MyScaleDraw("%.3f"));

    m_curve->setPen(QPen(Qt::darkRed));
}

void GraphSpectrum::setYValues(const QVector<qreal> &yValues)
{
    if (yValues.size() != m_xValues.size()) {
        m_xValues = QVector<qreal>(yValues.size());
        qreal F = m_fs / yValues.size();
        for (int i = 0; i < m_xValues.size(); i++) {
            m_xValues[i] = i * F * 0.001;
        }
    }
    m_yValues = yValues;
    FftEngine::spectrumRealDb(m_yValues.data(), m_yValues.size());
    m_curve->setSamples(m_xValues.data(), m_yValues.data(), yValues.size() / 2);
    replot();
}
