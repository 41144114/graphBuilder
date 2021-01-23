#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QVector>
#include <QDropEvent>
#include <QDragEnterEvent>
#include "graphview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void onGraphViewClosed();

protected:
    void dropEvent(QDropEvent* event);
    void dragEnterEvent(QDragEnterEvent *e);

private:
    Ui::MainWindow *ui;
    void readFile(QString fName);
    QFile* m_file;
    QList<QVector<double>> m_dataList;

    GraphView m_graphView;
};

#endif // MAINWINDOW_H
