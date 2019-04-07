#include "keyword.h"
#include <QEvent>
#include <QMessageBox>
#include <QDesktopServices>
#include <QApplication>
#include <QResource>
#include <QUrl>
#include <QFile>

Keyword::Keyword(QWidget *parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clicked()));
    keyInput = new KeywordInput();

}

void Keyword::clicked(){
    keyInput->show();
    keyInput->installEventFilter(this);
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
