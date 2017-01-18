#include "mytabwidget.h"

myTabWidget::myTabWidget(QWidget* parent)
{
    this->setParent(parent);
    connect(this , SIGNAL(currentChanged(int)),this,SLOT(currentChangedSlot(int)));

  //  setFixedSize(600, 600);

}
void myTabWidget::myTabWidgetInitialize(void)
{
    mywatchdog = new watchdog();
    myrealtimeInfo = new realtimeInfo();
    myboardInfo = new boardInfo();
    mygpio = new gpio();
    mystorage = new storage();


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

}
void myTabWidget::currentChangedSlot(int index)
{
    if (index == REALTIMEINFOTAB)
    {
        myrealtimeInfo->startTimer();

    }
    else
    {
        myrealtimeInfo->stopTimer();
    }

    int i =0 ;;
    for (i =0 ; i < this->count();i++)
        if(i != index)
            this->widget(i)->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    this->widget(index)->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->widget(index)->resize(this->widget(index)->minimumSizeHint());
        this->widget(index)->adjustSize();
        resize(minimumSizeHint());
        adjustSize();
}
