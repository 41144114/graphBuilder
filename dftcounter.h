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
    void setData(QVector<double> *xPoints, QVector<double> *yPoints,
                 double* xOutPoints, double* yOutPoints, int startIndex, int finishIndex);

public slots:
//    void getDFT(QVector<double> *xPoints, QVector<double> *yPoints, QVector<double>* xOutPoints, QVector<double>* yOutPoints);
    void onCount();
signals:
    void ready();

private:
    QVector<double> *_xPoints;
    QVector<double> *_yPoints;
    double* _xOutPoints;
    double* _yOutPoints;
    int _startIndex;
    int _finishIndex;
};

#endif // DFTCOUNTER_H
