#ifndef GRAPHSPECTRUM_H
#define GRAPHSPECTRUM_H

#include "graphbase.h"

class GraphSpectrum : public GraphBase
{
    Q_OBJECT
public:
    GraphSpectrum(QWidget *parent = nullptr);
    void setYValues(const QVector<qreal> &yValues) override;
};

#endif // GRAPHSPECTRUM_H
