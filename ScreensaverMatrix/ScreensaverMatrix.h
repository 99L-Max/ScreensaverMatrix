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
    QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    //� �� �������, ������ ��� �� static �� ��������
    static const unsigned int countColumns = 180;//���������� ���������
    static const unsigned int countSymbols = 25;//���������� �������� � ��������
    const int deltaX = sizeScreen.width() / countColumns;//��� ��������� ��������
    QChar symbols[countColumns][countSymbols];//������ ��������
    int startPosition[countColumns];//���������� �� � ��������� ��������
    int sizeFont[countColumns];//������ ������
    int color[countColumns];//���� �������
    //������� ������. ����� random ����� ���������� �������
    static const unsigned int countColors = 9;
    QColor sampleColor[countColors] = {
        Qt::red, QColor(255, 69, 0), Qt::yellow,
        Qt::green, Qt::cyan, Qt::blue,
        QColor(75, 0, 130), QColor(255, 0, 255), Qt::white
    };
    //�������� ��� ���������. ������ ����, ����� ������� ���������� �, ����� �������
    //����� �� �������� �������, ����� �������� ��� ������� �������.
    //��������� �������� ����������� ���������� �������� � ��������. 
    //����� ������ �������� ������� ����������� �� 1 � ��� �������� ������������ � ����� �������� � ��������, 
    //����� ���� ���� ����� �� ������ ������� �������� ������� ��� �������,
    //����� �� 1 ������, ����� �� 2 ������ � �. �.
    int brakeColumn[countColumns];

    void updateScreen();//
    QChar randomSymbol();//��������� ������. ����� ��� ���������� ����� �������� ��� ���������

protected:
    void paintEvent(QPaintEvent*) override;//��������
};
