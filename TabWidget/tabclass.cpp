#include "tabclass.h"

#include <QDebug>
#include <QPixmap>
#include <QImage>

TabClass::TabClass(QWidget *parent) : QWidget(parent)
{

}

void TabClass::mainCreateImage(QStringList imageList){
    int cnt = imageList.length();
    for(int i=0; i<cnt; i++){
        QImage *img = new QImage();
        QPixmap *buffer = new QPixmap();

        if(img->load(imageList[i])){
            QImage tmpImg =img->convertToFormat(QImage::Format_ARGB32_Premultiplied);
            qDebug() << tmpImg.alphaChannel();
            *buffer = QPixmap::fromImage(tmpImg);
            *buffer = buffer->scaled(tmpImg.width(), tmpImg.height(), Qt::KeepAspectRatio);
            this->bufferList.push_back(buffer);
        }
        else{
            // 파일 열기 실패
        }

        mainPage = new MainTabPage();
        mainPage->setImage(buffer, this->width(), this->height());
        mainPageList.push_back(mainPage);
        emit this->addMainTab(mainPage, imageList[i]);
    }
}

void TabClass::subTabCreate(QString name){
    subPage = new SubTabPage();
    subPage->setImage(name);
    this->subPageList.push_back(subPage);
    emit this->addSubTab(subPage, name);
}

void TabClass::getAllBuffList(vector<QPixmap *> &buffList){
    buffList.assign(this->bufferList.begin(), this->bufferList.end());
}

void TabClass::getBuff(QPixmap*& buff, int index){
    buff = this->bufferList.at(index);
}

void TabClass::setAllBuffList(vector<QPixmap *> buffList){
    this->bufferList.assign(buffList.begin(), buffList.end());
}

void TabClass::resetPixmap(QPixmap* buf, int pageNum){
    this->mainPage = this->mainPageList[pageNum];
    this->mainPage->setLayerPixel(buf);

}
