#include "myscaledraw.h"

MyScaleDraw::MyScaleDraw(const QString &format) :
    QwtScaleDraw(),
    m_format(format)
{
}

void MyScaleDraw::setFormat(const QString &format)
{
    m_format = format;
}

QwtText MyScaleDraw::label(double value) const
{
    QString result = QString::asprintf(m_format.toStdString().c_str(), value);
    return result;
}
