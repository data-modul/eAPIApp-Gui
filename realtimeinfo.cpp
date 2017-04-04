
#include "realtimeinfo.h"

const EApiId_t EApiValues[]={
    EAPI_ID_BOARD_BOOT_COUNTER_VAL,
    EAPI_ID_BOARD_RUNNING_TIME_METER_VAL ,
    /* HW Monitoring  */
    /* Temperature  */
    EAPI_ID_HWMON_CPU_TEMP               ,
    EAPI_ID_HWMON_SYSTEM_TEMP            ,
    /* Voltage */
    EAPI_ID_HWMON_VOLTAGE_3V3            ,
    EAPI_ID_HWMON_VOLTAGE_VBAT           ,
    EAPI_ID_HWMON_VOLTAGE_5VSB           ,
    EAPI_ID_HWMON_VOLTAGE_12V            ,
    /* Fan Rotations */
    EAPI_ID_HWMON_FAN_CPU
};

realtimeInfo::realtimeInfo(QWidget *parent)
    :QWidget(parent)
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    QFont fontlabel;
    fontlabel.setBold(true);
    fontlabel.setPointSize(11);

    QFont fontvalue;
    fontvalue.setPointSize(11);

    sensorLabel  = new QLabel("Sensor");
    sensorLabel->setFont(fontlabel);
    sensorLabel->setAlignment(Qt::AlignCenter);
    sensorLabel->setStyleSheet("QLabel { background-color : #143850; color : white; border: 1px solid white }");

    sensorValueLabel  = new QLabel("Value");
    sensorValueLabel->setFont(fontlabel);
    sensorValueLabel->setAlignment(Qt::AlignCenter);
    sensorValueLabel->setStyleSheet("QLabel { background-color : #143850; color : white; border: 1px solid white }");

    UnitLabel  = new QLabel("Unit");
    UnitLabel->setFont(fontlabel);
    UnitLabel->setAlignment(Qt::AlignCenter);
    UnitLabel->setStyleSheet("QLabel { background-color : #143850; color : white; border: 1px solid white }");

    sensorlayout=new QHBoxLayout;
    sensorlayout->setSpacing(50);
    sensorlayout->addWidget(sensorLabel);
    sensorlayout->addWidget(sensorValueLabel);
    sensorlayout->addWidget(UnitLabel);

    /**************** TEMP ****************************************/
    cpuTempLabel  = new QLabel("CPU Temperature");
    cpuTempLabel->setFont(fontvalue);
    cpuTempLabel->setAlignment(Qt::AlignCenter);
    cpuTempLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    cpuTempValueLabel  = new QLabel;
    cpuTempValueLabel->setFont(fontvalue);
    cpuTempValueLabel->setAlignment(Qt::AlignCenter);
    cpuTempValueLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    cpuTempUnitLabel  = new QLabel("Celsius");
    cpuTempUnitLabel->setFont(fontvalue);
    cpuTempUnitLabel->setAlignment(Qt::AlignCenter);
    cpuTempUnitLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");


    moduleTempLabel  = new QLabel("Module Temperature");
    moduleTempLabel->setFont(fontvalue);
    moduleTempLabel->setAlignment(Qt::AlignCenter);
    moduleTempLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    moduleTempValueLabel  = new QLabel;
    moduleTempValueLabel->setFont(fontvalue);
    moduleTempValueLabel->setAlignment(Qt::AlignCenter);
    moduleTempValueLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    moduleTempUnitLabel  = new QLabel("Celsius");
    moduleTempUnitLabel->setFont(fontvalue);
    moduleTempUnitLabel->setAlignment(Qt::AlignCenter);
    moduleTempUnitLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");


    cpuTemplayout=new QHBoxLayout;
    cpuTemplayout->setSpacing(50);
    cpuTemplayout->addWidget(cpuTempLabel);
    cpuTemplayout->addWidget(cpuTempValueLabel);
    cpuTemplayout->addWidget(cpuTempUnitLabel);

    moduleTemplayout=new QHBoxLayout;
    moduleTemplayout->setSpacing(50);
    moduleTemplayout->addWidget(moduleTempLabel);
    moduleTemplayout->addWidget(moduleTempValueLabel);
    moduleTemplayout->addWidget(moduleTempUnitLabel);

    tempLayout = new QVBoxLayout;
    tempLayout->addLayout(cpuTemplayout);
    tempLayout->addLayout(moduleTemplayout);

    groupTemp = new QGroupBox("Temperature Sensors");
    groupTemp->setFont(fontlabel);
    groupTemp->setLayout(tempLayout);

    /************ VOLTAGE ********************************************/
    s0VoltageLabel  = new QLabel("3.3V S0");
    s0VoltageLabel->setFont(fontvalue);
    s0VoltageLabel->setAlignment(Qt::AlignCenter);
    s0VoltageLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    s0VoltageValueLabel  = new QLabel;
    s0VoltageValueLabel->setFont(fontvalue);
    s0VoltageValueLabel->setAlignment(Qt::AlignCenter);
    s0VoltageValueLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    s0VoltageUnitLabel  = new QLabel("V");
    s0VoltageUnitLabel->setFont(fontvalue);
    s0VoltageUnitLabel->setAlignment(Qt::AlignCenter);
    s0VoltageUnitLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    s0Voltagelayout=new QHBoxLayout;
    s0Voltagelayout->setSpacing(50);
    s0Voltagelayout->addWidget(s0VoltageLabel);
    s0Voltagelayout->addWidget(s0VoltageValueLabel);
    s0Voltagelayout->addWidget(s0VoltageUnitLabel);

    /**/

    battVoltageLabel  = new QLabel("Battery Voltage");
    battVoltageLabel->setFont(fontvalue);
    battVoltageLabel->setAlignment(Qt::AlignCenter);
    battVoltageLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    battVoltageValueLabel  = new QLabel;
    battVoltageValueLabel->setFont(fontvalue);
    battVoltageValueLabel->setAlignment(Qt::AlignCenter);
    battVoltageValueLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    battVoltageUnitLabel  = new QLabel("V");
    battVoltageUnitLabel->setFont(fontvalue);
    battVoltageUnitLabel->setAlignment(Qt::AlignCenter);
    battVoltageUnitLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    battVoltagelayout=new QHBoxLayout;
    battVoltagelayout->setSpacing(50);
    battVoltagelayout->addWidget(battVoltageLabel);
    battVoltagelayout->addWidget(battVoltageValueLabel);
    battVoltagelayout->addWidget(battVoltageUnitLabel);

    /**/

    s5VoltageLabel  = new QLabel("5.0V S5");
    s5VoltageLabel->setFont(fontvalue);
    s5VoltageLabel->setAlignment(Qt::AlignCenter);
    s5VoltageLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    s5VoltageValueLabel  = new QLabel;
    s5VoltageValueLabel->setFont(fontvalue);
    s5VoltageValueLabel->setAlignment(Qt::AlignCenter);
    s5VoltageValueLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    s5VoltageUnitLabel  = new QLabel("V");
    s5VoltageUnitLabel->setFont(fontvalue);
    s5VoltageUnitLabel->setAlignment(Qt::AlignCenter);
    s5VoltageUnitLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    s5Voltagelayout=new QHBoxLayout;
    s5Voltagelayout->setSpacing(50);
    s5Voltagelayout->addWidget(s5VoltageLabel);
    s5Voltagelayout->addWidget(s5VoltageValueLabel);
    s5Voltagelayout->addWidget(s5VoltageUnitLabel);

    /**/

    inputVoltageLabel  = new QLabel("Wide Range Input");
    inputVoltageLabel->setFont(fontvalue);
    inputVoltageLabel->setAlignment(Qt::AlignCenter);
    inputVoltageLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    inputVoltageValueLabel  = new QLabel;
    inputVoltageValueLabel->setFont(fontvalue);
    inputVoltageValueLabel->setAlignment(Qt::AlignCenter);
    inputVoltageValueLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    inputVoltageUnitLabel  = new QLabel("V");
    inputVoltageUnitLabel->setFont(fontvalue);
    inputVoltageUnitLabel->setAlignment(Qt::AlignCenter);
    inputVoltageUnitLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    inputVoltagelayout=new QHBoxLayout;
    inputVoltagelayout->setSpacing(50);
    inputVoltagelayout->addWidget(inputVoltageLabel);
    inputVoltagelayout->addWidget(inputVoltageValueLabel);
    inputVoltagelayout->addWidget(inputVoltageUnitLabel);

    voltageLayout = new QVBoxLayout;
    voltageLayout->addLayout(s0Voltagelayout);
    voltageLayout->addLayout(battVoltagelayout);
    voltageLayout->addLayout(s5Voltagelayout);
    voltageLayout->addLayout(inputVoltagelayout);

    groupVoltage = new QGroupBox("Voltage Sensors");
    groupVoltage->setFont(fontlabel);
    groupVoltage->setLayout(voltageLayout);

    /************* FAN *******************************************/
    fanLabel  = new QLabel("Carrier Fan");
    fanLabel->setFont(fontvalue);
    fanLabel->setAlignment(Qt::AlignCenter);
    fanLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    fanValueLabel  = new QLabel;
    fanValueLabel->setFont(fontvalue);
    fanValueLabel->setAlignment(Qt::AlignCenter);
    fanValueLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    fanUnitLabel  = new QLabel("RPM");
    fanUnitLabel->setFont(fontvalue);
    fanUnitLabel->setAlignment(Qt::AlignCenter);
    fanUnitLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");


    fanlayout=new QHBoxLayout;
    fanlayout->setSpacing(50);
    fanlayout->addWidget(fanLabel);
    fanlayout->addWidget(fanValueLabel);
    fanlayout->addWidget(fanUnitLabel);

    groupFan = new QGroupBox("Fan Sensors");
    groupFan->setFont(fontlabel);
    groupFan->setLayout(fanlayout);


    /**************** RTM ****************************************/
    bootRTMLabel  = new QLabel("Boot Counter");
    bootRTMLabel->setFont(fontvalue);
    bootRTMLabel->setAlignment(Qt::AlignCenter);
    bootRTMLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    bootRTMValueLabel  = new QLabel;
    bootRTMValueLabel->setFont(fontvalue);
    bootRTMValueLabel->setAlignment(Qt::AlignCenter);
    bootRTMValueLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    bootRTMUnitLabel  = new QLabel("Boots");
    bootRTMUnitLabel->setFont(fontvalue);
    bootRTMUnitLabel->setAlignment(Qt::AlignCenter);
    bootRTMUnitLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");


    runTimeRTMLabel  = new QLabel("Running Time");
    runTimeRTMLabel->setFont(fontvalue);
    runTimeRTMLabel->setAlignment(Qt::AlignCenter);
    runTimeRTMLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    runTimeRTMValueLabel  = new QLabel;
    runTimeRTMValueLabel->setFont(fontvalue);
    runTimeRTMValueLabel->setAlignment(Qt::AlignCenter);
    runTimeRTMValueLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");

    runTimeRTMUnitLabel  = new QLabel("HH:MM");
    runTimeRTMUnitLabel->setFont(fontvalue);
    runTimeRTMUnitLabel->setAlignment(Qt::AlignCenter);
    runTimeRTMUnitLabel->setStyleSheet("QLabel { background-color : white; color : #143850; border: 1px solid white }");


    bootRTMlayout=new QHBoxLayout;
    bootRTMlayout->setSpacing(50);
    bootRTMlayout->addWidget(bootRTMLabel);
    bootRTMlayout->addWidget(bootRTMValueLabel);
    bootRTMlayout->addWidget(bootRTMUnitLabel);

    runTimeRTMlayout=new QHBoxLayout;
    runTimeRTMlayout->setSpacing(50);
    runTimeRTMlayout->addWidget(runTimeRTMLabel);
    runTimeRTMlayout->addWidget(runTimeRTMValueLabel);
    runTimeRTMlayout->addWidget(runTimeRTMUnitLabel);

    rtmLayout = new QVBoxLayout;
    rtmLayout->addLayout(bootRTMlayout);
    rtmLayout->addLayout(runTimeRTMlayout);

    groupRTM = new QGroupBox("Operating System");
    groupRTM->setFont(fontlabel);
    groupRTM->setLayout(rtmLayout);


    /**************** Backlight ****************************************/

    currentBrightnessValue  = new QLabel;
    currentBrightnessValue->setFont(fontvalue);
    currentBrightnessValue->setAlignment(Qt::AlignLeft);
    currentBrightnessValue->setStyleSheet("QLabel { color : #143850 }");

    tick0 = new QLabel("0");
    tick10 = new QLabel("10");

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0,10);
    slider->setSingleStep(1);
    slider->setTickInterval(1);
    slider->setTickPosition(QSlider::TicksBelow);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));

    gridBrightness = new QGridLayout;
    gridBrightness->addWidget(slider,0,0,1,10);
    gridBrightness->addWidget(tick0,1,0,1,1);
    gridBrightness->addWidget(tick10,1,10,1,1);

    brightnessLayout = new QVBoxLayout;
    brightnessLayout->addWidget(currentBrightnessValue);
    brightnessLayout->addLayout(gridBrightness);

    groupBrightness = new QGroupBox("Brightness");
    groupBrightness->setFont(fontlabel);
    groupBrightness->setLayout(brightnessLayout);

    EApiStatus_t StatusCode = EAPI_STATUS_SUCCESS;
    uint32_t Value = 0;
    char  *pBuffer;
    int pBufferLen = 100;

    pBuffer=(char *)malloc((pBufferLen) * sizeof(char));

    StatusCode=EApiVgaGetBacklightBrightness(EAPI_ID_BACKLIGHT_1, &Value);
    if(StatusCode == EAPI_STATUS_SUCCESS)
    {
        snprintf(pBuffer, pBufferLen,"Current Brightness is: %u",Value);
        currentBrightnessValue->setText(pBuffer);
    }
    else
        currentBrightnessValue->setText("Current Brightness is: Error!");

    slider->setValue(Value);

    /********************************************************/
    grid = new QGridLayout;
    grid->setHorizontalSpacing(0);
    grid->addLayout(sensorlayout,0,0,1,2);
    grid->addWidget(groupTemp,1,0,1,2);
    grid->addWidget(groupVoltage,2,0,1,2);
    grid->addWidget(groupFan,3,0,1,2);
    grid->addWidget(groupRTM,4,0,1,2);
    grid->addWidget(groupBrightness,5,0,1,2);
    grid->setRowStretch(1,1);
    grid->setRowStretch(2,1);
    grid->setRowStretch(3,1);
    grid->setRowStretch(4,1);
    grid->setRowStretch(5,1);
    grid->setRowStretch(6,1);
    grid->setRowStretch(7,1);
    setLayout(grid);
}

