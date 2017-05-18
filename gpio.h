#ifndef GPIO_H
#define GPIO_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTimer>

class gpio: public QWidget
{
    Q_OBJECT
public:
    gpio(QWidget *parent = 0);

public slots:
    void gpio00clicked(bool checked);
    void gpio01clicked(bool checked);
    void gpio02clicked(bool checked);
    void gpio03clicked(bool checked);
    void gpio04clicked(bool checked);
    void gpio05clicked(bool checked);
    void gpio06clicked(bool checked);
    void gpio07clicked(bool checked);
    void gpioBank00clicked(bool checked);
    void button00Clicked();
    void button01Clicked();
    void button02Clicked();
    void button03Clicked();
    void button04Clicked();
    void button05Clicked();
    void button06Clicked();
    void button07Clicked();
    void getActionClicked();
    void setActionClicked();
    void inOutClicked();
    void highLowClicked();
    void timeoutTimer();
    void demoClicked();

private:
    unsigned int gpioID;
    unsigned int keepGpioID;
    bool gpiodetect;
    uint32_t mask;
    uint32_t direction;
    uint32_t level;
    bool levelFlag;
    bool directionFlag;
    int width;
    int height;

    QLabel *pinCounts;

    QRadioButton *gpioList[8];
    QRadioButton *gpioBank00;

    QPushButton *pinButtonList[8];

    QVBoxLayout *deviceLayout;
    QVBoxLayout *valueLayout;
    QVBoxLayout *directionLayout;
    QVBoxLayout *actionLayout;
    QVBoxLayout *statusLayout;
    QVBoxLayout *gpioListALayout;
    QVBoxLayout *gpioListBLayout;

    QHBoxLayout *bankButtonLayout;
    QHBoxLayout *directionValueLayout;
    QHBoxLayout *getSetLayout;
    QHBoxLayout *pinDirectionLayout;
    QHBoxLayout *pinLevelLayout;
    QHBoxLayout *pinNumberLayout;
    QHBoxLayout *gpioListLayout;

    QGroupBox *deviceGroup;
    QGroupBox *actionGroup;
    QGroupBox *statusGroup;

    QLabel *directionLabel;
    QPushButton *inOutButton;

    QLabel *valueLabel;
    QPushButton *highLowButton;

    QPushButton *getAction;
    QPushButton *setAction;

    QLabel *pinNumberList[8];
    QLabel *pinDirectionList[8];
    QLabel *pinLevelList[8];
    QLabel *errorLabel;

    QGridLayout *grid;

     QTimer  *timer;
     int  counter;
     QPushButton *demo;
     bool demoState;
};

#endif // GPIO_H
