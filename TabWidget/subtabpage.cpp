#include "subtabpage.h"
#include "ui_subtabpage.h"
#include <QDebug>
#include <QGridLayout>

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
    for(int i=0; i<10; i++){
        QImage *img = new QImage();
        QPixmap* buf=  new QPixmap();
        dir = QCoreApplication::applicationDirPath() +  name + QString::number(i) + ".jpg";
        if(img->load(dir)){
            *buf = QPixmap::fromImage(*img);
            QLabel* layer = new QLabel();
            layer->setMouseTracking(true);
            layer->setPixmap(*buf);
            layer->show();
            this->imgList.push_back(layer);

            grid->addWidget(layer);
        }
        else {
        }
    }
    //ui->SubContentsArea->setLayout(grid);
}
