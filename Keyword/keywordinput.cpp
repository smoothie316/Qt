#include "keywordinput.h"
#include "ui_keywordinput.h"
#include "loadingdialog.h"

#include <QResource>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCompleter>
#include <QDesktopServices>
#include <QLabel>
#include <QMovie>

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

}

void KeywordInput::on_bnAdd_clicked()
{   
    //QString filePath = QApplication::applicationDirPath();
    this->_className = ui->lnEdit->text();
    this->close();

    //inputName의폴더 생성
    QString logPath = _className;
    QDir dir;
    dir.mkpath("debug/" + logPath);
    bool b = false;
    // 실행 파일의 경로를 설정 한다.
    QString _exePath = "debug//lassoFunction//lasso.exe";
    QProcess *processEXE = new QProcess(this);
    LoadingDialog lDialog;
    // 실행 파일이 있는지 체크 한다.
    if (QFile::exists(_exePath))
    {
        //lDialog.show();
    // 실행 파일이 정상적으로 존재 한다면 QProcess 생성
    // 비교를 하는 이유는 다른 곳에서 생성했을 수도 있다.

    // 간혹 실행파일의 시작위치를 지정해 주지 않으면 오동작 하는 프로그램이 있다.
        //std::string _workingPath = (_exePath.toStdString()).substr(0, (_exePath.toStdString()).find_last_of('/') - 1);
        //processEXE->setWorkingDirectory(QString::fromStdString(_workingPath));
        processEXE->setWorkingDirectory("debug//lassoFunction");
    // 아규먼트가 필요하다면 이렇게 ..
        QStringList _arguments;
        _arguments << _className << "debug/";
        //_arguments << "debug/";

        qDebug() << _arguments;
        qDebug() << _exePath;
    // 실행한다..
        processEXE->execute(_exePath, _arguments);
    // 아규먼트가 불필요 하다면 ...
    // processEXE->start(_exePath);
    }
    lDialog.close();
    qDebug() << "DONE";
    emit className(this->_className);
}
