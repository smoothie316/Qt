#include "colorselect.h"
#include "ui_colorselect.h"

ColorSelect::ColorSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSelect)
{
    ui->setupUi(this);

    ui->widget->setStyleSheet(
    {

    }
    );
}

ColorSelect::~ColorSelect()
{
    delete ui;
}
