
#include "gpio.h"
#include <unistd.h>
#include <EApi.h>

const EApiId_t EApiGpioDevices[]={
    EAPI_GPIO_GPIO_ID(0)  ,
    EAPI_GPIO_GPIO_ID(1)  ,
    EAPI_GPIO_GPIO_ID(2)  ,
    EAPI_GPIO_GPIO_ID(3)  ,
    EAPI_GPIO_GPIO_ID(4)  ,
    EAPI_GPIO_GPIO_ID(5)  ,
    EAPI_GPIO_GPIO_ID(6)  ,
    EAPI_GPIO_GPIO_ID(7)  ,
    EAPI_ID_GPIO_BANK00
};

gpio::gpio(QWidget *parent)
    :QWidget(parent)
{
    QFont fontlabel;
    fontlabel.setBold(true);
    fontlabel.setPointSize(11);

    QFont fontvalue;
    fontvalue.setBold(false);
    fontvalue.setPointSize(11);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutTimer()));

    EApiStatus_t StatusCode;
    uint32_t input, output;
    StatusCode = EApiGPIOGetDirectionCaps(0, &input, &output);
    if (StatusCode == EAPI_STATUS_UNSUPPORTED && input == 0x00 && output == 0x00)
        gpiodetect = false;
    else
        gpiodetect = true;

    int i = 0;
    width = 30;
    height = 50;
    demoState = false;

    pinCounts = new QLabel("Pin Count: 8");
    pinCounts->setFont(fontlabel);

    for (i = 0 ; i<8 ; i++)
    {
        char temp[10];
        sprintf(temp,"GPIO 0%d",i);
        gpioList[i] = new QRadioButton(temp);
        gpioList[i]->setFont(fontvalue);
    }
    gpioBank00 = new QRadioButton("GPIO Bank00");
    gpioBank00->setFont(fontvalue);

    gpioList[0]->setChecked(1);
    mask = 0x01;
    gpioID = EApiGpioDevices[0];

    /*************************************/

    for (i = 0 ; i<8 ; i++)
    {
        char temp[5];
        sprintf(temp,"0%d",i);
        pinButtonList[i] = new QPushButton(temp);
        pinButtonList[i]->setStyleSheet("color: #BFBFBF");
        pinButtonList[i]->setEnabled(false);
    }

    connect( pinButtonList[0], SIGNAL( clicked() ), this, SLOT( button00Clicked() ) );
    connect( pinButtonList[1], SIGNAL( clicked() ), this, SLOT( button01Clicked() ) );
    connect( pinButtonList[2], SIGNAL( clicked() ), this, SLOT( button02Clicked() ) );
    connect( pinButtonList[3], SIGNAL( clicked() ), this, SLOT( button03Clicked() ) );
    connect( pinButtonList[4], SIGNAL( clicked() ), this, SLOT( button04Clicked() ) );
    connect( pinButtonList[5], SIGNAL( clicked() ), this, SLOT( button05Clicked() ) );
    connect( pinButtonList[6], SIGNAL( clicked() ), this, SLOT( button06Clicked() ) );
    connect( pinButtonList[7], SIGNAL( clicked() ), this, SLOT( button07Clicked() ) );

    connect( gpioList[0], SIGNAL( toggled(bool) ), this, SLOT( gpio00clicked(bool) ) );
    connect( gpioList[1], SIGNAL( toggled(bool) ), this, SLOT( gpio01clicked(bool) ) );
    connect( gpioList[2], SIGNAL( toggled(bool) ), this, SLOT( gpio02clicked(bool) ) );
    connect( gpioList[3], SIGNAL( toggled(bool) ), this, SLOT( gpio03clicked(bool) ) );
    connect( gpioList[4], SIGNAL( toggled(bool) ), this, SLOT( gpio04clicked(bool) ) );
    connect( gpioList[5], SIGNAL( toggled(bool) ), this, SLOT( gpio05clicked(bool) ) );
    connect( gpioList[6], SIGNAL( toggled(bool) ), this, SLOT( gpio06clicked(bool) ) );
    connect( gpioList[7], SIGNAL( toggled(bool) ), this, SLOT( gpio07clicked(bool) ) );
    connect( gpioBank00, SIGNAL( toggled(bool) ), this, SLOT( gpioBank00clicked(bool) ) );

    bankButtonLayout = new QHBoxLayout;
    for (i = 7 ; i>=0 ; i--)
        bankButtonLayout->addWidget(pinButtonList[i]);

    deviceLayout = new QVBoxLayout;
    deviceLayout->addWidget(pinCounts);

    gpioListALayout = new QVBoxLayout;
    gpioListBLayout = new QVBoxLayout;
    for (i = 0 ; i<4 ; i++)
        gpioListALayout->addWidget(gpioList[i]);
    for (i = 4 ; i<8 ; i++)
        gpioListBLayout->addWidget(gpioList[i]);

    gpioListLayout = new QHBoxLayout;
    gpioListLayout->addLayout(gpioListALayout);
    gpioListLayout->addLayout(gpioListBLayout);

    deviceLayout->addLayout(gpioListLayout);
    deviceLayout->addWidget(gpioBank00);
    deviceLayout->addLayout(bankButtonLayout);

    deviceGroup = new QGroupBox("Device");
    deviceGroup->setFont(fontlabel);
    deviceGroup->setLayout(deviceLayout);

    if (gpiodetect == false)
        deviceGroup->setEnabled(false);

    /*******************************************/

    directionLabel = new QLabel("Direction:");
    directionLabel->setFont(fontvalue);

    inOutButton = new QPushButton("INPUT");
    inOutButton->setFont(fontlabel);
    inOutButton->setStyleSheet("color: green");

    directionLayout=new QVBoxLayout;
    directionLayout->addWidget(directionLabel);
    directionLayout->addWidget(inOutButton);

    valueLabel = new QLabel("Level(value):");
    valueLabel->setFont(fontvalue);

    highLowButton = new QPushButton("HIGH");
    highLowButton->setFont(fontlabel);
    highLowButton->setStyleSheet("color: green");

    direction = EAPI_GPIO_INPUT;
    level = EAPI_GPIO_HIGH;
    levelFlag = true; /* high */
    directionFlag = true;

    valueLayout=new QVBoxLayout;
    valueLayout->addWidget(valueLabel);
    valueLayout->addWidget(highLowButton);

    connect( inOutButton, SIGNAL( clicked() ), this, SLOT( inOutClicked() ) );
    connect( highLowButton, SIGNAL( clicked() ), this, SLOT( highLowClicked() ) );

    directionValueLayout=new QHBoxLayout;
    directionValueLayout->addLayout(directionLayout);
    directionValueLayout->addLayout(valueLayout);

    getAction = new QPushButton("Get");
    setAction = new QPushButton("Set");
    demo = new QPushButton("Start Demo");

    connect( getAction, SIGNAL( clicked() ), this, SLOT( getActionClicked() ) );
    connect( setAction, SIGNAL( clicked() ), this, SLOT( setActionClicked() ) );
    connect( demo, SIGNAL( clicked() ), this, SLOT( demoClicked() ) );

    getSetLayout=new QHBoxLayout;
    getSetLayout->addWidget(getAction);
    getSetLayout->addWidget(setAction);
    getSetLayout->addWidget(demo);

    actionLayout=new QVBoxLayout;
    actionLayout->addLayout(directionValueLayout);
    actionLayout->addLayout(getSetLayout);

    actionGroup = new QGroupBox("Action");
    actionGroup->setFont(fontlabel);
    actionGroup->setLayout(actionLayout);

    if (gpiodetect == false)
        actionGroup->setEnabled(false);

    /*****************************************/

    for (i = 0 ; i<8 ; i++)
    {
        char temp[5];
        sprintf(temp,"0%d",i);
        pinNumberList[i] = new QLabel(temp);

        QSizePolicy sp_retain = pinNumberList[i]->sizePolicy();
        sp_retain.setRetainSizeWhenHidden(true);
        pinNumberList[i]->setSizePolicy(sp_retain);
    }

    pinNumberLayout=new QHBoxLayout;
    for (i = 7 ; i>=0 ; i--)
        pinNumberLayout->addWidget(pinNumberList[i]);

    for (i = 0 ; i<8 ; i++)
    {
        QPixmap pixmapNoInfo(":/question.png");
        pinDirectionList[i] = new QLabel;
        pinDirectionList[i]->setPixmap(pixmapNoInfo.scaled(width,height,Qt::KeepAspectRatio));

        QSizePolicy sp_retain = pinDirectionList[i]->sizePolicy();
        sp_retain.setRetainSizeWhenHidden(true);
        pinDirectionList[i]->setSizePolicy(sp_retain);
    }

    pinDirectionLayout=new QHBoxLayout;
    for (i = 7 ; i>=0 ; i--)
        pinDirectionLayout->addWidget(pinDirectionList[i]);

    for (i = 0 ; i<8 ; i++)
    {
        QPixmap pixmapNoInfo(":/question.png");
        pinLevelList[i] = new QLabel;
        pinLevelList[i]->setPixmap(pixmapNoInfo.scaled(width,height,Qt::KeepAspectRatio));

        QSizePolicy sp_retain = pinLevelList[i]->sizePolicy();
        sp_retain.setRetainSizeWhenHidden(true);
        pinLevelList[i]->setSizePolicy(sp_retain);
    }

    pinLevelLayout=new QHBoxLayout;
    for (i = 7 ; i>=0 ; i--)
        pinLevelLayout->addWidget(pinLevelList[i]);

    errorLabel = new QLabel;
    errorLabel->setFont(fontvalue);
    errorLabel->setStyleSheet("color : red");

    statusLayout=new QVBoxLayout;
    statusLayout->addLayout(pinNumberLayout);
    statusLayout->addLayout(pinDirectionLayout);
    statusLayout->addLayout(pinLevelLayout);
    statusLayout->addWidget(errorLabel);

    statusGroup = new QGroupBox("Status");
    statusGroup->setFont(fontlabel);
    statusGroup->setLayout(statusLayout);

    if (gpiodetect == false)
        statusGroup->setEnabled(false);

    /***********************************/

    grid = new QGridLayout;
    grid->addWidget(deviceGroup,0,0,1,2);
    grid->addWidget(actionGroup,1,0,1,2);
    grid->addWidget(statusGroup,3,0,1,2);
    setLayout(grid);
}

