#ifndef MAINTABCLASS_H
#define MAINTABCLASS_H

#include <QWidget>
#include <QTabWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QResizeEvent>

#include <TabWidget/maintabpage.h>

#include <vector>
using namespace std;

class MainTabClass : public QTabWidget
{
    Q_OBJECT
public:
    MainTabClass(QWidget *parent = nullptr);

signals:

public slots:
    void createImage(QStringList imageList);
    void tabCloseRequested(int i);
    void recentTool(int btnNum);

private:
    MainTabPage* page;
    vector<MainTabPage*> pageList;
};

#endif // MAINTABCLASS_H
