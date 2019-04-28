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
signals:
    void setEnd();
// 슬롯
private slots:
    void RGBSliderMoved(int position, int RGBInfo);
    // 0: Red, 1 : Green, 2 : Blue
    void colorRadioClicked(int R, int G, int B);
    void on_pushButton_clicked();

// 함수
public:
    explicit SetPaintWidget(QWidget *parent = nullptr);
    ~SetPaintWidget();


private:

// 변수
public:
protected:
private:
    Ui::SetPaintWidget *ui;
    ColorSelect* cs;
    int R, G, B, A;
};

#endif // SETPAINTWIDGET_H
