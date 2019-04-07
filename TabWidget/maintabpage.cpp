#include "maintabpage.h"
#include "ui_maintabpage.h"

#include <QLabel>
#include <QMessageBox>
#include <QResizeEvent>

MainTabPage::MainTabPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTabPage)
{
    ui->setupUi(this);
    buf= nullptr;
}

MainTabPage::~MainTabPage()
{
    delete ui;
}

void MainTabPage::setImage(QPixmap* buffer, int w, int h){
    buf = buffer;
    QLabel* layer  = new QLabel(this->ui->MainEditContents);
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
