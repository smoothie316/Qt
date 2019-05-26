#include "subtabpage.h"
#include "ui_subtabpage.h"
#include <QDebug>
#include <QGridLayout>
#include <QFile>
#include <string>
#include <io.h>
#include <conio.h>

SubTabPage::SubTabPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubTabPage)
{
    ui->setupUi(this);
}

SubTabPage::~SubTabPage()
{
    delete ui;
}

void SubTabPage::setImage(QString name){
    QString dir;
    QGridLayout *grid = new QGridLayout(ui->SubContentsArea);
    int column = 0;
    int row = 0;
    dir = QCoreApplication::applicationDirPath() + "/" + name + "/" + "*.*";
    int total = countFileNum(dir);
    for(int i=0; i<total; i++){
        QImage *img = new QImage();
        QPixmap* buf=  new QPixmap();
        dir = QCoreApplication::applicationDirPath() + "/" + name + "/" + this->fileName[i];
        if(img->load(dir)){
            *buf = QPixmap::fromImage(img->scaled(150,150, Qt::KeepAspectRatio));
            QLabel* layer = new QLabel();
            layer->installEventFilter(this);
            layer->setMouseTracking(true);
            layer->setPixmap(*buf);
            layer->setObjectName(QString::number(i));
            //layer->show();
            this->imgList.push_back(layer);
            grid->addWidget(layer, row, column++);
            if(column == 3){
                column = 0;
                row += 1;
            }
            bufList.push_back(buf);
        }
        else {
        }
    }
    //ui->SubContentsArea->setLayout(grid);
}

bool SubTabPage::eventFilter(QObject *object, QEvent *event){
    if(event->type()== QMouseEvent::MouseButtonPress){
        clicked = true;
    }
    if(event->type() == QMouseEvent::MouseButtonRelease){
        clicked = false;
    }
    return QWidget::eventFilter(object, event);
}

void SubTabPage::mouseMoveEvent(QMouseEvent *event){
    if(clicked){
        qDebug() << event->pos();
    }
}


int SubTabPage::countFileNum(QString dir){
    int count = 0;
    _finddata_t fd;
    intptr_t handle;
    int result = 1;

    string _str = dir.toStdString();

    handle = _findfirst(_str.c_str(), &fd);

    if(handle == -1){

    }
    while(result != -1){
        result = _findnext(handle, &fd);
        if(strcmp(fd.name, ".") == 0 || strcmp(fd.name, "..") == 0 || strcmp(fd.name, "") == 0)
            continue;
        count++;
        this->fileName.push_back(QString(fd.name));
    }
    _findclose(handle);


    return count;
}

