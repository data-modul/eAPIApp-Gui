#include "pwm.h"
#include <unistd.h>
#include <QStandardItemModel>

static const QStandardItemModel* model;
static unsigned int modeFlag=0;
static unsigned int alignmentFlag=0;
static unsigned int polarityFlag=0;
static unsigned int outputFlag=0;
static unsigned int minStepsFlag=0;
static unsigned int maxStepsFlag=0;
static unsigned int periodFlag=0;
static unsigned int dutyFlag=0;

pwm::pwm(QWidget *parent)
    :QWidget(parent)
{
    QFont fontlabel;
    fontlabel.setBold(true);
    fontlabel.setPointSize(11);

    QFont fontvalue;
    fontvalue.setBold(false);
    fontvalue.setPointSize(11);

    EApiStatus_t StatusCode;
    QStringList list;

    pwmch0 = new QRadioButton("PWM Channel0");
    pwmch0->setFont(fontvalue);
    pwmch0->setChecked(1);
    connect( pwmch0, SIGNAL( toggled(bool) ), this, SLOT( pwmch0clicked(bool) ) );
    pwmch0->setChecked(1);
    Id = EAPIEX_ID_PWM_CHANNEL_0;

    pwmch1 = new QRadioButton("PWM Channel1");
    pwmch1->setFont(fontvalue);
    pwmch1->setChecked(0);
    connect( pwmch1, SIGNAL( toggled(bool) ), this, SLOT( pwmch1clicked(bool) ) );

    channelSelectionLayout=new QHBoxLayout;
    channelSelectionLayout->setSpacing(50);
    channelSelectionLayout->addWidget(pwmch0);
    channelSelectionLayout->addWidget(pwmch1);

    capLabel = new QLabel("Channel Capacity");
    capLabel->setFont(fontlabel);

    minPeriodCapLabel = new QLabel("Minimum Period:");
    minPeriodCapLabel->setFont(fontvalue);
    minPeriodCapValue = new QLabel("---");
    minPeriodCapValue->setFont(fontvalue);

    minGradCapLabel = new QLabel("Minimum Granularity:");
    minGradCapLabel->setFont(fontvalue);
    minGradCapValue = new QLabel("---");
    minGradCapValue->setFont(fontvalue);

    firstRowCapLayout=new QHBoxLayout;
    firstRowCapLayout->setSpacing(30);
    firstRowCapLayout->addWidget(minPeriodCapLabel);
    firstRowCapLayout->addWidget(minPeriodCapValue);
    firstRowCapLayout->addWidget(minGradCapLabel);
    firstRowCapLayout->addWidget(minGradCapValue);

    maxPeriodCapLabel = new QLabel("Maximum Period:");
    maxPeriodCapLabel->setFont(fontvalue);
    maxPeriodCapValue = new QLabel("---");
    maxPeriodCapValue->setFont(fontvalue);

    maxGradCapLabel = new QLabel("Maximum Granularity:");
    maxGradCapLabel->setFont(fontvalue);
    maxGradCapValue = new QLabel("---");
    maxGradCapValue->setFont(fontvalue);

    secondRowCapLayout=new QHBoxLayout;
    secondRowCapLayout->setSpacing(30);
    secondRowCapLayout->addWidget(maxPeriodCapLabel);
    secondRowCapLayout->addWidget(maxPeriodCapValue);
    secondRowCapLayout->addWidget(maxGradCapLabel);
    secondRowCapLayout->addWidget(maxGradCapValue);

    capLayout = new QVBoxLayout;
    capLayout->setSpacing(10);
    capLayout->addLayout(channelSelectionLayout);
    capLayout->addWidget(capLabel);
    capLayout->addLayout(firstRowCapLayout);
    capLayout->addLayout(secondRowCapLayout);

    channelGroup = new QGroupBox("Desired PWM Channel");
    channelGroup->setFont(fontlabel);
    channelGroup->setLayout(capLayout);
/********************************************************/
    currentGrid = new QGridLayout;
    currentGrid->setHorizontalSpacing(0);
    currentGrid->setSpacing(20);

    currentPeriodLabel = new QLabel("Period:");
    currentPeriodLabel->setFont(fontlabel);
    currentGrid->addWidget(currentPeriodLabel,0,0);

    currentPeriodValue = new QLabel("---");
    currentPeriodValue->setFont(fontvalue);
    currentGrid->addWidget(currentPeriodValue,0,1);

    currentDutycycleLabel = new QLabel("Duty-cycle:");
    currentDutycycleLabel->setFont(fontlabel);
    currentGrid->addWidget(currentDutycycleLabel,0,2);

    currentDutycycleValue = new QLabel("---");
    currentDutycycleValue->setFont(fontvalue);
    currentGrid->addWidget(currentDutycycleValue,0,3);

    currentPolarityLabel = new QLabel("Polarity:");
    currentPolarityLabel->setFont(fontlabel);
    currentGrid->addWidget(currentPolarityLabel,0,4);

    currentPolarityValue = new QLabel("---");
    currentPolarityValue->setFont(fontvalue);
    currentGrid->addWidget(currentPolarityValue,0,5);

    currentModeLabel = new QLabel("Resolution Mode:");
    currentModeLabel->setFont(fontlabel);
    currentGrid->addWidget(currentModeLabel,1,0);

    currentModeValue = new QLabel("---");
    currentModeValue->setFont(fontvalue);
    currentGrid->addWidget(currentModeValue,1,1);

    currentAlignmentLabel = new QLabel("Alignment:");
    currentAlignmentLabel->setFont(fontlabel);
    currentGrid->addWidget(currentAlignmentLabel,1,2);

    currentAlignmentValue = new QLabel("---");
    currentAlignmentValue->setFont(fontvalue);
    currentGrid->addWidget(currentAlignmentValue,1,3);

    currentGranularityLabel = new QLabel("Granularity:");
    currentGranularityLabel->setFont(fontlabel);
    currentGrid->addWidget(currentGranularityLabel,1,4);

    currentGranularityValue = new QLabel("---");
    currentGranularityValue->setFont(fontvalue);
    currentGrid->addWidget(currentGranularityValue,1,5);

    currentChOutputLabel = new QLabel("Channel Output:");
    currentChOutputLabel->setFont(fontlabel);
    currentGrid->addWidget(currentChOutputLabel,2,0);

    currentChOutputValue = new QLabel("---");
    currentChOutputValue->setFont(fontvalue);
    currentGrid->addWidget(currentChOutputValue,2,1);

    getStateButton = new QPushButton("Get State");
    getStateButton->setFont(fontlabel);
    currentGrid->addWidget(getStateButton,2,4);
    connect( getStateButton, SIGNAL( clicked() ), this, SLOT( getClicked() ) );

    currentGroup = new QGroupBox("Current State");
    currentGroup->setFont(fontlabel);
    currentGroup->setLayout(currentGrid);

    /************************ new state ********************************************/
    thirdGrid = new QGridLayout;
    thirdGrid->setHorizontalSpacing(0);
    thirdGrid->setSpacing(20);

    newModeLabel = new QLabel("Channel mode:");
    newModeLabel->setFont(fontlabel);

    thirdGrid->addWidget(newModeLabel,0,0);

    newmode = new QComboBox;
    newmode->setFont(fontvalue);
    list=(QStringList()<<"8-Bit"<<"16-Bit");
    newmode->addItems(list);
    if (Id == EAPIEX_ID_PWM_CHANNEL_1) /* channel 2 has only one mode 8bit */
    {
        int row = newmode->findText( "16-Bit" );

        model = dynamic_cast< QStandardItemModel * >( newmode->model() );
        QStandardItem* item = model->item( row);
        item->setEnabled( false );
    }
    connect(newmode , SIGNAL(currentIndexChanged(int)),this,SLOT(modeSelectionChanged(int)));
    nextmode = 0;

    thirdGrid->addWidget(newmode,0,1);

    minStepLabel = new QLabel("Min steps:");
    minStepLabel->setFont(fontvalue);

    thirdGrid->addWidget(minStepLabel,0,2);

    minStep = new QLineEdit;
    minStep->setFont(fontvalue);
    connect(minStep, SIGNAL(textChanged(QString)), this, SLOT(minStepChanged(QString)));
    minStepValue = 0;
    thirdGrid->addWidget(minStep,0,3);

    /******/
    newAlignmentLabel = new QLabel("Channel Alignment:");
    newAlignmentLabel->setFont(fontlabel);
    thirdGrid->addWidget(newAlignmentLabel,1,0);

    newAlignment = new QComboBox;
    newAlignment->setFont(fontvalue);
    thirdGrid->addWidget(newAlignment,1,1);

    newAlignment->addItem("Center");
    newAlignment->addItem("Left");
    connect(newAlignment , SIGNAL(currentIndexChanged(int)),this,SLOT(alignmentSelectionChanged(int)));
    nextalignment = 0;

    maxStepLabel = new QLabel("Max steps:");
    maxStepLabel->setFont(fontvalue);
    thirdGrid->addWidget(maxStepLabel,1,2);

    maxStep = new QLineEdit;
    maxStep->setFont(fontvalue);
    connect(maxStep, SIGNAL(textChanged(QString)), this, SLOT(maxStepChanged(QString)));
    maxStepValue = 0;
    thirdGrid->addWidget(maxStep,1,3);

    /*****/
    newPolarityLabel = new QLabel("Channel Polarity:");
    newPolarityLabel->setFont(fontlabel);
     thirdGrid->addWidget(newPolarityLabel,2,0);

    newPolarity = new QComboBox;
    newPolarity->setFont(fontvalue);
    newPolarity->addItem("Normal");
    newPolarity->addItem("Inversed");
    connect(newPolarity , SIGNAL(currentIndexChanged(int)),this,SLOT(polaritySelectionChanged(int)));
    nextpolarity = 0;
      thirdGrid->addWidget(newPolarity,2,1);

    newPeriodLabel  = new QLabel("Period:");
    newPeriodLabel->setFont(fontvalue);
    thirdGrid->addWidget(newPeriodLabel,2,2);

    newPeriod = new QSpinBox;
    newPeriod->setFont(fontvalue);
    newPeriod->setSingleStep(1);
    connect(newPeriod, SIGNAL(valueChanged(int)), this, SLOT(periodChanged(int)));
    thirdGrid->addWidget(newPeriod,2,3);

    /***************************************************************/
    newEnableLabel = new QLabel("Channel Output:");
    newEnableLabel->setFont(fontlabel);
    thirdGrid->addWidget(newEnableLabel,3,0);

    newEnable = new QComboBox;
    newEnable->setFont(fontvalue);
    newEnable->addItem("Enable");
    newEnable->addItem("Disable");
    connect(newEnable , SIGNAL(currentIndexChanged(int)),this,SLOT(enableSelectionChanged(int)));
    nextenable = 0;
    thirdGrid->addWidget(newEnable,3,1);

    newDutyLabel  = new QLabel("Duty-cycle:");
    newDutyLabel->setFont(fontvalue);
    thirdGrid->addWidget(newDutyLabel,3,2);

    newDuty = new QSpinBox;
    newDuty->setFont(fontvalue);
    newDuty->setMinimum(0);
    newDuty->setSingleStep(1);
    newDuty->setValue(0);
    connect(newDuty, SIGNAL(valueChanged(int)), this, SLOT(dutyChanged(int)));
    thirdGrid->addWidget(newDuty,3,3);

    resultLabel  = new QLabel("Result: --- ");
    resultLabel->setFont(fontvalue);
    resultLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
     thirdGrid->addWidget(resultLabel,4,0,1,3);

    setStateButton = new QPushButton("Set State");
    setStateButton->setFont(fontlabel);
    connect( setStateButton, SIGNAL( clicked() ), this, SLOT( setClicked() ) );
     thirdGrid->addWidget(setStateButton,4,3);

     newGroup = new QGroupBox("New State");
     newGroup->setFont(fontlabel);
     newGroup->setLayout(thirdGrid);


    grid = new QGridLayout;
    grid->setHorizontalSpacing(0);
    grid->addWidget(channelGroup,0,0,1,2);
    grid->addWidget(currentGroup,1,0,1,2);
    grid->addWidget(newGroup,2,0,1,2);
    grid->setRowStretch(1,1);
    grid->setRowStretch(2,1);
    // grid->setRowStretch(3,1);
    setLayout(grid);
    pwmch0clicked(true);
}

