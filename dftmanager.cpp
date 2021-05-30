#include "dftmanager.h"
#include <QVector>
#include <QThread>
#include <QDebug>
#include "dftcounter.h"

DftManager::DftManager(QObject *parent) : QObject(parent)
{
    _xResult = new QVector<double>;
    _yResult = new QVector<double>;
    _threads = new QVector<QThread*>;
    _counters = new QVector<DFTCounter*>;
}

DftManager::~DftManager()
{
    while(_threads->count() > 0)
    {
        QThread* temp = _threads->takeLast();
        temp->terminate();
        delete temp;
        delete _counters->takeLast();
    }
}

void DftManager::onStart(QVector<double>* xPoints, QVector<double>* yPoints)
{
    _nThreads = QThread::idealThreadCount() - 1;
    _nReadyThreads = 0;
    QThread* thread;
    DFTCounter* counter;
    _xResult->resize(yPoints->size());
    _yResult->resize(yPoints->size());
    double* resX = _xResult->data();
    double* resY = _yResult->data();

    int nValues = xPoints->count() / _nThreads;
    int startIndex = 0;
    int finishIndex = xPoints->count()-1;

    for(int i = 0; i < _nThreads; ++i)
    {
        startIndex = i * nValues;
        finishIndex = startIndex + nValues - 1;
        if(i == _nThreads - 1)
            finishIndex = xPoints->count()-1;

        thread = new QThread();
        counter = new DFTCounter();
        _threads->append(thread);
        _counters->append(counter);
        counter->setData(xPoints, yPoints, &resX[startIndex], &resY[startIndex], startIndex, finishIndex);

        counter->moveToThread(thread);
        thread->start(QThread::HighPriority);
        connect(counter, &DFTCounter::ready, this, &DftManager::onStageFinished);
        connect(this, &DftManager::start, counter, &DFTCounter::onCount);
        emit start();
        disconnect(this, &DftManager::start, counter, &DFTCounter::onCount);
    }
}

void DftManager::onStageFinished()
{
    _nReadyThreads++;
    if(_nReadyThreads == _nThreads)
        emit finished(_xResult, _yResult);
}
