#include "colorselect.h"
#include "ui_colorselect.h"

ColorSelect::ColorSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSelect)
{
    ui->setupUi(this);
}

ColorSelect::~ColorSelect()
{
    delete ui;
}
