#include <QCoreApplication>
#include <QLoggingCategory>
#include <QtGui/QPainter>
#include <unistd.h>

#include "sensehatcompass.h"
#include "qsensehatfb.h"

SensehatCompass::SensehatCompass(QObject *parent) : QObject(parent)
{

    QSenseHatFb fb;
    qDebug("Framebuffer valid = %d", fb.isValid());
    if (!fb.isValid())
        return;

    fb.setLowLight(true);

    QPainter p(fb.paintDevice());
    int x = 7, dx = -1;
    Qt::GlobalColor col = Qt::white;
    for (int i = 0; i < 200; ++i) {
        p.fillRect(QRect(QPoint(), fb.size()), Qt::black);
        p.setPen(col);
        p.drawEllipse(QPoint(x, 4), 3, 3);
        p.drawLine(QPoint(x, 4), QPoint(x + 3, 7));
        x += dx;
        if (x < -4 || x > 10)
            dx *= -1;
        usleep(1000 * 100);
        if (!(i % 8)) {
            col = Qt::GlobalColor(col + 1);
            if (col == Qt::transparent)
                col = Qt::white;
        }
    }

    p.fillRect(QRect(QPoint(), fb.size()), Qt::black);
}

