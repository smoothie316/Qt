#include "maintabpage.h"
#include "ui_maintabpage.h"

#include <QLabel>
#include <QResizeEvent>
#include <QDebug>

MainTabPage::MainTabPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTabPage)
{
    ui->setupUi(this);

    this->buf= nullptr;
    this->clickedTool = 1;
    this->setMouseCursor();
}

MainTabPage::~MainTabPage()
{
    delete ui;
}

void MainTabPage::setImage(QPixmap* buffer, int w, int h){
    buf = buffer;
    QLabel* layer = new QLabel(this->ui->MainEditContents);
    layer->setMouseTracking(true);
    layer->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));
    layer->show();
    this->layerSet.push_back(layer);
}

void MainTabPage::resizeEvent(QResizeEvent *event){
    int w = event->size().width();
    int h = event->size().height();
    // 해상도 저하
    if(!layerSet.empty()){
        for(size_t i=0; i<layerSet.size(); i++){
            layerSet[i]->setGeometry(0,0,w,h);
            layerSet[i]->clear();
            layerSet[i]->setPixmap(buf->scaled(w,h,Qt::KeepAspectRatio));
            layerSet[i]->show();
        }
    }
}



void MainTabPage::setMouseCursor(){
    if(this->clickedTool == 4){

    }
}

void MainTabPage::mouseMoveEvent(QMouseEvent *event){

}
void MainTabPage::mousePressEvent(QMouseEvent *event){

}

void MainTabPage::setLayerInfo(vector<QLabel*> layerList){
    this->layerSet.assign(layerList.begin(), layerList.end());
}

void MainTabPage::getAllLayerInfo(vector<QLabel*>& layerList){
    layerList.assign(this->layerSet.begin(), this->layerSet.end());
}

void MainTabPage::getLayerInfo(QLabel*& layer, int index){
    layer = this->layerSet.at(index);
}

void MainTabPage::setLayerPixel(QPixmap* buf){
    QLabel* label = this->layerSet.at(0);
    int w = label->width();
    int h = label->height();
    label->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));
    label->show();
}
