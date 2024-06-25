#include "aboutprogramwindow.h"
#include "ui_aboutprogramwindow.h"

AboutProgramWindow::AboutProgramWindow(QWidget* parent) : QWidget(parent), ui(new Ui::AboutProgramWindow)
{
    ui->setupUi(this);
    ui->labelDescription->setText("Строит графики по рядам данных из текста.\r\n"
                                  "Ряд данных должен располагаться в столбик.\r\n"
                                  "Числа в одной строке должны быть отделены точкой с запятой.\r\n"
                                  "Если вам нужно построить график по такому файлу, то эта программа\r\n"
                                  "будет куда эффективнее чем Excel. К тому же она проще и быстрее \r\n"
                                  "настраивается.\r\n"
                                  "А ещё она бесплатная)");
}

AboutProgramWindow::~AboutProgramWindow() { delete ui; }
