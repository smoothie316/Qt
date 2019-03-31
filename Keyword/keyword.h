#ifndef KEYWOR_H
#define KEYWOR_H

#include <QWidget>
#include <QPushButton>
#include <Keyword/keywordinput.h>

class Keyword : public QPushButton
{
    Q_OBJECT
public:
    explicit Keyword(QWidget *parent = nullptr);

signals:

public slots:
    void clicked();

private:
    KeywordInput* keyInput;
};

#endif // KEYWOR_H
