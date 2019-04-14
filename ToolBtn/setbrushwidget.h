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
    void getSize(int &size);
    void getRGB(int &R, int &G, int &B);

private slots:
    void on_SizeSlider_sliderMoved(int position);
    void RGBSliderMoved(int position, int RGBInfo);
    // 0: Red, 1 : Green, 2 : Blue, 3 : Alpha
    void colorRadioClicked(int R, int G, int B);

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::SetBrushWidget *ui;
    ColorSelect* cs;
    int brushSize;
    int newBrushSize;

    int R, G, B, A;
    int newR, newG, newB, newA;
};

#endif // SETBRUSHWIDGET_H
