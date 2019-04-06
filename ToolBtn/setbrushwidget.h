#ifndef SETBRUSHWIDGET_H
#define SETBRUSHWIDGET_H

#include <QDockWidget>

namespace Ui {
class SetBrushWidget;
}

class SetBrushWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SetBrushWidget(QWidget *parent = nullptr);
    ~SetBrushWidget();

private:
    Ui::SetBrushWidget *ui;
};

#endif // SETBRUSHWIDGET_H
