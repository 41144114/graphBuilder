#ifndef DFTCOUNTER_H
#define DFTCOUNTER_H

#include <QObject>
template <typename T> class QVector;

class DFTCounter : public QObject
{
    Q_OBJECT
public:
    explicit DFTCounter(QObject *parent = nullptr);
    ~DFTCounter();
public slots:
    void getDFT(QVector<double> *xPoints, QVector<double> *yPoints, QVector<double>* xOutPoints, QVector<double>* yOutPoints);
    void getDFT(QVector<double> *xPoints, QVector<double> *yPoints, QVector<double>* xOutPoints, QVector<double>* yOutPoints, int startIndex, int finishIndex);
signals:
    void ready();
};

#endif // DFTCOUNTER_H
