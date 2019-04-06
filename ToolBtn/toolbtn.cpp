#include "toolbtn.h"

#include <QDockWidget>

ToolBtn::ToolBtn(QWidget *parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clicked()));
    brushW = new SetBrushWidget();
    paintW = new SetPaintWidget();
    textW = new SetTextWidget();
    EraseW = new setEraseWidget();
}

void ToolBtn::clicked(){
    // Brush, Paint, Text, Erase

    switch(this->getNumber(this->objectName())){
        case 1:
        {
            QDockWidget* dock = new QDockWidget("Brush Set");
            dock->setWidget(brushW);
            dock->setFloating(true);
            dock->show();
            break;
        }
        case 2:
        {
            QDockWidget* dock1 = new QDockWidget("Paint Set");
            dock1->setWidget(paintW);
            dock1->setFloating(true);
            dock1->show();
            break;
        }
        case 3:
        {
            QDockWidget* dock2 = new QDockWidget("Text Set");
            dock2->setWidget(textW);
            dock2->setFloating(true);
            dock2->show();
            break;
        }
        case 4:{
            QDockWidget* dock3 = new QDockWidget("Erase Set");
            dock3->setWidget(EraseW);
            dock3->setFloating(true);
            dock3->show();
            break;
        }
    }
}

int ToolBtn::getNumber(QString str){
    if(str == QString("Brush"))
        return 1;
    if(str == QString("Paint"))
        return 2;
    if(str == QString("Text"))
        return 3;
    if(str == QString("Erase"))
        return 4;
    if(str == QString("Crop"))
        return 5;
    if(str == QString("Resize"))
        return 6;
    return -1;
}
