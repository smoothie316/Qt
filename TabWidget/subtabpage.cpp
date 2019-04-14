#include "subtabpage.h"
#include "ui_subtabpage.h"

SubTabPage::SubTabPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubTabPage)
{
    ui->setupUi(this);
}

SubTabPage::~SubTabPage()
{
    delete ui;
}
