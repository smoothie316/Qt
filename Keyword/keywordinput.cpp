#include "keywordinput.h"
#include "ui_keywordinput.h"

KeywordInput::KeywordInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeywordInput)
{
    ui->setupUi(this);
}

KeywordInput::~KeywordInput()
{
    delete ui;
}
