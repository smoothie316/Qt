#include "FileIO/fileclass.h"

#include <QDebug>

FileClass::FileClass(QWidget *parent) : QWidget(parent)
{

}

QStringList FileClass::keywordFileRead(){
    // keyword file read
    QFile file(":/Class/coco.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        if(!file.exists()){
            qDebug() << "No file";
        }
        else {
            qDebug() << "why";
        }
    }
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        keywordList.push_back(line);
    }
    // keyword file read end
    return keywordList;
}

void FileClass::ImageOpen(){
    // jpg, jpeg, png, bmp
    QString strFilter = "JPG image file (*.jpg) ;; JPEG image file (*.jpeg) ;; PNG image file (*.png);; BMP image file (*.bmp)";
    QStringList tmpStr = QFileDialog::getOpenFileNames(this, "Image", QDir::homePath(), strFilter);
    if(!tmpStr.isEmpty())
        emit createImage(tmpStr);
    else {
        // 파일 열기 실패
    }
}
