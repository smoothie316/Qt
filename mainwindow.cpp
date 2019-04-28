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
    connect(tools, SIGNAL(setEnd()), this, SLOT(setEndByTools()));
    this->ui->ToolStack->setCurrentIndex(0);
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
    this->tools->keyword->clicked();
}
void MainWindow::on_Brush_clicked(){
    this->recentClickedTool = 1;
    ui->ToolStack->addWidget(this->tools->brushW);
    ui->ToolStack->setCurrentIndex(1);
}
void MainWindow::on_Paint_clicked(){
    this->recentClickedTool = 2;
    ui->ToolStack->addWidget(this->tools->paintW);
    ui->ToolStack->setCurrentIndex(1);
}
void MainWindow::on_Text_clicked(){
    this->recentClickedTool = 3;
    ui->ToolStack->addWidget(this->tools->textW);
    ui->ToolStack->setCurrentIndex(1);
}
void MainWindow::on_Erase_clicked(){
    this->recentClickedTool = 4;
    ui->ToolStack->addWidget(this->tools->eraseW);
    ui->ToolStack->setCurrentIndex(1);
}
void MainWindow::on_Crop_clicked(){
    this->recentClickedTool = 5;
}
void MainWindow::on_Resize_clicked(){
    this->recentClickedTool = 6;
}

void MainWindow::changeToolPage(){

}
void MainWindow::setEndByTools(){
    this->ui->ToolStack->removeWidget(this->ui->ToolStack->widget(1));
    this->ui->ToolStack->setCurrentIndex(0);
}
