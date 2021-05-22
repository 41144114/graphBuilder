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

    _pPlot->xAxis->setTickLabelFont(QFont("Times", 12));
    _pPlot->yAxis->setTickLabelFont(QFont("Times", 12));
    _pPlot->xAxis->setLabelFont(QFont("Times", 12));
    _pPlot->yAxis->setLabelFont(QFont("Times", 12));
    ui->label->setFont(QFont("Times", 12));
    ui->label_2->setFont(QFont("Times", 12));
    ui->label->setStyleSheet("background-color: white");
    ui->label_2->setStyleSheet("background-color: white");

    setupGlobalMenu();

    connect(_pPlot, &QCustomPlot::mousePress, this, &GraphView::mousePress);
    connect(_pPlot, &QCustomPlot::mouseRelease, this, &GraphView::mouseRelease);
}

GraphView::~GraphView()
{
    delete ui;
}

void GraphView::buildGraph(QVector<double> *dataX, QVector<double> *dataY, QString xName, QString yName,
                           int color, int type, double width, QString header, QString pictureLabel)
{
    _curGraphIndex = 0;
    _pPlot->clearGraphs();

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

    resize(dataX, dataY);

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

void GraphView::resize(QVector<double> *dataX, QVector<double> *dataY)
{
    if(_curGraphIndex == 0)
    {
        _curMaxY = dataY->at(0);
        _curMinY = dataY->at(0);
        _curMinX = dataX->at(0);
        _curMaxX = dataX->at(0);
    }

    double maxY = _curMaxY;
    double minY = _curMinY;
    double minX = _curMinX;
    double maxX = _curMaxX;

    for(int i = 0; i < dataY->count(); ++i)
    {
        if(dataY->at(i) > maxY) maxY = dataY->at(i);
        if(dataY->at(i) < minY) minY = dataY->at(i);
        if(dataX->at(i) > maxX) maxX = dataX->at(i);
        if(dataX->at(i) < minX) minX = dataX->at(i);
    }

    if(maxY > _curMaxY)
        _curMaxY = maxY;
    if(minY < _curMinY)
        _curMinY = minY;
    if(maxX > _curMaxX)
        _curMaxX = maxX;
    if(minX < _curMinX)
        _curMinX = minX;

    _pPlot->yAxis->setRange(_curMaxY, _curMinY);
    _pPlot->xAxis->setRange(_curMaxX, _curMinX);
}

void GraphView::doScreen()
{
    this->raise();
    QApplication::clipboard()->setPixmap(QPixmap(this->windowHandle()->screen()->grabWindow(QWidget::winId())));
}

void GraphView::setDefaultSize()
{
    _pPlot->yAxis->setRange(_curMaxY, _curMinY);
    _pPlot->xAxis->setRange(_curMaxX, _curMinX);
    _pPlot->replot();
}

//============ Resize =================================================================================================
bool GraphView::checkNeedToResize(QPoint start, QPoint finish)
{
    if(abs(start.x() - finish.x()) > 15)
        if(abs(start.y() - finish.y()) > 15)
            return true;
    return false;
}

void GraphView::resizeByPoints(QPoint start, QPoint finish)
{
    _pPlot->yAxis->setRange(_pPlot->yAxis->pixelToCoord(start.y()),_pPlot->yAxis->pixelToCoord(finish.y()));
    _pPlot->xAxis->setRange(_pPlot->xAxis->pixelToCoord(start.x()),_pPlot->xAxis->pixelToCoord(finish.x()));
    _pPlot->replot();
}

void GraphView::mousePress(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        _startPoint = event->pos();
        isActualZoom = true;
    }
    else
        isActualZoom = false;


    if(event->button() == Qt::RightButton)
        setDefaultSize();
}

void GraphView::mouseRelease(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton && isActualZoom)
    {
        QPoint endPoint = event->pos();
        if(checkNeedToResize(_startPoint, endPoint))
            resizeByPoints(_startPoint, endPoint);
    }
}
//=====================================================================================================================
//=
//=
//=
//=
//================== Events ==========================================
void GraphView::closeEvent(QCloseEvent *event)
{
    _pPlot->clearGraphs();
    emit closed();
    event->accept();
}


//=========== Context menu ============================================================================================
void GraphView::setupGlobalMenu()
{
    connect(this, &GraphView::customContextMenuRequested,       this, &GraphView::onShowGlobalMenu);

    _pGlobalMenu = new QMenu(this);
    _pShowFourier = new QAction("Преобразование Фурье", this);
    connect(_pShowFourier,    &QAction::triggered,        this, &GraphView::onShowFourier);
    _pGlobalMenu->addAction(_pShowFourier);

}

void GraphView::onShowGlobalMenu(QPoint point)
{
    _pGlobalMenu->popup(this->mapToGlobal(point));
}

void GraphView::onShowFourier()
{

}
//=====================================================================================================================
