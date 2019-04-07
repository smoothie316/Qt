#include "mainwindow.h"
#include "ui_mainwindow.h"

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
