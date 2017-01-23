#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H


#include <QWidget>

class CircleWidget : public QWidget
{
    Q_OBJECT

public:
    CircleWidget(QWidget *parent = 0);

    void setFloatBased(bool floatBased);
    void setAntialiased(bool antialiased);
    void setDiameter(int d);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:
    void nextAnimationFrame();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    bool floatBased;
    bool antialiased;
    int frameNo;
    int diameter;
};

#endif // CIRCLEWIDGET_H
