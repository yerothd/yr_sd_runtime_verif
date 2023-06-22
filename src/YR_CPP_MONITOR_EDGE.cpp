/*
 * YR_CPP_MONITOR_EDGE.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */


#include "YR_CPP_MONITOR_EDGE.hpp"

#include "YR_CPP_MONITOR_STATE.hpp"



#include <QtCore/QDebug>


YR_CPP_MONITOR_EDGE::YR_CPP_MONITOR_EDGE(QString START_STATE_KEY,
										 QString END_STATE_KEY)
:_SOURCE_STATE(0),
 _TARGET_STATE(0),
 _guarded_CONDITION_expression(0),
 _EDGE_EVENT(0)
{
    _TARGET_STATE_KEY = END_STATE_KEY;

    _SOURCE_STATE_KEY = START_STATE_KEY;

    _TARGET_STATE = new YR_CPP_MONITOR_STATE(_TARGET_STATE_KEY);

    _SOURCE_STATE = new YR_CPP_MONITOR_STATE(_SOURCE_STATE_KEY);
}


YR_CPP_MONITOR_EDGE::YR_CPP_MONITOR_EDGE(YR_CPP_MONITOR_STATE &SOURCE_STATE,
										 YR_CPP_MONITOR_STATE &TARGET_STATE)
:_SOURCE_STATE(0),
 _TARGET_STATE(0),
 _guarded_CONDITION_expression(0),
 _EDGE_EVENT(0)
{
    _TARGET_STATE = &TARGET_STATE;

    _SOURCE_STATE = &SOURCE_STATE;

    _TARGET_STATE_KEY = TARGET_STATE.get_MONITOR_STATE_NAME();

    _SOURCE_STATE_KEY = SOURCE_STATE.get_MONITOR_STATE_NAME();
}


YR_CPP_MONITOR_EDGE::~YR_CPP_MONITOR_EDGE()
{
	if (0 != _TARGET_STATE)
	{
		delete _TARGET_STATE;
	}

	if (0 != _SOURCE_STATE)
	{
		delete _SOURCE_STATE;
	}

    if (0 != _EDGE_EVENT)
    {
        delete _EDGE_EVENT;
    }
}


QString YR_CPP_MONITOR_EDGE::YR_EXPORT_edge_CLASS_INSTANCE()
{
    QString YR_TO_EXPORT_edges_SOURCE_CODE;

    QString A_CURRENT_EDGE_ID_NAME =
                    QString("a_last_edge_%1").arg(GET_QSTRING_ID());


    YR_TO_EXPORT_edges_SOURCE_CODE
    	.append(QString("YR_CPP_MONITOR_EDGE *%1 = create_yr_monitor_edge(\"%2\", \"%3\");\n")
    				.arg(A_CURRENT_EDGE_ID_NAME,
    					 get_SOURCE_STATE_KEY(),
						 get_TARGET_STATE_KEY()));

    if (0 != _EDGE_EVENT)
    {
        YR_TO_EXPORT_edges_SOURCE_CODE
        	.append(QString("YR_CPP_MONITOR_EVENT *a_last_edge_event_%1 = %2->set_EDGE_EVENT(\"%3\");\n")
        				.arg(SIMULATE_QSTRING_NEXT_ID(),
        					 A_CURRENT_EDGE_ID_NAME,
							 _EDGE_EVENT->get_EVENT_TOKEN()));
    }


    return YR_TO_EXPORT_edges_SOURCE_CODE;
}


bool YR_CPP_MONITOR_EDGE::operator== (YR_CPP_MONITOR_EDGE &e1)
{
    YR_CPP_MONITOR_EVENT *e1_edge_event = e1.get_EDGE_EVENT();

    bool edge_event_EQUAL = true;

    if (0 != _EDGE_EVENT && 0 != e1_edge_event)
    {
        edge_event_EQUAL =
                        YR_CPP_UTILS::isEqualsCaseInsensitive(_EDGE_EVENT->get_EVENT_TOKEN(),
                                                             e1_edge_event->
                                                             get_EVENT_TOKEN());
    }

    return
                    edge_event_EQUAL &&
                    YR_CPP_UTILS::isEqualsCaseInsensitive(get_TARGET_STATE_KEY(),
                                                         e1.get_TARGET_STATE_KEY()) &&
                    YR_CPP_UTILS::isEqualsCaseInsensitive(get_SOURCE_STATE_KEY(),
                                                         e1.get_SOURCE_STATE_KEY());
}


/**
 * 'boo YR_CPP_MONITOR_EDGE::evaluate_GUARDED_CONDITION_expression()'
 * RETURNS ALWAYS 'True' whenever no guarded condition expression
 * is specified.
 */
