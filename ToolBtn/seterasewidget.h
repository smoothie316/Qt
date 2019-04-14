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

public:
    int sliderPos;

private:
    Ui::setEraseWidget *ui;
};

#endif // SETERASEWIDGET_H
