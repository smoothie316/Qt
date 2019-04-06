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

private:
    Ui::ColorSelect *ui;
};

#endif // COLORSELECT_H
