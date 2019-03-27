#include "fileclass.h"

#include <QFileDialog>

FileClass::FileClass(QWidget *parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(clicked()));
}

void FileClass::clicked(){
    if (this->objectName() == QString("FileOpen")){
        // 파일 오픈 코드. 사용가능한 확장자 지정 필요(strFilter).
        // 파일 복수선택 가능하게 만들기
        QString strFilter = "All files (*.*)";
        QString tmpStr = QFileDialog::getOpenFileName(this, "Image", QDir::homePath(), strFilter);
        if(!tmpStr.isEmpty()){
            imgList.push_back(tmpStr);
        }
        box.setText(tmpStr);
    }
    else if(this->objectName() == QString("FileSave")){
        // 파일 저장 코드 작성
    }
    box.exec();
}
