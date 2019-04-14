#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->tabs = new TabClass();
    this->fileIO = new FileClass();
    connect(fileIO, SIGNAL(createImage(QStringList)), tabs, SLOT(mainCreateImage(QStringList)));
    connect(tabs, SIGNAL(addMainTab(QWidget*, QString)), this, SLOT(addMainTab(QWidget*, QString)));

    this->tools = new ToolBtn();
    connect(this, SIGNAL(recentTool(int)), tools, SLOT(recentTool(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMainTab(QWidget* page, QString name){
    ui->MainTab->addTab(page, name);
}

void MainWindow::on_MainTab_tabCloseRequested(int index){
    // 이미지 파일 저장 관련 수행 필요
    ui->MainTab->removeTab(index);
}

void MainWindow::on_FileOpen_clicked(){
    fileIO->ImageOpen();
}
void MainWindow::on_Lasso_clicked(){
    this->recentClickedTool = 0;
    emit recentTool(this->recentClickedTool);
}
void MainWindow::on_Brush_clicked(){
    this->recentClickedTool = 1;
    emit recentTool(this->recentClickedTool);
}
void MainWindow::on_Paint_clicked(){
    this->recentClickedTool = 2;
    emit recentTool(this->recentClickedTool);
}
void MainWindow::on_Text_clicked(){
    this->recentClickedTool = 3;
    emit recentTool(this->recentClickedTool);
}
void MainWindow::on_Erase_clicked(){
    this->recentClickedTool = 4;
    emit recentTool(this->recentClickedTool);
}
void MainWindow::on_Crop_clicked(){
    this->recentClickedTool = 5;
    emit recentTool(this->recentClickedTool);
}
void MainWindow::on_Resize_clicked(){
    this->recentClickedTool = 6;
    emit recentTool(this->recentClickedTool);
}
