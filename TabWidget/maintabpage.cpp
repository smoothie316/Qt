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
                dbClicked = true;
                QString style= " ";
                QLabel* tmpLabel = this->textSet.at(this->activeText);
                tmpLabel->setStyleSheet(style);
                this->textInputStart = false;
                this->textInput = false;
                this->originPos = QPoint(0,0);
                this->prevPos = QPoint(0,0);
            }
        }
    }
    return QWidget::eventFilter(object, event);
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
    if(ctrlKey){
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
}

void MainTabPage::mousePressEvent(QMouseEvent *event){
    this->prevPos = QPoint(0,0);
    QSize widgetSize = this->layerSet.at(0)->size();
    if(event->button() == Qt::LeftButton){
        if(this->layerInfo->at(this->currentBufNum)->width() > this->layerInfo->at(this->currentBufNum)->height()){
            //double ratio = bufSize.height() / (double)widgetSize.height();
            originPos.setY((int)(event->y() - ((widgetSize.height()-bufSize.height())/2)));
            originPos.setX(event->x());
        }
        else {
            //double ratio = bufSize.width() / (double)widgetSize.width();
            originPos.setX((int)(event->x() - ((widgetSize.width()-bufSize.width())/2)));
            originPos.setY(event->y());
        }
        clicked = true;

        if(this->clickedTool == 3 && !textInput){
            this->textStart = event->pos();
        }
    }
}

void MainTabPage::mouseMoveEvent(QMouseEvent *event){
    QSize widgetSize = this->layerSet.at(0)->size();
    if((event->buttons() & Qt::LeftButton)){
        if(this->layerInfo->at(this->currentBufNum)->width() > this->layerInfo->at(this->currentBufNum)->height()){
            //double ratio = bufSize.height() / (double)widgetSize.height();
            prevPos = originPos;
            originPos.setY((int)(event->y() - ((widgetSize.height()-bufSize.height())/2)));
            originPos.setX(event->x());
        }
        else {
            //double ratio = bufSize.width() / (double)widgetSize.width();
            originPos.setX((int)(event->x() - ((widgetSize.width()-bufSize.width())/2)));
            originPos.setY(event->y());
        }
        clicked = true;
        if(this->clickedTool == 1){
            // brush
            QPixmap* tmpBuf = this->layerInfo->at(this->currentBufNum);
            *tmpBuf = tmpBuf->scaled(bufSize.width(), bufSize.height(), Qt::KeepAspectRatio);
            QPainter painter(tmpBuf);
            int R, G, B, size;
            this->tools->brushW->getRGB(R, G, B);
            this->tools->brushW->getSize(size);
            this->draw(painter, R, G, B, size);
        }
        else if(this->clickedTool == 4){
            // eraser
            QPixmap* tmpBuf = this->layerInfo->at(this->currentBufNum);
            *tmpBuf = tmpBuf->scaled(bufSize.width(), bufSize.height(), Qt::KeepAspectRatio);
            QPainter painter(tmpBuf);
            this->draw(painter, 255, 255, 255, this->tools->eraseW->eraserSize);
        }
        if(this->clickedTool == 3 && !textInput){
            this->textEnd = event->pos();
        }
    }
    this->update();
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
            this->textSet.at(this->activeText)->setStyleSheet(style2);
        text->setStyleSheet(style);
        if(this->tools->textW->isFontChanged)
            text->setFont(this->tools->textW->textFont);
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

//void MainTabPage::setTextColor(QLabel* text){
//    QBrush* textBrush = new QBrush(QColor(this->tools->textW->textR, this->tools->textW->textG, this->tools->textW->textB, this->tools->textW->textA));
//    QBrush* back = new QBrush(QColor(this->tools->textW->backR, this->tools->textW->backG, this->tools->textW->backB, this->tools->textW->backA));
//    textBrush->setStyle(Qt::SolidPattern);
//    back->setStyle(Qt::SolidPattern);

//    QPalette pText;
//    QPalette pBack;

//    pText.setBrush(QPalette::Active, QPalette::WindowText, *(textBrush));
//    pText.setBrush(QPalette::Inactive, QPalette::WindowText, *(textBrush));

//    pBack.setBrush(QPalette::Active, QPalette::Window, *(back));
//    pBack.setBrush(QPalette::Inactive, QPalette::Window, *(back));

//    text->setPalette(pText);
//    text->show();
//    text->setPalette(pBack);
//    text->show();
//}

//void MainTabPage::paintEvent(QPaintEvent *event){

//}

void MainTabPage::draw(QPainter &painter, int R, int G, int B, int size){
    painter.setRenderHint(QPainter::Antialiasing, true);
    this->penSize = size;
    this->R = R;
    this->G = G;
    this->B = B;
    this->penColor.setRgb(this->R, this->G, this->B);
    this->penColor.setRgb(this->R, this->G, this->B);
    this->paintPen.setColor(this->penColor);
    this->paintPen.setWidth(this->penSize);
    painter.setPen(this->paintPen);
    if(prevPos == QPoint(0,0))
        return;
    painter.drawLine(this->prevPos, this->originPos);

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
    int w = label->width();
    int h = label->height();
    label->clear();
    label->setPixmap(buf->scaled(w,h, Qt::KeepAspectRatio));
    update();
}

void MainTabPage::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        pixmap.save("debug/test.png","PNG");


        /*QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);*/

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

