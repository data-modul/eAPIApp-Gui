#ifndef REALTIMEINFO_H
#define REALTIMEINFO_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>
#include <EApi.h>
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>

class realtimeInfo: public QWidget
{
    Q_OBJECT
public:
    realtimeInfo(QWidget *parent = 0);
    void startTimer();
    void stopTimer();

public slots:
    void timeout();
    void sliderValueChanged(int value);

private:
    QTimer  *timer;

    QLabel *sensorLabel;
    QLabel *sensorValueLabel;
    QLabel *UnitLabel;
    QHBoxLayout* sensorlayout;

    QLabel *cpuTempLabel ;
    QLabel *cpuTempValueLabel;
    QLabel *cpuTempUnitLabel;
    QLabel *pchTempLabel;
    QLabel *pchTempValueLabel;
    QLabel *pchTempUnitLabel;
    QLabel *moduleTempLabel;
    QLabel *moduleTempValueLabel;
    QLabel *moduleTempUnitLabel;
    QHBoxLayout* cpuTemplayout;
    QHBoxLayout* pchTemplayout;
    QHBoxLayout* moduleTemplayout;

    QLabel *s0VoltageLabel;
    QLabel *s0VoltageValueLabel;
    QLabel *s0VoltageUnitLabel;
    QHBoxLayout* s0Voltagelayout;
    QLabel *battVoltageLabel;
    QLabel *battVoltageValueLabel;
    QLabel *battVoltageUnitLabel;
    QHBoxLayout* battVoltagelayout;
    QLabel *s5VoltageLabel;
    QLabel *s5VoltageValueLabel;
    QLabel *s5VoltageUnitLabel;
    QHBoxLayout* s5Voltagelayout;
    QLabel *inputVoltageLabel;
    QLabel *inputVoltageValueLabel;
    QLabel *inputVoltageUnitLabel;
    QHBoxLayout* inputVoltagelayout;

    QLabel *cpufanLabel;
    QLabel *cpufanValueLabel;
    QLabel *cpufanUnitLabel;
    QHBoxLayout* cpufanlayout;
    QLabel *sysfanLabel;
    QLabel *sysfanValueLabel;
    QLabel *sysfanUnitLabel;
    QHBoxLayout* sysfanlayout;

    QLabel *bootRTMLabel;
    QLabel *bootRTMValueLabel;
    QLabel *bootRTMUnitLabel;
    QLabel *runTimeRTMLabel;
    QLabel *runTimeRTMValueLabel;
    QLabel *runTimeRTMUnitLabel;
    QHBoxLayout* bootRTMlayout;
    QHBoxLayout* runTimeRTMlayout;

    QLabel *currentBrightnessValue;
    QLabel *tick0;
    QLabel *tick10;
    QSlider *slider;
    QGridLayout *gridBrightness;

    QVBoxLayout *tempLayout;
    QVBoxLayout *voltageLayout;
    QVBoxLayout *fanLayout;
    QVBoxLayout *rtmLayout;
    QVBoxLayout *brightnessLayout;

    QGroupBox *groupTemp;
    QGroupBox *groupVoltage;
    QGroupBox *groupFan;
    QGroupBox *groupRTM;
    QGroupBox *groupBrightness;

    QGridLayout *grid;

    void fill(void);

};

#endif // REALTIMEINFO_H

