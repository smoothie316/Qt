#ifndef MAINTABCLASS_H
#define MAINTABCLASS_H

#include <QWidget>
#include <QTabWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QResizeEvent>

#include <TabWidget/maintabpage.h>

class MainTabClass : public QTabWidget
{
    Q_OBJECT
public:
    MainTabClass(QWidget *parent = nullptr);

signals:

public slots:
    void createImage(QStringList imageList);
    void tabCloseRequested(int i);

private:
    MainTabPage* page;
};

#endif // MAINTABCLASS_H
