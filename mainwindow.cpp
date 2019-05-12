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
    connect(tabs, SIGNAL(addBuff()), this, SLOT(addBuff()));

    this->tools = new ToolBtn();
    connect(tools, SIGNAL(setEnd()), this, SLOT(setEndByTools()));
    this->ui->ToolStack->setCurrentIndex(0);

    this->currentPage = -1;
    this->totalPages = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMainTab(QWidget* page, QString name){
    this->totalPages++;
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

void MainWindow::on_LayerCreate_clicked()
{
    QLabel* label = new QLabel();
    QPixmap* buffer = new QPixmap();
    buffer->fill(Qt::white);
    this->layerInfo[this->currentPage].push_back(label);
}

void MainWindow::on_LayerDel_clicked()
{

}

void MainWindow::on_MainTab_currentChanged(int index)
{
    if(index != -1){
        this->currentPage = index;
        this->tabs->mainPageList.at(this->currentPage)->getLayerInfo(this->layers);
        QWidget* widget = new QWidget();
        QGridLayout* grid = new QGridLayout();
        vector<QLabel*> tmpvec;

        for(size_t i = 0; i<this->layers.size(); i++){
            //grid->addWidget(this->layers[i]);
            QLabel* label = new QLabel();
            label->setPixmap(this->bufferList[this->currentPage][0]->scaled(ui->LayerGroup->width(), ui->LayerGroup->height(), Qt::KeepAspectRatio));
            label->show();
            tmpvec.push_back(label);
        }
        if(this->layerInfo.size() == this->totalPages){
            for(size_t i =0; i < this->layers.size(); i++){
                grid->addWidget(this->layerInfo[this->currentPage][i]);
            }
        }
        else{
            this->layerInfo.push_back(tmpvec);
            for(size_t i =0; i< this->layers.size(); i++){
                grid->addWidget(this->layerInfo[this->currentPage][i]);
            }
        }
        widget->setLayout(grid);
        ui->LayerWidget->addWidget(widget);
        ui->LayerWidget->setCurrentIndex(this->currentPage+1);
    }
}

void MainWindow::addBuff(){
    vector<QPixmap*> tmp;
    tmp.push_back(this->tabs->bufferList[this->tabs->bufferList.size()-1]);
    this->bufferList.push_back(tmp);
}
