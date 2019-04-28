#ifndef KEYWORDINPUT_H
#define KEYWORDINPUT_H

#include <QDialog>

namespace Ui {
class KeywordInput;
}

class KeywordInput : public QDialog
{
    Q_OBJECT
signals:
    void setEnd();

// SLOT
private slots:
    void on_BackBtn_clicked();

// 함수
public:
    explicit KeywordInput(QWidget *parent = nullptr);
    ~KeywordInput() override;

protected:

private:

// 변수
public:

protected:

private:
    Ui::KeywordInput *ui;
};

#endif // KEYWORDINPUT_H
