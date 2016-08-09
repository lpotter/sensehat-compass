#ifndef MATRIXCOMPASS_H
#define MATRIXCOMPASS_H

#include <QObject>

class SensehatCompass : public QObject
{
    Q_OBJECT
public:
    explicit SensehatCompass(QObject *parent = 0);

signals:

public slots:
};

#endif // MATRIXCOMPASS_H
