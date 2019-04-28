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
signals:
    void setEnd();

// SLOT
private slots:
    void on_SizeSlider_sliderMoved(int position);
    void RGBSliderMoved(int position, int RGBInfo);
    // 0: Red, 1 : Green, 2 : Blue, 3 : Alpha
    void colorRadioClicked(int R, int G, int B);
    void on_pushButton_clicked();

// 함수
public:
    explicit SetBrushWidget(QWidget *parent = nullptr);
    ~SetBrushWidget();
    void getSize(int &size);
    void getRGB(int &R, int &G, int &B);

private:

// 변수
public:

protected:

private:
    Ui::SetBrushWidget *ui;
    ColorSelect* cs;
    int brushSize;

    int R, G, B, A;
};

#endif // SETBRUSHWIDGET_H
