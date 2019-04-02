#ifndef MAINTABPAGE_H
#define MAINTABPAGE_H

#include <QWidget>
#include <QPixmap>


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

public:
    void setImage(QPixmap *buffer);
};

#endif // MAINTABPAGE_H
