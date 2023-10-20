/*
 * YR_CPP_MONITOR_recovery_SQL_INSERT.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_MONITOR_RECOVERY_SQL_INSERT_
#define _YR_CPP_MONITOR_RECOVERY_SQL_INSERT_


#include "YR_CPP_MONITOR_recovery_Object.hpp"


class YR_CPP_MONITOR_recovery_SQL_INSERT : public YR_CPP_MONITOR_recovery_Object
{
	Q_OBJECT


public:

    YR_CPP_CLASS_OPERATORS

    inline YR_CPP_MONITOR_recovery_SQL_INSERT(QString RUNTIME_MONITOR_NAME)
    :YR_CPP_MONITOR_recovery_Object(RUNTIME_MONITOR_NAME)
    {
    }

    virtual inline ~YR_CPP_MONITOR_recovery_SQL_INSERT()
    {
    }


protected:

    inline YR_CPP_MONITOR_recovery_SQL_INSERT()
    :YR_CPP_MONITOR_recovery_Object()
    {
    }
};



#endif // _YR_CPP_MONITOR_RECOVERY_SQL_INSERT_
