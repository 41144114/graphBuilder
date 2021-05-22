#ifndef ABOUTPROGRAMWINDOW_H
#define ABOUTPROGRAMWINDOW_H

#include <QWidget>

namespace Ui {
class AboutProgramWindow;
}

class AboutProgramWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutProgramWindow(QWidget *parent = nullptr);
    ~AboutProgramWindow();

private:
    Ui::AboutProgramWindow *ui;
};

#endif // ABOUTPROGRAMWINDOW_H
