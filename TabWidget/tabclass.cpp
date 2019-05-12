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
            *buffer = QPixmap::fromImage(*img);
            *buffer = buffer->scaled(img->width(), img->height(), Qt::KeepAspectRatio);
            bufferList.push_back(buffer);
            emit addBuff();
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
