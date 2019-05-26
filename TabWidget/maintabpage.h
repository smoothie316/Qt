#ifndef MAINTABPAGE_H
#define MAINTABPAGE_H

#include <QWidget>
#include <QPixmap>
#include <vector>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QScrollBar>

#include <ToolBtn/toolbtn.h>
#include <colorselect.h>

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
//    virtual void   mouseMoveEvent ( QMouseEvent * event ) override;
//    virtual void   mousePressEvent ( QMouseEvent * event ) override;
    //virtual void   mouseReleaseEvent ( QMouseEvent * event );
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void wheelEvent(QWheelEvent *event);

private:
    void adjustScrollBar(QScrollBar* scrollBar, int factor);
private slots:

private:
    Ui::MainTabPage *ui;
    QPixmap* buf;
    QPixmap* cursorPix;
    vector<QLabel*> layerSet;
    ToolBtn* tools;
    bool ctrlKey =false;

    int w, h;
    int originW, originH;

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
    void setLayerInfo(vector<QLabel*> layerList);
    void setLayerPixel(QPixmap* buf);

    void getAllLayerInfo(vector<QLabel*>& layerList);
    void getLayerInfo(QLabel*& layer, int index);

    void addLayer();
    void setMouseCursor();

};

#endif // MAINTABPAGE_H
