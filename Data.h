#ifndef DATA_H
#define DATA_H
#include <QString>

struct Data
{
    QString _name;
    int _size;
    QString _percent;
    qreal _ratio; // отношение размера эл-та на размер папки

    Data(const QString& name, int size, const QString& percent, qreal ratio)
                : _name(name), _size(size), _percent(percent), _ratio(ratio) {}
};

#endif // DATA_H
