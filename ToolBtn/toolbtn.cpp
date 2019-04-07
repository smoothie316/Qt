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
            brushW->show();
            break;
        }
        case 2:
        {
            paintW->show();
            break;
        }
        case 3:
        {
            textW->show();
            break;
        }
        case 4:{
            EraseW->show();
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
