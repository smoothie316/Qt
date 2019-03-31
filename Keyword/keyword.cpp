#include "keyword.h"

Keyword::Keyword(QWidget *parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clicked()));
    keyInput = new KeywordInput();
}

void Keyword::clicked(){
    keyInput->show();
}
