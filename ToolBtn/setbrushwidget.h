#ifndef SETBRUSHWIDGET_H
#define SETBRUSHWIDGET_H

#include <QDialog>
#include <colorselect.h>

namespace Ui {
class SetBrushWidget;
}

class SetBrushWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SetBrushWidget(QWidget *parent = nullptr);
    ~SetBrushWidget();

private:
    Ui::SetBrushWidget *ui;
    ColorSelect* cs;
};

#endif // SETBRUSHWIDGET_H
