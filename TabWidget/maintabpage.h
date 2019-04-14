#ifndef MAINTABPAGE_H
#define MAINTABPAGE_H

#include <QWidget>
#include <QPixmap>
#include <vector>
#include <QLabel>
#include <QMouseEvent>

using namespace std;
namespace Ui {
class MainTabPage;
}

class MainTabPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainTabPage(QWidget *parent = nullptr);
    ~MainTabPage() override;

protected:
    void resizeEvent(QResizeEvent* event) override;
    //virtual void   mouseDoubleClickEvent ( QMouseEvent * event );
    virtual void   mouseMoveEvent ( QMouseEvent * event ) override;
    virtual void   mousePressEvent ( QMouseEvent * event ) override;
    //virtual void   mouseReleaseEvent ( QMouseEvent * event );

private:
    Ui::MainTabPage *ui;
    QPixmap* buf;
    vector<QLabel*> layerSet;
public:
    /*
    Brush : 1
    Paint : 2
    Text  : 3
    Erase : 4
    Crop  : 5
    Resize: 6
    */
    int clickedTool;

public:
    void setImage(QPixmap *bufferm, int w, int h);

};

#endif // MAINTABPAGE_H
