#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>

#include "boardinfo.h"
#include "realtimeinfo.h"
#include "watchdog.h"
#include "gpio.h"

#define BOARDINFOTAB 0
#define REALTIMEINFOTAB 1
#define WATCHDOGTAB 2
#define GPIOTAB 3

class myTabWidget: public QTabWidget
{
    Q_OBJECT
public:
    myTabWidget(QWidget* parent);
    void myTabWidgetInitialize(void);
public slots:
    void currentChangedSlot(int index);

private:
    watchdog *mywatchdog;
    realtimeInfo *myrealtimeInfo;
    boardInfo *myboardInfo;
    gpio *mygpio;
};

#endif // MYTABWIDGET_H