bool YR_CPP_MONITOR_EDGE::evaluate_GUARDED_CONDITION_expression()
{
	bool result = true;

    if (0 != _SOURCE_STATE)
    {
    	if (0 != _guarded_CONDITION_expression)
    	{
    		result = _guarded_CONDITION_expression
    					->evaluate_expression(_SOURCE_STATE
    							->GET_TRACE_OF_THIS_RUNTIME_MONITOR_STATE());
    	}
    }

    return result;
}


YR_CPP_MONITOR_EVENT *YR_CPP_MONITOR_EDGE::set_EDGE_EVENT(QString event_token)
{
    if (0 != _EDGE_EVENT)
    {
        delete _EDGE_EVENT;

        _EDGE_EVENT = 0;
    }

    _EDGE_EVENT = new YR_CPP_MONITOR_EVENT(event_token);

    return _EDGE_EVENT;
}


QString YR_CPP_MONITOR_EDGE::
	Get__precondition__STRING_VALUE_EXPRESSION(bool PRINT_WITH_STANDARD_trace_syntax /* = false */)
{
	QString result;

	if (0 != _SOURCE_STATE)
	{
		result = PRINT_WITH_STANDARD_trace_syntax 								?
				_SOURCE_STATE->GET_STRING_representation_OF_state_condition()	:
				_SOURCE_STATE->GET_STRING_representation_OF_state_condition__ENGINEERING_ACRONYM();
	}

	return result;
}


QString YR_CPP_MONITOR_EDGE::
	Get__POSTcondition__STRING_VALUE_EXPRESSION(bool PRINT_WITH_STANDARD_trace_syntax /* = false */)
{
	QString result;

	if (0 != _TARGET_STATE)
	{
		result = PRINT_WITH_STANDARD_trace_syntax 								?
				_TARGET_STATE->GET_STRING_representation_OF_state_condition()	:
				_TARGET_STATE->GET_STRING_representation_OF_state_condition__ENGINEERING_ACRONYM();
	}

	return result;
}


void YR_CPP_MONITOR_EDGE::
	set_PRE_CONDITION_notIN(QString DB_VARIABLE,
							QString db_query_TABLE__db_query_COLUMN)
{
	YR_CPP_MONITOR_STATE *start_state = get_SOURCE_STATE();

	if (0 != start_state)
	{
		start_state->
			set_notIN_PRE_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
	                                          	  db_query_TABLE__db_query_COLUMN);
	}
}


void YR_CPP_MONITOR_EDGE::
	set_PRE_CONDITION_IN(QString DB_VARIABLE,
                         QString db_query_TABLE__db_query_COLUMN)
{
	YR_CPP_MONITOR_STATE *start_state = get_SOURCE_STATE();

	if (0 != start_state)
	{
		start_state->
			set_IN_PRE_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                    						   db_query_TABLE__db_query_COLUMN);
	}
}


void YR_CPP_MONITOR_EDGE::
	set_POST_CONDITION_notIN(QString DB_VARIABLE,
                             QString db_query_TABLE__db_query_COLUMN)
{
	YR_CPP_MONITOR_STATE *end_state = get_TARGET_STATE();

	if (0 != end_state)
	{
		end_state->
			set_notin_POST_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
													  db_query_TABLE__db_query_COLUMN);
	}
}


void YR_CPP_MONITOR_EDGE::
	set_POST_CONDITION_IN(QString DB_VARIABLE,
                          QString db_query_TABLE__db_query_COLUMN)
{
	YR_CPP_MONITOR_STATE *end_state = get_TARGET_STATE();

	if (0 != end_state)
	{
		end_state->
			set_in_post_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
												  db_query_TABLE__db_query_COLUMN);
	}
}


bool YR_CPP_MONITOR_EDGE::
	CHECK_SOURCE_STATE_in_OR_notin_CONDITION(YR_CPP_MONITOR_STATE &a_potential_START_state,
											 YR_CPP_MONITOR &a_runtime_monitor)
{
    bool A_START_STATE_incoming_CONDITION_HOLDS_true = true;

    if (a_potential_START_state._SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.size() > 0)
    {
        A_START_STATE_incoming_CONDITION_HOLDS_true =
                        a_runtime_monitor.CHECK_PRE_CONDITION_IN(_SOURCE_STATE->
                                                                 _SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE);
    }
    else if (a_potential_START_state._SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.
             size() > 0)
    {
        A_START_STATE_incoming_CONDITION_HOLDS_true =
                        a_runtime_monitor.CHECK_PRE_CONDITION_notIN(_SOURCE_STATE->
                                                                    _SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE);
    }

    return A_START_STATE_incoming_CONDITION_HOLDS_true;
}


