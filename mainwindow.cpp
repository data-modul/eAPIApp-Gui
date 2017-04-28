#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytabwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myTabWidget *tabs = new myTabWidget(this);
    tabs->myTabWidgetInitialize();
    this->setWindowTitle(QString::fromUtf8("DATA MODUL EAPI Utility"));
    this->setCentralWidget(tabs);
}
MainWindow::~MainWindow()
{
    delete ui;
}

