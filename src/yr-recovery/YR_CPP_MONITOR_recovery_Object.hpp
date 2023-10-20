/*
 * YR_CPP_MONITOR_recovery_Object.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef YR_CPP_MONITOR_RECOVERY_OBJECT
#define YR_CPP_MONITOR_RECOVERY_OBJECT


#include "src/YR_CPP_MONITOR_object.hpp"


class YR_CPP_MONITOR_ERP_database;

class YR_CPP_MONITOR_EDGE;

class YR_CPP_MONITOR_STATE;


class YR_CPP_MONITOR_recovery_Object : public YR_CPP_MONITOR_object
{
	Q_OBJECT


public:

    YR_CPP_CLASS_OPERATORS


    inline YR_CPP_MONITOR_recovery_Object(QString RUNTIME_MONITOR_NAME)
    :YR_CPP_MONITOR_object(),
    _RUNTIME_MONITOR_NAME(RUNTIME_MONITOR_NAME)
    {
    }

    virtual inline ~YR_CPP_MONITOR_recovery_Object()
    {
    }


protected:

    inline YR_CPP_MONITOR_recovery_Object()
    :YR_CPP_MONITOR_object()
    {
    }


    QString _RUNTIME_MONITOR_NAME;
};



#endif // YR_CPP_MONITOR_RECOVERY_OBJECT
