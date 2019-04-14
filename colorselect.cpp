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
    ui->AlphaSlider->setRange(0,255);

    ui->RedSlider->setValue(0);
    ui->BlueSlider->setValue(0);
    ui->GreenSlider->setValue(0);
    ui->AlphaSlider->setValue(255);

    this->R = ui->RedSlider->value();
    this->B = ui->BlueSlider->value();
    this->G = ui->GreenSlider->value();
    this->alpha = ui->AlphaSlider->value();

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));
    ui->AlphaEdit->setText(QString::number(this->alpha));
}

ColorSelect::~ColorSelect()
{
    delete ui;
}

// getter
void ColorSelect::getRGB(int &R, int &G, int&B, int &A){
    R = this->R;
    G = this->G;
    B = this->B;
    A = this->alpha;
}

// setter
void ColorSelect::setRGB(int R, int G, int B, int A){
    this->R = R;
    this->G = G;
    this->B = B;
    this->alpha = A;

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));
    ui->AlphaEdit->setText(QString::number(this->alpha));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);
    ui->AlphaSlider->setValue(this->alpha);

    if(deleteCheck){
        switch(this->radioNumOld){
        case 0:
            ui->BlackRadioBtn->setChecked(true);            
            break;
        case 1:
            ui->RedRadioBtn->setChecked(true);
            break;
        case 2:
            ui->GreenRadioBtn->setChecked(true);
            break;
        case 3:
            ui->BlueRadioBtn->setChecked(true);
            break;
        case 4:
            ui->YellowRadioBtn->setChecked(true);
            break;
        }
    }
    this->radioNum = this->radioNumOld;

}

void ColorSelect::on_RedSlider_sliderMoved(int position)
{
    this->R = position;
    emit sliderMoved(this->R, 0);
    ui->RedEdit->setText(QString::number(this->R));
    this->removeCheck(this->radioNum);
}

void ColorSelect::on_GreenSlider_sliderMoved(int position)
{
    this->G = position;
    emit sliderMoved(this->G, 1);
    ui->GreenEdit->setText(QString::number(this->G));
    this->removeCheck(this->radioNum);
}

void ColorSelect::on_BlueSlider_sliderMoved(int position)
{
    this->B = position;
    emit sliderMoved(this->B, 2);
    ui->BlueEdit->setText(QString::number(this->B));
    this->removeCheck(this->radioNum);
}


void ColorSelect::on_AlphaSlider_sliderMoved(int position)
{
    this->alpha = position;
    emit sliderMoved(this->alpha, 3);
    ui->AlphaEdit->setText(QString::number(this->alpha));
    this->removeCheck(this->radioNum);
}

void ColorSelect::on_BlackRadioBtn_clicked()
{
    this->radioNum = 0;

    this->R = 0;
    this->G = 0;
    this->B = 0;
    emit radioClicked(this->R, this->G, this->B);

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);

    this->alpha=255;
    ui->AlphaEdit->setText(QString::number(this->alpha));
    ui->AlphaSlider->setValue(this->alpha);
}

void ColorSelect::on_RedRadioBtn_clicked()
{
    this->radioNum = 1;

    this->R = 255;
    this->G = 0;
    this->B = 0;
    emit radioClicked(this->R, this->G, this->B);

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);

    this->alpha=255;
    ui->AlphaEdit->setText(QString::number(this->alpha));
    ui->AlphaSlider->setValue(this->alpha);
}

void ColorSelect::on_GreenRadioBtn_clicked()
{
    this->radioNum = 2;

    this->R = 0;
    this->G = 255;
    this->B = 0;
    emit radioClicked(this->R, this->G, this->B);

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);

    this->alpha=255;
    ui->AlphaEdit->setText(QString::number(this->alpha));
    ui->AlphaSlider->setValue(this->alpha);
}

void ColorSelect::on_BlueRadioBtn_clicked()
{
    this->radioNum = 3;

    this->R = 0;
    this->G = 0;
    this->B = 255;
    emit radioClicked(this->R, this->G, this->B);

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);

    this->alpha=255;
    ui->AlphaEdit->setText(QString::number(this->alpha));
    ui->AlphaSlider->setValue(this->alpha);
}

void ColorSelect::on_YellowRadioBtn_clicked()
{
    this->radioNum = 4;

    this->R = 255;
    this->G = 255;
    this->B = 0;
    emit radioClicked(this->R, this->G, this->B);

    ui->RedEdit->setText(QString::number(this->R));
    ui->BlueEdit->setText(QString::number(this->B));
    ui->GreenEdit->setText(QString::number(this->G));

    ui->RedSlider->setValue(this->R);
    ui->BlueSlider->setValue(this->B);
    ui->GreenSlider->setValue(this->G);

    this->alpha=255;
    ui->AlphaEdit->setText(QString::number(this->alpha));
    ui->AlphaSlider->setValue(this->alpha);
}

void ColorSelect::removeCheck(int i){
    switch(i){
    case -1:
        break;
    case 0:
        // black
        this->deleteCheck = true;
        this->radioNumOld = i;
        ui->BlackRadioBtn->setAutoExclusive(false);
        ui->BlackRadioBtn->setChecked(false);
        ui->BlackRadioBtn->setAutoExclusive(true);
        this->radioNum = -1;
        break;
    case 1:
        // red
        this->deleteCheck = true;
        this->radioNumOld = i;
        ui->RedRadioBtn->setAutoExclusive(false);
        ui->RedRadioBtn->setChecked(false);
        ui->RedRadioBtn->setAutoExclusive(true);
        this->radioNum = -1;
        break;
    case 2:
        // green
        this->deleteCheck = true;
        this->radioNumOld = i;
        ui->GreenRadioBtn->setAutoExclusive(false);
        ui->GreenRadioBtn->setChecked(false);
        ui->GreenRadioBtn->setAutoExclusive(true);
        this->radioNum = -1;
        break;
    case 3:
        this->deleteCheck = true;
        this->radioNumOld = i;
        ui->BlueRadioBtn->setAutoExclusive(false);
        ui->BlueRadioBtn->setChecked(false);
        ui->BlueRadioBtn->setAutoExclusive(true);
        this->radioNum = -1;
        // blue
        break;
    case 4:
        this->deleteCheck = true;
        this->radioNumOld = i;
        ui->YellowRadioBtn->setAutoExclusive(false);
        ui->YellowRadioBtn->setChecked(false);
        ui->YellowRadioBtn->setAutoExclusive(true);
        this->radioNum = -1;
        // yellow
        break;
    }
}
