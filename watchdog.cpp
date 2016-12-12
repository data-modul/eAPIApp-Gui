#include "watchdog.h"
#include <QIntValidator>
#include <EApi.h>

watchdog::watchdog(QWidget *parent)
    :QWidget(parent)
{
    uint32_t maxDelay, maxeventTimeout, maxResetTimeout;
    preTimeout =0;
    timeout = 0;
    count = 0;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutTimer()));

    remainedTimer = new QTimer();
    connect(remainedTimer, SIGNAL(timeout()), this, SLOT(timeoutRemainedTimer()));

    modes = new QLabel(tr("Modes:"));
    singlestage = new QRadioButton(tr("Single stage"));
    multistages = new QRadioButton(tr("Multi Stages"));
    singlestage->setChecked(1);
    multiMode = false;

    connect( multistages, SIGNAL( toggled(bool) ), this, SLOT( multiStagesclicked(bool) ) );

    modeLayout = new QVBoxLayout;
    modeLayout->addWidget(modes);
    modeLayout->addWidget(singlestage);
    modeLayout->addWidget(multistages);

    modeGroup = new QGroupBox(tr("Mode Configuration"));
    modeGroup->setLayout(modeLayout);

    /******/
    EApiWDogGetCap(&maxDelay, &maxeventTimeout, &maxResetTimeout);
    maxeventTimeout = maxeventTimeout / 1000;
    maxResetTimeout = maxResetTimeout /1000;

    char temp[50];
    sprintf(temp,"Event Timeout in sec(max:%d):",maxeventTimeout);
    preTimeoutLabel = new QLabel(temp);
    pretimeoutValue = new QLineEdit;
    pretimeoutValue->setFixedWidth(100);
    QValidator *validatorPre = new QIntValidator(0, maxeventTimeout, this);
    pretimeoutValue->setValidator(validatorPre);
    preTimeoutRequiredLabel = new QLabel;

    connect(pretimeoutValue, SIGNAL(textChanged(QString)), this, SLOT(setPreTimeout(QString)));

    preTimeoutlayout=new QHBoxLayout;
    preTimeoutlayout->addWidget(preTimeoutLabel);
    preTimeoutlayout->addWidget(pretimeoutValue);
    preTimeoutlayout->addWidget(preTimeoutRequiredLabel);

    sprintf(temp,"Reset Timeout in sec(max:%d):",maxResetTimeout);
    timeoutLabel = new QLabel(temp);
    timeoutValue = new QLineEdit;
    timeoutValue->setFixedWidth(100);
    QValidator *validator = new QIntValidator(0, maxResetTimeout, this);
    timeoutValue->setValidator(validator);
    timeoutRequiredLabel = new QLabel(tr("*required"));

    connect(timeoutValue, SIGNAL(textChanged(QString)), this, SLOT(setTimeout(QString)));

    timeoutlayout=new QHBoxLayout;
    timeoutlayout->addWidget(timeoutLabel);
    timeoutlayout->addWidget(timeoutValue);
    timeoutlayout->addWidget(timeoutRequiredLabel);

    timeLayout = new QVBoxLayout;
    timeLayout->addLayout(preTimeoutlayout);
    timeLayout->addLayout(timeoutlayout);

    timeGroup = new QGroupBox(tr("Timeout Configuration"));
    timeGroup->setLayout(timeLayout);
    /******/
    output = new QLabel;
    outputRemainedTime = new QLabel;
    outputLayout = new QHBoxLayout;
    outputLayout->addWidget(output);
    outputLayout->addWidget(outputRemainedTime);

    outputGroup = new QGroupBox(tr("Output"));
    outputGroup->setLayout(outputLayout);

    /*******/
    start = new QPushButton(tr("Start"));
    connect( start, SIGNAL( clicked() ), this, SLOT( startClicked() ) );

    stop = new QPushButton(tr("Stop"));
    connect( stop, SIGNAL( clicked() ), this, SLOT( stopClicked() ) );

    stopTrigger = new QPushButton(tr("Stop Triggering"));
    connect( stopTrigger, SIGNAL( clicked() ), this, SLOT( stopTriggerClicked() ) );

    startEnable();

    actionlayout=new QHBoxLayout;
    actionlayout->setSpacing(50);
    actionlayout->addWidget(start);
    actionlayout->addWidget(stop);
    actionlayout->addWidget(stopTrigger);

    grid = new QGridLayout;
    grid->setHorizontalSpacing(0);
    grid->addWidget(modeGroup,0,0,1,2);
    grid->addWidget(timeGroup,1,0,1,2);
    grid->addLayout(actionlayout,3,0,1,2);
    grid->addWidget(outputGroup,2,0,1,2);
    setLayout(grid);
}
void watchdog::multiStagesclicked(bool checked)
{
    if(checked)
        preTimeoutRequiredLabel->setText("*required");
    else
        preTimeoutRequiredLabel->setText("");

    multiMode  = checked;
}
void watchdog::setPreTimeout(QString text)
{
    preTimeout = text.toInt();
}
void watchdog::setTimeout(QString text)
{
    timeout = (text.toInt());
}
void watchdog::startClicked()
{
    EApiStatus_t StatusCode;

    if (multiMode == true  && preTimeout == 0 )
    {
        output->setText("PreTimeout and Timeout should be set in multi stages mode");
        return;
    }
    if(timeout == 0)
    {
        output->setText("Timeout should be set");
        return;
    }

    StatusCode = EApiWDogStart(0,preTimeout*1000,timeout*1000);
    if(StatusCode != EAPI_STATUS_SUCCESS)
    {
        output->setText("Error in starting Watchdog");
    }
    else
    {
        unsigned long ping = 0;
        if (multiMode == true)
        {
            ping = preTimeout + timeout - 2;
        }
        else
        {
            if(preTimeout)
                ping = (long)(preTimeout - 2);
            else
                ping = (long) (timeout - 2);
        }
        timer->start(ping*1000);
        count = 1;
        char temp[50];
       sprintf(temp,"%d sec remains to next trigger",timer->remainingTime() /1000);
       outputRemainedTime->setText(temp);

        remainedTimer->start(1000);
        output->setText("Watchdog is starting");
        startDisable();
    }
}
void watchdog::stopClicked()
{
    EApiWDogStop();
    startEnable();
    timer->stop();
    remainedTimer->stop();
    outputRemainedTime->setText("");
    output->setText("Watchdog is stopped");
}
void watchdog::stopTriggerClicked()
{
    timer->stop();
    remainedTimer->stop();
   outputRemainedTime->setText("");
    output->setText("Triggering is stopped, system is going to reboot after timeout");
}
void watchdog::timeoutTimer()
{
    char temp[50];
    EApiWDogTrigger();
    sprintf(temp,"%d times of triggers",count);
    output->setText(temp);
    count++;
}
void watchdog::timeoutRemainedTimer()
{
    char temp[50];
    int remainedTime = timer->remainingTime() /1000;
    if(remainedTime > 0)
    {
        sprintf(temp,"%d sec remains to next trigger",remainedTime);
        outputRemainedTime->setText(temp);
    }
    else
        outputRemainedTime->setText("");
}
void watchdog::startEnable()
{
    start->setEnabled(true);
    stop->setEnabled(false);
    stopTrigger->setEnabled(false);
}
void watchdog::startDisable()
{
    start->setEnabled(false);
    stop->setEnabled(true);
    stopTrigger->setEnabled(true);
}
