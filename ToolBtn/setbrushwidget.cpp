#include "setbrushwidget.h"
#include "ui_setbrushwidget.h"

SetBrushWidget::SetBrushWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetBrushWidget)
{
    ui->setupUi(this);
    cs = new ColorSelect();
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(cs);
    ui->ColorBox->setLayout(grid);
}

SetBrushWidget::~SetBrushWidget()
{
    delete ui;
}
