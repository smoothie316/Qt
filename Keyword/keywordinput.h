#ifndef KEYWORDINPUT_H
#define KEYWORDINPUT_H

#include <QDialog>

namespace Ui {
class KeywordInput;
}

class KeywordInput : public QDialog
{
    Q_OBJECT

// SLOT
private slots:
    void on_BackBtn_clicked();
    void on_bnAdd_clicked();
signals:
    void className(QString name);
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
    QString _className;
};

#endif // KEYWORDINPUT_H
