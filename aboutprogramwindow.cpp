#include "aboutprogramwindow.h"
#include "ui_aboutprogramwindow.h"

AboutProgramWindow::AboutProgramWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutProgramWindow)
{
    ui->setupUi(this);
    ui->label_4->setText("Строит графики по файлам.\r\n"
                         "Требования:\r\n\t"
                         "данные должны быть расположены в столбик,\r\n\t"
                         "данные в одной строке должны быть разделены символом \';\'\r\n\t");
}

AboutProgramWindow::~AboutProgramWindow()
{
    delete ui;
}
