#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->tabs = new TabClass();
    this->fileIO = new FileClass();
    connect(fileIO, SIGNAL(createImage(QStringList)), tabs, SLOT(mainCreateImage(QStringList)));
    connect(tabs, SIGNAL(addMainTab(QWidget*, QString)), this, SLOT(addMainTab(QWidget*, QString)));
    connect(tabs, SIGNAL(addSubTab(QWidget*, QString)), this, SLOT(addSubTab(QWidget*, QString)));
    connect(this, SIGNAL(resetPixmap(QPixmap*, int)), tabs, SLOT(resetPixmap(QPixmap*, int)));

    this->tools = new ToolBtn();
    connect(tools, SIGNAL(setEnd()), this, SLOT(setEndByTools()));
    connect(tools, SIGNAL(setName(QString)), this, SLOT(setSubPageName(QString)));
    this->ui->ToolStack->setCurrentIndex(0);

    this->currentPage = -1;
    this->totalPages = -1;
    this->currentBufNum = 0;
    //bufImage 폴더 생성
    QString logPath = "debug/bufImage";
    QDir dir;
    dir.mkpath(logPath);
}

MainWindow::~MainWindow(){
    QString filePath = QApplication::applicationDirPath();
    //FileClass().removeDir("debug/bufImage");
    FileClass().removeAllDir();
    //bufImage 폴더 삭제
    delete ui;
}

bool MainWindow::eventFilter(QObject* object, QEvent* event){
    if(event->type() == QMouseEvent::MouseButtonPress){
        //마우스 클릭 이벤트 발생시
        QStringList list = object->objectName().split(",");
        this->currentBufNum = list[1].toInt();
        qDebug() << this->currentBufNum;
        this->currentBuff = this->layerInfo.at(this->currentPage).at(this->currentBufNum);
        return true;
    }
    return QWidget::eventFilter(object, event);
}

// Tab page 관련 설정
void MainWindow::addMainTab(QWidget* page, QString name){
    // main tab widget에 page를 추가하고 이미지 표시
    // 모든 데이터 초기화 담당

    QString style = "border-color:rgb(0,0,0); border-width:1.2px; border-style:solid;";

    this->totalPages++;
    vector<QPixmap*> tmpVec;
    QWidget* widget = new QWidget();
    QGridLayout* grid = new QGridLayout();
    QLabel* tmpLayer = new QLabel(widget);
    QPixmap* tmpBuf = new QPixmap();
    // 레이어QLabel 이벤트 처리
    tmpLayer->installEventFilter(this);
    this->tabs->getBuff(tmpBuf, this->totalPages);
    tmpLayer->setPixmap(tmpBuf->scaled(ui->LayerWidget->width(), ui->LayerWidget->height(), Qt::KeepAspectRatio));
    tmpLayer->show();
    tmpVec.push_back(tmpBuf);
    this->layerInfo.insert(make_pair(this->totalPages, tmpVec));
    tmpLayer->setObjectName(QString::number(this->totalPages)+ "," + QString::number(0));
    tmpLayer->setStyleSheet(style);

    //bufImage 폴더에 임시 저장
    QStringList nameList = name.split("/");
    int listCount = name.split("/").length()-1;
    QString filename ="debug/bufImage/"+ nameList[listCount];
    tmpBuf->save(filename,"PNG");
    qDebug() << filename;

    grid->addWidget(tmpLayer);
    widget->setLayout(grid);
    vector<QLabel*> tmpLabelVec;
    tmpLabelVec.push_back(tmpLayer);
    this->labelInfo.insert(make_pair(this->totalPages, tmpLabelVec));
    ui->LayerWidget->addWidget(widget);
    ui->MainTab->addTab(page, name);
}

