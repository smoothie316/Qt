#ifndef KEYWOR_H
#define KEYWOR_H

#include <QWidget>
#include <Keyword/keywordinput.h>

class Keyword : public QWidget
{
    Q_OBJECT
public:
    explicit Keyword(QWidget *parent = nullptr);

signals:

public slots:


public:
    void clicked();

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    KeywordInput* keyInput;
};

#endif // KEYWOR_H
