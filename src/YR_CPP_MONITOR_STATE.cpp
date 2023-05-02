/*
 * YR_CPP_MONITOR_STATE.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */


#include "YR_CPP_MONITOR_STATE.hpp"


#include <QtCore/QDebug>



const QString YR_CPP_MONITOR_STATE::_MONITOR_STATE_NAME_string_key("MONITOR_STATE_NAME");



YR_CPP_MONITOR_STATE::~YR_CPP_MONITOR_STATE()
{
    _state_id = -1;
}


void YR_CPP_MONITOR_STATE::
	set_PRE_CONDITION_notIN(QString DB_VARIABLE,
							QString db_query_TABLE__db_query_COLUMN)
{
	if (is_FINAL_STATE())
	{
		QDEBUG_STRING_OUTPUT_2("YR_CPP_MONITOR_STATE::set_PRE_CONDITION_notIN",
					QString("A PRE-CONDITION CANNOT BE set on a FINAL state"));

		return ;
	}

    set_notIN_PRE_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                          db_query_TABLE__db_query_COLUMN);
}


void YR_CPP_MONITOR_STATE::
	set_PRE_CONDITION_IN(QString DB_VARIABLE,
                         QString db_query_TABLE__db_query_COLUMN)
{
	if (is_FINAL_STATE())
	{
		QDEBUG_STRING_OUTPUT_2("YR_CPP_MONITOR_STATE::set_PRE_CONDITION_notIN",
					QString("A PRE-CONDITION CANNOT BE set on a FINAL state"));

		return ;
	}

    set_IN_PRE_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                       db_query_TABLE__db_query_COLUMN);
}


void YR_CPP_MONITOR_STATE::
	set_POST_CONDITION_notIN(QString DB_VARIABLE,
                             QString db_query_TABLE__db_query_COLUMN)
{
	if (is_START_STATE())
	{
		QDEBUG_STRING_OUTPUT_2("YR_CPP_MONITOR_STATE::set_POST_CONDITION_notIN",
					QString("A POST-CONDITION CANNOT BE set on a start state"));

		return ;
	}

    set_notin_POST_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                              db_query_TABLE__db_query_COLUMN);
}


void YR_CPP_MONITOR_STATE::
	set_POST_CONDITION_IN(QString DB_VARIABLE,
                          QString db_query_TABLE__db_query_COLUMN)
{
	if (is_START_STATE())
	{
		QDEBUG_STRING_OUTPUT_2("YR_CPP_MONITOR_STATE::set_POST_CONDITION_notIN",
					QString("A POST-CONDITION CANNOT BE set on a start state"));

		return ;
	}

    set_in_post_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                          db_query_TABLE__db_query_COLUMN);
}


const QStringList &
YR_CPP_MONITOR_STATE::
ADD_RUNTIME_MONITOR_TRACE_EVENT(QString a_runtime_monitor_trace_event)
{
    _TRACE.append(a_runtime_monitor_trace_event);

    return _TRACE;
}


void YR_CPP_MONITOR_STATE::set_FINAL_STATE(bool is_final_state)
{
    _final_state = is_final_state;

    if (_final_state)
    {
//                      qDebug() << "THIS ["
//                                       << get_MONITOR_STATE_NAME()
//                                       << "] is a final state";
    }
}


void YR_CPP_MONITOR_STATE::print()
{
    qDebug() << QString("%1 (IS_START_STATE: %2; IS_FINAL_STATE: %3)").
             arg(get_MONITOR_STATE_NAME(), bool_To_String(is_START_STATE()),
                 bool_To_String(is_FINAL_STATE()));
}
