#include "mytabwidget.h"

myTabWidget::myTabWidget(QWidget* parent)
{
    this->setParent(parent);
    connect(this , SIGNAL(currentChanged(int)),this,SLOT(currentChangedSlot(int)));

    setFixedSize(600, 600);

}
void myTabWidget::myTabWidgetInitialize(void)
{
    mywatchdog = new watchdog();
    myrealtimeInfo = new realtimeInfo();
    myboardInfo = new boardInfo();

    addTab(mywatchdog,"Watchdog");
    setTabIcon(WATCHDOGTAB,QIcon(":/watchdog.jpg"));

    addTab(myrealtimeInfo,"System Monitor");
    setTabIcon(REALTIMEINFOTAB,QIcon(":/hw.png"));

    addTab(myboardInfo,"Board Information");
    setTabIcon(BOARDINFOTAB,QIcon(":/Logo.jpg"));

}
void myTabWidget::currentChangedSlot(int index)
{
    if (index == BOARDINFOTAB)
    {
        myrealtimeInfo->stopTimer();
        myboardInfo->fill();
    }
    else if (index == REALTIMEINFOTAB)
    {
        myrealtimeInfo->startTimer();

    }
    else if (index == WATCHDOGTAB)
    {
        myrealtimeInfo->stopTimer();

    }

}
