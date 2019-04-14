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

private slots:
    void RGBSliderMoved(int position, int RGBInfo);
    // 0: Red, 1 : Green, 2 : Blue
    void colorRadioClicked(int R, int G, int B);

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::SetPaintWidget *ui;
    ColorSelect* cs;
    int R, G, B, A;
    int newR, newG, newB, newA;
};

#endif // SETPAINTWIDGET_H
