#ifndef FILECLASS_H
#define FILECLASS_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

#include <vector>

using namespace std;

class FileClass : public QPushButton
{
    Q_OBJECT
public:
    explicit FileClass(QWidget *parent = nullptr);

signals:

public slots:
    void clicked();

private:
    QMessageBox box;

    vector<QString> imgList;
};

#endif // FILECLASS_H
