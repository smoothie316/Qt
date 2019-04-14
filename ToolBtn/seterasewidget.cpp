#include "seterasewidget.h"
#include "ui_seterasewidget.h"

setEraseWidget::setEraseWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setEraseWidget)
{
    ui->setupUi(this);

    ui->SizeSlider->setRange(1, 100);
    ui->SizeSlider->setValue(10);

    this->sliderPos = ui->SizeSlider->value();
    ui->SizeLineEdit->setText(QString::number(this->sliderPos));
}

setEraseWidget::~setEraseWidget()
{
    delete ui;
}

void setEraseWidget::on_SizeSlider_sliderMoved(int position)
{
    this->sliderPos = position;
    ui->SizeLineEdit->setText(QString::number(this->sliderPos));
}

void setEraseWidget::on_CircleRadio_clicked()
{

}

void setEraseWidget::on_RectRadio_clicked()
{

}

void setEraseWidget::on_SizeLineEdit_editingFinished()
{

}
