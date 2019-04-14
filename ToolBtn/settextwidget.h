#ifndef SETTEXTWIDGET_H
#define SETTEXTWIDGET_H

#include <QDialog>
#include <colorselect.h>
#include <QDockWidget>

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

private:
    Ui::SetTextWidget *ui;
    ColorSelect *cs;
    QDockWidget *csDock;
};

#endif // SETTEXTWIDGET_H
