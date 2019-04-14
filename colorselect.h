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
signals:
    void sliderMoved(int position, int RGBInfo);
    // 0: Red, 1: Green, 2:Blue, 3: alpha

    void radioClicked(int r, int g, int b);

private slots:
    void on_RedSlider_sliderMoved(int position);
    void on_GreenSlider_sliderMoved(int position);
    void on_BlueSlider_sliderMoved(int position);
    void on_BlackRadioBtn_clicked();
    void on_RedRadioBtn_clicked();
    void on_GreenRadioBtn_clicked();
    void on_BlueRadioBtn_clicked();
    void on_YellowRadioBtn_clicked();

    void on_AlphaSlider_sliderMoved(int position);

public:
    void getRGB(int &R, int &G, int &B, int &A);
    void setRGB(int R, int G, int B, int A);

private:
    void removeCheck(int i);

private:
    Ui::ColorSelect *ui;
    int radioNum  = -1;
    int radioNumOld = 0;
    bool deleteCheck = false;

public:
    int R,G,B;
    int alpha;

};

#endif // COLORSELECT_H
