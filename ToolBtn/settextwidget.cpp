#include "settextwidget.h"
#include "ui_settextwidget.h"

#include <QDebug>

SetTextWidget::SetTextWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTextWidget)
{
    ui->setupUi(this);
    this->ui->SizeSlider->setRange(1, 100);
    this->ui->SizeSlider->setValue(this->fontSize);
    this->ui->SizeLineEdit->setText(QString::number(this->fontSize));

    csText = new ColorSelect();
    csText->getRGB(this->textR, this->textG, this->textB, this->textA);
    csText->getRGB(this->textR, this->textG, this->textB, this->textA);
    csDockText = new QDockWidget("Text Color");
    csDockText->setWidget(csText);
    csDockText->setFloating(true);

    connect(csText, SIGNAL(sliderMoved(int, int)), this, SLOT(RGBSliderMoved(int, int)));
    connect(csText, SIGNAL(radioClicked(int, int, int)), this, SLOT(colorRadioClicked(int, int, int)));

    csBack = new ColorSelect();
    csBack->setRGB(255,255,255, 0);
    csBack->getRGB(this->backR, this->backG, this->backB, this->backA);
    csBack->getRGB(this->backR, this->backG, this->backB, this->backA);
    csDockBack = new QDockWidget("Text Background Color");
    csDockBack->setWidget(csBack);
    csDockBack->setFloating(true);

    connect(csBack, SIGNAL(sliderMoved(int, int)), this, SLOT(RGBSliderMoved(int, int)));
    connect(csBack, SIGNAL(radioClicked(int, int, int)), this, SLOT(colorRadioClicked(int, int, int)));

    this->textBackgroundColor = false;
    this->isFontChanged = false;

    ui->TextBackgroundColorLabel->setAutoFillBackground(true);
}

SetTextWidget::~SetTextWidget()
{
    delete ui;
}

void SetTextWidget::on_ColorSelect1_clicked(){
    csDockText->showNormal();
    this->textBackgroundColor = false;
}

void SetTextWidget::on_ColorSelect2_clicked(){
    csDockBack->showNormal();
    this->textBackgroundColor = true;
}

void SetTextWidget::on_fontComboBox_currentFontChanged(const QFont &f){
    //set font
    this->isFontChanged = true;
    this->textFont = f;
}

void SetTextWidget::on_SizeSlider_sliderMoved(int position){
    this->fontSize = position;
    ui->SizeLineEdit->setText(QString::number(this->fontSize));
    this->isFontChanged = true;
    this->textFont.setPointSize(this->fontSize);
}

void SetTextWidget::RGBSliderMoved(int position, int RGBInfo){
    switch(RGBInfo){
    case 0:
        this->R = position;
        if(this->textBackgroundColor){
            this->backR = this->R;
        }
        else {
            this->textR = this->R;
        }
        break;
    case 1:
        this->G = position;
        if(this->textBackgroundColor){
            this->backG = this->G;
        }
        else {
            this->textG = this->G;
        }
        break;
    case 2:
        this->B = position;
        if(this->textBackgroundColor){
            this->backB = this->B;
        }
        else {
            this->textB = this->B;
        }
        break;
    case 3:
        this->A = position;
        if(this->textBackgroundColor){
            this->backA = this->A;
        }
        else {
            this->textA = this->A;
        }
        break;
    }
    this->setNewPaletteInfo();
}

void SetTextWidget::colorRadioClicked(int R, int G, int B){
    this->R = R;
    this->G = G;
    this->B = B;
    this->A = 255;

    if(this->textBackgroundColor){
        this->backR = this->R;
        this->backG = this->G;
        this->backB = this->B;
        this->backA = this->A;
    }
    else{
        this->textR = this->R;
        this->textG = this->G;
        this->textB = this->B;
        this->textA = this->A;
    }

    this->setNewPaletteInfo();
}

void SetTextWidget::setNewPaletteInfo(){
    QPalette paletteText;
    QPalette paletteBack;

    //textColor
    this->textBrush = new QBrush(QColor(this->textR, this->textG, this->textB, this->textA));
    this->textBrush->setStyle(Qt::SolidPattern);

    //black background
    this->textBackgroundBrush = new QBrush(QColor(this->backR, this->backG, this->backB, this->backA));
    this->textBackgroundBrush->setStyle(Qt::SolidPattern);

    //set white text
    paletteText.setBrush(QPalette::Active, QPalette::WindowText, *(this->textBrush));
    paletteText.setBrush(QPalette::Inactive, QPalette::WindowText, *(this->textBrush));

    //set black background
    paletteBack.setBrush(QPalette::Active, QPalette::Window, *(this->textBackgroundBrush));
    paletteBack.setBrush(QPalette::Inactive, QPalette::Window, *(this->textBackgroundBrush));

    //set palette
    ui->TextColorLabel->setPalette(paletteText);
    ui->TextColorLabel->show();
    ui->TextBackgroundColorLabel->setPalette(paletteBack);
    ui->TextBackgroundColorLabel->show();
}

void SetTextWidget::setPaletteInfo(){
    QPalette paletteText;
    QPalette paletteBack;

    //textColor
    this->textBrush = new QBrush(QColor(this->textR, this->textG, this->textB, this->textA));
    this->textBrush->setStyle(Qt::SolidPattern);

    //black background
    this->textBackgroundBrush = new QBrush(QColor(this->backR, this->backG, this->backB, this->backA));
    this->textBackgroundBrush->setStyle(Qt::SolidPattern);

    //set white text
    paletteText.setBrush(QPalette::Active, QPalette::WindowText, *(this->textBrush));
    paletteText.setBrush(QPalette::Inactive, QPalette::WindowText, *(this->textBrush));

    //set black background
    paletteBack.setBrush(QPalette::Active, QPalette::Window, *(this->textBackgroundBrush));
    paletteBack.setBrush(QPalette::Inactive, QPalette::Window, *(this->textBackgroundBrush));

    //set palette
    ui->TextColorLabel->setPalette(paletteText);
    ui->TextColorLabel->show();
    ui->TextBackgroundColorLabel->setPalette(paletteBack);
    ui->TextBackgroundColorLabel->show();
}

void SetTextWidget::on_pushButton_clicked()
{
    emit setEnd();
}