void MainWindow::on_MainTab_tabCloseRequested(int index){
    // main tab widget에 page를 삭제할 때 사용되는 함수
    // 이미지 파일 저장 관련 수행 필요
    this->totalPages--;

    //종료된 탭의 파일 삭제
    QString name = ui->MainTab->tabText(index);
    qDebug() << name;
    QStringList nameList = name.split("/");
    int listCount = name.split("/").length()-1;
    QString filename ="debug/bufImage/"+ nameList[listCount];
    QFile::remove(filename);

    ui->MainTab->removeTab(index);
    ui->LayerWidget->removeWidget(ui->LayerWidget->currentWidget());
}

void MainWindow::on_LayerCreate_clicked(){
    // 레이어 추가 (create 버튼)

    // 테두리 추가
    QString style = "border-color:rgb(0,0,0); border-width:1.2px; border-style:solid;";

    QPixmap *origin = this->layerInfo.at(this->currentPage).at(0);
    QPixmap* tmpPix = new QPixmap(origin->width(), origin->height());
    QImage* tmpImg = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32_Premultiplied);
    tmpImg->fill(Qt::transparent);
    *tmpPix = QPixmap::fromImage(*tmpImg);

    this->currentBufNum++;
    qDebug() << this->currentBufNum;
    QWidget* widget = this->ui->LayerWidget->currentWidget();
    QLabel* tmpLayer = new QLabel(widget);
    tmpLayer->setPixmap(tmpPix->scaled(this->width(), this->height(), Qt::KeepAspectRatio));
    tmpLayer->setObjectName(QString::number(this->currentPage)+ "," + QString::number(this->currentBufNum));
    this->layerInfo.at(this->currentPage).push_back(tmpPix);
    this->labelInfo.at(this->currentPage).push_back(tmpLayer);
    tmpLayer->installEventFilter(this);
    tmpLayer->setStyleSheet(style);

    widget->layout()->addWidget(tmpLayer);
    // MainPage QLabel 새로그리는 Event 발생


    QPixmap buff = sumBuff();
    emit resetPixmap(&buff, this->currentPage);
}

void MainWindow::on_LayerDel_clicked(){
    // 레이어 삭제 (delete 버튼)
    QWidget* widget = this->labelInfo.at(this->currentPage).at(this->currentBufNum);
    this->layerInfo.at(this->currentPage).erase(this->layerInfo.at(this->currentPage).begin() + this->currentBufNum);
    this->labelInfo.at(this->currentPage).erase(this->labelInfo.at(this->currentPage).begin() + this->currentBufNum);
    this->currentBufNum -= 1;
    if(this->currentBufNum < 0)
        this->currentBufNum = 0;
    delete widget;
    this->resetAllLayerName();
    // MainPage QLabel 새로그리는 Event 발생시키기


    QPixmap buff = sumBuff();
    emit resetPixmap(&buff, this->currentPage);
}

void MainWindow::on_LayerUp_clicked()
{
    if(this->currentBufNum == 0)
        return;

    layerSwap(this->currentBufNum-1, this->currentBufNum);
    labelSwap(this->currentBufNum-1, this->currentBufNum);

    this->currentBufNum--;

    QPixmap buff = sumBuff();
    emit resetPixmap(&buff, this->currentPage);
}

void MainWindow::on_LayerDown_clicked()
{
    if(this->currentBufNum == this->labelInfo.at(this->currentPage).size()-1)
        return;

    layerSwap(this->currentBufNum, this->currentBufNum+1);
    labelSwap(this->currentBufNum, this->currentBufNum+1);

    this->currentBufNum++;

    QPixmap buff = sumBuff();
    emit resetPixmap(&buff, this->currentPage);
}

QPixmap MainWindow::sumBuff(){
    QPixmap buff;
    QPixmap *origin = this->layerInfo.at(this->currentPage).at(0);
    QImage* finalImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32_Premultiplied);
    for(int k = this->layerInfo.at(this->currentPage).size()-1; k >= 0  ; k-- ){
        QImage tmp = this->layerInfo.at(this->currentPage).at(k)->toImage();
        for(int i = 0; i<origin->width(); i++){
            for(int j=0; j<origin->height(); j++){
                if(tmp.pixelColor(i,j) == Qt::transparent)
                    continue;
                finalImage->setPixel(i,j, tmp.pixel(i,j));
            }
        }
    }
    buff = QPixmap::fromImage(*finalImage);
    return buff;
}

