#ifndef TABCLASS_H
#define TABCLASS_H

#include <QWidget>
#include <QStringList>
#include <vector>

#include <TabWidget/maintabpage.h>
#include <TabWidget/subtabpage.h>

using namespace std;
class TabClass : public QWidget
{
    Q_OBJECT
public:
    explicit TabClass(QWidget *parent = nullptr);

signals:
    void addMainTab(QWidget* page, QString name);
    void addBuff();

public slots:
    void mainCreateImage(QStringList imageList);

public:
    MainTabPage* mainPage;
    vector<MainTabPage*> mainPageList;

    SubTabPage* subPage;
    vector<SubTabPage*> subPageList;

    vector<QPixmap*> bufferList;
};

#endif // TABCLASS_H
