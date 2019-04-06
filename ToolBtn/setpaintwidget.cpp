#include "setpaintwidget.h"
#include "ui_setpaintwidget.h"

SetPaintWidget::SetPaintWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPaintWidget)
{
    ui->setupUi(this);
}

SetPaintWidget::~SetPaintWidget()
{
    delete ui;
}
