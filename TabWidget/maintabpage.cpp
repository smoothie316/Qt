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
    connect(this, SIGNAL(addTextLayer(QPixmap*, QLabel*)), parent, SLOT(addTextLayer(QPixmap*, QLabel*)));
    connect(this, SIGNAL(currentBufSize(QSize)), parent, SLOT(currentBufSize(QSize)));

    this->buf= nullptr;
    this->clickedTool = 1;
    this->setMouseCursor();
    this->w = 0;
    this->h = 0;
    originPos = QPoint(0,0);
    prevPos = QPoint(0,0);

    setAcceptDrops(true);
}

MainTabPage::~MainTabPage()
{
    delete ui;
}

void MainTabPage::setImage(QPixmap* buffer, int w, int h){
    this->buf = buffer;
    QLabel* layer = new QLabel();

    // layeri event관련 설정
    layer->installEventFilter(this);
    layer->setMouseTracking(true);

    // 화면에 맞춰 조절하여 출력
    layer->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));
    layer->setObjectName("canvas");

    ui->MainEdit->setWidget(layer);
    this->layerSet.push_back(layer);

    qDebug() << "set Image";
    qDebug() << bufSize;
}

void MainTabPage::resizeEvent(QResizeEvent *event){
    this->w = event->size().width();
    this->h = event->size().height();

    qDebug() << "resize";
    // 해상도 저하
    if(!layerSet.empty()){
        for(size_t i=0; i<layerSet.size(); i++){
            //layerSet[i]->setGeometry(0,0,w,h);
            layerSet[i]->clear();
            layerSet[i]->setPixmap(buf->scaled(w,h,Qt::KeepAspectRatio));
            this->bufSize = buf->scaled(w,h,Qt::KeepAspectRatio).size();
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

        }
    }
    else {
        QStringList list = object->objectName().split("_");
        if(list[0] == "text"){
            if(event->type() == QMouseEvent::MouseButtonPress){
                // 텍스트 입력시 입력되게
                this->textInputStart = true;
            }
            if(event->type() == QMouseEvent::MouseButtonDblClick){
                // layer 저장
                QString style= " ";
                QLabel* tmpLabel = this->textSet.at(this->activeText);
                tmpLabel->setStyleSheet(style);

                this->createTextLayerPix();
                emit addTextLayer(this->textPix, tmpLabel);

                this->dbClicked = true;
                this->textInputStart = false;
                this->textInput = false;
                this->originPos = QPoint(0,0);
                this->prevPos = QPoint(0,0);
            }
        }
        else if(list[0] == "icon"){
            this->currentIconNum = list[1].toInt();
            if(event->type() == QMouseEvent::MouseButtonPress){
                this->iconClicked = true;
            }
            if(event->type() == QMouseEvent::MouseButtonDblClick){
                QString style = "";
                this->iconSet.at(this->currentIconNum)->setStyleSheet(style);
                QLabel* tmpLabel = new QLabel();
                this->createIconLayerPix();
                emit addTextLayer(this->clickedIcon, tmpLabel);
                this->iconSet.at(this->currentIconNum)->setVisible(false);
                this->iconClicked = false;
            }
        }
    }
    return QWidget::eventFilter(object, event);
}

void MainTabPage::createTextLayerPix(){
    changePoint(this->textStart);
    changePoint(this->textEnd);
    QPixmap *origin = this->layerInfo->at(0);
    QSize originSize = origin->size();

    QImage* finalImg = new QImage(originSize, QImage::Format_ARGB32);
    finalImg->fill(Qt::transparent);
    int w = abs(this->textStart.x() - this->textEnd.x());
    int h = abs(this->textStart.y() - this->textEnd.y());
    QImage tmp = this->textPix->scaled(w,h,Qt::KeepAspectRatio).toImage();
    int x = 0, y = 0;
    for(int i = min(this->textStart.x(), this->textEnd.x()); i<max(this->textStart.x(),this->textEnd.x()); i++){
        for(int j = min(this->textStart.y(), this->textEnd.y()); j < max(this->textStart.y(), this->textEnd.y()); j++){
            finalImg->setPixel(i,j,tmp.pixel(x,y));
            y++;
        }
        x++;
        y = 0;
    }
    *this->textPix = QPixmap::fromImage(*finalImg);
}

