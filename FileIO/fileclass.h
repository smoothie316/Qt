#ifndef FILECLASS_H
#define FILECLASS_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QStringList>

class FileClass : public QWidget
{
    Q_OBJECT
public:
    explicit FileClass(QWidget *parent = nullptr);

signals:
    void createImage(QStringList imageList);
public slots:

public:
    void ImageOpen();
public:
    QStringList keywordFileRead();

private:
    QStringList keywordList;
};

#endif // FILECLASS_H
