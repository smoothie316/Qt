#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <ToolBtn/toolbtn.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->FileOpen, SIGNAL(createImage(QStringList)), ui->MainTab, SLOT(createImage(QStringList)));

    connect(ui->Crop, SIGNAL(btnNumber(int)), this, SLOT(btnNumber(int)));
    connect(ui->Text, SIGNAL(btnNumber(int)), this, SLOT(btnNumber(int)));
    connect(ui->Brush, SIGNAL(btnNumber(int)), this, SLOT(btnNumber(int)));
    connect(ui->Erase, SIGNAL(btnNumber(int)), this, SLOT(btnNumber(int)));
    connect(ui->Paint, SIGNAL(btnNumber(int)), this, SLOT(btnNumber(int)));
    connect(ui->Resize, SIGNAL(btnNumber(int)), this, SLOT(btnNumber(int)));
    this->recentClickedTool = 1;
    emit recentTool(this->recentClickedTool);

    connect(this, SIGNAL(recentTool(int)), ui->MainTab, SLOT(recentTool(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumber(int btnNum){
    this->recentClickedTool = btnNum;
    emit recentTool(this->recentClickedTool);
}
