#include "ScreensaverMatrix.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreensaverMatrix w;
    w.showFullScreen();
    return a.exec();
}
