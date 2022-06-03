#include "ScreensaverMatrix.h"
#include <time.h>

ScreensaverMatrix::ScreensaverMatrix(QWidget *parent) : QMainWindow(parent)
{
    srand(time(NULL));//��������� ��������������� ����� �� ������ �������
    ui.setupUi(this);
    connect(&timer, &QTimer::timeout, this, &ScreensaverMatrix::updateScreen);
    timer.start(150);
    for (int i = 0; i < countColumns; i++)
    {
        sizeFont[i] = rand() % 8 + 5;//����� �� 5 �� 12
        startPosition[i] = rand() % sizeScreen.height();
        color[i] = rand() % countColors;
        brakeColumn[i] = rand() % 81 + 20;//[80; 100]
        for (int j = 0; j < countSymbols; j++)
        {
            symbols[i][j] = randomSymbol();
        }   
    }
    setCursor(Qt::BlankCursor);//��� ������ ��������� :)
}

void ScreensaverMatrix::updateScreen()
{
    repaint();
}

QChar ScreensaverMatrix::randomSymbol()
{
    return chars[qrand() % chars.length()];
}

void ScreensaverMatrix::paintEvent(QPaintEvent*)
{
    //���������� �����������
    //��� ������ ������� ������, ��� �����
    int startX = -deltaX;
    int stepAndSizeSymbol;
    //���������
    QPainter p;
    p.begin(this);
    p.setBrush(QBrush(Qt::black));
    p.fillRect(sizeScreen, p.brush());
    for (int i = 0; i < countColumns; i++)
    {
        startX += deltaX;
        stepAndSizeSymbol = sizeFont[i] + 4;
        p.setFont(QFont("Times", sizeFont[i], QFont::Bold));
        for (int j = 0; j < brakeColumn[i] && j < countSymbols; j++)
        {
            p.setPen(QPen(QColor(sampleColor[color[i]].red() * j / countSymbols, sampleColor[color[i]].green() * j / countSymbols, sampleColor[color[i]].blue() * j / countSymbols)));
            p.drawText(startX, startPosition[i] + j * stepAndSizeSymbol, stepAndSizeSymbol, stepAndSizeSymbol, Qt::AlignCenter, QString(symbols[i][j]));
        }
        //���������� ��������� ������� �������
        if (startPosition[i] < sizeScreen.height() && brakeColumn[i] > 0)
        {
            startPosition[i] += stepAndSizeSymbol;
            brakeColumn[i]--;
        }
        else
        {
            sizeFont[i] = rand() % 8 + 5;
            startPosition[i] = -(sizeFont[i] + 4) * countSymbols;
            color[i] = rand() % countColors;
            brakeColumn[i] = rand() % 81 + 20;//[80; 100]
        }
        //����� �������� � �������
        for (int j = 0; j < countSymbols - 1; j++)
            symbols[i][j] = symbols[i][j + 1];
        symbols[i][countSymbols - 1] = randomSymbol();
    }
    p.end();
}
