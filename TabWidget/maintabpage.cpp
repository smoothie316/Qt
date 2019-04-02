#include "maintabpage.h"
#include "ui_maintabpage.h"

MainTabPage::MainTabPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTabPage)
{
    ui->setupUi(this);
}

MainTabPage::~MainTabPage()
{
    delete ui;
}

void MainTabPage::setImage(QPixmap* buffer){
    *buffer = buffer->scaled(this->width(), this->height(), Qt::KeepAspectRatio);
    ui->ImageLabel->setPixmap(*buffer);
    ui->ImageLabel->show();
}
