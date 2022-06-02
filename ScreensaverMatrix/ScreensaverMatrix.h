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
    static const unsigned int countColumns = 200;//Количество столбиков
    static const unsigned int countSymbols = 25;//Количество символов в столбике
    const int deltaX = sizeScreen.width() / countColumns;//Шаг рисования столбика
    char symbols[countColumns][countSymbols];//Массив символов
    int startPosition[countColumns];//Координата по у рисования столбика
    int sizeFont[countColumns];//Размер шрифта
    //RainbowMatrix
    int color[countColumns];//Цвет столбца
    //Образцы цветов. Через random цвета получаются блёклыми
    static const unsigned int countColors = 9;
    QColor sampleColor[countColors] = {
        QColor(255, 0, 0), QColor(255, 69, 0), QColor(255, 255, 0),
        QColor(0, 255, 0), QColor(0, 255, 255), QColor(0, 0, 255),
        QColor(123, 104, 238), QColor(255, 0, 255), QColor(75, 0, 130)
    };

    void updateScreen();//
    char randomSymbol();//Случайный симбол. Цифра или английская буква строчная или прописная

protected:
    void paintEvent(QPaintEvent*) override;//Рисовние
};
