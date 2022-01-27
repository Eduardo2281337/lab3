#ifndef DATA_H
#define DATA_H
#include <QString>

struct Data
{
    QString _name;
    int _size;
    qreal _ratio; // отношение размера эл-та на размер папки

    Data(const QString& name, int size, qreal ratio)
                : _name(name), _size(size), _ratio(ratio) {}
};

#endif // DATA_H
