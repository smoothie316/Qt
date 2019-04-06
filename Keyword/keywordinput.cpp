#include "keywordinput.h"
#include "ui_keywordinput.h"

KeywordInput::KeywordInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeywordInput)
{
    ui->setupUi(this);
    ui->comboBox->setAutoCompletion(false);
    ui->comboBox->addItem("test");
    ui->comboBox->addItem("abc");
    ui->comboBox->addItem("acb");
}

KeywordInput::~KeywordInput()
{
    delete ui;
}
