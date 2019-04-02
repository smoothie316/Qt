#ifndef FILECLASS_H
#define FILECLASS_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

#include <QStringList>

class FileClass : public QPushButton
{
    Q_OBJECT
public:
    explicit FileClass(QWidget *parent = nullptr);

signals:
    void createImage(QStringList imageList);
public slots:
    void clicked();

private:
    QMessageBox box;

};

#endif // FILECLASS_H
