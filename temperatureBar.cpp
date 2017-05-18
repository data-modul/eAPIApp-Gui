#include "temperatureBar.h"

#include <QPainter>

#include <stdlib.h>

TemperatureBar::TemperatureBar(QWidget *parent)
    : QWidget(parent)
{
    floatBased = false;
    antialiased = false;
diameter = 0;
    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void TemperatureBar::setFloatBased(bool floatBased)
{
    this->floatBased = floatBased;
    update();
}

void TemperatureBar::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}

QSize TemperatureBar::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize TemperatureBar::sizeHint() const
{
    return QSize(180, 180);
}

void TemperatureBar::nextAnimationFrame()
{
    update();
}
void TemperatureBar::setDiameter(int d)
{
    diameter = d;
}
void TemperatureBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, antialiased);
    painter.translate(width() / 2, height() / 2);

    QPen pen;
    QFont font;
    font.setPixelSize(12);

    int hscale = (height() - 40) / 100;
    int wscale = width() / 100;
    if(wscale > 1)
        wscale = 1;

    int lowOffset = 20;
    int leftoffset = 10;
    int leftTickOffest = leftoffset + 5;
    int widthMaintick = 6;
    int widthMinortick =  widthMaintick / 2;

    painter.setPen(Qt::NoPen);
    if (diameter < 10 )
        painter.setBrush(Qt::blue);
    else if (diameter < 50 )
        painter.setBrush(Qt::darkMagenta);
    else
        painter.setBrush(Qt::red);

    painter.drawRect(QRect(-leftoffset*wscale,50*hscale  , 20*wscale, -(diameter*hscale)));

        pen.setWidthF(0.5);
        pen.setColor(Qt::gray);
        painter.setPen(pen);
        painter.setFont(font);

        for (int i =0 ; i <= 100 ; i++)
        {
            if (i % 10 == 0)
            {
                painter.drawLine(-leftTickOffest*wscale, (50 - i )*hscale , -(leftTickOffest + widthMaintick)*wscale, (50 - i )*hscale );
                QRect rect = QRect(-45*wscale, (50 - i )*hscale - (lowOffset/2), 20, 20);
                painter.drawText(rect,Qt::AlignRight , QString::number(i));
            }
            else if (i % 2 == 0)
            {
                painter.drawLine(-leftTickOffest*wscale, (50 - i )*hscale , -(leftTickOffest + widthMinortick)*wscale, (50 - i )*hscale );
            }
        }

    char temp[30];
    sprintf(temp,"%d °C",diameter);
    font.setPixelSize(14);
    painter.setFont(font);
    painter.drawText(-leftTickOffest*wscale,50*hscale +15 ,temp);
}
