#ifndef SETTEXTWIDGET_H
#define SETTEXTWIDGET_H

#include <QDialog>
#include <colorselect.h>
#include <QDockWidget>
#include <QPalette>
#include <QBrush>

namespace Ui {
class SetTextWidget;
}

class SetTextWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SetTextWidget(QWidget *parent = nullptr);
    ~SetTextWidget();

private slots:
    void on_ColorSelect1_clicked();
    void on_ColorSelect2_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_SizeSlider_sliderMoved(int position);
    void RGBSliderMoved(int position, int RGBInfo);
    // 0 : Red, 1 : Green, 2 : Blue
    void colorRadioClicked(int R, int G, int B);

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

public:
    void getPaletteInfo(QBrush* text, QBrush* background);

protected:
    void closeEvent(QCloseEvent *event);


private:
    void setNewPaletteInfo();
    void setPaletteInfo();

private:
    Ui::SetTextWidget *ui;
    ColorSelect *csText;
    ColorSelect *csBack;
    QDockWidget *csDockText;
    QDockWidget *csDockBack;

    int R, G, B, A;

    int textR, textG, textB, textA;
    int newTextR, newTextG, newTextB, newTextA;

    int backR, backG, backB, backA;
    int newBackR, newBackG, newBackB, newBackA;

    bool textBackgroundColor;

    QBrush* textBrush;
    QBrush* textBackgroundBrush;
};

#endif // SETTEXTWIDGET_H
