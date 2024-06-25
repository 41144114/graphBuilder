#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QAction>
#include <QCloseEvent>
#include <QDateTime>
#include <QMainWindow>
#include <QVector>

class QCustomPlot;
class DftManager;

namespace Ui
{
class GraphView;
}

class GraphView : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphView(QWidget* parent = nullptr);
    ~GraphView();
    void buildGraph(QVector<double>* dataX, QVector<double>* dataY, QString xName, QString yName, int color, int type,
                    double width, QString header, QString pictureLabel);
    void addGraph(QVector<double>* dataX, QVector<double>* dataY, int color, int type, double width);
    void setEnabledContext(bool isEnabled);

signals:
    void closed();
    void startFourierCount(QVector<double>* xValues, QVector<double>* yValues);

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void mousePress(QMouseEvent* event);
    void mouseRelease(QMouseEvent* event);
    void onShowGlobalMenu(QPoint point);
    void onShowFourier(QVector<double>* xValues, QVector<double>* yValues);
    void onCountFourier();

private:
    Ui::GraphView* ui;
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
    bool _isActualZoom;
    bool _isNotZoomedState;
    bool _isEnableContest;
    QVector<double>* _dataX;
    QVector<double>* _dataY;

    QDateTime _startTime;

    QThread* _fourierMngrThread;
    DftManager* _dftManager;

    void doScreen();
    void setDefaultSize();
    bool checkNeedToResize(QPoint start, QPoint finish);
    void resizeByPoints(QPoint start, QPoint finish);
    void resize(QVector<double>* dataX, QVector<double>* dataY);
    QPen setupPen(double width, int type, int color);
    void setupGlobalMenu();
};

#endif // GRAPHVIEW_H
