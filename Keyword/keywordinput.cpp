#include "keywordinput.h"
#include "ui_keywordinput.h"

KeywordInput::KeywordInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeywordInput)
{
    ui->setupUi(this);

    QCompleter* completer = new QCompleter( this );
    completer->setModel( ui->listWidget->model() );
    completer->setCaseSensitivity( Qt::CaseInsensitive );
    ui->lnEdit->setCompleter( completer );

    QString filePath = QApplication::applicationDirPath();
    QFile file(filePath + "/coco.txt");

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        if(!file.exists()){
            qDebug() << "No File";
        }
        else{
            qDebug() << "why?";
        }
    }

    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        ui->listWidget->addItem(line);
        ui->lnEdit->clear();
    }

}


KeywordInput::~KeywordInput()
{
    delete ui;
}

