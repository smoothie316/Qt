#ifndef TOOLBTN_H
#define TOOLBTN_H

#include <QWidget>
#include <QPushButton>

#include <ToolBtn/setbrushwidget.h>
#include <ToolBtn/seterasewidget.h>
#include <ToolBtn/setpaintwidget.h>
#include <ToolBtn/settextwidget.h>

class ToolBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit ToolBtn(QWidget *parent = nullptr);

signals:

public slots:
    void clicked();

private:
    SetBrushWidget* brushW;
    SetPaintWidget* paintW;
    SetTextWidget* textW;
    setEraseWidget* eraseW;


private:
    int getNumber(QString str);
};

#endif // TOOLBTN_H
