#include "bigvectorholder.h"
#include <QDebug>

BigVectorHolder::BigVectorHolder() {}

void BigVectorHolder::appendData(double data)
{
    if (_data.isEmpty())
        _data.append(new QVector<double>);

    try
    {
        _data.last()->append(data);
    } catch (std::exception e)
    {
        _data.append(new QVector<double>);
        _data.last()->append(data);
    }
}

QVector<double>* BigVectorHolder::getVectorByIndex(int index) { return _data.at(index); }

int BigVectorHolder::getVectorsCount() { return _data.count(); }
