#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void btnNumber(int btnNum);
private:
    Ui::MainWindow *ui;

public:
    /*
    Brush : 1
    Paint : 2
    Text  : 3
    Erase : 4
    Crop  : 5
    Resize: 6
    */
    int recentClickedTool;
};

#endif // MAINWINDOW_H
