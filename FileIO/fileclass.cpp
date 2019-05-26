#include "FileIO/fileclass.h"

#include <QDebug>
#include <QApplication>

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

bool FileClass::removeDir(const QString & dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists()) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = QDir().rmdir(dirName);
    }
    return result;
}

void FileClass::removeAllDir()
{
    QString dirName[81] = {"bufImage","person", "bicycle", "car", "motorcycle", "airplane",
            "bus", "train", "truck", "boat", "traffic light",
            "fire hydrant", "stop sign", "parking meter", "bench", "bird",
            "cat", "dog", "horse", "sheep", "cow", "elephant", "bear",
            "zebra", "giraffe", "backpack", "umbrella", "handbag", "tie",
            "suitcase", "frisbee", "skis", "snowboard", "sports ball",
            "kite", "baseball bat", "baseball glove", "skateboard",
            "surfboard", "tennis racket", "bottle", "wine glass", "cup",
            "fork", "knife", "spoon", "bowl", "banana", "apple",
            "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza",
            "donut", "cake", "chair", "couch", "potted plant", "bed",
            "dining table", "toilet", "tv", "laptop", "mouse", "remote",
            "keyboard", "cell phone", "microwave", "oven", "toaster",
            "sink", "refrigerator", "book", "clock", "vase", "scissors",
             "teddy bear", "hair drier", "toothbrush"};

    for(int i = 0; i <81; i++){
        QDir dir("debug/" + dirName[i]);

        if (dir.exists()) {
            removeDir("debug/" + dirName[i]);
        }
    }
}
