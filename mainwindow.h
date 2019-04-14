#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Keyword/keyword.h>
#include <TabWidget/tabclass.h>
#include <ToolBtn/toolbtn.h>
#include <FileIO/fileclass.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void recentTool(int recentToolBtn);

private slots:
    void addMainTab(QWidget* page, QString name);
    void on_MainTab_tabCloseRequested(int index);
    void on_FileOpen_clicked();
    void on_Lasso_clicked();
    void on_Brush_clicked();
    void on_Crop_clicked();
    void on_Resize_clicked();
    void on_Text_clicked();
    void on_Erase_clicked();
    void on_Paint_clicked();

private:
    Ui::MainWindow *ui;

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
};

#endif // MAINWINDOW_H
