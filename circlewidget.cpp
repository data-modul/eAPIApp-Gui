#include "circlewidget.h"

#include <QPainter>

#include <stdlib.h>

CircleWidget::CircleWidget(QWidget *parent)
    : QWidget(parent)
{
    floatBased = false;
    antialiased = false;
    frameNo = 0;

    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CircleWidget::setFloatBased(bool floatBased)
{
    this->floatBased = floatBased;
    update();
}

void CircleWidget::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}

QSize CircleWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CircleWidget::sizeHint() const
{
    return QSize(180, 180);
}

void CircleWidget::nextAnimationFrame()
{
    // ++frameNo;
    update();
}
void CircleWidget::setDiameter(int d)
{
    diameter = d;

}

void CircleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, antialiased);
    painter.translate(width() / 2, height() / 2);

    //  for (int diameter = 0; diameter < 256; diameter += 9) {

  //  int alpha = 200;// - (delta * delta) / 4 - diameter;

        //painter.setPen(QPen(QColor(0, diameter / 2, 127, alpha), 3));
        painter.setPen(Qt::NoPen);
        QRadialGradient gradient(QPointF(0, 0), 50);
        gradient.setColorAt(0, Qt::blue);
        gradient.setColorAt(1, Qt::red);
        painter.setBrush(gradient);

     // painter.drawEllipse(QRect(-diameter / 2, -diameter / 2, diameter, diameter));

        painter.drawRoundRect(QRect(-25,0, 50, -diameter));
        painter.setPen(QPen(QColor(0, diameter / 2, 127, 255), 3));

        char temp[30];
        sprintf(temp,"%d °C",diameter);
        painter.drawText(-15,20,temp);

    // }
}
