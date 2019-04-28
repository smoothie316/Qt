#include "seterasewidget.h"
#include "ui_seterasewidget.h"

setEraseWidget::setEraseWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setEraseWidget)
{
    ui->setupUi(this);

    ui->SizeSlider->setRange(1, 100);
    ui->SizeSlider->setValue(10);

    this->eraserSize = ui->SizeSlider->value();
    ui->SizeLineEdit->setText(QString::number(this->eraserSize));

    ui->CircleRadio->setChecked(this->circleChecked);
    ui->RectRadio->setChecked(this->rectChecked);
}

setEraseWidget::~setEraseWidget()
{
    delete ui;
}

void setEraseWidget::on_SizeSlider_sliderMoved(int position)
{
    this->eraserSize = position;
    ui->SizeLineEdit->setText(QString::number(this->eraserSize));
}

void setEraseWidget::on_CircleRadio_clicked()
{
    this->circleChecked = true;
    this->rectChecked = false;
}

void setEraseWidget::on_RectRadio_clicked()
{
    this->circleChecked = false;
    this->rectChecked = true;
}

void setEraseWidget::on_SizeLineEdit_editingFinished()
{

}

void setEraseWidget::on_pushButton_clicked()
{
    emit setEnd();
}
