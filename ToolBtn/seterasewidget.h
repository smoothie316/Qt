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

private:
    Ui::setEraseWidget *ui;
};

#endif // SETERASEWIDGET_H
