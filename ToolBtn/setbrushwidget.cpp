#include "setbrushwidget.h"
#include "ui_setbrushwidget.h"

SetBrushWidget::SetBrushWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SetBrushWidget)
{
    ui->setupUi(this);
}

SetBrushWidget::~SetBrushWidget()
{
    delete ui;
}
