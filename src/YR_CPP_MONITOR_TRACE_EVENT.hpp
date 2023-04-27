/*
 * YR_CPP_MONITOR_TRACE_EVENT.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_MONITOR_TRACE_EVENT_HPP_
#define _YR_CPP_MONITOR_TRACE_EVENT_HPP_


#include "utils/YR_CPP_UTILS.hpp"

#include "YR_CPP_MONITOR_object.hpp"


#include <QtCore/QString>

#include <QtCore/QList>


class YR_CPP_MONITOR_EVENT;


class YR_CPP_MONITOR_TRACE_EVENT:public YR_CPP_MONITOR_object
{
Q_OBJECT public:

    YR_CPP_CLASS_OPERATORS YR_CPP_MONITOR_TRACE_EVENT()
    {
    }

    virtual ~ YR_CPP_MONITOR_TRACE_EVENT()
    {
    }

    bool is_in_TRACE_EVENT(QString &A_TRACE_EVENT);

protected:

    QList < YR_CPP_MONITOR_EVENT * >_TRACE_EVENTS;

};


#endif // _YR_CPP_MONITOR_TRACE_EVENT_HPP_
