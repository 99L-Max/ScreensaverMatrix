#pragma once

#include <QtWidgets>
#include <QPainter>
#include "ui_ScreensaverMatrix.h"
#include "qdesktopwidget.h"

class ScreensaverMatrix : public QMainWindow
{
    Q_OBJECT

public:
    ScreensaverMatrix(QWidget *parent = Q_NULLPTR);

private:
    Ui::ScreensaverMatrixClass ui;
    QRect sizeScreen = QApplication::desktop()->screenGeometry();//Размеры экрана
    QTimer timer;
    //Я не понимаю, почему ему не static не нравится
    static const unsigned int countColumns = 200;
    static const unsigned int countSymbols = 25;
    const int deltaX = sizeScreen.width() / countColumns;
    char symbols[countColumns][countSymbols];
    int startPosition[countColumns];
    int sizeFont[countColumns];

    void updateScreen();
    char randomSymbol();

protected:
    void paintEvent(QPaintEvent*) override;
};