void pwm::pwmch0clicked(bool checked)
{
    EApiId_t compan;
    uint32_t feature = EAPIEX_PWM_QUERY_FLAG;
    EApiStatus_t StatusCode;

    if(checked)
    {
        int row = newmode->findText( "16-Bit" );
        model = dynamic_cast< QStandardItemModel * >( newmode->model() );
        QStandardItem* item = model->item( row);
        item->setEnabled( true );

        Id  = EAPIEX_ID_PWM_CHANNEL_0;
        StatusCode = EApiExPwmGetCaps(Id,&minperiod,&maxperiod,&mingranularity,&maxgranularity,&compan,&feature);
        if(!EAPI_TEST_SUCCESS(StatusCode))
        {
            minPeriodCapValue->setText("---");
            minGradCapValue->setText("---");
            maxPeriodCapValue->setText("---");
            maxGradCapValue->setText("---");
        }
        else
        {
            minPeriodCapValue->setText(QString::number(minperiod));
            minGradCapValue->setText(QString::number(mingranularity));
            maxPeriodCapValue->setText(QString::number(maxperiod));
            maxGradCapValue->setText(QString::number(maxgranularity));
        }

        newPeriod->setRange(minperiod, maxperiod);
        newPeriod->setValue(minperiod);
        periodFlag=0;
    }
}
void pwm::pwmch1clicked(bool checked)
{
    EApiId_t compan;
    uint32_t feature = EAPIEX_PWM_QUERY_FLAG;
    EApiStatus_t StatusCode;

    if(checked)
    {
        int row = newmode->findText( "16-Bit" );
        model = dynamic_cast< QStandardItemModel * >( newmode->model() );
        QStandardItem* item = model->item( row);
        item->setEnabled( false );

        newmode->setCurrentIndex(0);
        newmode->update();
        nextmode = 0;

        Id  = EAPIEX_ID_PWM_CHANNEL_1;
        StatusCode = EApiExPwmGetCaps(Id,&minperiod,&maxperiod,&mingranularity,&maxgranularity,&compan,&feature);
        if(!EAPI_TEST_SUCCESS(StatusCode))
        {
            minPeriodCapValue->setText("---");
            minGradCapValue->setText("---");
            maxPeriodCapValue->setText("---");
            maxGradCapValue->setText("---");
        }
        else
        {
            minPeriodCapValue->setText(QString::number(minperiod));
            minGradCapValue->setText(QString::number(mingranularity));
            maxPeriodCapValue->setText(QString::number(maxperiod));
            maxGradCapValue->setText(QString::number(maxgranularity));
        }
        newPeriod->setRange(minperiod, maxperiod);
        newPeriod->setValue(minperiod);
        periodFlag=0;
    }

}

