#include "mytabwidget.h"

myTabWidget::myTabWidget(QWidget* parent)
{
    this->setParent(parent);
    connect(this , SIGNAL(currentChanged(int)),this,SLOT(currentChangedSlot(int)));
}
void myTabWidget::myTabWidgetInitialize(void)
{
    mywatchdog = new watchdog();
    myrealtimeInfo = new realtimeInfo();
    myboardInfo = new boardInfo();
    mygpio = new gpio();
    mystorage = new storage();
    myi2c = new i2c();

    addTab(myboardInfo,"Board Information");
    setTabIcon(BOARDINFOTAB,QIcon(":/Logo.jpg"));

    addTab(myrealtimeInfo,"System Monitor");
    setTabIcon(REALTIMEINFOTAB,QIcon(":/hw.png"));

   addTab(mywatchdog,"Watchdog");
    setTabIcon(WATCHDOGTAB,QIcon(":/whg.png"));

    addTab(mygpio,"GPIO");
    setTabIcon(GPIOTAB,QIcon(":/gpio.png"));

    addTab(mystorage,"STORAGE");
    setTabIcon(STORAGETAB,QIcon(":/Storage.png"));

    addTab(myi2c,"I2C");
    setTabIcon(I2CTAB,QIcon(":/i2c.png"));

}
void myTabWidget::currentChangedSlot(int index)
{
    if (index == REALTIMEINFOTAB)
        myrealtimeInfo->startTimer();
    else
        myrealtimeInfo->stopTimer();
}
