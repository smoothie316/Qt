#ifndef SETERASEWIDGET_H
#define SETERASEWIDGET_H

#include <QDialog>

namespace Ui {
class setEraseWidget;
}

class setEraseWidget : public QDialog
{
    Q_OBJECT

signals:
    void setEnd();
// SLOT
private slots:
    void on_SizeSlider_sliderMoved(int position);
    void on_CircleRadio_clicked();
    void on_RectRadio_clicked();
    void on_SizeLineEdit_editingFinished();
    void on_pushButton_clicked();


// 함수
public:
    explicit setEraseWidget(QWidget *parent = nullptr);
    ~setEraseWidget();

private:


// 변수
public:
    int eraserSize;

protected:

private:
    Ui::setEraseWidget *ui;
    bool circleChecked = true;
    bool rectChecked = false;
};

#endif // SETERASEWIDGET_H
