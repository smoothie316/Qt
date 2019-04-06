#ifndef SETPAINTWIDGET_H
#define SETPAINTWIDGET_H

#include <QDialog>
#include <colorselect.h>

namespace Ui {
class SetPaintWidget;
}

class SetPaintWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SetPaintWidget(QWidget *parent = nullptr);
    ~SetPaintWidget();

private:
    Ui::SetPaintWidget *ui;
    ColorSelect* cs;
};

#endif // SETPAINTWIDGET_H
