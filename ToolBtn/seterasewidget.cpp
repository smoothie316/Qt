#include "seterasewidget.h"
#include "ui_seterasewidget.h"

setEraseWidget::setEraseWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setEraseWidget)
{
    ui->setupUi(this);
}

setEraseWidget::~setEraseWidget()
{
    delete ui;
}
