#include "dftcounter.h"

#include "math.h"
#include <QVector>
#include <QDebug>
const double kPi = 3.1415926535897932384626433832795;
const double kPi2 = 2 * kPi;
const double kPi_2 = kPi/2;
const double k3Pi_2 = 3*kPi/2;

DFTCounter::DFTCounter(QObject *parent) : QObject(parent)
{

}

DFTCounter::~DFTCounter()
{

}

//void DFTCounter::getDFT(QVector<double>* xPoints, QVector<double>* yPoints, QVector<double> *xOutPoints, QVector<double> *yOutPoints)
//{
//    int nPoints = xPoints->count();
//    double delta = xPoints->at(1) - xPoints->at(0);
//    double x = 0;
//    double* re = new double[nPoints];
//    double* im = new double[nPoints];
//    double* reStart = re;
//    double* imStart = im;
//    double temp2, temp1, temp;
//    double sinus, cosinus;
//    double* yCurrentPointer = yPoints->data();
//    for(int i = 0; i < nPoints; ++i)
//    {
//        *re = 0;																//Чистка ячеек памяти
//        *im = 0;
//        temp = 0;
//        temp1 = -kPi2*i/nPoints;
//        yCurrentPointer = yPoints->data();
//        for (int j = 0; j < nPoints; j++)
//        {
//            sinus = sin(temp);
//            temp2 = temp - kPi2*floor(temp/kPi2);//Угол в пределах 0 - 2Пи
//            cosinus = (temp2 < kPi_2 || temp2 > k3Pi_2) ? sqrt(1-sinus*sinus) : -sqrt(1-sinus*sinus);
//            *re += *yCurrentPointer*cosinus/nPoints;
//            *im += *yCurrentPointer*sinus/nPoints;
//            temp += temp1;
//            yCurrentPointer++;
//        }
//        yOutPoints->append(2*sqrt((*re)*(*re)+(*im)*(*im)));
//        xOutPoints->append(x);
//        x += delta;
//        re++;
//        im++;
//    }
//    delete[] imStart;
//    delete[] reStart;
//    emit ready();
//}

void DFTCounter::onCount()
{
    int nPoints = _xPoints->count();
    double delta = _xPoints->at(1) - _xPoints->at(0);
    double x = delta * _startIndex;
    double* re = new double[nPoints];
    double* im = new double[nPoints];
    double* reStart = re;
    double* imStart = im;
    double temp2, temp1, temp;
    double sinus, cosinus;
    double* yCurrentPointer = _yPoints->data();
    for(int i = _startIndex; i < _finishIndex; ++i)
    {
        *re = 0;
        *im = 0;
        temp = 0;
        temp1 = -kPi2*i/nPoints;
        yCurrentPointer = _yPoints->data();
        for (int j = 0; j < nPoints; ++j)
        {
            sinus = sin(temp);
            temp2 = temp - kPi2*floor(temp/kPi2);//Угол в пределах 0 - 2Пи
            cosinus = (temp2 < kPi_2 || temp2 > k3Pi_2) ? sqrt(1-sinus*sinus) : -sqrt(1-sinus*sinus);
            *re += *yCurrentPointer*cosinus/nPoints;
            *im += *yCurrentPointer*sinus/nPoints;
            temp += temp1;
            yCurrentPointer++;
        }
        *_yOutPoints = 2*sqrt((*re)*(*re)+(*im)*(*im));
        *_xOutPoints = x;
        _yOutPoints++;
        _xOutPoints++;
        x += delta;
        re++;
        im++;
    }
    delete[] imStart;
    delete[] reStart;
    emit ready();
}

void DFTCounter::setData(QVector<double> *xPoints, QVector<double> *yPoints, double *xOutPoints, double *yOutPoints, int startIndex, int finishIndex)
{
    _xPoints = xPoints;
    _yPoints = yPoints;
    _xOutPoints = xOutPoints;
    _yOutPoints = yOutPoints;
    _startIndex = startIndex;
    _finishIndex = finishIndex;
}
