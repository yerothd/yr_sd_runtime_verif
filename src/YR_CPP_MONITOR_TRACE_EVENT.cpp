/*
 * YR_CPP_MONITOR_TRACE_EVENT.hpp
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */


#include "YR_CPP_MONITOR_TRACE_EVENT.hpp"

#include "YR_CPP_MONITOR_EVENT.hpp"



bool YR_CPP_MONITOR_TRACE_EVENT::is_in_TRACE_EVENT(QString &A_TRACE_EVENT)
{
    YR_CPP_MONITOR_EVENT *cur_Event_TO_CHECK = 0;

    for (int k = 0; k < _TRACE_EVENTS.size(); ++k)
    {
        cur_Event_TO_CHECK = _TRACE_EVENTS.at(k);

        if (0 != cur_Event_TO_CHECK)
        {
            if (cur_Event_TO_CHECK->get_EVENT_TOKEN() == A_TRACE_EVENT)
            {
                return true;
            }
        }
    }
    return false;
}
