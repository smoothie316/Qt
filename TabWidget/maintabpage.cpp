#include "maintabpage.h"
#include "ui_maintabpage.h"

#include <QLabel>
#include <QSizePolicy>
#include <QMessageBox>


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

void MainTabPage::setImage(QPixmap* buffer, int w, int h){
    *buffer = buffer->scaled(w,h, Qt::KeepAspectRatio);
    QLabel* layer0  = new QLabel(this->ui->MainEditContents);
    layer0->setPixmap(*buffer);
    layer0->show();

}
