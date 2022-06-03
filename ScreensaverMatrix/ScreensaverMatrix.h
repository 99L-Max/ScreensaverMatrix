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
    QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    //Я не понимаю, почему ему не static не нравится
    static const unsigned int countColumns = 180;//Количество столбиков
    static const unsigned int countSymbols = 25;//Количество символов в столбике
    const int deltaX = sizeScreen.width() / countColumns;//Шаг рисования столбика
    QChar symbols[countColumns][countSymbols];//Массив символов
    int startPosition[countColumns];//Координата по у рисования столбика
    int sizeFont[countColumns];//Размер шрифта
    int color[countColumns];//Цвет столбца
    //Образцы цветов. Через random цвета получаются блёклыми
    static const unsigned int countColors = 9;
    QColor sampleColor[countColors] = {
        Qt::red, QColor(255, 69, 0), Qt::yellow,
        Qt::green, Qt::cyan, Qt::blue,
        QColor(75, 0, 130), QColor(255, 0, 255), Qt::white
    };
    //Значения для остановки. Вместо того, чтобы считать координату у, после которой
    //нужно не рисовать столбик, введём счётчики для индекса символа.
    //Начальное значение превосходит количество символов в столбике. 
    //После каждый итерации счётчик уменьшается на 1 и его значение приближается к числу символов в столбике, 
    //после чего цикл будет на каждой итераии рисовать сначала все символы,
    //затем на 1 меньше, затем на 2 меньше и т. д.
    int brakeColumn[countColumns];

    void updateScreen();//
    QChar randomSymbol();//Случайный симбол. Цифра или английская буква строчная или прописная

protected:
    void paintEvent(QPaintEvent*) override;//Рисовние
};
