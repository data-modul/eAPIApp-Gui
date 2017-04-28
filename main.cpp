#include <QApplication>
#include <signal.h>
#include <EApi.h>
#include <QDesktopWidget>
#include "mainwindow.h"

void signalhandler(int sig){
    if(sig==SIGINT){
        EApiLibUnInitialize();
        qApp->quit();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!EAPI_TEST_SUCCESS(EApiLibInitialize()))
        exit(0);

    MainWindow *w = new MainWindow();
    QDesktopWidget wid;

    int width = w->frameGeometry().width();
    int height = w->frameGeometry().height();

    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();

    w->setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);
    w->show();

    signal(SIGINT, signalhandler);
    const int ret = a.exec();
    EApiLibUnInitialize();
    return ret;
}
