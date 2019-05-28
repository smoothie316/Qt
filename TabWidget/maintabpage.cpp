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

    //ui->MainEdit->setWidgetResizable(true);

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

    //QString style = "border-color:rgb(0,0,0); border-width:1.2px; border-style:solid;";
    buf = buffer;
    QLabel* layer = new QLabel();
    layer->installEventFilter(this);
    this->w = w;
    this->h = h;
    layer->installEventFilter(this);
    layer->setMouseTracking(true);
    layer->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));
    bufSize = buf->scaled(w,h,Qt::KeepAspectRatio).size();
    bufSize = layer->size();
    layer->setObjectName("canvas");
    ui->MainEdit->setWidget(layer);
    this->layerSet.push_back(layer);
    qDebug() << "set Image";
    qDebug() << bufSize;
}

void MainTabPage::resizeEvent(QResizeEvent *event){
    int w = event->size().width();
    int h = event->size().height();
    this->w = w;
    this->h = h;
    qDebug() << "resize";
    // 해상도 저하
    if(!layerSet.empty()){
        for(size_t i=0; i<layerSet.size(); i++){
            //layerSet[i]->setGeometry(0,0,w,h);
            layerSet[i]->clear();
            layerSet[i]->setPixmap(buf->scaled(w,h,Qt::KeepAspectRatio));
            bufSize = buf->scaled(w,h,Qt::KeepAspectRatio).size();
            qDebug() << bufSize;
            layerSet[i]->show();
        }
    }
}

void MainTabPage::setMouseCursor(){
    // mouse cursor 주변 모양
    if(this->clickedTool == 4){

    }
}
bool MainTabPage::eventFilter(QObject* object, QEvent *event){\
    if(object->objectName() == "canvas"){
        if(event->type() == QMouseEvent::MouseButtonPress){
//            qDebug() << this->bufSize;
//            qDebug() << this->layerSet.at(0)->size();
        }
    }
    return QWidget::eventFilter(object, event);
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
            bufSize = buf->scaled(w,h,Qt::KeepAspectRatio).size();
            //bufSize = this->layerSet[i]->size();
        }
    }
}

void MainTabPage::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(this->layerInfo->at(this->currentBufNum)->width() > this->layerInfo->at(this->currentBufNum)->height()){
            double ratio = (this->layerInfo->at(this->currentBufNum)->height()) / (double)(bufSize.height());
            QSize widgetSize = this->layerSet.at(0)->size();
            originPos.setY((int)(event->y() * ratio) + ((widgetSize.height()-bufSize.height())/2));
            originPos.setX(event->x() * ratio);
        }
        else {
            double ratio = (this->layerInfo->at(this->currentBufNum)->width()) / (bufSize.width());
        }
        //originPos = event->pos();
        clicked = true;
    }
}

void MainTabPage::mouseMoveEvent(QMouseEvent *event){
    if((event->buttons() & Qt::LeftButton)){
        if(this->layerInfo->at(this->currentBufNum)->width() > this->layerInfo->at(this->currentBufNum)->height()){
            double ratio = (this->layerInfo->at(this->currentBufNum)->height()) / (double)(bufSize.height());
            QSize widgetSize = this->layerSet.at(0)->size();
            originPos.setY((int)(event->y() * ratio) + ((widgetSize.height()-bufSize.height())/2));
            originPos.setX(event->x() * ratio);
        }
        else {
            double ratio = (this->layerInfo->at(this->currentBufNum)->width()) / (bufSize.width());
        }
        clicked = true;
    }
}

void MainTabPage::mouseReleaseEvent(QMouseEvent *event){
    clicked = false;
}

void MainTabPage::paintEvent(QPaintEvent *event){
    if(clicked){
        QPainter painter(this->layerInfo->at(this->currentBufNum));
        painter.setRenderHint(QPainter::Antialiasing, true);
        int R, G, B;
        this->tools->brushW->getRGB(R,G,B);
        QPen paintPen(QColor(R,G,B));
        int size =0;
        this->tools->brushW->getSize(size);
        paintPen.setWidth(size);
        painter.setPen(paintPen);
        painter.drawPoint(originPos);
        QPixmap buf = sumBuff();
        this->setLayerPixel(&buf);
        //painter.end();
        update();
    }
}

QPixmap MainTabPage::sumBuff(){
    QPixmap buff;
    QPixmap *origin = this->layerInfo->at(this->currentBufNum);
    QImage* finalImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32_Premultiplied);
    for(int k = this->layerInfo->size()-1; k >= 0  ; k-- ){
        QImage tmp = this->layerInfo->at(k)->toImage();
        for(int i = 0; i<origin->width(); i++){
            for(int j=0; j<origin->height(); j++){
                if(tmp.pixelColor(i,j) == Qt::transparent)
                    continue;
                finalImage->setPixel(i,j, tmp.pixel(i,j));
            }
        }
    }
    buff = QPixmap::fromImage(*finalImage);
    return buff;
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
