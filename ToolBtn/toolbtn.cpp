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

    connect(brushW, SIGNAL(setEnd()),this, SLOT(setEndSigByWidget()));
    connect(paintW, SIGNAL(setEnd()),this, SLOT(setEndSigByWidget()));
    connect(eraseW, SIGNAL(setEnd()),this, SLOT(setEndSigByWidget()));
    connect(textW, SIGNAL(setEnd()),this, SLOT(setEndSigByWidget()));
    connect(keyword, SIGNAL(className(QString)), this, SLOT(receiveName(QString)));
}

void ToolBtn::setEndSigByWidget(){
    emit setEnd();
}

void ToolBtn::receiveName(QString name){
    emit setName(name);
}
