#ifndef MYSCALEDRAW_H
#define MYSCALEDRAW_H

#include <qwt_scale_draw.h>

class MyScaleDraw : public QwtScaleDraw
{
public:
    MyScaleDraw(const QString &format = "%.3f");
    virtual ~MyScaleDraw() {}

    void setFormat(const QString &format);

protected:
    virtual QwtText label(double value) const;

private:
    QString m_format;
};

#endif // MYSCALEDRAW_H