void realtimeInfo::fill(void)
{
    EApiStatus_t StatusCode = EAPI_STATUS_SUCCESS;
    unsigned i=0;
    uint32_t Value;
    unsigned int size;
    char  *pBuffer;
    int pBufferLen = 100;

    pBuffer=(char *)malloc((pBufferLen) * sizeof(char));
    size = sizeof(EApiValues)/(sizeof(EApiValues[0]));
    for(i=0;i<size;i++){
        StatusCode = EApiBoardGetValue(EApiValues[i],&Value);
        if (StatusCode == EAPI_STATUS_SUCCESS)
        {
            switch(EApiValues[i])
            {
            case EAPI_ID_BOARD_BOOT_COUNTER_VAL:
                snprintf(pBuffer, pBufferLen,"%u", Value);
                bootRTMValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_BOARD_RUNNING_TIME_METER_VAL:
                snprintf(pBuffer, pBufferLen,"%u:%u", Value/60, Value%60);
                runTimeRTMValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_HWMON_CPU_TEMP:
                Value-=EAPI_KELVINS_OFFSET;
                snprintf(pBuffer, pBufferLen,"%u.%u", ((int32_t)Value)/10,Value%10);
                cpuTempValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_HWMON_SYSTEM_TEMP:
                Value-=EAPI_KELVINS_OFFSET;
                snprintf(pBuffer, pBufferLen,"%u.%u",((int32_t)Value)/10, Value%10);
                moduleTempValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_HWMON_VOLTAGE_3V3:
                Value/=10;
                snprintf(pBuffer, pBufferLen,"%u.%02u",Value/100, Value%100);
                s0VoltageValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_HWMON_VOLTAGE_VBAT:
                Value/=10;
                snprintf(pBuffer, pBufferLen,"%u.%02u",Value/100, Value%100);
                battVoltageValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_HWMON_VOLTAGE_5VSB:
                Value/=10;
                snprintf(pBuffer, pBufferLen,"%u.%02u",Value/100, Value%100);
                s5VoltageValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_HWMON_VOLTAGE_12V:
                Value/=10;
                snprintf(pBuffer, pBufferLen,"%u.%02u",Value/100, Value%100);
                inputVoltageValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_HWMON_FAN_CPU:
                snprintf(pBuffer, pBufferLen,"%u",Value);
                fanValueLabel->setText(pBuffer);
                break;
            }
        }
        else
        {
            switch(EApiValues[i])
            {
            case EAPI_ID_BOARD_BOOT_COUNTER_VAL:
                bootRTMValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_BOARD_RUNNING_TIME_METER_VAL:
                runTimeRTMValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_HWMON_CPU_TEMP:
                cpuTempValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_HWMON_SYSTEM_TEMP:
                moduleTempValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_HWMON_VOLTAGE_3V3:
                s0VoltageValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_HWMON_VOLTAGE_VBAT:
                battVoltageValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_HWMON_VOLTAGE_5VSB:
                s5VoltageValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_HWMON_VOLTAGE_12V:
                inputVoltageValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_HWMON_FAN_CPU:
                fanValueLabel->setText("Unsupported");
                break;
            }
        }
    }
    free(pBuffer);
}
void realtimeInfo::sliderValueChanged(int value)
{
    EApiStatus_t StatusCode = EAPI_STATUS_SUCCESS;

    StatusCode=EApiVgaSetBacklightBrightness(EAPI_ID_BACKLIGHT_1, value );
    if(StatusCode != EAPI_STATUS_SUCCESS)
        currentBrightnessValue->setText("Current Brightness is: Error!");
    else
    {
        uint32_t Value;
        char  *pBuffer;
        int pBufferLen = 100;

        pBuffer=(char *)malloc((pBufferLen) * sizeof(char));

        StatusCode=EApiVgaGetBacklightBrightness(EAPI_ID_BACKLIGHT_1, &Value);
        if(StatusCode == EAPI_STATUS_SUCCESS)
        {
            snprintf(pBuffer, pBufferLen,"Current Brightness is: %u",Value);
            currentBrightnessValue->setText(pBuffer);
        }
        else
            currentBrightnessValue->setText("Current Brightness is: Error!");
    }
}
void realtimeInfo::timeout()
{
    fill();
}
void realtimeInfo::startTimer(void)
{
    fill();
    timer->start(1000);
}
void realtimeInfo::stopTimer(void)
{
    timer->stop();
}

