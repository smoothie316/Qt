#include "setbrushwidget.h"
#include "ui_setbrushwidget.h"

#include <QDebug>

SetBrushWidget::SetBrushWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetBrushWidget)
{
    ui->setupUi(this);
    cs = new ColorSelect();
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(cs);
    ui->ColorBox->setLayout(grid);
    cs->getRGB(this->R, this->G, this->B, this->A);
    cs->getRGB(this->newR, this->newG, this->newB, this->newA);

    ui->SizeSlider->setRange(1,100);
    ui->SizeSlider->setValue(10);
    this->brushSize = ui->SizeSlider->value();
    this->newBrushSize = this->brushSize;
    ui->SizeLineEdit->setText(QString::number(this->brushSize));
    qDebug() << this->brushSize;
    connect(cs, SIGNAL(sliderMoved(int, int)), this, SLOT(RGBSliderMoved(int, int)));
    connect(cs, SIGNAL(radioClicked(int, int, int)), this, SLOT(colorRadioClicked(int, int, int)));
}

SetBrushWidget::~SetBrushWidget()
{
    delete ui;
}

void SetBrushWidget::on_SizeSlider_sliderMoved(int position)
{
    this->newBrushSize = position;
    ui->SizeLineEdit->setText(QString::number(this->newBrushSize));
}

void SetBrushWidget::RGBSliderMoved(int position, int RGBInfo){
    switch(RGBInfo){
    case 0:
        this->newR = position;
        break;
    case 1:
        this->newG = position;
        break;
    case 2:
        this->newB = position;
        break;
    case 3:
        this->newA = position;
        break;
    }
    qDebug() << QString::number(newR) + ", " + QString::number(newG) + ", " + QString::number(newB);
}

void SetBrushWidget::colorRadioClicked(int R, int G, int B){
    this->newR = R;
    this->newG = G;
    this->newB = B;
    this->newA = 255;
    qDebug() << QString::number(newR) + ", " + QString::number(newG) + ", " + QString::number(newB);
}

void SetBrushWidget::on_buttonBox_accepted(){
    this->R = this->newR;
    this->G = this->newG;
    this->B = this->newB;
    this->A = this->newA;
    this->brushSize = this->newBrushSize;
}

void SetBrushWidget::on_buttonBox_rejected(){
    cs->setRGB(this->R, this->G, this->B, this->A);

    ui->SizeLineEdit->setText(QString::number(this->brushSize));
    ui->SizeSlider->setValue(this->brushSize);
}

void SetBrushWidget::closeEvent(QCloseEvent *event){
    this->on_buttonBox_rejected();
}