void MainTabPage::createIconLayerPix(){
    QPoint endPoint = this->droppedPoint;
    endPoint.setX(endPoint.x() + iconSize.width());
    endPoint.setY(endPoint.y() + iconSize.height());
    changePoint(this->droppedPoint);
    changePoint(endPoint);

    QPixmap *origin = this->layerInfo->at(0);
    QSize originSize = origin->size();

    QImage* finalImg = new QImage(originSize, QImage::Format_ARGB32);
    finalImg->fill(Qt::transparent);
    int w = abs(this->droppedPoint.x() - endPoint.x());
    int h = abs(this->droppedPoint.y() - endPoint.y());
    QImage tmp = this->iconPixSet.at(this->currentIconNum).scaled(w,h,Qt::KeepAspectRatio).toImage();
    int x =0; int y= 0;
    for(int i=this->droppedPoint.x(); i< endPoint.x(); i++){
        for(int j=this->droppedPoint.y(); j<endPoint.y(); j++){
            finalImg->setPixel(i,j,tmp.pixel(x,y));
            y++;
        }
        x++;
        y= 0;
    }
    this->clickedIcon = new QPixmap(originSize);
    *this->clickedIcon = QPixmap::fromImage(*finalImg);
}

void MainTabPage::keyPressEvent(QKeyEvent *event){
    if(event->modifiers() == Qt::CTRL)
        ctrlKey = true;
    if(textInputStart){
        QLabel* tmpLabel = this->textSet.at(this->activeText);
        QString textInputted = this->inputtedTextList.at(this->activeText);
        if(event->key() == Qt::Key_Backspace){
            textInputted = textInputted.mid(0, textInputted.length()-1);
        }
        else if(event->key() == Qt::Key_Enter){
            textInputted += "\n";
        }
        else{
           textInputted += event->text();
        }
        this->inputtedTextList.at(this->activeText) = textInputted;

        this->textPix = new QPixmap(tmpLabel->width(), tmpLabel->height());
        this->textPix->fill(Qt::transparent);

        QPainter painter(this->textPix);
        int R, G, B, A;
        R = this->tools->textW->textR;
        G = this->tools->textW->textG;
        B = this->tools->textW->textB;
        A = this->tools->textW->textA;
        painter.setPen(QColor(R,G,B,A));
        painter.setFont(this->tools->textW->textFont);

        QRect rect(0,0, tmpLabel->width(), tmpLabel->height());
        painter.drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, textInputted);
        painter.end();

        tmpLabel->setPixmap(*(this->textPix));
        tmpLabel->show();
    }
}
void MainTabPage::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Control){
        ctrlKey = false;
    }
}
void MainTabPage::wheelEvent(QWheelEvent *event){
    if(ctrlKey && this->clickedTool == 6){
        const double degree = event->delta() / 12.0;
        int w = this->w * (degree/100);
        int h = this->h * (degree/100);
        w += this->w;
        h += this->h;
        this->w = w;
        this->h = h;
        for(int i=0; i<this->layerSet.size(); i++){
            this->layerSet[i]->clear();
            this->layerSet[i]->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));
            bufSize = buf->scaled(w,h,Qt::KeepAspectRatio).size();
        }
    }
    else if(ctrlKey && this->clickedTool == 0){
        const double degree = event->delta() / 12.0;
        int w = this->iconSize.width() * (degree/100.0);
        int h = this->iconSize.height() * (degree/100.0);

        w += iconSize.width();
        h += iconSize.height();

        iconSize.setWidth(w);
        iconSize.setHeight(h);

        QLabel* tmpLayer = this->iconSet.at(this->currentIconNum);
        tmpLayer->clear();
        QPoint tmp = this->droppedPoint;
        tmp.setX(tmp.x() + iconSize.width());
        tmp.setY(tmp.y() + iconSize.height());
        QRect iconRect(this->droppedPoint, tmp);
        tmpLayer->setGeometry(iconRect);
        tmpLayer->setPixmap(iconPixSet.at(this->currentIconNum).scaled(w,h, Qt::KeepAspectRatio));
        tmpLayer->show();

        //qDebug() << "wheel";
    }

}

void MainTabPage::changePoint(QPoint &point){
    QSize widgetSize = this->layerSet.at(0)->size();
    if(this->bufSize.width() > this->bufSize.height()){
        point.setY((int)point.y() - ((widgetSize.height()- bufSize.height())/2));
        double ratio = (double)(this->layerInfo->at(0)->size().height()) / (double)bufSize.height();
        point.setX((int)(point.x() * ratio));
        point.setY((int)(point.y() * ratio));
    }
    else{
        point.setX((int)point.x() - ((widgetSize.width() - bufSize.width())/2));
        double ratio = (double)(this->layerInfo->at(0)->size().height()) / (double)bufSize.height();
        point.setX((int)(point.x() * ratio));
        point.setY((int)(point.y() * ratio));
    }
}

