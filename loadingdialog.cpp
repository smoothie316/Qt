#include "loadingdialog.h"
#include "ui_loadingdialog.h"
#include <QLabel>
#include <QMovie>
#include <QFile>
#include <QBuffer>
#include <QDebug>

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
//    QString filePath = QApplication::applicationDirPath();

//    QMovie *Movie=new QMovie(filePath + "circleloader.gif");
//    ui->label->setMovie(Movie);
//    Movie->start();
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}
