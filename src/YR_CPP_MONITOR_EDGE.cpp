/*
 * YR_CPP_MONITOR_EDGE.hpp
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
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


QString
YR_CPP_MONITOR_EDGE::
YR_EXPORT_edge_CLASS_INSTANCE(QString &a_yr_rtm_MONITOR_name)
{
    QString YR_TO_EXPORT_edges_SOURCE_CODE;

    QString A_CURRENT_EDGE_ID_NAME =
                    QString("a_last_edge_%1").arg(GET_QSTRING_ID());


    YR_TO_EXPORT_edges_SOURCE_CODE.
    append(QString
           ("YR_CPP_MONITOR_EDGE *%1 = %2->create_yr_monitor_edge(\"%3\", \"%4\");\n").
           arg(A_CURRENT_EDGE_ID_NAME, a_yr_rtm_MONITOR_name,
               get_SOURCE_STATE_KEY(), get_TARGET_STATE_KEY()));

    if (0 != _EDGE_EVENT)
    {
        YR_TO_EXPORT_edges_SOURCE_CODE.
        append(QString
               ("YR_CPP_MONITOR_EVENT *a_last_edge_event_%1 = %2->set_EDGE_EVENT(\"%3\");\n").
               arg(SIMULATE_QSTRING_NEXT_ID(), A_CURRENT_EDGE_ID_NAME,
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
                        YR_CPP_UTILS::isEqualCaseInsensitive(_EDGE_EVENT->get_EVENT_TOKEN(),
                                                             e1_edge_event->
                                                             get_EVENT_TOKEN());
    }

    return
                    edge_event_EQUAL &&
                    YR_CPP_UTILS::isEqualCaseInsensitive(get_TARGET_STATE_KEY(),
                                                         e1.get_TARGET_STATE_KEY()) &&
                    YR_CPP_UTILS::isEqualCaseInsensitive(get_SOURCE_STATE_KEY(),
                                                         e1.get_SOURCE_STATE_KEY());
}


bool YR_CPP_MONITOR_EDGE::evaluate_GUARDED_CONDITION_expression()
{
    if (0 != _guarded_CONDITION_expression)
    {
        return _guarded_CONDITION_expression->evaluate_expression();
    }

    return true;
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


void YR_CPP_MONITOR_EDGE::
	set_PRE_CONDITION_notIN(QString DB_VARIABLE,
							QString db_query_TABLE__db_query_COLUMN)
{
	YR_CPP_MONITOR_STATE *start_state = get_START_STATE();

	if (0 != start_state)
	{
		start_state->
			set_notIN_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
	                                          	  db_query_TABLE__db_query_COLUMN);
	}
}


void YR_CPP_MONITOR_EDGE::
	set_PRE_CONDITION_IN(QString DB_VARIABLE,
                         QString db_query_TABLE__db_query_COLUMN)
{
	YR_CPP_MONITOR_STATE *start_state = get_START_STATE();

	if (0 != start_state)
	{
		start_state->
			set_IN_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                    						   db_query_TABLE__db_query_COLUMN);
	}
}


void YR_CPP_MONITOR_EDGE::
	set_POST_CONDITION_notIN(QString DB_VARIABLE,
                             QString db_query_TABLE__db_query_COLUMN)
{
	YR_CPP_MONITOR_STATE *end_state = get_END_STATE();

	if (0 != end_state)
	{
		end_state->
			set_db_NOT_IN_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
													  db_query_TABLE__db_query_COLUMN);
	}
}


void YR_CPP_MONITOR_EDGE::
	set_POST_CONDITION_IN(QString DB_VARIABLE,
                          QString db_query_TABLE__db_query_COLUMN)
{
	YR_CPP_MONITOR_STATE *end_state = get_END_STATE();

	if (0 != end_state)
	{
		end_state->
			set_db_in_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
												  db_query_TABLE__db_query_COLUMN);
	}
}


bool
YR_CPP_MONITOR_EDGE::CHECK_SOURCE_STATE_in_OR_notin_CONDITION
(YR_CPP_MONITOR_STATE &a_potential_START_state,
 YR_CPP_MONITOR &a_runtime_monitor)
{
    bool A_START_STATE_incoming_CONDITION_HOLDS_true = false;

    if (a_potential_START_state._SET_IN_STATEPROPERTYKEY_TO_VALUE.size() > 0)
    {
        A_START_STATE_incoming_CONDITION_HOLDS_true =
                        a_runtime_monitor.CHECK_PRE_CONDITION_IN(_SOURCE_STATE->
                                                                 _SET_IN_STATEPROPERTYKEY_TO_VALUE);
    }
    else if (a_potential_START_state._SET_notIN_STATEPROPERTYKEY_TO_VALUE.
             size() > 0)
    {
        A_START_STATE_incoming_CONDITION_HOLDS_true =
                        a_runtime_monitor.CHECK_PRE_CONDITION_notIN(_SOURCE_STATE->
                                                                    _SET_notIN_STATEPROPERTYKEY_TO_VALUE);
    }

    return A_START_STATE_incoming_CONDITION_HOLDS_true;
}


bool
YR_CPP_MONITOR_EDGE::
ADDITIONAL_FINAL_STATE_lookup(YR_CPP_MONITOR_STATE &a_potential_final_state,
                              YR_CPP_MONITOR &a_runtime_monitor)
{
    bool is_FINAL_STATE = false;

    if (a_potential_final_state._SET_db_IN_STATEPROPERTYKEY_TO_VALUE.size() >
            0)
    {
        //qDebug() << "_SET_db_IN_STATEPROPERTYKEY_TO_VALUE > 0";

        is_FINAL_STATE = a_runtime_monitor.CHECK_db_post_condition_IN
                         (_TARGET_STATE->_SET_db_IN_STATEPROPERTYKEY_TO_VALUE);

        return is_FINAL_STATE;
    }
    else if (a_potential_final_state._SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE.
             size() > 0)
    {
        //qDebug() << "_SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE > 0";

        is_FINAL_STATE = a_runtime_monitor.CHECK_db_post_condition_notIN
                         (_TARGET_STATE->_SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE);

        return is_FINAL_STATE;
    }

    return is_FINAL_STATE;
}


void
YR_CPP_MONITOR_EDGE::
GET_error_final_STATES(YR_CPP_MONITOR &a_runtime_monitor,
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
        qDebug() <<
                 " ******************************************** START ****************************************************";
        qDebug() <<
                 " *YR_CPP_MONITOR_EDGE::print_FOR_YEROTH_ERP specification edge event: "
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


QString YR_CPP_MONITOR_EDGE::print_to_dot_file()
{
    if (0 != _EDGE_EVENT)
    {
        if (0 != _guarded_CONDITION_expression)
        {
            return QString("\"%1\" -> \"%2\" [xlabel=\"[%3]/%4\"];").
                   arg(_SOURCE_STATE_KEY, _TARGET_STATE_KEY,
                       _guarded_CONDITION_expression->toString(),
                       _EDGE_EVENT->get_EVENT_TOKEN());
        }
        else
        {
            return QString("\"%1\" -> \"%2\" [xlabel=\"%3\"];").
                   arg(_SOURCE_STATE_KEY, _TARGET_STATE_KEY,
                       _EDGE_EVENT->get_EVENT_TOKEN());
        }
    }
    else
    {
        return QString("\"%1\" -> \"%2\"").arg(_SOURCE_STATE_KEY,
                                               _TARGET_STATE_KEY);
    }
}
