#ifndef BIGVECTORHOLDER_H
#define BIGVECTORHOLDER_H

#include <QVector>

class BigVectorHolder
{
public:
    BigVectorHolder();
    void appendData(double data);
    QVector<double>* getVectorByIndex(int index);
    int getVectorsCount();

private:
    QVector<QVector<double>*> _data;
};

#endif // BIGVECTORHOLDER_H