void pwm::getClicked()
{
    uint32_t feature;
    EApiStatus_t StatusCode;

    StatusCode = EApiExPwmGetConfig(Id, &period,&dutycycle,&polarity,&feature,&enable,&granularity);
    mode = feature & EAPIEX_PWM_FEATURE_16BIT;
    alignment = feature & EAPIEX_PWM_FEATURE_CENTER_MODE;
    if(!EAPI_TEST_SUCCESS(StatusCode))
    {
        currentPeriodValue->setText("---");
        currentDutycycleValue->setText("---");
        currentPolarityValue->setText("---");
        currentModeValue->setText("---");
        currentAlignmentValue->setText("---");
        currentGranularityValue->setText("---");
        currentChOutputValue->setText("---");
    }
    else
    {
        minPeriodCapValue->setText(QString::number(minperiod));
        minGradCapValue->setText(QString::number(mingranularity));
        maxPeriodCapValue->setText(QString::number(maxperiod));
        maxGradCapValue->setText(QString::number(maxgranularity));



        currentPeriodValue->setText(QString::number(period));
        currentDutycycleValue->setText(QString::number(dutycycle));
        if(polarity == EAPIEX_PWM_POLARITY_NORMAL)
            currentPolarityValue->setText("Normal");
        else
            currentPolarityValue->setText("Inversed");
        if(mode == EAPIEX_PWM_FEATURE_16BIT)
            currentModeValue->setText("16-Bit");
        else
            currentModeValue->setText("8-Bit");
        if(alignment == EAPIEX_PWM_FEATURE_CENTER_MODE)
            currentAlignmentValue->setText("Center-aligned");
        else
            currentAlignmentValue->setText("Left-aligned");
        currentGranularityValue->setText(QString::number(granularity));
        if(enable == EAPIEX_PWM_SET_ON)
        {
            currentChOutputValue->setStyleSheet("color: green");
            currentChOutputValue->setText("On");
        }
        else
        {
            currentChOutputValue->setStyleSheet("color: red");
            currentChOutputValue->setText("Off");
        }
    }
}

