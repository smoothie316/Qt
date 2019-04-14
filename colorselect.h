#ifndef COLORSELECT_H
#define COLORSELECT_H

#include <QWidget>

namespace Ui {
class ColorSelect;
}

class ColorSelect : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSelect(QWidget *parent = nullptr);
    ~ColorSelect();

private slots:
    void on_RedSlider_sliderMoved(int position);
    void on_GreenSlider_sliderMoved(int position);
    void on_BlueSlider_sliderMoved(int position);
    void on_BlackRadioBtn_clicked();
    void on_RedRadioBtn_clicked();
    void on_GreenRadioBtn_clicked();
    void on_BlueRadioBtn_clicked();
    void on_YellowRadioBtn_clicked();

private:
    Ui::ColorSelect *ui;

public:
    int R,G,B;
};

#endif // COLORSELECT_H
