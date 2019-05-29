#ifndef SUBTABPAGE_H
#define SUBTABPAGE_H

#include <QWidget>
#include <QLabel>

#include <vector>
#include <iostream>
#include <QMouseEvent>


using namespace std;
class QDragEnterEvent;
class QDropEvent;
namespace Ui {
class SubTabPage;
}

class SubTabPage : public QWidget
{
    Q_OBJECT

public:
    explicit SubTabPage(QWidget *parent = nullptr);
    ~SubTabPage();
// 함수
public:
    void setImage(QString name);
private:
    int countFileNum(QString dir);

protected:
    bool eventFilter(QObject* object, QEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

// 변수
public:
protected:
private:
    Ui::SubTabPage *ui;
    vector<QLabel*> imgList;
    vector<QPixmap*> bufList;
    vector<QString> fileName;
    bool clicked = false;

};

#endif // SUBTABPAGE_H
