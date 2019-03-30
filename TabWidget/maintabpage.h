#ifndef MAINTABPAGE_H
#define MAINTABPAGE_H

#include <QWidget>

namespace Ui {
class MainTabPage;
}

class MainTabPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainTabPage(QWidget *parent = nullptr);
    ~MainTabPage();

private:
    Ui::MainTabPage *ui;
};

#endif // MAINTABPAGE_H
