#include <QApplication>
#include <QMainWindow>
#include <signal.h>
#include <EApi.h>

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

    if(!EAPI_TEST_SUCCESS(EApiLibInitialize()))
        exit(0);

    w->setWindowTitle(QString::fromUtf8("DATA MODUL EAPI Tester"));
    w->resize(600, 600);

    QWidget *centralWidget = new QWidget(w);
    myTabWidget *tabs = new myTabWidget(centralWidget);
tabs->myTabWidgetInitialize();

    w->setCentralWidget(centralWidget);
    w->show();
    signal(SIGINT, signalhandler);

    const int ret = a.exec();
    EApiLibUnInitialize();
    return ret;
}
