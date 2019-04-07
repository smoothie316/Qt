#ifndef MAINTABPAGE_H
#define MAINTABPAGE_H

#include <QWidget>
#include <QPixmap>
#include <vector>
#include <QLabel>

using namespace std;
namespace Ui {
class MainTabPage;
}

class MainTabPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainTabPage(QWidget *parent = nullptr);
    ~MainTabPaㅉge() override;

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::MainTabPage *ui;
    QPixmap* buf;
    vector<QLabel*> layerSet;

public:
    void setImage(QPixmap *bufferm, int w, int h);
};

#endif // MAINTABPAGE_H
