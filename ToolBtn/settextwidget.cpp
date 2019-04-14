#include "settextwidget.h"
#include "ui_settextwidget.h"

#include <QDebug>

SetTextWidget::SetTextWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTextWidget)
{
    ui->setupUi(this);

    csText = new ColorSelect();
    csText->getRGB(this->textR, this->textG, this->textB, this->textA);
    csText->getRGB(this->newTextR, this->newTextG, this->newTextB, this->newTextA);
    csDockText = new QDockWidget("Text Color");
    csDockText->setWidget(csText);
    csDockText->setFloating(true);

    connect(csText, SIGNAL(sliderMoved(int, int)), this, SLOT(RGBSliderMoved(int, int)));
    connect(csText, SIGNAL(radioClicked(int, int, int)), this, SLOT(colorRadioClicked(int, int, int)));

    csBack = new ColorSelect();
    csBack->setRGB(255,255,255, 0);
    csBack->getRGB(this->backR, this->backG, this->backB, this->backA);
    csBack->getRGB(this->newBackR, this->newBackG, this->newBackB, this->newBackA);
    csDockBack = new QDockWidget("Text Background Color");
    csDockBack->setWidget(csBack);
    csDockBack->setFloating(true);

    connect(csBack, SIGNAL(sliderMoved(int, int)), this, SLOT(RGBSliderMoved(int, int)));
    connect(csBack, SIGNAL(radioClicked(int, int, int)), this, SLOT(colorRadioClicked(int, int, int)));

    this->textBackgroundColor = false;

    ui->TextBackgroundColorLabel->setAutoFillBackground(true);
}

SetTextWidget::~SetTextWidget()
{
    delete ui;
}

void SetTextWidget::on_ColorSelect1_clicked(){
    csDockText->show();
    this->textBackgroundColor = false;
}

void SetTextWidget::on_ColorSelect2_clicked(){
    csDockBack->show();
    this->textBackgroundColor = true;
}

void SetTextWidget::on_fontComboBox_currentFontChanged(const QFont &f){
    //set font
    QFont font;
    font.setPointSize(32);
    font.setBold(true);
}

void SetTextWidget::on_SizeSlider_sliderMoved(int position){

}

void SetTextWidget::RGBSliderMoved(int position, int RGBInfo){

    switch(RGBInfo){
    case 0:
        this->R = position;
        if(this->textBackgroundColor){
            this->newBackR = this->R;
        }
        else {
            this->newTextR = this->R;
        }
        break;
    case 1:
        this->G = position;
        if(this->textBackgroundColor){
            this->newBackG = this->G;
        }
        else {
            this->newTextG = this->G;
        }
        break;
    case 2:
        this->B = position;
        if(this->textBackgroundColor){
            this->newBackB = this->B;
        }
        else {
            this->newTextB = this->B;
        }
        break;
    case 3:
        this->A = position;
        if(this->textBackgroundColor){
            this->newBackA = this->A;
        }
        else {
            this->newTextA = this->A;
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
        this->newBackR = this->R;
        this->newBackG = this->G;
        this->newBackB = this->B;
        this->newBackA = this->A;
    }
    else{
        this->newTextR = this->R;
        this->newTextG = this->G;
        this->newTextB = this->B;
        this->newTextA = this->A;
    }

    this->setNewPaletteInfo();
}

void SetTextWidget::setNewPaletteInfo(){
    QPalette paletteText;
    QPalette paletteBack;

    //textColor
    this->textBrush = new QBrush(QColor(this->newTextR, this->newTextG, this->newTextB, this->newTextA));
    this->textBrush->setStyle(Qt::SolidPattern);

    //black background
    this->textBackgroundBrush = new QBrush(QColor(this->newBackR, this->newBackG, this->newBackB, this->newBackA));
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


void SetTextWidget::on_buttonBox_accepted()
{
    this->textR = this->newTextR;
    this->textG = this->newTextG;
    this->textB = this->newTextB;
    this->textA = this->newTextA;

    this->backR = this->newBackR;
    this->backG = this->newBackG;
    this->backB = this->newBackB;
    this->backA = this->newBackA;
}

void SetTextWidget::on_buttonBox_rejected()
{
    csText->setRGB(this->textR, this->textG, this->textB, this->textA);
    csBack->setRGB(this->backR, this->backG, this->backB, this->backA);
    this->setPaletteInfo();
}

void SetTextWidget::closeEvent(QCloseEvent *event) {
    this->on_buttonBox_rejected();
}
