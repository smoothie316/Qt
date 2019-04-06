#include "setpaintwidget.h"
#include "ui_setpaintwidget.h"

SetPaintWidget::SetPaintWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPaintWidget)
{
    ui->setupUi(this);
    cs = new ColorSelect();
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(cs);
    ui->ColorBox->setLayout(grid);
}

SetPaintWidget::~SetPaintWidget()
{
    delete ui;
}