void gpio::gpio00clicked(bool checked)
{
    if(checked)
    {
        gpioID  = EApiGpioDevices[0];
        mask = 0x01;
        int i;
        for (i = 0 ; i<8 ; i++)
        {
            pinButtonList[i]->setStyleSheet("color: #BFBFBF");
            pinButtonList[i]->setEnabled(false);
        }
    }
}
void gpio::gpio01clicked(bool checked)
{
    if(checked)
    {
        gpioID  = EApiGpioDevices[1];
        mask = 0x02;
        int i;
        for (i = 0 ; i<8 ; i++)
        {
            pinButtonList[i]->setStyleSheet("color: #BFBFBF");
            pinButtonList[i]->setEnabled(false);
        }
    }
}
void gpio::gpio02clicked(bool checked)
{
    if(checked)
    {
        gpioID  = EApiGpioDevices[2];
        mask = 0x04;
        int i;
        for (i = 0 ; i<8 ; i++)
        {
            pinButtonList[i]->setStyleSheet("color: #BFBFBF");
            pinButtonList[i]->setEnabled(false);
        }
    }
}
void gpio::gpio03clicked(bool checked)
{
    if(checked)
    {
        gpioID  = EApiGpioDevices[3];
        mask = 0x08;
        int i;
        for (i = 0 ; i<8 ; i++)
        {
            pinButtonList[i]->setStyleSheet("color: #BFBFBF");
            pinButtonList[i]->setEnabled(false);
        }
    }
}
void gpio::gpio04clicked(bool checked)
{
    if(checked)
    {
        gpioID  = EApiGpioDevices[4];
        mask = 0x10;
        int i;
        for (i = 0 ; i<8 ; i++)
        {
            pinButtonList[i]->setStyleSheet("color: #BFBFBF");
            pinButtonList[i]->setEnabled(false);
        }
    }
}
void gpio::gpio05clicked(bool checked)
{
    if(checked)
    {
        gpioID  = EApiGpioDevices[5];
        mask = 0x20;
        int i;
        for (i = 0 ; i<8 ; i++)
        {
            pinButtonList[i]->setStyleSheet("color: #BFBFBF");
            pinButtonList[i]->setEnabled(false);
        }
    }
}
void gpio::gpio06clicked(bool checked)
{
    if(checked)
    {
        gpioID  = EApiGpioDevices[6];
        mask = 0x40;
        int i;
        for (i = 0 ; i<8 ; i++)
        {
            pinButtonList[i]->setStyleSheet("color: #BFBFBF");
            pinButtonList[i]->setEnabled(false);
        }
    }
}
void gpio::gpio07clicked(bool checked)
{
    if(checked)
    {
        gpioID  = EApiGpioDevices[7];
        mask = 0x80;
        int i;
        for (i = 0 ; i<8 ; i++)
        {
            pinButtonList[i]->setStyleSheet("color: #BFBFBF");
            pinButtonList[i]->setEnabled(false);
        }
    }
}
void gpio::gpioBank00clicked(bool checked)
{
    if(checked)
    {
        gpioID  = EApiGpioDevices[8];
        mask = 0x00;
        int i;
        for (i = 0 ; i<8 ; i++)
        {
            pinButtonList[i]->setStyleSheet("color: black");
            pinButtonList[i]->setEnabled(true);
        }
    }
}
void gpio::button00Clicked()
{
    if ((mask & 0x01) == 0x01)
    {
        pinButtonList[0]->setStyleSheet("color: black");
        mask = mask & 0xFE;
    }
    else
    {
        pinButtonList[0]->setStyleSheet("color: red");
        mask = mask | 0x01;
    }
}
void gpio::button01Clicked()
{
    if ((mask & 0x02) == 0x02)
    {
        pinButtonList[1]->setStyleSheet("color: black");
        mask = mask & 0xFD;
    }
    else
    {
        pinButtonList[1]->setStyleSheet("color: red");
        mask = mask | 0x02;
    }
}
void gpio::button02Clicked()
{
    if ((mask & 0x04) == 0x04)
    {
        pinButtonList[2]->setStyleSheet("color: black");
        mask = mask & 0xFB;
    }
    else
    {
        pinButtonList[2]->setStyleSheet("color: red");
        mask = mask | 0x04;
    }
}
void gpio::button03Clicked()
{
    if ((mask & 0x08) == 0x08)
    {
        pinButtonList[3]->setStyleSheet("color: black");
        mask = mask & 0xF7;
    }
    else
    {
        pinButtonList[3]->setStyleSheet("color: red");
        mask = mask | 0x08;
    }
}
void gpio::button04Clicked()
{
    if ((mask & 0x10) == 0x10)
    {
        pinButtonList[4]->setStyleSheet("color: black");
        mask = mask & 0xEF;
    }
    else
    {
        pinButtonList[4]->setStyleSheet("color: red");
        mask = mask | 0x10;
    }
}
void gpio::button05Clicked()
{
    if ((mask & 0x20) == 0x20)
    {
        pinButtonList[5]->setStyleSheet("color: black");
        mask = mask & 0xDF;
    }
    else
    {
        pinButtonList[5]->setStyleSheet("color: red");
        mask = mask | 0x20;
    }
}
void gpio::button06Clicked()
{
    if ((mask & 0x40) == 0x40)
    {
        pinButtonList[6]->setStyleSheet("color: black");
        mask = mask & 0xBF;
    }
    else
    {
        pinButtonList[6]->setStyleSheet("color: red");
        mask = mask | 0x40;
    }
}
void gpio::button07Clicked()
{
    if ((mask & 0x80) == 0x80)
    {
        pinButtonList[7]->setStyleSheet("color: black");
        mask = mask & 0x7F;
    }
    else
    {
        pinButtonList[7]->setStyleSheet("color: red");
        mask = mask | 0x80;
    }
}
void gpio::getActionClicked()
{
    uint32_t tempDirection;
    uint32_t tempLevel;
    EApiStatus_t StatusCodeDirection;
    EApiStatus_t StatusCodeLevel;
    int i;
    QPixmap pixmapIn(":/input-icon.png");
    QPixmap pixmapOut(":/output-icon.png");
    QPixmap pixmapLow(":/low.png");
    QPixmap pixmapHigh(":/high.png");
    QPixmap pixmapNoInfo(":/question.png");

    StatusCodeDirection = EApiGPIOGetDirection(gpioID, mask, &tempDirection);
    StatusCodeLevel=EApiGPIOGetLevel(gpioID, mask, &tempLevel);

    if((EAPI_TEST_SUCCESS(StatusCodeDirection)) || (EAPI_TEST_SUCCESS(StatusCodeLevel)))
    {
        for(i = 0 ; i < 8; i++)
        {
            if (mask & (0x01 << i))
            {
                if(EAPI_TEST_SUCCESS(StatusCodeDirection))
                {
                    if (gpioID  == EApiGpioDevices[8])
                    {
                        if ((0x01 << i ) & tempDirection)
                            pinDirectionList[i]->setPixmap(pixmapIn.scaled(width,height,Qt::KeepAspectRatio));
                        else
                            pinDirectionList[i]->setPixmap(pixmapOut.scaled(width,height,Qt::KeepAspectRatio));
                    }
                    else
                    {
                        if (tempDirection)
                            pinDirectionList[i]->setPixmap(pixmapIn.scaled(width,height,Qt::KeepAspectRatio));
                        else
                            pinDirectionList[i]->setPixmap(pixmapOut.scaled(width,height,Qt::KeepAspectRatio));
                    }
                }
                else
                {
                    pinDirectionList[i]->setPixmap(pixmapNoInfo.scaled(width,height,Qt::KeepAspectRatio));
                }

                if(EAPI_TEST_SUCCESS(StatusCodeLevel))
                {
                    if (gpioID  == EApiGpioDevices[8])
                    {
                        if ((0x01 << i ) & tempLevel)
                            pinLevelList[i]->setPixmap(pixmapHigh.scaled(width,height,Qt::KeepAspectRatio));
                        else
                            pinLevelList[i]->setPixmap(pixmapLow.scaled(width,height,Qt::KeepAspectRatio));
                    }
                    else
                    {
                        if (tempLevel)
                            pinLevelList[i]->setPixmap(pixmapHigh.scaled(width,height,Qt::KeepAspectRatio));
                        else
                            pinLevelList[i]->setPixmap(pixmapLow.scaled(width,height,Qt::KeepAspectRatio));
                    }

                }
                else
                {
                    pinLevelList[i]->setPixmap(pixmapNoInfo.scaled(width,height,Qt::KeepAspectRatio));
                }
            }
            else
            {
                pinDirectionList[i]->setPixmap(pixmapNoInfo.scaled(width,height,Qt::KeepAspectRatio));
                pinLevelList[i]->setPixmap(pixmapNoInfo.scaled(width,height,Qt::KeepAspectRatio));
            }
        }
    }

    if((!EAPI_TEST_SUCCESS(StatusCodeDirection)) && (!EAPI_TEST_SUCCESS(StatusCodeLevel)))
        errorLabel->setText("Error in Get Direction and Level");
    else if(!EAPI_TEST_SUCCESS(StatusCodeDirection))
        errorLabel->setText("Error in Get Direction");
    else if(!EAPI_TEST_SUCCESS(StatusCodeLevel))
        errorLabel->setText("Error in Get Level");
    else
        errorLabel->setText("");
}
void gpio::setActionClicked()
{
    EApiStatus_t StatusCodeDirection;
    EApiStatus_t StatusCodeLevel;

    StatusCodeDirection = EApiGPIOSetDirection(gpioID, mask, direction);
    StatusCodeLevel=EApiGPIOSetLevel(gpioID, mask, level);

    if((!EAPI_TEST_SUCCESS(StatusCodeDirection)) && (!EAPI_TEST_SUCCESS(StatusCodeLevel)))
        errorLabel->setText("Error in Set Direction and Level");
    else if(!EAPI_TEST_SUCCESS(StatusCodeDirection))
        errorLabel->setText("Error in Set Direction");
    else if(!EAPI_TEST_SUCCESS(StatusCodeLevel))
        errorLabel->setText("Error in Set Level");
    else
        errorLabel->setText("");
}
void gpio::inOutClicked()
{
    if (directionFlag == true)
    {
        inOutButton->setStyleSheet("color: red");
        inOutButton->setText("OUPUT");
        direction = EAPI_GPIO_OUTPUT;
        directionFlag = false;
    }
    else
    {
        inOutButton->setStyleSheet("color: green");
        inOutButton->setText("INPUT");
        direction = mask;
        directionFlag = true;
    }
}
void gpio::highLowClicked()
{
    if (levelFlag == true)
    {
        highLowButton->setStyleSheet("color: red");
        highLowButton->setText("LOW");
        level = EAPI_GPIO_LOW;
        levelFlag = false;
    }
    else
    {
        highLowButton->setStyleSheet("color: green");
        highLowButton->setText("HIGH");
        level = mask;
        levelFlag = true;
    }
}
void gpio::demoClicked()
{
    if (demoState == false)
    {
        demoState = true;
        counter = 0;
        demo->setText("Stop Demo");
        keepGpioID = gpioID;
        timer->start(1000);
    }
    else
    {
        timer->stop();
        demoState = false;
        demo->setText("Start Demo");

        if (keepGpioID >= 8)
            gpioBank00->toggled(true);
        else
            gpioList[keepGpioID]->toggled(true);
    }
}
void gpio::timeoutTimer()
{
    direction = EAPI_GPIO_OUTPUT;
    mask = 0xFF;
    gpioID = EApiGpioDevices[8];

    level = counter;

    counter++;
    if (counter >= 0xFF )
        counter = 0;

    setAction->click();
    getAction->click();
}
