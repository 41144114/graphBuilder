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

    void on_checkBox_clicked();

protected:
    void dropEvent(QDropEvent* event);
    void dragEnterEvent(QDragEnterEvent *e);

private:
    Ui::MainWindow *ui;
    QFile* _pFile;
    QList<QVector<double>> _dataList;
    QString _head;
    bool _isHeadAdded;

    GraphView _graphView;


    void readFile(QString fName);
    void clearData();
    void setComboBoxContent();
    void crutchWithHead();
};

#endif // MAINWINDOW_H
