#include "toolbtn.h"

#include <QDockWidget>

ToolBtn::ToolBtn(QWidget *parent) : QWidget(parent)
{
    brushW = new SetBrushWidget();
    brushW->setWindowTitle("Brush Options");
    paintW = new SetPaintWidget();
    paintW->setWindowTitle("Paint Options");
    textW = new SetTextWidget();
    textW->setWindowTitle("Text Options");
    eraseW = new setEraseWidget();
    eraseW->setWindowTitle("Eraser Optinos");
    keyword = new Keyword();
    keyword->setWindowTitle("Keyword input window");
}

void ToolBtn::recentTool(int i){
    switch(i){
        case 0:{
            //Lasso
            keyword->clicked();
            break;
        }
        case 1:{
            // brush
            brushW->show();
            break;
        }
        case 2:{
            // paint
            paintW->show();
            break;
        }
        case 3:{
            // text
            textW->show();
            break;
        }
        case 4:{
            // eraser
            eraseW->show();
            break;
        }
        case 5:{
            // Crop
            break;
        }
        case 6:{
            // Resize
            break;
        }
    }
}
