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

    ui->MainEdit->setWidgetResizable(true);

    this->buf= nullptr;
    this->clickedTool = 1;
    this->setMouseCursor();
    this->w = 0;
    this->h = 0;
}

MainTabPage::~MainTabPage()
{
    delete ui;
}

void MainTabPage::setImage(QPixmap* buffer, int w, int h){
    buf = buffer;
    QWidget* widget = new QWidget();
    QLayout *vBox = new QVBoxLayout();
    widget->setLayout(vBox);
    QLabel* layer = new QLabel();
    this->w = w;
    this->h = h;
    layer->installEventFilter(this);
    layer->setMouseTracking(true);
    layer->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));
    vBox->addWidget(layer);
    ui->MainEdit->setWidget(widget);
    this->layerSet.push_back(layer);
}

void MainTabPage::resizeEvent(QResizeEvent *event){
    int w = event->size().width();
    int h = event->size().height();
    this->w = w;
    this->h = h;
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
    // mouse cursor 주변 모양
    if(this->clickedTool == 4){

    }
}
void MainTabPage::keyPressEvent(QKeyEvent *event){
    if(event->modifiers() == Qt::CTRL)
        ctrlKey = true;
}
void MainTabPage::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Control){
        ctrlKey = false;
    }
}
void MainTabPage::wheelEvent(QWheelEvent *event){
    if(ctrlKey){
        const double degree = event->delta() / 12.0;
        int w = this->w * (degree/100);
        int h = this->h * (degree/100);
        w += this->w;
        h += this->h;
        this->w = w;
        this->h = h;
        for(int i=0; i<this->layerSet.size(); i++){
            //this->layerSet[i]->setGeometry(0,0,w,h);
            this->layerSet[i]->clear();
            this->layerSet[i]->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));

        }
    }
}

void adjustScrollBar(QScrollBar* scrollBar, int factor){
    scrollBar->setValue(factor * scrollBar->value());
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
