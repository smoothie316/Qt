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

    connect(this, SIGNAL(drawEnd()), parent, SLOT(drawEnd()));

    this->buf= nullptr;
    this->clickedTool = 1;
    this->setMouseCursor();
    this->w = 0;
    this->h = 0;
    originPos = QPoint(0,0);
    prevPos = QPoint(0,0);
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
    //layer->installEventFilter(this);
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
    this->prevPos = QPoint(0,0);
    if(event->button() == Qt::LeftButton){
        //prevPos = event->pos();
        if(this->layerInfo->at(this->currentBufNum)->width() > this->layerInfo->at(this->currentBufNum)->height()){
            QSize widgetSize = this->layerSet.at(0)->size();
            //qDebug() << widgetSize;
            double ratio = bufSize.height() / (double)widgetSize.height();
            //qDebug() << ratio;
            originPos.setY((int)(event->y() - ((widgetSize.height()-bufSize.height())/2)));
            originPos.setX(event->x());
        }
        else {
            double ratio = (this->layerInfo->at(this->currentBufNum)->width()) / (bufSize.width());
        }
        //originPos = event->pos();
        clicked = true;
        qDebug() << "clicked";
    }
}

void MainTabPage::mouseMoveEvent(QMouseEvent *event){

    if((event->buttons() & Qt::LeftButton)){
        if(this->layerInfo->at(this->currentBufNum)->width() > this->layerInfo->at(this->currentBufNum)->height()){
            QSize widgetSize = this->layerSet.at(0)->size();
            double ratio = bufSize.height() / (double)widgetSize.height();
            //int y= event->y() - ((widgetSize.height()-bufSize.height())/2);
            prevPos = originPos;
            originPos.setY((int)(event->y() - ((widgetSize.height()-bufSize.height())/2)));
            originPos.setX(event->x());
        }
        else {
            double ratio = (this->layerInfo->at(this->currentBufNum)->width()) / (bufSize.width());
        }
        clicked = true;
    }
}

void MainTabPage::mouseReleaseEvent(QMouseEvent *event){
    clicked = false;
    emit drawEnd();
}

void MainTabPage::paintEvent(QPaintEvent *event){
    QPixmap* tmpBuf = this->layerInfo->at(this->currentBufNum);
    *tmpBuf = tmpBuf->scaled(bufSize.width(), bufSize.height(), Qt::KeepAspectRatio);
    if(clicked && this->clickedTool == 1){
        QPainter painter(tmpBuf);
        painter.setRenderHint(QPainter::Antialiasing, true);
        this->tools->brushW->getRGB(R,G,B);
        this->tools->brushW->getSize(this->penSize);

        this->draw(painter);

        QPixmap buff = sumBuff();
        this->setLayerPixel(&buff);
    }

    if(clicked && this->clickedTool == 4){
//        QPixmap* eraseInfo = new QPixmap(tmpBuf->width(), tmpBuf->height());
//        eraseInfo->fill(Qt::transparent);
        QPainter painter(tmpBuf);
        painter.setRenderHint(QPainter::Antialiasing, true);
        this->penSize = this->tools->eraseW->eraserSize;
        this->R = 255;
        this->G = 255;
        this->B = 255;
        this->penColor.setRgb(this->R, this->G, this->B);

        this->draw(painter);

        QPixmap buff= sumBuff();
        this->setLayerPixel(&buff);
    }
}

void MainTabPage::draw(QPainter &painter){
    this->penColor.setRgb(this->R, this->G, this->B);
    this->paintPen.setColor(this->penColor);
    this->paintPen.setWidth(this->penSize);
    painter.setPen(this->paintPen);
    if(prevPos == QPoint(0,0))
        return;
    painter.drawLine(this->prevPos, this->originPos);

    update();
}

QPixmap MainTabPage::sumBuff(){
    QPixmap buff;
    QPixmap *origin = this->layerInfo->at(0);
    QImage* finalImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32_Premultiplied);
    finalImage->fill(Qt::transparent);
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
    label->clear();
    label->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));
    update();
}
