#ifndef KEYWORDINPUT_H
#define KEYWORDINPUT_H

#include <QDialog>
#include <qfile.h>
#include <QTextStream>
#include <QDebug>
#include <QCompleter>

namespace Ui {
class KeywordInput;
}

class KeywordInput : public QDialog
{
    Q_OBJECT

public:
    explicit KeywordInput(QWidget *parent = nullptr);
    ~KeywordInput();

private:
    Ui::KeywordInput *ui;
};

#endif // KEYWORDINPUT_H
