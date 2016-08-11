//Copyright 2015- Raspberry Pi Foundation

//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:

//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.

//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.

//    * Neither the name of the copyright holder nor the
//      names of its contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.

//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//POSSIBILITY OF SUCH DAMAGE.

//* Copyright (C) 2016 Canonical Ltd


#include <QCoreApplication>
#include <QLoggingCategory>
#include <QtGui/QPainter>
#include <unistd.h>
#include <QCompass>

#include "sensehatcompass.h"
#include "qsensehatfb.h"

// parts from compass.py example from python-sense-hat

SensehatCompass::SensehatCompass(QObject *parent)
    : QObject(parent)
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
//    qDebug() << Q_FUNC_INFO << direction;
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

