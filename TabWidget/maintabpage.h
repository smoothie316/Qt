#ifndef MAINTABPAGE_H
#define MAINTABPAGE_H

#include <QWidget>
#include <QPixmap>
#include <vector>
#include <map>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPaintEvent>
#include <QScrollBar>
#include <QPainter>
#include <QPen>
#include <QtWidgets>

#include <ToolBtn/toolbtn.h>
#include <colorselect.h>

using namespace std;
class QDropEvent;
namespace Ui {
class MainTabPage;
}

class MainTabPage : public QWidget
{
    Q_OBJECT
signals:
    void drawEnd();
    void addTextLayer(QPixmap* pix, QLabel* label);
    void currentBufSize(QSize bufSize);
public:
    explicit MainTabPage(QWidget *parent = nullptr);
    ~MainTabPage() override;

public:
    void setImage(QPixmap *bufferm, int w, int h);
    void setLayerInfo(vector<QLabel*> layerList);
    void setLayerPixel(QPixmap* buf);
    QPixmap sumBuff();

    void getAllLayerInfo(vector<QLabel*>& layerList);
    void getLayerInfo(QLabel*& layer, int index);

    void addLayer();
    void setMouseCursor();

    void saveImage(QString dir);

protected:
    void resizeEvent(QResizeEvent* event) override;
    bool eventFilter(QObject *object, QEvent *event) override;
    void mouseMoveEvent ( QMouseEvent * event ) override;
    virtual void mousePressEvent ( QMouseEvent * event ) override;
    void mouseReleaseEvent ( QMouseEvent * event ) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

    virtual void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

private:
    void adjustScrollBar(QScrollBar* scrollBar, int factor);
    void draw(QPainter &painter, int R, int G, int B, int size);
    void changePoint(QPoint& point);
    void createTextLayerPix();
    void createIconLayerPix();
private slots:

private:
    Ui::MainTabPage *ui;

    //QPixmap* cursorPix;
    vector<QLabel*> layerSet;
    vector<QLabel*> textSet;
    vector<QString> inputtedTextList;
    bool ctrlKey =false;

    QPixmap* buf;
    int w, h;
    QSize bufSize; // 화면에 표시되는 이미지 크기

    bool clicked = false; // 마우스 이벤트용
    QColor penColor;
    QPen paintPen;
    int R, G, B;
    int penSize;

    int activeText =-1;
    bool textInput = false;
    bool textInputStart = false;
    bool dbClicked = false;
    QPixmap* textPix;

    vector<QLabel*> iconSet;
    vector<QPixmap> iconPixSet;
    QPixmap* clickedIcon;
    int currentIconNum = -1;
    bool iconClicked =false;
    QSize iconSize;
    QPoint droppedPoint;

    bool sizeInit = false;
    int resizeNum = 0;
public:
    /*
    Lasso : 0
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
    QPoint originPos, prevPos;
    QPoint textStart, textEnd;


};

#endif // MAINTABPAGE_H
