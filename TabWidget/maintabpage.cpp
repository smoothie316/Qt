#include "maintabpage.h"
#include "ui_maintabpage.h"

MainTabPage::MainTabPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTabPage)
{
    ui->setupUi(this);
}

MainTabPage::~MainTabPage()
{
    delete ui;
}
