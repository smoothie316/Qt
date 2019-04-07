#include "keyword.h"
#include <QEvent>
#include <QMessageBox>

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
        // html파일 열기
    }
}
