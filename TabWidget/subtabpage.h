#ifndef SUBTABPAGE_H
#define SUBTABPAGE_H

#include <QWidget>
#include <QLabel>

#include <vector>

using namespace std;

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
protected:


// 변수
public:
protected:
private:
    Ui::SubTabPage *ui;
    vector<QLabel*> imgList;
};

#endif // SUBTABPAGE_H
