#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphview.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFile>
#include <QMainWindow>
#include <QVector>

class AboutProgramWindow;
class PaletteMngr;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void onGraphViewClosed();

    void on_checkBox_clicked();
    void onShowGlobalMenu(QPoint point);
    void onAboutQt();
    void onAboutProgram();
    void onTheme();

protected:
    void dropEvent(QDropEvent* event);
    void dragEnterEvent(QDragEnterEvent* e);

private:
    Ui::MainWindow* ui;
    AboutProgramWindow* _pAboutProgram;
    PaletteMngr* _pPaletteMngr;
    QFile* _pFile;
    QVector<QVector<double>> _dataList;
    QString _head;
    QMenu* _pGlobalMenu;
    QAction* _pAboutQtAction;
    QAction* _pAboutProgrammAction;
    QAction* _pThemeAction;
    bool _isHeadAdded;
    bool _isDarkTheme;

    GraphView _graphView;

    void readFile(QString fName);
    void clearData();
    void setComboBoxContent();
    void crutchWithHead();
    void setupGlobalMenu();

    void saveSettings();
    void loadSettings();
};

#endif // MAINWINDOW_H
