#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>

#include "boardinfo.h"
#include "realtimeinfo.h"
#include "watchdog.h"
#include "gpio.h"
#include "storage.h"
#include "i2c.h"
#include "pwm.h"


#define BOARDINFOTAB 0
#define REALTIMEINFOTAB 1
#define WATCHDOGTAB 2
#define GPIOTAB 3
#define STORAGETAB 4
#define I2CTAB 5
#define PWMTAB 6

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
    storage *mystorage;
    i2c *myi2c;
    pwm *mypwm;
};

#endif // MYTABWIDGET_H
