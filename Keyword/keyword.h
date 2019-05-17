#ifndef KEYWOR_H
#define KEYWOR_H

#include <QWidget>
#include <Keyword/keywordinput.h>

class Keyword : public QWidget
{
    Q_OBJECT

signals:
    void className(QString name);

// SLOT
private slots:
    void receiveInput(QString name);
// 함수
public:
    explicit Keyword(QWidget *parent = nullptr);
    void clicked();

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:

// 변수
public:

protected:

private:
    KeywordInput* keyInput;
};

#endif // KEYWOR_H
