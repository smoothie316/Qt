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

    ui->SizeSlider->setRange(1,100);
    ui->SizeSlider->setValue(10);
    this->brushSize = ui->SizeSlider->value();
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
    this->brushSize = position;
    ui->SizeLineEdit->setText(QString::number(this->brushSize));
}

void SetBrushWidget::RGBSliderMoved(int position, int RGBInfo){
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

void SetBrushWidget::colorRadioClicked(int R, int G, int B){
    this->R = R;
    this->G = G;
    this->B = B;
    this->A = 255;
    qDebug() << QString::number(R) + ", " + QString::number(G) + ", " + QString::number(B);
}

void SetBrushWidget::on_pushButton_clicked()
{
    emit setEnd();
}
