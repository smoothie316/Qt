#include "keyword.h"
#include <QEvent>
#include <QMessageBox>
#include <QDesktopServices>
#include <QApplication>
#include <QUrl>

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
        QString filePath = QApplication::applicationDirPath();
        QDesktopServices::openUrl(QUrl(filePath+"/table.html", QUrl::TolerantMode));
    }
    return false;
}