void MainWindow::layerSwap(int a, int b){
    vector<QPixmap*> tmpLayer = this->layerInfo.at(this->currentPage);
    QPixmap* tmpPix = this->layerInfo.at(this->currentPage).at(a);
    this->layerInfo.at(this->currentPage).at(a) = this->layerInfo.at(this->currentPage).at(b);
    this->layerInfo.at(this->currentPage).at(b) = tmpPix;
}

void MainWindow::labelSwap(int a, int b){
    vector<QLabel*> tmpLabel = this->labelInfo.at(this->currentPage);
    vector<QPixmap*> tmpPix = this->layerInfo.at(this->currentPage);
    this->labelInfo.at(this->currentPage).at(a)->setPixmap(tmpPix.at(a)->scaled(tmpLabel.at(a)->width(), tmpLabel.at(a)->height(), Qt::KeepAspectRatio));
    this->labelInfo.at(this->currentPage).at(b)->setPixmap(tmpPix.at(b)->scaled(tmpLabel.at(b)->width(), tmpLabel.at(b)->height(), Qt::KeepAspectRatio));
    this->labelInfo.at(this->currentPage).at(a)->show();
    this->labelInfo.at(this->currentPage).at(b)->show();
}

void MainWindow::resetAllLayerName(){
    for(int i=0; i<this->labelInfo.at(this->currentPage).size(); i++){
        QWidget* widget = this->labelInfo.at(this->currentPage).at(i);
        widget->setObjectName(QString::number(this->currentPage) + "," + QString::number(i));
    }
}

void MainWindow::on_MainTab_currentChanged(int index){
    if(index != -1){
        this->currentPage = index;
        ui->LayerWidget->setCurrentIndex(this->currentPage + 1);
    }
}
void MainWindow::setSubPageName(QString name){
    this->tabs->subTabCreate(name);
}
void MainWindow::addSubTab(QWidget* page, QString name){
    //this->tabs->subPageList.at(this->tabs->subPageList.size()-1)->setImage("/cat/");
    ui->SubTab->addTab(page, name);
}
void MainWindow::on_SubTab_tabCloseRequested(int index){
    ui->SubTab->removeTab(index);
}

// Tool Button 설정 slot들
void MainWindow::on_FileOpen_clicked(){
    // 사용자가 이미지 파일을 열기 위해 file open버튼을 클릭했을 때 발생
    //
    fileIO->ImageOpen();
}
void MainWindow::on_Lasso_clicked(){
    this->recentClickedTool = 0;
    this->tools->keyword->clicked();
}
void MainWindow::on_Brush_clicked(){
    this->recentClickedTool = 1;
    ui->ToolStack->addWidget(this->tools->brushW);
    ui->ToolStack->setCurrentIndex(1);
}
void MainWindow::on_Paint_clicked(){
    this->recentClickedTool = 2;
    ui->ToolStack->addWidget(this->tools->paintW);
    ui->ToolStack->setCurrentIndex(1);
}
void MainWindow::on_Text_clicked(){
    this->recentClickedTool = 3;
    ui->ToolStack->addWidget(this->tools->textW);
    ui->ToolStack->setCurrentIndex(1);
}
void MainWindow::on_Erase_clicked(){
    this->recentClickedTool = 4;
    ui->ToolStack->addWidget(this->tools->eraseW);
    ui->ToolStack->setCurrentIndex(1);
}
void MainWindow::on_Crop_clicked(){
    this->recentClickedTool = 5;
}
void MainWindow::on_Resize_clicked(){
    this->recentClickedTool = 6;
}
void MainWindow::changeToolPage(){

}
void MainWindow::setEndByTools(){
    this->ui->ToolStack->removeWidget(this->ui->ToolStack->widget(1));
    this->ui->ToolStack->setCurrentIndex(0);
}


