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
    void getAllBuffList(vector<QPixmap*>& buffList);
    void getBuff(QPixmap*& buff, int index);

    void setAllBuffList(vector<QPixmap*> buffList);
    void subTabCreate(QString name);


signals:
    void addMainTab(QWidget* page, QString name);
    void addSubTab(QWidget* page, QString name);
    void addBuff();

public slots:
    void mainCreateImage(QStringList imageList);
    void resetPixmap(QPixmap* buf, int pageNum);

private:
    MainTabPage* mainPage;
    SubTabPage* subPage;
    vector<QPixmap*> bufferList;
    QWidget* _parent;

public:
    vector<MainTabPage*> mainPageList;
    vector<SubTabPage*> subPageList;

};

#endif // TABCLASS_H
