#ifndef SUBTABCLASS_H
#define SUBTABCLASS_H

#include <QWidget>
#include <QTabWidget>

class SubTabClass : public QTabWidget
{
    Q_OBJECT
public:
    SubTabClass(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SUBTABCLASS_H
