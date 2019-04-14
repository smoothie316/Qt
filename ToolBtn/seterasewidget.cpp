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
    this->newEraserSize = position;
    ui->SizeLineEdit->setText(QString::number(this->newEraserSize));
}

void setEraseWidget::on_CircleRadio_clicked()
{
    this->newCircleChecked = true;
    this->newRectChecked = false;
}

void setEraseWidget::on_RectRadio_clicked()
{
    this->newCircleChecked = false;
    this->newRectChecked = true;
}

void setEraseWidget::on_SizeLineEdit_editingFinished()
{

}

void setEraseWidget::on_buttonBox_accepted()
{
    this->circleChecked = this->newCircleChecked;
    this->rectChecked = this->newRectChecked;

    this->eraserSize = this->newEraserSize;
}

void setEraseWidget::on_buttonBox_rejected()
{
    ui->CircleRadio->setChecked(this->circleChecked);
    ui->RectRadio->setChecked(this->rectChecked);

    ui->SizeLineEdit->setText(QString::number(this->eraserSize));
    ui->SizeSlider->setValue(this->eraserSize);
}

void setEraseWidget::closeEvent(QCloseEvent *event){
    this->on_buttonBox_rejected();
}
