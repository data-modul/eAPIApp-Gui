#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>

#include "boardinfo.h"
#include "realtimeinfo.h"
#include "watchdog.h"

#define BOARDINFOTAB 2
#define REALTIMEINFOTAB 1
#define WATCHDOGTAB 0

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
};

#endif // MYTABWIDGET_H
