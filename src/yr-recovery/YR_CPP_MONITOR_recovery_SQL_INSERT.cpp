/*
 * YR_CPP_MONITOR_recovery_SQL_INSERT.cpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#include "YR_CPP_MONITOR_recovery_SQL_INSERT.hpp"


#include "src/YR_CPP_MONITOR_STATE.hpp"



bool YR_CPP_MONITOR_recovery_SQL_INSERT::EXECUTE_sql_insert_recovery_QUERY_NOW()
{
    bool query_success = false;

    QString SQL_QUERY_STRING =
                build_SQL_QUERY_STRING_for_ERROR_STATE_SAFE_RECOVERY();

    QDEBUG_STRING_OUTPUT_2("YR_CPP_MONITOR_recovery_SQL_INSERT::EXECUTE_sql_insert_recovery_QUERY_NOW; SQL_QUERY_STRING",
                            SQL_QUERY_STRING);


    bool dbg_MSG = true;


    query_success =
        YR_CPP_UTILS::execQueryRowCount(SQL_QUERY_STRING,
                                        dbg_MSG);

    return query_success;
}


QString YR_CPP_MONITOR_recovery_SQL_INSERT::build_SQL_QUERY_STRING_for_ERROR_STATE_SAFE_RECOVERY()
 {
    ___SQL_INSERT_QUERY_for_ERROR_STATE_SAFE_RECOVERY.clear();


    if (0 == _A_SOURCE_STATE)
    {
        return "";
    }


    if (!_A_SOURCE_STATE->Get_SQL_RECOVERY_QUERY_STRING().isEmpty())
    {
        return _A_SOURCE_STATE->Get_SQL_RECOVERY_QUERY_STRING();
    }


    // MISSING database table column definition case
    // !! this is the only suported and identified case
    //    that is automatically recoverable by this library !!

    QString DB_SQL_TABLE_Column_Value_ANEW =
        _A_SOURCE_STATE->get_STATE_CONDITION__db_variable();


    QDEBUG_STRING_OUTPUT_2("DB_SQL_TABLE_Column_Value_ANEW",
                            DB_SQL_TABLE_Column_Value_ANEW);


    QString db_query_TABLE__db_query_COLUMN =
        _A_SOURCE_STATE
            ->GET_notIN_STATEPROPERTY_KEY_VALUE(DB_SQL_TABLE_Column_Value_ANEW);


    QDEBUG_STRING_OUTPUT_2("db_query_TABLE__db_query_COLUMN",
                            db_query_TABLE__db_query_COLUMN);


    if (!db_query_TABLE__db_query_COLUMN.isEmpty())
    {
        QList<QString> db_query_values = db_query_TABLE__db_query_COLUMN.split(".");

        if (db_query_values.size() > 0)
        {
            QString DB_SQL_TABLE = db_query_values.at(0);

            QString DB_SQL_TABLE_Column = db_query_values.at(1);


            ___SQL_INSERT_QUERY_for_ERROR_STATE_SAFE_RECOVERY =
                QString("insert into %1 (id, %2) values ('%3', '%4');")
                    .arg(DB_SQL_TABLE,
                         DB_SQL_TABLE_Column,
                         QString("(SELECT id FROM %1 ORDER BY id DESC LIMIT 0, 1)")
                            .arg(DB_SQL_TABLE),
                         DB_SQL_TABLE_Column_Value_ANEW);
        }
    }


    return ___SQL_INSERT_QUERY_for_ERROR_STATE_SAFE_RECOVERY;
 }


