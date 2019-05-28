#ifndef MAINTABPAGE_H
#define MAINTABPAGE_H

#include <QWidget>
#include <QPixmap>
#include <vector>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPaintEvent>
#include <QScrollBar>

#include <ToolBtn/toolbtn.h>
#include <colorselect.h>
#include <Paint/shape.h>

#include <functional>
#include <memory>

using namespace std;
using namespace Paint;
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
    bool eventFilter(QObject *object, QEvent *event);
    //virtual void   mouseDoubleClickEvent ( QMouseEvent * event );
    virtual void   mouseMoveEvent ( QMouseEvent * event ) override;
    virtual void   mousePressEvent ( QMouseEvent * event ) override;
    virtual void   mouseReleaseEvent ( QMouseEvent * event ) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void paintEvent(QPaintEvent* event) override;

private:
    void adjustScrollBar(QScrollBar* scrollBar, int factor);
private slots:

private:
    Ui::MainTabPage *ui;
    QPixmap* buf;
    QPixmap* cursorPix;
    vector<QLabel*> layerSet;
    bool ctrlKey =false;

    int w, h;
    int originW, originH;

    QSize bufSize;
    bool clicked = false;
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
    int currentBufNum = 0;
    vector<QPixmap*>* layerInfo;
    ToolBtn* tools;

    typedef std::function<
        std::unique_ptr<Shape>(
            const QPoint&, int, const QColor&)> shape_factory_t;

    std::unique_ptr<Shape> currentShape;
    QPoint originPos, nextPos;

public:
    void setImage(QPixmap *bufferm, int w, int h);
    void setLayerInfo(vector<QLabel*> layerList);
    void setLayerPixel(QPixmap* buf);
    QPixmap sumBuff();

    void getAllLayerInfo(vector<QLabel*>& layerList);
    void getLayerInfo(QLabel*& layer, int index);

    void addLayer();
    void setMouseCursor();

};

#endif // MAINTABPAGE_H
