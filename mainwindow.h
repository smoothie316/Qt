#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Keyword/keyword.h>
#include <TabWidget/tabclass.h>
#include <ToolBtn/toolbtn.h>
#include <FileIO/fileclass.h>
#include <vector>
#include <map>
using namespace std;
class QDragEnterEvent;
class QDropEvent;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void resetPixmap(QPixmap* buf, int pageNum);

private slots:
    void addMainTab(QWidget* page, QString name);
    void addSubTab(QWidget* page, QString name);
    void on_MainTab_tabCloseRequested(int index);
    void on_FileOpen_clicked();
    void on_Lasso_clicked();
    void on_Brush_clicked();
    void on_Crop_clicked();
    void on_Resize_clicked();
    void on_Text_clicked();
    void on_Erase_clicked();
    void on_Paint_clicked();
    void setEndByTools();
    void on_LayerCreate_clicked();
    void on_LayerDel_clicked();
    void on_MainTab_currentChanged(int index);
    void setSubPageName(QString name);
    void on_SubTab_tabCloseRequested(int index);
    void on_LayerUp_clicked();
    void on_LayerDown_clicked();
    //void dragEnterEvent(QDragEnterEvent *event) override;
    //void dragMoveEvent(QDragMoveEvent *event) override;
    //void dropEvent(QDropEvent *event) override;
    //void mousePressEvent(QMouseEvent *event) override;

public slots:
    void drawEnd();
    void addTextLayer(QPixmap* pix, QLabel* label);
    void currentBufSize(QSize bufSize);

// 함수 
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *object, QEvent* event);
private:
    void changeToolPage();
    void resetAllLayerName();
    void layerSwap(int a, int b);
    void labelSwap(int a, int b);
    void resetLabel(int index);
    void resetLayer(int index);
    QPixmap sumBuff();

// 변수
public:
  /* Lasso : 0
   * Brush : 1
   * Paint : 2
   * Text  : 3
   * Erase : 4
   * Crop  : 5
   * Resize: 6 */
    int recentClickedTool;
    TabClass* tabs;
    ToolBtn* tools;
    FileClass* fileIO;

    QPixmap* currentBuff;
protected:

private:
    Ui::MainWindow *ui;

    int currentPage;
    int totalPages;

    int currentBufNum;

    // key : page number
    // value : layer(label) instance and buffer info pair list
    map<int, vector<QPixmap*> >  layerInfo;
    map<int, vector<QLabel*> > labelInfo;
    QSize bufSize;

    QString className;
};

#endif // MAINWINDOW_H
