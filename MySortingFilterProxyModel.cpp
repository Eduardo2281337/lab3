#include "MySortingFilterProxyModel.h"


// сортировка данных таблицы с учетом особенностей данных выводимых в представление
bool MySortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    QVariant leftData = sourceModel()->data(source_left);
    QVariant rightData = sourceModel()->data(source_right);
    switch (source_left.column()) {
        case 0: return leftData < rightData;
        case 1:  {
            qlonglong left_size = 0;
            qlonglong right_size = 0;
            if (leftData.toString().contains("bytes")) {
               // split выступает в роли сепаратора, сначала отделяем число до пробела, потом конвертируем в double
                left_size = leftData.toString().split(QLatin1Char(' '))[0].toDouble();
            }
            if (rightData.toString().contains("bytes")) {
                right_size = rightData.toString().split(QLatin1Char(' '))[0].toDouble();
            }
            if (leftData.toString().contains("KiB")) {
                left_size = leftData.toString().split(QLatin1Char(' '))[0].toDouble() * 1024;
            }
            if (rightData.toString().contains("KiB")) {
                right_size = rightData.toString().split(QLatin1Char(' '))[0].toDouble() * 1024;
            }
            if (leftData.toString().contains("MiB")) {
                left_size = leftData.toString().split(QLatin1Char(' '))[0].toDouble() * 1048576;
            }
            if (rightData.toString().contains("MiB")) {
                right_size = rightData.toString().split(QLatin1Char(' '))[0].toDouble() * 1048576;
            }
            if (leftData.toString().contains("GiB")) {
                left_size = leftData.toString().split(QLatin1Char(' '))[0].toDouble() * 134217728;
            }
            if (rightData.toString().contains("GiB")) {
                right_size = rightData.toString().split(QLatin1Char(' '))[0].toDouble() * 134217728;
            }
            return left_size < right_size;
        }
        case 2: {
            if (leftData.toString().contains("< 0.01"))
                leftData = "0.0099 %";
            if (rightData.toString().contains("< 0.01"))
                rightData = "0.0099 %";
            return leftData.toString().split(QLatin1Char(' '))[0].toFloat() < rightData.toString().split(QLatin1Char(' '))[0].toFloat();
        }

    }

    return leftData < rightData;
}
