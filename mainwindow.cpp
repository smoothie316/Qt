#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->FileOpen, SIGNAL(createImage(QStringList)), ui->MainTab, SLOT(createImage(QStringList)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Paint_clicked()
{
    QDockWidget *dock = new QDockWidget();
    this->addDockWidget(Qt::TopDockWidgetArea, dock);
    dock->setFloating(true);
    dock->show();
}