void MainTabPage::mousePressEvent(QMouseEvent *event){
    this->prevPos = QPoint(0,0);
    if(event->button() == Qt::LeftButton){
        this->originPos = event->pos();
        changePoint(this->originPos);

        clicked = true;
        qDebug() << "test";
        if(this->clickedTool == 3 && !textInput){
            this->textStart = event->pos();
        }
    }
}

void MainTabPage::mouseMoveEvent(QMouseEvent *event){
    if((event->buttons() & Qt::LeftButton)){
        this->prevPos = this->originPos;
        this->originPos = event->pos();
        changePoint(this->originPos);

        clicked = true;
        qDebug() << "test";
        if(this->clickedTool == 1){
            // brush
            QPixmap* tmpBuf = this->layerInfo->at(this->currentBufNum);
            //QPixmap paintBuf = tmpBuf->scaled(bufSize.width(), bufSize.height(), Qt::KeepAspectRatio);
            QPainter painter(tmpBuf);
            int R, G, B, size;
            this->tools->brushW->getRGB(R, G, B);
            this->tools->brushW->getSize(size);
            this->draw(painter, R, G, B, size);
        }
        else if(this->clickedTool == 4){
            // eraser
            QPixmap* tmpBuf = this->layerInfo->at(this->currentBufNum);
            QPainter painter(tmpBuf);
            this->draw(painter, 255, 255, 255, this->tools->eraseW->eraserSize);
        }
        if(this->clickedTool == 3 && !textInput){
            this->textEnd = event->pos();
        }
    }
    //this->update();
}

void MainTabPage::mouseReleaseEvent(QMouseEvent *event){
    clicked = false;
    if(this->clickedTool == 1 || this->clickedTool == 4)
        emit drawEnd();
    if(this->clickedTool == 3 && !dbClicked){
        this->originPos = QPoint(0,0);
        this->prevPos = QPoint(0,0);

        QString style = "border-color:rgb(0,0,0); border-width:1.2px; border-style:solid;";
        QString style2 = "";
        QLabel* text = new QLabel(this);
        text->installEventFilter(this);
        text->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        QRect textRect(this->textStart, this->textEnd);
        text->setGeometry(textRect);
        if(this->activeText != -1)
            this->textSet.at(this->activeText)->setVisible(false);
        text->setStyleSheet(style);
        text->show();
        this->activeText = this->textSet.size();
        text->setObjectName("text_"+QString::number(this->activeText));
        this->textSet.push_back(text);
        this->inputtedTextList.push_back("");
        this->textInput = true;
    }
    else if(dbClicked)
        dbClicked = false;
}


void MainTabPage::draw(QPainter &painter, int R, int G, int B, int size){
    painter.setRenderHint(QPainter::Antialiasing, true);
    this->penSize = size;
    this->R = R;
    this->G = G;
    this->B = B;
    this->penColor.setRgb(this->R, this->G, this->B);
    this->paintPen.setColor(this->penColor);
    this->paintPen.setWidth(this->penSize);
    painter.setPen(this->paintPen);
    if(prevPos == QPoint(0,0))
        return;
    painter.drawLine(this->prevPos, this->originPos);
    painter.end();
    QPixmap buff= sumBuff();
    this->setLayerPixel(&buff);
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
    //*this->buf = buf->copy();
    //this->buf = buf;
    int w = label->width();
    int h = label->height();
    label->clear();
    label->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));
    update();
}

void MainTabPage::dropEvent(QDropEvent *event)
{
    // 저장하는 코드 작성
    // 저장되는 QPoint : 원래 mainTabPage 좌표
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        //pixmap.save("debug/test.png","PNG");

        this->droppedPoint = event->pos();
        QPoint tmp = droppedPoint;
        this->iconSize = pixmap.size();
        tmp.setX(tmp.x() + iconSize.width());
        tmp.setY(tmp.y() + iconSize.height());
        qDebug() << droppedPoint;
        QString style = "border-color:rgb(0,0,0); border-width:1.2px; border-style:solid;";
        QLabel* icon = new QLabel(this);
        icon->setObjectName("icon_"+QString::number(++this->currentIconNum));
        icon->installEventFilter(this);
        icon->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

        QRect iconRect(droppedPoint, tmp);
        icon->setGeometry(iconRect);
        icon->setStyleSheet(style);
        icon->setPixmap(pixmap);
        icon->show();

        this->iconSet.push_back(icon);
        this->iconPixSet.push_back(pixmap);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MainTabPage::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MainTabPage::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {

            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