bool
YR_CPP_MONITOR_EDGE::
ADDITIONAL_FINAL_STATE_lookup(YR_CPP_MONITOR_STATE &a_potential_final_state,
                              YR_CPP_MONITOR &a_runtime_monitor)
{
    if (a_potential_final_state._SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.size() >
            0)
    {
        //qDebug() << "_SET_db_IN_STATEPROPERTYKEY_TO_VALUE > 0";

        bool is_FINAL_STATE_in = a_runtime_monitor.CHECK_post_condition_IN
                         (_TARGET_STATE->_SET_IN_POST_STATEPROPERTYKEY_TO_VALUE);

        return is_FINAL_STATE_in;
    }
    else if (a_potential_final_state._SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.
             size() > 0)
    {
        //qDebug() << "_SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE > 0";

        bool is_FINAL_STATE_NOT_in = a_runtime_monitor.CHECK_post_condition_notIN
                         (_TARGET_STATE->_SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE);

        return is_FINAL_STATE_NOT_in;
    }

    return false;
}


void
YR_CPP_MONITOR_EDGE::
GET_error_final_STATES__OVER_EDGES(YR_CPP_MONITOR &a_runtime_monitor,
                       	   	   	   QList < YR_CPP_MONITOR_STATE * > &results_states)
{
    results_states.clear();

    if (0 != _SOURCE_STATE)
    {
        if (_SOURCE_STATE->is_FINAL_STATE())
        {
            bool is_final_state = ADDITIONAL_FINAL_STATE_lookup(*_SOURCE_STATE,
                                                                a_runtime_monitor);
            if (is_final_state)
            {
                qDebug() <<
                         " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] edge event accepting final state: "
                         << _SOURCE_STATE->get_MONITOR_STATE_NAME() << " **";
                results_states.append(_SOURCE_STATE);
            }
        }
    }

    if (0 != _TARGET_STATE)
    {
        if (_TARGET_STATE->is_FINAL_STATE())
        {
            bool is_final_state = ADDITIONAL_FINAL_STATE_lookup(*_TARGET_STATE,
                                                                a_runtime_monitor);
            if (is_final_state)
            {
                qDebug() <<
                         " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] edge event accepting final state: "
                         << _TARGET_STATE->get_MONITOR_STATE_NAME() << " **";
                qDebug() <<
                         " ********************************************** END *****************************************************";
                results_states.append(_TARGET_STATE);
            }
        }
    }
}


void YR_CPP_MONITOR_EDGE::print_FOR_YEROTH_ERP()
{
    if (0 != _EDGE_EVENT)
    {
        qDebug() << QString(" ****************** START (%1) ******************")
					 .arg(_EDGE_EVENT->get_EVENT_TOKEN());

        qDebug() << " *YR_CPP_MONITOR_EDGE::print_FOR_YEROTH_ERP specification edge event: "
                 << _EDGE_EVENT->get_EVENT_TOKEN() << "**";
    }
}


void YR_CPP_MONITOR_EDGE::print()
{
    if (0 != _EDGE_EVENT)
    {
        qDebug() << "YR_CPP_MONITOR_EDGE::print _ event_METHOD_FUNCTION: " <<
                 _EDGE_EVENT->get_EVENT_TOKEN();
        qDebug() << "YR_CPP_MONITOR_EDGE::print _ event_PARAMETERS_list: " <<
                 _EVENT_PARAMETERS_LIST;
    }
}


QString YR_CPP_MONITOR_EDGE::print_to_dot_file(bool PRINT_WITH_SQL_EVENT_LOG_TOKEN /* = false */)
{
    if (0 != _EDGE_EVENT)
    {
        if (0 != _guarded_CONDITION_expression)
        {
            return QString("\"%1\" -> \"%2\" [xlabel=\"[%3]/%4\"];")
                    .arg(_SOURCE_STATE_KEY,
                    	 _TARGET_STATE_KEY,
						 PRINT_WITH_SQL_EVENT_LOG_TOKEN ?
								 	_guarded_CONDITION_expression->toString__WITH__sql_event_log_SYNTAX() :
									_guarded_CONDITION_expression->toString__WITH__standard_trace_syntax(),
						 _EDGE_EVENT->get_EVENT_TOKEN());
        }
        else
        {
            return QString("\"%1\" -> \"%2\" [xlabel=\"%3\"];")
                    .arg(_SOURCE_STATE_KEY,
                    	 _TARGET_STATE_KEY,
						 _EDGE_EVENT->get_EVENT_TOKEN());
        }
    }
    else
    {
        return QString("\"%1\" -> \"%2\"")
        		.arg(_SOURCE_STATE_KEY,
        			 _TARGET_STATE_KEY);
    }
}
