#include "ScreensaverMatrix.h"
#include <time.h>

ScreensaverMatrix::ScreensaverMatrix(QWidget *parent) : QMainWindow(parent)
{
    srand(time(NULL));//Генерация псевдослучайных чисел на основе времени
    ui.setupUi(this);
    connect(&timer, &QTimer::timeout, this, &ScreensaverMatrix::updateScreen);
    timer.start(150);
    for (int i = 0; i < countColumns; i++)
    {
        sizeFont[i] = rand() % 8 + 5;//Шрифт от 5 до 12
        startPosition[i] = rand() % sizeScreen.height();
        color[i] = rand() % countColors;
        for (int j = 0; j < countSymbols; j++)
        {
            symbols[i][j] = randomSymbol();
        }   
    }
    setCursor(Qt::BlankCursor);//Для лучшей атмосферы :)
}

void ScreensaverMatrix::updateScreen()
{
    repaint();
}

char ScreensaverMatrix::randomSymbol()
{
    //Не прошло и месяца, как пригодилось XD
    //Спасибо Тихомирову А. С.
    int alpha = rand() % 62;
    if(alpha < 10)
        return (char)('0' + rand() % 10);
    else if(alpha < 36)
        return (char)('a' + rand() % 26);
    else
        return (char)('A' + rand() % 26);
}

void ScreensaverMatrix::paintEvent(QPaintEvent*)
{
    //Переменные оптимизации
    //Нет смысла считать больше, чем нужно
    int startX = -deltaX;
    int endX = 0;
    //Рисование
    QPainter p;
    p.begin(this);
    p.setBrush(QBrush(Qt::black));
    p.fillRect(sizeScreen, p.brush());
    for (int i = 0; i < countColumns; i++)
    {
        startX += deltaX;
        endX += deltaX;
        p.setFont(QFont("Times", sizeFont[i], QFont::Bold));
        for (int j = 0; j < countSymbols; j++)
        {
            //Одноцветный вариант без массива color
            //p.setPen(QPen(QColor(0, j * 10, 0)));

            //RainbowMatrix
            p.setPen(QPen(QColor(sampleColor[color[i]].red() * j / countSymbols, sampleColor[color[i]].green() * j / countSymbols, sampleColor[color[i]].blue() * j / countSymbols)));
            p.drawText(startX, startPosition[i] + j * sizeFont[i], endX, startPosition[i] + (j + 1) * sizeFont[i], Qt::AlignCenter, QString(symbols[i][j]));
        }
        //Обновление начальной позиции столбца
        if (startPosition[i] < sizeScreen.height())
        {
            startPosition[i] += sizeFont[i];
        }
        else
        {
            sizeFont[i] = rand() % 8 + 5;
            startPosition[i] = -sizeFont[i] * countSymbols;
            color[i] = rand() % countColors;
        }
        //Сдвиг символов в массиве
        for (int j = 0; j < countSymbols - 1; j++)
            symbols[i][j] = symbols[i][j + 1];
        symbols[i][countSymbols - 1] = randomSymbol();
    }
    p.end();
}
