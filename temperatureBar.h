#ifndef TEMPERATUREBAR_H
#define TEMPERATUREBAR_H


#include <QWidget>

class TemperatureBar : public QWidget
{
    Q_OBJECT

public:
    TemperatureBar(QWidget *parent = 0);

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
    int diameter;
};

#endif // TEMPERATUREBAR_H
