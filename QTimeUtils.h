#ifndef QTIMEUTILS_H
#define QTIMEUTILS_H

#include <QTime>

//==============================================================================
#define SEC_MS  1000
#define MIN_MS  (SEC_MS * 60)
#define HOUR_MS (MIN_MS * 60)
#define DAY_MS  (24 * HOUR_MS)

template <typename T>
QTime operator -(T const &end, T const &beginning);

template <>
QTime operator -(QTime const &end, QTime const &beginning)
{
    int diff = beginning.msecsTo(end);

    if (diff < 0)
        diff = DAY_MS + diff;

    return QTime(diff / HOUR_MS, (diff % HOUR_MS) / MIN_MS, (diff % MIN_MS) / SEC_MS, diff % SEC_MS);
}

#undef SEC_MS
#undef MIN_MS
#undef HOUR_MS
#undef DAY_MS
//==============================================================================

#endif // QTIMEUTILS_H
