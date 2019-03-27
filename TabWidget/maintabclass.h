#ifndef MAINTABCLASS_H
#define MAINTABCLASS_H

#include <QWidget>
#include <QTabWidget>

class MainTabClass : public QTabWidget
{
    Q_OBJECT
public:
    MainTabClass(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINTABCLASS_H
