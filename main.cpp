#include <QApplication>
#include <QMainWindow>
#include <signal.h>
#include <EApi.h>
#include <QDesktopWidget>
#include "mytabwidget.h"

void signalhandler(int sig){
    if(sig==SIGINT){
        EApiLibUnInitialize();
        qApp->quit();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow *w = new QMainWindow();


    QRect screenGeometry = a.desktop()->screenGeometry();

    if(!EAPI_TEST_SUCCESS(EApiLibInitialize()))
        exit(0);

    w->setWindowTitle(QString::fromUtf8("DATA MODUL EAPI Utility"));

    myTabWidget *tabs = new myTabWidget(w);
    tabs->myTabWidgetInitialize();

    w->setCentralWidget(tabs);


    int x = (screenGeometry.width()-tabs->width()) / 2;
    int y = (screenGeometry.height()-tabs->height()) / 2;

    w->move(x, y);
    w->show();

    signal(SIGINT, signalhandler);
    const int ret = a.exec();
    EApiLibUnInitialize();
    return ret;

}
