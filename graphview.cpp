#include "graphview.h"
#include "ui_graphview.h"

#include "qcustomplot.h"
#include <QPen>
#include <QColor>
#include <QPixmap>
#include <QClipboard>
#include <QDebug>

GraphView::GraphView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphView)
{
    ui->setupUi(this);
    _pPlot = new QCustomPlot(this);
    ui->gridLayout->addWidget(_pPlot);
    _pDoScreenAction = new QAction("getScreen", this);
    _pDoScreenAction->setShortcut(tr("Ctrl+C"));
    connect(_pDoScreenAction, &QAction::triggered, this, &GraphView::doScreen);
    this->addAction(_pDoScreenAction);

    //_pPlot->xAxis->setBasePen(QPen(QColor(Qt::red))); //<-установка линии самой оси
    _pPlot->xAxis->setTickLabelFont(QFont("Times", 12));
    _pPlot->yAxis->setTickLabelFont(QFont("Times", 12));
    _pPlot->xAxis->setLabelFont(QFont("Times", 12));
    _pPlot->yAxis->setLabelFont(QFont("Times", 12));
}

GraphView::~GraphView()
{
    delete ui;
}

void GraphView::buildGraph(QVector<double> *dataX, QVector<double> *dataY, QString xName, QString yName, bool isHeader, int color, int type)
{

    _curGraphIndex = 0;
    if(isHeader)
    {
        dataX->takeFirst();
        dataY->takeFirst();
    }
    QPointer<QCPGraph> mGraph1;
    mGraph1 = _pPlot->addGraph(_pPlot->xAxis, _pPlot->axisRect()->axis(QCPAxis::atRight, 0));
    QPen pen;
    pen.setWidthF(0.5);
    switch(color)
    {
        case 0: pen.setColor(Qt::black);       break;
        case 1: pen.setColor(Qt::darkGray);    break;
        case 2: pen.setColor(Qt::gray);        break;
        case 3: pen.setColor(Qt::lightGray);   break;
        default: pen.setColor(Qt::black);        break;
    }

    switch(type)
    {
        case 0: pen.setStyle(Qt::SolidLine); break;
        case 1: pen.setStyle(Qt::DashLine); break;
        case 2: pen.setStyle(Qt::DashDotLine); break;
        default: pen.setStyle(Qt::SolidLine); break;
    }

    mGraph1->setPen(pen);
    mGraph1->setData(*dataX, *dataY);

    _pPlot->xAxis->rescale();
    double max = dataY->at(0);
    double min = dataY->at(0);
    for(int i = 1; i < dataY->count(); ++i)
    {
        if(dataY->at(i) > max) max = dataY->at(i);
        if(dataY->at(i) < min) min = dataY->at(i);
    }
    _pPlot->yAxis->setRange(max, min);
    mGraph1->rescaleValueAxis(false, false);

    _pPlot->xAxis->setLabel(xName);
    _pPlot->yAxis->setLabel(yName);
    _pPlot->replot();
    show();
}

void GraphView::addGraph(QVector<double> *dataX, QVector<double> *dataY, bool isHeader, int color, int type)
{
    _curGraphIndex++;
    _pPlot->addGraph(_pPlot->xAxis, _pPlot->axisRect()->axis(QCPAxis::atRight, 0));
}


void GraphView::doScreen()
{
    this->raise();
    QApplication::clipboard()->setPixmap(QPixmap(this->windowHandle()->screen()->grabWindow(QWidget::winId())));
}


//================== Events ==========================================
void GraphView::closeEvent(QCloseEvent *event)
{
    _pPlot->clearGraphs();
    emit closed();
    event->accept();
}
