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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:

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

// 함수
    void on_SubTab_tabCloseRequested(int index);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:

private:
    void changeToolPage();

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
protected:

private:
    Ui::MainWindow *ui;

    int currentPage;
    int totalPages;

    // key : page number
    // value : layer(label) instance and buffer info pair list
    map<int, map<QLabel*, QPixmap*> >  layerInfo;

    QString className;
};

#endif // MAINWINDOW_H
