#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->tabs = new TabClass();
    this->fileIO = new FileClass();
    connect(fileIO, SIGNAL(createImage(QStringList)), tabs, SLOT(mainCreateImage(QStringList)));
    connect(tabs, SIGNAL(addMainTab(QWidget*, QString)), this, SLOT(addMainTab(QWidget*, QString)));
    connect(tabs, SIGNAL(addSubTab(QWidget*, QString)), this, SLOT(addSubTab(QWidget*, QString)));

    this->tools = new ToolBtn();
    connect(tools, SIGNAL(setEnd()), this, SLOT(setEndByTools()));
    connect(tools, SIGNAL(setName(QString)), this, SLOT(setSubPageName(QString)));
    this->ui->ToolStack->setCurrentIndex(0);

    this->currentPage = -1;
    this->totalPages = -1;
}

MainWindow::~MainWindow(){
    delete ui;
}

// Tab page 관련 설정
void MainWindow::addMainTab(QWidget* page, QString name){
    // main tab widget에 page를 추가하고 이미지 표시
    // 모든 데이터 초기화 담당
    this->totalPages++;
    map<QLabel*, QPixmap*> tmpMap;
    QWidget* widget = new QWidget();
    QGridLayout* grid = new QGridLayout();
    QLabel* tmpLayer = new QLabel(widget);
    QPixmap* tmpBuf = new QPixmap();

    this->tabs->getBuff(tmpBuf, this->totalPages);
    tmpLayer->setPixmap(tmpBuf->scaled(ui->LayerWidget->width(), ui->LayerWidget->height(), Qt::KeepAspectRatio));
    tmpLayer->show();
    tmpMap.insert(make_pair(tmpLayer, tmpBuf));
    this->layerInfo.insert(make_pair(this->totalPages, tmpMap));
    for(auto itr = tmpMap.begin(); itr != tmpMap.end(); ++itr){
        grid->addWidget(itr->first);
    }
    widget->setLayout(grid);
    ui->LayerWidget->addWidget(widget);
    ui->MainTab->addTab(page, name);
}
void MainWindow::on_MainTab_tabCloseRequested(int index){
    // main tab widget에 page를 삭제할 때 사용되는 함수
    // 이미지 파일 저장 관련 수행 필요
    this->totalPages--;
    ui->MainTab->removeTab(index);
}
void MainWindow::on_LayerCreate_clicked(){
    // 레이어 추가 (create 버튼)
}
void MainWindow::on_LayerDel_clicked(){
    // 레이어 삭제 (delete 버튼)
}
void MainWindow::on_MainTab_currentChanged(int index){
    if(index != -1){
        this->currentPage = index;
        ui->LayerWidget->setCurrentIndex(this->currentPage + 1);
    }
    qDebug() << ui->LayerWidget->count();
}
void MainWindow::setSubPageName(QString name){
    this->tabs->subTabCreate(name);
}
void MainWindow::addSubTab(QWidget* page, QString name){
    this->tabs->subPageList.at(this->tabs->subPageList.size()-1)->setImage("/"
                                                                           "+--cat/");
    ui->SubTab->addTab(page, name);
}
void MainWindow::on_SubTab_tabCloseRequested(int index){
    ui->SubTab->removeTab(index);
}

// Tool Button 설정 slot들
void MainWindow::on_FileOpen_clicked(){
    // 사용자가 이미지 파일을 열기 위해 file open버튼을 클릭했을 때 발생
    //
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

