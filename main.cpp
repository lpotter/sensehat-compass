#include <QCoreApplication>
#include "sensehatcompass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SensehatCompass compass;

    return a.exec();
}
