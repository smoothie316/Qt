#include "keywordinput.h"
#include "ui_keywordinput.h"

#include <QResource>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCompleter>

#include <FileIO/fileclass.h>

KeywordInput::KeywordInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeywordInput)
{
    ui->setupUi(this);

    QCompleter* completer = new QCompleter( this );
    completer->setModel( ui->listWidget->model() );
    completer->setCaseSensitivity( Qt::CaseInsensitive );
    ui->lnEdit->setCompleter( completer );

    FileClass file;
    QStringList keywordList = file.keywordFileRead();

    for(int i = 0; i < keywordList.length(); i++){
        ui->listWidget->addItem(keywordList[i]);
        ui->lnEdit->clear();
    }
}


KeywordInput::~KeywordInput()
{
    delete ui;
}


void KeywordInput::on_BackBtn_clicked()
{
    emit setEnd();
}
