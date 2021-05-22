#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QMainWindow>
#include <QVector>
#include <QCloseEvent>
#include <QAction>

class QCustomPlot;

namespace Ui {
class GraphView;
}

class GraphView : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = 0);
    ~GraphView();
    void buildGraph(QVector<double> *dataX, QVector<double> *dataY, QString xName, QString yName, int color, int type, double width, QString header, QString pictureLabel);
    void addGraph(QVector<double> *dataX, QVector<double> *dataY, int color, int type, double width);

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void mousePress(QMouseEvent* event);
    void mouseRelease(QMouseEvent* event);
    void onShowGlobalMenu(QPoint point);
    void onShowFourier();


private:
    Ui::GraphView *ui;
    QCustomPlot* _pPlot;
    QAction* _pDoScreenAction;
    QMenu* _pGlobalMenu;
    QAction* _pShowFourier;
    double _curMaxX;
    double _curMaxY;
    double _curMinX;
    double _curMinY;
    int _curGraphIndex;
    QPoint _startPoint;
    bool isActualZoom;

    void doScreen();
    void setDefaultSize();
    bool checkNeedToResize(QPoint start, QPoint finish);
    void resizeByPoints(QPoint start, QPoint finish);
    void resize(QVector<double> *dataX, QVector<double> *dataY);
    QPen setupPen(double width, int type, int color);
    void setupGlobalMenu();


};

#endif // GRAPHVIEW_H
