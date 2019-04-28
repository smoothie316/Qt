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
        this->R = position;
        break;
    case 1:
        this->G = position;
        break;
    case 2:
        this->B = position;
        break;
    case 3:
        this->A = position;
        break;
    }
    qDebug() << QString::number(R) + ", " + QString::number(G) + ", " + QString::number(B);
}

void SetPaintWidget::colorRadioClicked(int R, int G, int B){
    this->R = R;
    this->G = G;
    this->B = B;
    this->A = 255;
    qDebug() << QString::number(R) + ", " + QString::number(G) + ", " + QString::number(B);
}

void SetPaintWidget::on_pushButton_clicked()
{
    emit setEnd();
}
