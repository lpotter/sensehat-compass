#ifndef MATRIXCOMPASS_H
#define MATRIXCOMPASS_H

#include <QObject>
#include <QCompass>
#include "qsensehatfb.h"

class SensehatCompass : public QObject
{
    Q_OBJECT
public:
    explicit SensehatCompass(QObject *parent = 0);

signals:

public slots:
    void compassChanged();
private:
    QCompass *compass;
    QSenseHatFb fb;
    void setPixel(QPoint point);
    QVector<int> ledLoop;
    qreal ledDegreeRatio;

};

#endif // MATRIXCOMPASS_H
