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
signals:
    void setEnd();

// SLOT
private slots:
    void on_ColorSelect1_clicked();
    void on_ColorSelect2_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_SizeSlider_sliderMoved(int position);
    void RGBSliderMoved(int position, int RGBInfo);
    // 0 : Red, 1 : Green, 2 : Blue
    void colorRadioClicked(int R, int G, int B);
    void on_pushButton_clicked();

// 함수    
public:
    explicit SetTextWidget(QWidget *parent = nullptr);
    ~SetTextWidget();
    void getPaletteInfo(QBrush* text, QBrush* background);

private:
    void setNewPaletteInfo();
    void setPaletteInfo();

// 변수
public:
    QFont textFont;
    int textR, textG, textB, textA;
    int backR, backG, backB, backA;
    int fontSize = 11;
    bool textBackgroundColor;
    bool isFontChanged;
protected:

private:
    Ui::SetTextWidget *ui;
    ColorSelect *csText;
    ColorSelect *csBack;
    QDockWidget *csDockText;
    QDockWidget *csDockBack;
    int R, G, B, A;

    QBrush* textBrush;
    QBrush* textBackgroundBrush;
};

#endif // SETTEXTWIDGET_H
