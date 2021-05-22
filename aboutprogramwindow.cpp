#include "aboutprogramwindow.h"
#include "ui_aboutprogramwindow.h"

AboutProgramWindow::AboutProgramWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutProgramWindow)
{
    ui->setupUi(this);
}

AboutProgramWindow::~AboutProgramWindow()
{
    delete ui;
}
