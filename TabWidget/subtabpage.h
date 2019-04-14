#ifndef SUBTABPAGE_H
#define SUBTABPAGE_H

#include <QWidget>

namespace Ui {
class SubTabPage;
}

class SubTabPage : public QWidget
{
    Q_OBJECT

public:
    explicit SubTabPage(QWidget *parent = nullptr);
    ~SubTabPage();

private:
    Ui::SubTabPage *ui;
};

#endif // SUBTABPAGE_H
