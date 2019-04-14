#include "setpaintwidget.h"
#include "ui_setpaintwidget.h"

#include <QDebug>

SetPaintWidget::SetPaintWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPaintWidget)
{
    ui->setupUi(this);
    cs = new ColorSelect();
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(cs);
    ui->ColorBox->setLayout(grid);

    cs->getRGB(this->R, this->G, this->B, this->A);
    cs->getRGB(this->newR, this->newG, this->newB, this->newA);
    connect(cs, SIGNAL(sliderMoved(int, int)), this, SLOT(RGBSliderMoved(int, int)));
    connect(cs, SIGNAL(radioClicked(int, int, int)), this, SLOT(colorRadioClicked(int, int, int)));
}

SetPaintWidget::~SetPaintWidget()
{
    delete ui;
}


void SetPaintWidget::RGBSliderMoved(int position, int RGBInfo){
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

void SetPaintWidget::colorRadioClicked(int R, int G, int B){
    this->newR = R;
    this->newG = G;
    this->newB = B;
    this->newA = 255;
    qDebug() << QString::number(newR) + ", " + QString::number(newG) + ", " + QString::number(newB);
}

void SetPaintWidget::on_buttonBox_accepted(){
    this->R = this->newR;
    this->G = this->newG;
    this->B = this->newB;
    this->A = this->newA;
}

void SetPaintWidget::on_buttonBox_rejected(){
    cs->setRGB(this->R, this->G, this->B, this->A);
}

void SetPaintWidget::closeEvent(QCloseEvent *event){
    this->on_buttonBox_rejected();
}
