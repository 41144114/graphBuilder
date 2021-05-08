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

private:
    Ui::GraphView *ui;
    QCustomPlot* _pPlot;
    QAction* _pDoScreenAction;
    int _curGraphIndex;
    void doScreen();
    QPen setupPen(double width, int type, int color);
};

#endif // GRAPHVIEW_H
