/*
 * YR_CPP_MONITOR_EVENT.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_MONITOR_EVENT_HPP_
#define _YR_CPP_MONITOR_EVENT_HPP_


#include "utils/YR_CPP_UTILS.hpp"

#include "YR_CPP_MONITOR_object.hpp"


#include <QtCore/QString>


class YR_CPP_MONITOR_EVENT:public YR_CPP_MONITOR_object
{
Q_OBJECT public:

    YR_CPP_CLASS_OPERATORS YR_CPP_MONITOR_EVENT(QString &event_token):_event_token(event_token.
                                                                                       trimmed())
    {
    }

    virtual ~ YR_CPP_MONITOR_EVENT()
    {
    }

    inline bool operator== (YR_CPP_MONITOR_EVENT &monitor_event_1);

    inline QString get_EVENT_TOKEN()
    {
        return _event_token.trimmed();
    }

protected:

    YR_CPP_MONITOR_EVENT():_event_token(YR_CPP_UTILS::EMPTY_STRING)
    {
    }

private:

    QString _event_token;
};


bool YR_CPP_MONITOR_EVENT::operator== (YR_CPP_MONITOR_EVENT &monitor_event_1)
{
    return YR_CPP_UTILS::isEqualsCaseInsensitive(_event_token,
                                                monitor_event_1.
                                                get_EVENT_TOKEN());
}


#endif // _YR_CPP_MONITOR_EVENT_HPP_
