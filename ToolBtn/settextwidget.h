#ifndef SETTEXTWIDGET_H
#define SETTEXTWIDGET_H

#include <QDialog>

namespace Ui {
class SetTextWidget;
}

class SetTextWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SetTextWidget(QWidget *parent = nullptr);
    ~SetTextWidget();

private:
    Ui::SetTextWidget *ui;
};

#endif // SETTEXTWIDGET_H
