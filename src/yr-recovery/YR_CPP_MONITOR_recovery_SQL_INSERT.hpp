/*
 * YR_CPP_MONITOR_recovery_SQL_INSERT.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_MONITOR_RECOVERY_SQL_INSERT_
#define _YR_CPP_MONITOR_RECOVERY_SQL_INSERT_


#include "YR_CPP_MONITOR_recovery_Object.hpp"


class YR_CPP_MONITOR_STATE;


/**
 * WE ONLY SUPPORT "MISSING DATABASE TABLE COLUMN VALUE DEFINITION" as
 * DESCRIBED IN yeroth_qvge user's guide (https://zenodo.org/record/8387240).
 */

class YR_CPP_MONITOR_recovery_SQL_INSERT : public YR_CPP_MONITOR_recovery_Object
{
	Q_OBJECT


public:

    YR_CPP_CLASS_OPERATORS


    inline YR_CPP_MONITOR_recovery_SQL_INSERT(YR_CPP_MONITOR        *A_RUNTIME_MONITOR,
                                              YR_CPP_MONITOR_STATE  *a_source_state)
    :YR_CPP_MONITOR_recovery_Object(A_RUNTIME_MONITOR,
                                    a_source_state)
    {
    }


    virtual inline ~YR_CPP_MONITOR_recovery_SQL_INSERT()
    {
    }


    virtual bool EXECUTE_sql_insert_recovery_QUERY_NOW();


    virtual QString build_SQL_QUERY_STRING_for_ERROR_STATE_SAFE_RECOVERY();


protected:

    inline YR_CPP_MONITOR_recovery_SQL_INSERT()
    :YR_CPP_MONITOR_recovery_Object()
    {
    }


    QString ___SQL_INSERT_QUERY_for_ERROR_STATE_SAFE_RECOVERY;
};



#endif // _YR_CPP_MONITOR_RECOVERY_SQL_INSERT_