void pwm::modeSelectionChanged(int index)
{
    QString temp;

    temp = newmode->itemText(index);
    if(temp == "16-Bit")
        nextmode = EAPIEX_PWM_FEATURE_16BIT;
    else
        nextmode = 0;

    modeFlag = 1;
}

void pwm::minStepChanged(QString text)
{
    minStepValue = text.toInt();
    minStepsFlag = 1;
}

void pwm::maxStepChanged(QString text)
{
    maxStepValue = text.toInt();
    maxStepsFlag = 1 ;
}

void pwm::alignmentSelectionChanged(int index)
{
    QString temp;
    temp = newAlignment->itemText(index);
    if(temp == "Center")
        nextalignment = EAPIEX_PWM_FEATURE_CENTER_MODE;
    else
        nextalignment = 0;

    alignmentFlag = 1;
}

void pwm::polaritySelectionChanged(int index)
{
    QString temp;
    temp = newPolarity->itemText(index);
    if(temp == "Inversed")
        nextpolarity = EAPIEX_PWM_POLARITY_INVERSED;
    else
        nextpolarity = EAPIEX_PWM_POLARITY_NORMAL;

    polarityFlag=1;
}

void pwm::enableSelectionChanged(int index)
{
    QString temp;
    temp = newEnable->itemText(index);
    if(temp == "Enable")
        nextenable = EAPIEX_PWM_SET_ON;
    else
        nextenable = EAPIEX_PWM_SET_OFF;

    outputFlag=1;
}

