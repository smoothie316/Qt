#include "colorselect.h"
#include "ui_colorselect.h"

ColorSelect::ColorSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSelect)
{
    ui->setupUi(this);

    ui->RedSlider->setRange(0,255);
    ui->BlueSlider->setRange(0,255);
    ui->GreenSlider->setRange(0,255);

    ui->RedSlider->setValue(0);
    ui->BlueSlider->setValue(0);
    ui->GreenSlider->setValue(0);

    this->R = ui->RedSlider->value();
    this->B = ui->BlueSlider->value();
    this->G = ui->GreenSlider->value();

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));
}

ColorSelect::~ColorSelect()
{
    delete ui;
}

void ColorSelect::on_RedSlider_sliderMoved(int position)
{
    this->R = position;
    ui->RedEdit->setText(QString::number(this->R));
}

void ColorSelect::on_GreenSlider_sliderMoved(int position)
{
    this->G = position;
    ui->GreenEdit->setText(QString::number(this->G));
}

void ColorSelect::on_BlueSlider_sliderMoved(int position)
{
    this->B = position;
    ui->BlueEdit->setText(QString::number(this->B));
}

void ColorSelect::on_BlackRadioBtn_clicked()
{
    this->R = 0;
    this->G = 0;
    this->B = 0;

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);
}

void ColorSelect::on_RedRadioBtn_clicked()
{
    this->R = 255;
    this->G = 0;
    this->B = 0;

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);
}

void ColorSelect::on_GreenRadioBtn_clicked()
{
    this->R = 0;
    this->G = 255;
    this->B = 0;

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);
}

void ColorSelect::on_BlueRadioBtn_clicked()
{
    this->R = 0;
    this->G = 0;
    this->B = 255;

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);
}

void ColorSelect::on_YellowRadioBtn_clicked()
{
    this->R = 255;
    this->G = 255;
    this->B = 0;

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);
}
