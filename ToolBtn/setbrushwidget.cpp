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

    ui->SizeSlider->setRange(1,255);
    ui->SizeSlider->setValue(1);

    this->sliderPos = ui->SizeSlider->value();
    ui->SizeLineEdit->setText(QString::number(this->sliderPos));
}

SetBrushWidget::~SetBrushWidget()
{
    delete ui;
}

void SetBrushWidget::on_SizeSlider_sliderMoved(int position)
{
    this->sliderPos = position;
    ui->SizeLineEdit->setText(QString::number(this->sliderPos));
}
