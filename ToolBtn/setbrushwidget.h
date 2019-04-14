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

public:
    int sliderPos;

private slots:
    void on_SizeSlider_sliderMoved(int position);

private:
    Ui::SetBrushWidget *ui;
    ColorSelect* cs;
};

#endif // SETBRUSHWIDGET_H
