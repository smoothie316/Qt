#include "keyword.h"
#include <QEvent>
#include <QDesktopServices>
#include <QApplication>
#include <QUrl>

Keyword::Keyword(QWidget *parent) : QWidget(parent)
{
    keyInput = new KeywordInput();
    connect(keyInput, SIGNAL(className(QString)), this, SLOT(receiveInput(QString)));
}

void Keyword::clicked(){
    keyInput->installEventFilter(this);
    keyInput->show();
}

bool Keyword::eventFilter(QObject *object, QEvent *event){
    if(object == keyInput && event->type() == QEvent::EnterWhatsThisMode){
        // 파일 경로 설정문제
        QString filePath = QApplication::applicationDirPath();
        //QResource rc(":/Class/table.html");
        //qDebug() << rc.absoluteFilePath();
        QDesktopServices::openUrl(QUrl(filePath + "/table.html", QUrl::TolerantMode));
        return true;
    }
    return false;
}

void Keyword::receiveInput(QString name){
    emit className(name);
}
