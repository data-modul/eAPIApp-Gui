#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QTimer>
#include <EApi.h>

class watchdog: public QWidget
{
    Q_OBJECT
public:
    watchdog(QWidget *parent = 0);

public slots:
    void startClicked();
    void stopClicked();
    void stopTriggerClicked();
    void setPreTimeout(QString text);
    void setTimeout(QString text);
    void multiStagesclicked(bool checked);
    void timeoutTimer();
    void timeoutRemainedTimer();
private:
    QTimer  *timer;
    QTimer *remainedTimer;
    bool multiMode; /* false means single mode, true means multi mode */
    int preTimeout;
    int timeout;
    int count;

    QLabel *modes;
    QRadioButton *singlestage;
    QRadioButton *multistages;

    QPushButton *start;
    QPushButton *stop;
    QPushButton *stopTrigger;

    QLabel *preTimeoutLabel;
    QLineEdit *pretimeoutValue;
    QLabel *preTimeoutRequiredLabel;
    QLabel *timeoutLabel;
    QLineEdit *timeoutValue;
    QLabel *timeoutRequiredLabel;

    QLabel *output;
    QLabel *outputRemainedTime;
    QLabel *whgpicture;

    QVBoxLayout *modeLayout;
    QVBoxLayout *timeLayout;
    QVBoxLayout *insideoutputLayout;

    QHBoxLayout *outputLayout;
    QHBoxLayout* preTimeoutlayout;
    QHBoxLayout* timeoutlayout;
    QHBoxLayout* actionlayout;

    QGroupBox *modeGroup;
    QGroupBox *timeGroup;
    QGroupBox *outputGroup;

    QGridLayout *grid;

    void startEnable();
    void startDisable();
};

#endif // WATCHDOG_H
