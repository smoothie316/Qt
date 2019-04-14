#ifndef TOOLBTN_H
#define TOOLBTN_H

#include <QWidget>

#include <ToolBtn/setbrushwidget.h>
#include <ToolBtn/seterasewidget.h>
#include <ToolBtn/setpaintwidget.h>
#include <ToolBtn/settextwidget.h>
#include <Keyword/keyword.h>

class ToolBtn : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBtn(QWidget *parent = nullptr);

signals:

public slots:
    void recentTool(int i);

public:


private:
    Keyword* keyword;
    SetBrushWidget* brushW;
    SetPaintWidget* paintW;
    SetTextWidget* textW;
    setEraseWidget* eraseW;
};

#endif // TOOLBTN_H
