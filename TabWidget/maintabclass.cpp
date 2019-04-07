#include "TabWidget/maintabclass.h"
#include <QMessageBox>

MainTabClass::MainTabClass(QWidget *parent) : QTabWidget(parent)
{
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequested(int)));
}

void MainTabClass::createImage(QStringList imageList){
    QMessageBox msg;
    int cnt = imageList.length();
    for(int i = 0; i < cnt; i++){

        QImage *img = new QImage();
        QPixmap *buffer = new QPixmap();

        if(img->load(imageList[i])){
            *buffer = QPixmap::fromImage(*img);
            *buffer = buffer->scaled(img->width(), img->height());
        }
        else{
            // 파일 열기 싫패
        }

        page = new MainTabPage();
        page->setImage(buffer, this->width(), this->height());
        this->addTab(page, imageList[i]);

    }
}


void MainTabClass::tabCloseRequested(int i){
    this->removeTab(i);
}
