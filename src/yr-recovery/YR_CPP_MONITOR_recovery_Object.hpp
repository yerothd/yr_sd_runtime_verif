/*
 * YR_CPP_MONITOR_recovery_Object.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef YR_CPP_MONITOR_RECOVERY_OBJECT
#define YR_CPP_MONITOR_RECOVERY_OBJECT


#include "src/YR_CPP_MONITOR.hpp"

#include "src/YR_CPP_MONITOR_object.hpp"


class YR_CPP_MONITOR;

class YR_CPP_MONITOR_STATE;


class YR_CPP_MONITOR_recovery_Object : public YR_CPP_MONITOR_object
{
	Q_OBJECT


public:

    YR_CPP_CLASS_OPERATORS


    inline YR_CPP_MONITOR_recovery_Object(YR_CPP_MONITOR        *A_RUNTIME_MONITOR,
                                          YR_CPP_MONITOR_STATE  *a_source_state,
                                          YR_CPP_MONITOR_STATE  *a_target_state)
    :YR_CPP_MONITOR_object(),
     _A_RUNTIME_MONITOR(0),
     _A_SOURCE_STATE(a_source_state),
     _A_TARGET_STATE(a_target_state)
    {
    }

    virtual inline ~YR_CPP_MONITOR_recovery_Object()
    {
    }


protected:

    inline YR_CPP_MONITOR_recovery_Object()
    :YR_CPP_MONITOR_object(),
    _A_RUNTIME_MONITOR(0)
    {
    }


    YR_CPP_MONITOR          *_A_RUNTIME_MONITOR;

    YR_CPP_MONITOR_STATE    *_A_SOURCE_STATE;

    YR_CPP_MONITOR_STATE    *_A_TARGET_STATE;
};



#endif // YR_CPP_MONITOR_RECOVERY_OBJECT
