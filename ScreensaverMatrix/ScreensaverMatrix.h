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
    QRect sizeScreen = QApplication::desktop()->screenGeometry();//������� ������
    QTimer timer;
    //� �� �������, ������ ��� �� static �� ��������
    static const unsigned int countColumns = 200;//���������� ���������
    static const unsigned int countSymbols = 25;//���������� �������� � ��������
    const int deltaX = sizeScreen.width() / countColumns;//��� ��������� ��������
    char symbols[countColumns][countSymbols];//������ ��������
    int startPosition[countColumns];//���������� �� � ��������� ��������
    int sizeFont[countColumns];//������ ������
    //RainbowMatrix
    int color[countColumns];//���� �������
    //������� ������. ����� random ����� ���������� �������
    static const unsigned int countColors = 9;
    QColor sampleColor[countColors] = {
        QColor(255, 0, 0), QColor(255, 69, 0), QColor(255, 255, 0),
        QColor(0, 255, 0), QColor(0, 255, 255), QColor(0, 0, 255),
        QColor(123, 104, 238), QColor(255, 0, 255), QColor(75, 0, 130)
    };

    void updateScreen();//
    char randomSymbol();//��������� ������. ����� ��� ���������� ����� �������� ��� ���������

protected:
    void paintEvent(QPaintEvent*) override;//��������
};
