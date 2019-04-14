#include "settextwidget.h"
#include "ui_settextwidget.h"

SetTextWidget::SetTextWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTextWidget)
{
    ui->setupUi(this);
    cs = new ColorSelect();
    csDock = new QDockWidget("Font");
    csDock->setWidget(cs);
    csDock->setFloating(true);
}

SetTextWidget::~SetTextWidget()
{
    delete ui;
}

void SetTextWidget::on_ColorSelect1_clicked()
{
    csDock->show();
    csDock->setFocus();
}

void SetTextWidget::on_ColorSelect2_clicked()
{
    csDock->show();
}

void SetTextWidget::on_fontComboBox_currentFontChanged(const QFont &f)
{

}

void SetTextWidget::on_SizeSlider_sliderMoved(int position)
{

}
