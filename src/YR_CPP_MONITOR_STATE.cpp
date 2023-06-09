/*
 * YR_CPP_MONITOR_STATE.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */


#include "YR_CPP_MONITOR_STATE.hpp"


#include "YR_CPP_MONITOR.hpp"


#include <QtCore/QDebug>


const QString YR_CPP_MONITOR_STATE::_MONITOR_STATE_NAME_string_key("MONITOR_STATE_NAME");



void YR_CPP_MONITOR_STATE::
	set_PRE_CONDITION_notIN(QString DB_VARIABLE,
							QString db_query_TABLE__db_query_COLUMN)
{
	if (is_FINAL_STATE())
	{
		QDEBUG_STRING_OUTPUT_2("YR_CPP_MONITOR_STATE::set_PRE_CONDITION_notIN",
							   "A PRE-CONDITION CANNOT BE set on a FINAL state");

		return ;
	}


    _STATE_CONDITION__db_variable = DB_VARIABLE;

    _STATE_CONDITION__db_query_TABLE__db_query_COLUMN =
    		db_query_TABLE__db_query_COLUMN;


    set_notIN_PRE_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                          	  db_query_TABLE__db_query_COLUMN);


    _SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.clear();

    _SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.clear();

    _SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.clear();
}


void YR_CPP_MONITOR_STATE::
	set_PRE_CONDITION_IN(QString DB_VARIABLE,
                         QString db_query_TABLE__db_query_COLUMN)
{
	if (is_FINAL_STATE())
	{
		QDEBUG_STRING_OUTPUT_2("YR_CPP_MONITOR_STATE::set_PRE_CONDITION_notIN",
							   "A PRE-CONDITION CANNOT BE set on a FINAL state");

		return ;
	}


    _STATE_CONDITION__db_variable = DB_VARIABLE;

    _STATE_CONDITION__db_query_TABLE__db_query_COLUMN =
    		db_query_TABLE__db_query_COLUMN;


    set_IN_PRE_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                       	   db_query_TABLE__db_query_COLUMN);


    _SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.clear();

    _SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.clear();

    _SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.clear();
}


/**
 * REMOVES ANY OTHER state-condition.
 */
void YR_CPP_MONITOR_STATE::
	set_POST_CONDITION_notIN(QString DB_VARIABLE,
                             QString db_query_TABLE__db_query_COLUMN)
{
	if (is_START_STATE())
	{
		QDEBUG_STRING_OUTPUT_2("YR_CPP_MONITOR_STATE::set_POST_CONDITION_notIN",
							   "A POST-CONDITION CANNOT BE set on a start state");

		return ;
	}


    _STATE_CONDITION__db_variable = DB_VARIABLE;

    _STATE_CONDITION__db_query_TABLE__db_query_COLUMN =
    		db_query_TABLE__db_query_COLUMN;


    set_notin_POST_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                               db_query_TABLE__db_query_COLUMN);


    _SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.clear();

    _SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.clear();

    _SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.clear();
}


/**
 * REMOVES ANY OTHER state-condition.
 */
void YR_CPP_MONITOR_STATE::
	set_POST_CONDITION_IN(QString DB_VARIABLE,
                          QString db_query_TABLE__db_query_COLUMN)
{
	if (is_START_STATE())
	{
		QDEBUG_STRING_OUTPUT_2("YR_CPP_MONITOR_STATE::set_POST_CONDITION_notIN",
							   "A POST-CONDITION CANNOT BE set on a start state");

		return ;
	}


    _STATE_CONDITION__db_variable = DB_VARIABLE;

    _STATE_CONDITION__db_query_TABLE__db_query_COLUMN =
    		db_query_TABLE__db_query_COLUMN;


    set_in_post_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                          db_query_TABLE__db_query_COLUMN);


    _SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.clear();

    _SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.clear();

    _SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.clear();
}


QString YR_CPP_MONITOR_STATE::GET_STRING_representation_OF_state_condition()
{
	QString result;

	if (_SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.contains(_STATE_CONDITION__db_variable))
	{
		result = QString("in_pre(%1, %2)")
					.arg(_STATE_CONDITION__db_variable,
						 _SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE
						 	 .value(_STATE_CONDITION__db_variable));
	}
	else if (_SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.contains(_STATE_CONDITION__db_variable))
	{
		result = QString("not_in_pre(%1, %2)")
					.arg(_STATE_CONDITION__db_variable,
						 _SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE
						 	 .value(_STATE_CONDITION__db_variable));
	}
	else if (_SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.contains(_STATE_CONDITION__db_variable))
	{
		result = QString("in_post(%1, %2)")
					.arg(_STATE_CONDITION__db_variable,
						 _SET_IN_POST_STATEPROPERTYKEY_TO_VALUE
						 	 .value(_STATE_CONDITION__db_variable));
	}
	else if (_SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.contains(_STATE_CONDITION__db_variable))
	{
		result = QString("not_in_post(%1, %2)")
					.arg(_STATE_CONDITION__db_variable,
						 _SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE
						 	 .value(_STATE_CONDITION__db_variable));
	}

	return result;
}


const QStringList &YR_CPP_MONITOR_STATE::
	ADD_RUNTIME_MONITOR_INCOMING_TRACE_EVENT(QList<QString> &a_runtime_monitor_trace_event)
{
	for (int k = a_runtime_monitor_trace_event.size() - 1;
		 k >= 0;
		 --k)
	{
		_TRACE.prepend(a_runtime_monitor_trace_event.at(k));
	}

	return _TRACE;
}


const QStringList &YR_CPP_MONITOR_STATE::
	ADD_RUNTIME_MONITOR_TRACE_EVENT(QString a_runtime_monitor_trace_event)
{
    _TRACE.append(a_runtime_monitor_trace_event);

    return _TRACE;
}


void YR_CPP_MONITOR_STATE::set_START_STATE(YR_CPP_MONITOR 	&A_RUNTIME_MONITOR,
										   bool 			is_start_state)
{
	if (is_start_state)
	{
		YR_CPP_MONITOR_EDGE *a_root_edge =
				A_RUNTIME_MONITOR.create_yr_monitor_edge(YR_CPP_UTILS::EMPTY_STRING,
														 get_MONITOR_STATE_NAME());

		A_RUNTIME_MONITOR.set_yr_root_edge(a_root_edge);
	}
	else
	{
		YR_CPP_MONITOR_EDGE *a_root_edge = A_RUNTIME_MONITOR.GET_root_edge();

		if (0 != a_root_edge)
		{
			A_RUNTIME_MONITOR.DELETE_yr_monitor_edge(a_root_edge);
		}
	}

    _start_state = is_start_state;
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
    qDebug() << QString("%1 (IS_START_STATE: %2; IS_FINAL_STATE: %3)")
    				.arg(get_MONITOR_STATE_NAME(),
    					 bool_To_String(is_START_STATE()),
						 bool_To_String(is_FINAL_STATE()));
}
