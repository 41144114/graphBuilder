#ifndef DFTMANAGER_H
#define DFTMANAGER_H

#include <QObject>
class DFTCounter;

class DftManager : public QObject
{
    Q_OBJECT
public:
    explicit DftManager(QObject* parent = 0);
    ~DftManager();

signals:
    void finished(QVector<double>* xValues, QVector<double>* yValues);
    void start();

public slots:
    void onStart(QVector<double>* xPoints, QVector<double>* yPoints);

private slots:
    void onStageFinished();

private:
    QVector<double>* _xResult;
    QVector<double>* _yResult;
    int _nThreads;
    int _nReadyThreads;
    QVector<QThread*>* _threads;
    QVector<DFTCounter*>* _counters;
};

#endif // DFTMANAGER_H