void pwm::periodChanged(int value)
{
    nextperiod = value;
    newDuty->setMaximum(nextperiod);
    periodFlag=1;
}

void pwm::dutyChanged(int value)
{
    nextdutycycle = value;
    dutyFlag=1;
}
void pwm::setClicked()
{
    uint32_t feature;
    EApiStatus_t StatusCode;
    uint32_t localFlag = 0;

    if(dutyFlag == 1 && modeFlag == 0 && alignmentFlag == 0 &&
            polarityFlag == 0 && outputFlag == 0 && minStepsFlag == 0 &&
            maxStepsFlag == 0 && periodFlag == 0)
    {
        printf("debug___1\n");
        StatusCode = EApiExPwmSetDuty(Id, nextdutycycle);
    }
    else if(dutyFlag == 0 && modeFlag == 0 && alignmentFlag == 0 &&
            polarityFlag == 0 && outputFlag == 1 && minStepsFlag == 0 &&
            maxStepsFlag == 0 && periodFlag == 0)
    {
        printf("debug___2\n");
        StatusCode = EApiExPwmSetEnable(Id,nextenable);
    }
    else if(dutyFlag == 0 && modeFlag == 0 && alignmentFlag == 0 &&
            polarityFlag == 1 && outputFlag == 0 && minStepsFlag == 0 &&
            maxStepsFlag == 0 && periodFlag == 0)
    {
        printf("debug___3\n");
        StatusCode = EApiExPwmSetPolarity(Id, nextpolarity);
    }
    else
    {
        printf("debug___4  %u  %u  %u %u %u %u %u %u\n", dutyFlag , modeFlag ,alignmentFlag, polarityFlag, outputFlag , minStepsFlag ,maxStepsFlag, periodFlag);
        feature = nextmode | nextalignment;
        StatusCode = EApiExPwmSetConfig(Id, &nextperiod,&nextdutycycle,&nextpolarity,&feature,&minStepValue,&maxStepValue,&nextenable,&granularity);
        localFlag = 1;
    }

    if(!EAPI_TEST_SUCCESS(StatusCode))
    {
        resultLabel->setText("Result: Error during set state.");
    }
    else
    {
        if (localFlag)
        {
            char  pBuffer[200];
            snprintf(pBuffer, 200,"Result: Period=%u, Duty-cycle=%u, Granularity=%u",nextperiod,nextdutycycle,granularity);
            resultLabel->setText(pBuffer);
        }
        else
        {
            resultLabel->setText("Result: Successful");
        }
    }

    modeFlag=0;
    alignmentFlag=0;
    polarityFlag=0;
    outputFlag=0;
    minStepsFlag=0;
    maxStepsFlag=0;
    periodFlag=0;
    dutyFlag=0;
}
