#ifndef PWM_H
#define PWM_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <EApi.h>
#include <EApiExt.h>

#ifndef _MSC_VER
  #include <unistd.h>
#endif

class pwm: public QWidget
{
    Q_OBJECT
public:
    pwm(QWidget *parent = 0);

public slots:
    void pwmch0clicked(bool checked);
    void pwmch1clicked(bool checked);
    void getClicked();
    void setClicked();
    void modeSelectionChanged(int index);
    void alignmentSelectionChanged(int index);
    void polaritySelectionChanged(int index);
    void enableSelectionChanged(int index);
    void minStepChanged(QString text);
    void maxStepChanged(QString text);
    void periodChanged(int value);
    void dutyChanged(int value);

private:
    EApiId_t Id;
    uint32_t minperiod;
    uint32_t maxperiod;
    uint32_t mingranularity;
    uint32_t maxgranularity;

    uint32_t period;
    uint32_t dutycycle;
    uint32_t polarity;
    uint32_t enable;
    uint32_t granularity;

    uint32_t mode;
    uint32_t alignment;

    uint32_t nextperiod;
    uint32_t nextdutycycle;
    uint32_t nextpolarity;
    uint32_t nextenable;
    uint32_t nextmode;
    uint32_t nextalignment;
    uint32_t minStepValue;
    uint32_t maxStepValue;

    QRadioButton *pwmch0;
    QRadioButton *pwmch1;

    QLabel *capLabel;

    QLabel *minPeriodCapLabel;
    QLabel *minPeriodCapValue;

    QLabel *maxPeriodCapLabel;
    QLabel *maxPeriodCapValue;

    QLabel *minGradCapLabel;
    QLabel *minGradCapValue;

    QLabel *maxGradCapLabel;
    QLabel *maxGradCapValue;

    QLabel *currentPeriodLabel;
    QLabel *currentPeriodValue;

    QLabel *currentDutycycleLabel;
    QLabel *currentDutycycleValue;

    QLabel *currentPolarityLabel;
    QLabel *currentPolarityValue;

    QLabel *currentModeLabel;
    QLabel *currentModeValue;

    QLabel *currentAlignmentLabel;
    QLabel *currentAlignmentValue;

    QLabel *currentGranularityLabel;
    QLabel *currentGranularityValue;

    QLabel *currentChOutputLabel;
    QLabel *currentChOutputValue;

    QLabel *newModeLabel;
    QComboBox *newmode;

    QLabel *minStepLabel;
    QLineEdit *minStep;

    QLabel *newAlignmentLabel;
    QComboBox *newAlignment;

    QLabel *maxStepLabel;
    QLineEdit *maxStep;

    QLabel *newPolarityLabel;
    QComboBox *newPolarity;

    QLabel *newEnableLabel;
    QComboBox *newEnable;

    QLabel *newPeriodLabel;
    QSpinBox *newPeriod;

    QLabel *newDutyLabel;
    QSpinBox *newDuty;

    QLabel *resultLabel;
    QPushButton *getStateButton;
    QPushButton *setStateButton;

    QHBoxLayout *channelSelectionLayout;
    QHBoxLayout *firstRowCapLayout;
    QHBoxLayout *secondRowCapLayout;


    QVBoxLayout *capLayout;

    QGroupBox *channelGroup;
    QGroupBox *currentGroup;
     QGroupBox *newGroup;

    QGridLayout *grid;
    QGridLayout *currentGrid;
    QGridLayout *thirdGrid;
};

#endif // PWM_H
