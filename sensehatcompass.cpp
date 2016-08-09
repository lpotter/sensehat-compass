#include <QCoreApplication>
#include <QLoggingCategory>
#include <QtGui/QPainter>
#include <unistd.h>
#include <QCompass>

#include "sensehatcompass.h"
#include "qsensehatfb.h"
#define LED_LOOP = [4, 5, 6, 7, 15, 23, 31, 39, 47, 55, 63, 62, 61, 60, 59, 58, 57, 56, 48, 40, 32, 24, 16, 8, 0, 1, 2, 3]
//#define LED_DEGREE_RATIO = sizeof
SensehatCompass::SensehatCompass(QObject *parent) : QObject(parent)
{
    ledLoop = {4, 5, 6, 7, 15, 23, 31, 39, 47, 55, 63, 62, 61, 60, 59, 58, 57, 56, 48, 40, 32, 24, 16, 8, 0, 1, 2, 3};

    ledDegreeRatio = ledLoop.size() / 360.0;

    compass = new QCompass(this);
    if (!compass->connectToBackend())
            qWarning() <<  "Could not connect to compass" << compass->identifier();

    compass->setDataRate(50);

    connect(compass,SIGNAL(readingChanged()),this,SLOT(compassChanged()));

    if (!fb.isValid()) {
        qDebug("Framebuffer not valid = %d", fb.isValid());
        return;
    }

    fb.setLowLight(true);
    compass->start();
}

void SensehatCompass::compassChanged()
{
  //  qreal level = compass->reading()->calibrationLevel();
    qreal direction = compass->reading()->azimuth();
    qDebug() << Q_FUNC_INFO << direction;
    int directionInverted = 360 - direction;
    int index = int(ledDegreeRatio * directionInverted);
    int offset = ledLoop[index];
    setPixel(QPoint(offset / 8 , offset % 8));
}

void SensehatCompass::setPixel(QPoint point)
{
    Qt::GlobalColor col = Qt::red;
    QPainter p(fb.paintDevice());
    p.fillRect(QRect(QPoint(), fb.size()), Qt::black);
    p.setPen(col);
    p.drawPoint(point);
}

