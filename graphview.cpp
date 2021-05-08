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
    setWindowTitle("Окно графиков");
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
    ui->label->setFont(QFont("Times", 12));
    ui->label_2->setFont(QFont("Times", 12));
    ui->label->setStyleSheet("background-color: white");
    ui->label_2->setStyleSheet("background-color: white");
}

GraphView::~GraphView()
{
    delete ui;
}

void GraphView::buildGraph(QVector<double> *dataX, QVector<double> *dataY, QString xName, QString yName,
                           int color, int type, double width, QString header, QString pictureLabel)
{
    _curGraphIndex = 0;

    addGraph(dataX, dataY, color, type, width);

    if(header.isEmpty())
        ui->label->setVisible(false);
    else
    {
        ui->label->setText(header);
        ui->label->setVisible(true);
    }

    if(pictureLabel.isEmpty())
        ui->label_2->setVisible(false);
    else
    {
        ui->label_2->setText(pictureLabel);
        ui->label_2->setVisible(true);
    }

    _pPlot->xAxis->setLabel(xName);
    _pPlot->yAxis->setLabel(yName);
    _pPlot->replot();
    show();
}

void GraphView::addGraph(QVector<double> *dataX, QVector<double> *dataY, int color, int type, double width)
{
    _pPlot->addGraph(_pPlot->xAxis, _pPlot->yAxis);
    QPen pen = setupPen(width, type, color);


    _pPlot->graph(_curGraphIndex)->setPen(pen);
    _pPlot->graph(_curGraphIndex)->setData(*dataX, *dataY);

    double max = dataY->at(0);
    double min = dataY->at(0);
    double minX = dataX->at(0);
    double maxX = dataX->at(0);
    for(int i = 1; i < dataY->count(); ++i)
    {
        if(dataY->at(i) > max) max = dataY->at(i);
        if(dataY->at(i) < min) min = dataY->at(i);
        if(dataX->at(i) > maxX) maxX = dataX->at(i);
        if(dataX->at(i) < minX) minX = dataX->at(i);
    }

    if(_curGraphIndex == 0)
    {
        _pPlot->yAxis->setRange(max, min);
        _pPlot->xAxis->setRange(maxX, minX);
    }
    else
    {
        if(_pPlot->yAxis->range().maxRange < max)
            _pPlot->yAxis->setRange(max, _pPlot->yAxis->range().minRange);
        if(_pPlot->yAxis->range().minRange > min)
            _pPlot->yAxis->setRange(_pPlot->yAxis->range().maxRange, min);

        if(_pPlot->xAxis->range().maxRange < maxX)
            _pPlot->xAxis->setRange(maxX, _pPlot->xAxis->range().minRange);
        if(_pPlot->xAxis->range().minRange > minX)
            _pPlot->xAxis->setRange(_pPlot->xAxis->range().maxRange, minX);
    }

    _curGraphIndex++;
    _pPlot->replot();
}

QPen GraphView::setupPen(double width, int type, int color)
{
    QPen pen;
    pen.setWidthF(width);
    switch(color)
    {
        case 0: pen.setColor(Qt::black);        break;
        case 1: pen.setColor(Qt::darkGray);     break;
        case 2: pen.setColor(Qt::gray);         break;
        case 3: pen.setColor(Qt::lightGray);    break;
        case 4: pen.setColor(Qt::blue);         break;
        case 5: pen.setColor(Qt::darkCyan);     break;
        case 6: pen.setColor(Qt::cyan);         break;
        case 7: pen.setColor(Qt::yellow);       break;
        case 8: pen.setColor(Qt::darkYellow);   break;
        case 9: pen.setColor(Qt::red);          break;
        case 10: pen.setColor(Qt::magenta);     break;
        case 11: pen.setColor(Qt::green);       break;
    }

    switch(type)
    {
        case 0: pen.setStyle(Qt::SolidLine); break;
        case 1: pen.setStyle(Qt::DashLine); break;
        case 2: pen.setStyle(Qt::DashDotLine); break;
        default: pen.setStyle(Qt::SolidLine); break;
    }
    return pen;
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
