#include "dftcounter.h"

#include "math.h"
#include <QVector>
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

//int DFTCounter::dft()
//{
//    re = new double[n];
//    im = new double[n];
//    A = new double[n];
//    phi = new double[n];
//    for (int i = 0; i < n; i++)
//    {
//        re[i] = 0;																//Чистка ячеек памяти
//        im[i] = 0;
//        for (int j = 0; j < n; j++)
//        {
//            re[i] += y[j]*cos(-2*kPi*i*j/n)/n;									//
//            im[i] += y[j]*sin(-2*kPi*i*j/n)/n;
//            //cout << re[i] << '\t' << im[i] << endl;
//        }
//        A[i] = 2*sqrt((re[i])*(re[i])+(im[i])*(im[i]));
//        phi[i] = atan2(im[i], re[i]);
//    }
//    return 0;
//}

void DFTCounter::getDFT(QVector<double>* xPoints, QVector<double>* yPoints, QVector<double> *xOutPoints, QVector<double> *yOutPoints)
{
    int nPoints = xPoints->count();
    double delta = xPoints->at(1) - xPoints->at(0);
    double x = 0;
    double* re = new double[nPoints];
    double* im = new double[nPoints];
    double* reStart = re;
    double* imStart = im;
    double temp2, temp1, temp;
    double sinus, cosinus;
    double* yCurrentPointer = yPoints->data();
    for(int i = 0; i < nPoints; ++i)
    {
        *re = 0;																//Чистка ячеек памяти
        *im = 0;
        temp = 0;
        temp1 = -kPi2*i/nPoints;
        yCurrentPointer = yPoints->data();
        for (int j = 0; j < nPoints; j++)
        {
            sinus = sin(temp);
            temp2 = temp - kPi2*floor(temp/kPi2);//Угол в пределах 0 - 2Пи
            cosinus = (temp2 < kPi_2 || temp2 > k3Pi_2) ? sqrt(1-sinus*sinus) : -sqrt(1-sinus*sinus);
            *re += *yCurrentPointer*cosinus/nPoints;
            *im += *yCurrentPointer*sinus/nPoints;
            temp += temp1;
            yCurrentPointer++;
        }
        yOutPoints->append(2*sqrt((*re)*(*re)+(*im)*(*im)));
        xOutPoints->append(x);
        x += delta;
        re++;
        im++;
    }
    delete[] imStart;
    delete[] reStart;
    emit ready();
}

void DFTCounter::getDFT(QVector<double>* xPoints, QVector<double>* yPoints, QVector<double> *xOutPoints, QVector<double> *yOutPoints, int startIndex, int finishIndex)
{
    int nPoints = xPoints->count();
    double delta = xPoints->at(1) - xPoints->at(0);
    double x = 0;
    double* re = new double[nPoints];
    double* im = new double[nPoints];
    double* reStart = re;
    double* imStart = im;
    double temp2, temp1, temp;
    double sinus, cosinus;
    double* yCurrentPointer = yPoints->data();
    for(int i = startIndex; i < finishIndex; ++i)
    {
        *re = 0;																//Чистка ячеек памяти
        *im = 0;
        temp = 0;
        temp1 = -kPi2*i/nPoints;
        yCurrentPointer = yPoints->data();
        for (int j = 0; j < nPoints; j++)
        {
            sinus = sin(temp);
            temp2 = temp - kPi2*floor(temp/kPi2);//Угол в пределах 0 - 2Пи
            cosinus = (temp2 < kPi_2 || temp2 > k3Pi_2) ? sqrt(1-sinus*sinus) : -sqrt(1-sinus*sinus);
            *re += *yCurrentPointer*cosinus/nPoints;
            *im += *yCurrentPointer*sinus/nPoints;
            temp += temp1;
            yCurrentPointer++;
        }
        yOutPoints->append(2*sqrt((*re)*(*re)+(*im)*(*im)));
        xOutPoints->append(x);
        x += delta;
        re++;
        im++;
    }
    delete[] imStart;
    delete[] reStart;
    emit ready();
}
