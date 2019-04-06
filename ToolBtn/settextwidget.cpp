#include "settextwidget.h"
#include "ui_settextwidget.h"

SetTextWidget::SetTextWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTextWidget)
{
    ui->setupUi(this);
}

SetTextWidget::~SetTextWidget()
{
    delete ui;
}
