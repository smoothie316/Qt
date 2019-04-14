#ifndef SETERASEWIDGET_H
#define SETERASEWIDGET_H

#include <QDialog>

namespace Ui {
class setEraseWidget;
}

class setEraseWidget : public QDialog
{
    Q_OBJECT

public:
    explicit setEraseWidget(QWidget *parent = nullptr);
    ~setEraseWidget();

private slots:
    void on_SizeSlider_sliderMoved(int position);
    void on_CircleRadio_clicked();
    void on_RectRadio_clicked();
    void on_SizeLineEdit_editingFinished();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
protected:
    void closeEvent(QCloseEvent *event);
public:
    int eraserSize;
    int newEraserSize;

private:
    Ui::setEraseWidget *ui;
    bool circleChecked = true;
    bool rectChecked = false;
    bool newCircleChecked = true;
    bool newRectChecked = false;
};

#endif // SETERASEWIDGET_H
