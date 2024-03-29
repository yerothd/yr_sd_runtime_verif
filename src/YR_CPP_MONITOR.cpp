/*
 * YR_CPP_MONITOR.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUNDOU
 */


#include "YR_CPP_MONITOR.hpp"

#include "YR_CPP_MONITOR_EDGE.hpp"

#include "YR_CPP_MONITOR_STATE.hpp"


#include "src/yr-recovery/YR_CPP_MONITOR_recovery_SQL_INSERT.hpp"


#include "utils/YR_CPP_MONITOR_ERP-database.hpp"

#include "utils/YR_CPP_UTILS.hpp"


#include <QtTest/QtTest>

#include <QtCore/QDebug>
#include <QtCore/QProcess>
#include <QtCore/QFile>
#include <QtCore/QTextStream>


#include <cstdlib>



const char YR_CPP_MONITOR::INCOMING_TRACE_EVENT_SEPARATOR_CHARACTER = ';';



YR_CPP_MONITOR *YR_CPP_MONITOR::CREATE_MONITOR(QString RUNTIME_MONITOR_NAME /*= YR_CPP_UTILS::EMPTY_STRING*/)
{
    YR_CPP_MONITOR *A_RUNTIME_MONITOR = new YR_CPP_MONITOR;

    if (0 != A_RUNTIME_MONITOR)
    {
        if (!YR_CPP_UTILS::isEqualsCaseInsensitive(RUNTIME_MONITOR_NAME,
                                                   YR_CPP_UTILS::EMPTY_STRING))
        {
            A_RUNTIME_MONITOR->set_RUNTIME_MONITOR_NAME(RUNTIME_MONITOR_NAME);
        }
        else
        {
            A_RUNTIME_MONITOR
				->set_RUNTIME_MONITOR_NAME(QString("A_YR_RUNTIME_MONITOR_GENERIC_NAME"));
        }
    }

    return A_RUNTIME_MONITOR;
}


YR_CPP_MONITOR *YR_CPP_MONITOR::CREATE_MONITOR(QString db_type,
                                               QString db_name,
                                               QString db_ip_address,
                                               QString db_user_name,
                                               QString db_user_pwd,
                                               QString db_connection_options /* = YR_CPP_UTILS::EMPTY_STRING */,
                                               QString RUNTIME_MONITOR_NAME /* = YR_CPP_UTILS::EMPTY_STRING */)
{
    YR_CPP_MONITOR *a_new_monitor_FOR_RUNTIME_VERIFICATION =
                    YR_CPP_MONITOR::CREATE_MONITOR(RUNTIME_MONITOR_NAME);

    if (0 != a_new_monitor_FOR_RUNTIME_VERIFICATION)
    {
        a_new_monitor_FOR_RUNTIME_VERIFICATION
			->SET_DB_CONFIGURATION_PARAMETERS(db_type,
											  db_name,
											  db_ip_address,
											  db_user_name,
											  db_user_pwd,
											  db_connection_options);
    }

    return a_new_monitor_FOR_RUNTIME_VERIFICATION;
}


YR_CPP_MONITOR::~YR_CPP_MONITOR()
{
    if (0 != _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS)
    {
        _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->close();

        delete _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS;
    }

    if (0 != _ROOT_EDGE)
    {
        delete _ROOT_EDGE;
    }
}


void YR_CPP_MONITOR::set_yr_root_edge(YR_CPP_MONITOR_EDGE *ROOT_EDGE)
{
    if (0 != ROOT_EDGE 		&&
    	_ROOT_EDGE != ROOT_EDGE)
    {
        DELETE_yr_monitor_edge(_ROOT_EDGE);
    }

    _ROOT_EDGE = ROOT_EDGE;

    set_current_triggered_EDGE(_ROOT_EDGE);

    if (!_EDGES.contains(_ROOT_EDGE))
    {
        _EDGES.append(_ROOT_EDGE);
    }
}


void YR_CPP_MONITOR::
	YR_register_set_final_state_CALLBACK_FUNCTION
		(void (*CALL_BACK_final_state)(YR_CPP_MONITOR 		*a_runtime_monitor,
									   YR_CPP_MONITOR_EDGE 	*an_EDGE_leading_TO_error_FINAL_state))
{
    if (0 != CALL_BACK_final_state)
    {
        _CALL_BACK_final_state = CALL_BACK_final_state;
    }
}


bool YR_CPP_MONITOR::RESET_RUNTIME_MONITOR()
{
	bool ret_value = false;

	assert (0 != _ROOT_EDGE);

	if (0 != _ROOT_EDGE &&
		0 != _ROOT_EDGE->get_TARGET_STATE())
	{
		YR_CPP_MONITOR_STATE *a_state_CURRENT = 0;

		for (uint k = 0; k < _STATES.size(); ++k)
		{
			a_state_CURRENT = _STATES.at(k);

			if (0 != a_state_CURRENT)
			{
				a_state_CURRENT->CLEAR_INCOMING_trace_event_log();
			}
		}

		_TRACE_LOG.clear();

		set_current_triggered_EDGE(_ROOT_EDGE);

		ret_value = true;
	}

	return ret_value;
}


bool YR_CPP_MONITOR::CAN_recover_FROM_THIS_ACCEPTING_ERROR_State
                        (YR_CPP_MONITOR_STATE *an_error_accepting_state)
{
    bool can_recover = false;

    if (0 != an_error_accepting_state)
    {
        if (!_recoverable_error_STATES__To__SQL_query_TOEXECUTE_for_Recovery
                .value(an_error_accepting_state, QString("")).isEmpty())
        {
            can_recover = true;
        }
    }

    return can_recover;
}


void YR_CPP_MONITOR::
        execute_RECOVERY_SQL_QUERY_from_accepting_error_state
            (YR_CPP_MONITOR_STATE *a_previous_source_state,
             YR_CPP_MONITOR_STATE *an_error_accepting_state)
{
    if (0 != a_previous_source_state &&
        0 != an_error_accepting_state)
    {
        if (!a_previous_source_state->Get_PRE_CONDITION_notIN().isEmpty())
        {
            QDEBUG_STRING_OUTPUT_1("*** execute_RECOVERY_SQL_QUERY_from_accepting_error_state - INSERT SQL QUERY (not_in_pre)");

            YR_CPP_MONITOR_recovery_SQL_INSERT
                execute_recovery_Sql_query_string_OBJECT(this,
                                                         a_previous_source_state,
                                                         an_error_accepting_state);

            execute_recovery_Sql_query_string_OBJECT.RUN_SQL_query_string();
        }
    }
}


/**
 * WE ONLY SUPPORT "MISSING DATABASE TABLE COLUMN VALUE DEFINITION" as
 * DESCRIBED IN yeroth_qvge user's guide (https://zenodo.org/record/8387240).
 */
void YR_CPP_MONITOR::set_Recovery_action(YR_CPP_MONITOR_STATE *a_previous_source_state,
                                         YR_CPP_MONITOR_STATE *an_error_accepting_state)
{
    if (0 == a_previous_source_state ||
        0 == an_error_accepting_state)
    {
        return ;
    }

    if (!an_error_accepting_state->is_ERROR_STATE())
    {
        return ;
    }


    YR_CPP_MONITOR_recovery_SQL_INSERT
        AN_SQL_INSERT_recovery_object(this,
                                      a_previous_source_state,
                                      an_error_accepting_state);


    QString SQL_query_TOEXECUTE_for_Recovery =
        AN_SQL_INSERT_recovery_object
            .build_SQL_QUERY_STRING_for_ERROR_STATE_SAFE_RECOVERY();

    QDEBUG_STRING_OUTPUT_2("set_Recovery_action; SQL_query_TOEXECUTE_for_Recovery",
                           SQL_query_TOEXECUTE_for_Recovery);

    _recoverable_error_STATES__To__SQL_query_TOEXECUTE_for_Recovery
        .insert(an_error_accepting_state,
                SQL_query_TOEXECUTE_for_Recovery);
}



/**
 * THIS ALGORITHM ASSUMES FOLLOWING CONSIDERATIONS ON MEALY MACHINES
 * STATES DIAGRAMS IN yr_sd_runtime_verif CONTEXT:
 *
 * 1. Each runtime monitor state has only 1 outgoing edge.
 */
bool YR_CPP_MONITOR::YR_trigger_an_edge_event(QString 	an_edge_event,
											  bool 		debug_MSG /* = true */)
{
    if (0 == _current_STATE)
    {
    	return false;
    }

    YR_CPP_MONITOR_EDGE *cur_STATE_OUTGOING_EDGE = _current_STATE->get_AN_outgoing_edge();

    if (0 == cur_STATE_OUTGOING_EDGE)
    {
    	return false;
    }

    /*
     * trace(_current_STATE) = _TRACE_LOG
     */
    _current_STATE->ADD_RUNTIME_MONITOR_INCOMING_TRACE_EVENT(_TRACE_LOG);


    bool yr_cur_edge_GUARDED_CONDITION_trigerred =
    		cur_STATE_OUTGOING_EDGE->evaluate_GUARDED_CONDITION_expression();


    if (true == yr_cur_edge_GUARDED_CONDITION_trigerred   &&
    	YR_CPP_UTILS::isEqualsCaseInsensitive(an_edge_event,
    			cur_STATE_OUTGOING_EDGE->get_EDGE_EVENT_TOKEN()))
    {
    	if (debug_MSG)
    	{
    		cur_STATE_OUTGOING_EDGE->print_FOR_YEROTH_ERP();

    		qDebug() << " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] edge event guarded condition: "
					 << cur_STATE_OUTGOING_EDGE->get_guarded_CONDITION_expression__TO_STRING()
					 << " **";

    		qDebug() << " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] edge event evaluated triggered guarded condition: "
					 << BOOL_TO_STRING(yr_cur_edge_GUARDED_CONDITION_trigerred)
					 << " **";

    		qDebug() << " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] edge event start state: "
    				 << _current_STATE->get_MONITOR_STATE_NAME()
					 << " **";
    	}

    	//check converse condition of pre-condition doesn't apply
    	bool precondition_IS_TRUE =
    			cur_STATE_OUTGOING_EDGE
					->CHECK_SOURCE_STATE_in_OR_notin_CONDITION(*_current_STATE,
															   *this);

    	if (debug_MSG)
    	{
    		qDebug() << QString(" *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] "
    							"START STATE [%1] precondition_IS_TRUE: ")
							.arg(cur_STATE_OUTGOING_EDGE
									->get_SOURCE_STATE()
										->GET_STRING_representation_OF_state_condition())
    				 << BOOL_TO_STRING(precondition_IS_TRUE)
					 << " **";
    	}

    	if (precondition_IS_TRUE)
    	{
    		set_current_triggered_EDGE(cur_STATE_OUTGOING_EDGE);

    	    /*
    	     * trace(_current_STATE) = _TRACE_LOG, <cur_STATE_OUTGOING_EDGE->get_EDGE_EVENT_TOKEN()>
    	     */

    		YR_CPP_MONITOR_STATE * a_potential_accepting_state = cur_STATE_OUTGOING_EDGE->get_TARGET_STATE();

    		if (0 != a_potential_accepting_state 							&&
    			CHECK_whether__STATE__is__Accepting(*a_potential_accepting_state))
    		{

                qDebug() << " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] edge event accepting state: "
                         << a_potential_accepting_state->get_MONITOR_STATE_NAME() << " **";
                qDebug() << " ******************************* ACCEPTING STATE *******************************";

                if (a_potential_accepting_state->is_ERROR_STATE())
    			{
                    qDebug() << " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] EDGE EVENT ERROR STATE: "
                             << a_potential_accepting_state->get_MONITOR_STATE_NAME() << " **";
                    qDebug() << " ******************************* ERROR STATE *******************************";


                    if (CAN_recover_FROM_THIS_ACCEPTING_ERROR_State(a_potential_accepting_state))
                    {
                        YR_CPP_MONITOR_STATE * a_previous_source_state
                            = cur_STATE_OUTGOING_EDGE->get_SOURCE_STATE();

                        execute_RECOVERY_SQL_QUERY_from_accepting_error_state
                            (a_previous_source_state,
                             a_potential_accepting_state);
                    }


                    if (0 != _CALL_BACK_final_state)
                    {
                    	(*_CALL_BACK_final_state)(this, cur_STATE_OUTGOING_EDGE);
                    }
    			}
    		}

    		return true;
    	}
    }

    /*
     * NO TRACE FOR THIS STATE ANYMORE
     * IN CASE NO EVENT WAS TRIGERRED.
     */
    _current_STATE->remove_RUNTIME_MONITOR_INCOMING_TRACE_EVENT();

    return false;
}


bool YR_CPP_MONITOR::SET_DB_CONFIGURATION_PARAMETERS(QString db_type,
                                                     QString db_name,
                                                     QString db_ip_address,
                                                     QString db_user_name,
                                                     QString db_user_pwd,
                                                     QString db_connection_options
													 	 /* = YR_CPP_UTILS::EMPTY_STRING */
                                                    )
{
    if (0 == _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS)
    {
        QDEBUG_STRING_OUTPUT_1("!! YR_CPP_MONITOR::SET_DB_CONFIGURATION_PARAMETERS: "
        					   "QSqlDatabase object instance NOT INSTANTIATED !!!");

        return false;
    }

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->set_db_type(db_type);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->set_db_name(db_name);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->set_db_ip_address(db_ip_address);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->set_db_user_name(db_user_name);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->set_db_user_pwd(db_user_pwd);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS
		->set_db_connection_options(db_connection_options);


    bool isDatabaseOpened =
                    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->open();

//      QDEBUG_STRING_OUTPUT_2("!! YR_CPP_MONITOR::SET_DB_CONFIGURATION_PARAMETERS: database opened: ",
//                                                 BOOL_TO_STRING(isDatabaseOpened));


    return isDatabaseOpened;
}


/**
 * THIS METHOD COULD USE SQL QUERY !
 */
bool YR_CPP_MONITOR::is_in_SET_ALGEBRA(QString a_SET_VARIABLE,
                                       QString a_SUPPOSED_SET_VARIABLE)
{
//      qDebug() << QString("YR_CPP_MONITOR::is_in_SET_ALGEBRA; "
//                                              "a_SET_VARIABLE: %1 "
//                                              "a_SUPPOSED_SET_VARIABLE: %2")
//                                      .arg(a_SET_VARIABLE,
//                                               a_SUPPOSED_SET_VARIABLE);

    QStringList SQL_table_column_LIST = a_SET_VARIABLE.split(".", Qt::SkipEmptyParts);


    QString strQuery = QString("select * from %1 WHERE %2 = '%3';")
    						.arg(SQL_table_column_LIST.at(0),
                                 SQL_table_column_LIST.at(1),
								 a_SUPPOSED_SET_VARIABLE);

    //qDebug() << "strQuery: " << strQuery;

    int rowCount = YR_CPP_UTILS::execQueryRowCount(strQuery, true);

    //qDebug() << "rowCount > 0: " << BOOL_TO_STRING(rowCount > 0);

    return (rowCount > 0);
}


bool YR_CPP_MONITOR::
	CHECK_whether__STATE__is__Accepting(YR_CPP_MONITOR_STATE &A_POTENTIAL_ACCEPTING_STATE)
{
    if (A_POTENTIAL_ACCEPTING_STATE._SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.size() > 0)
    {
        //qDebug() << "_SET_db_IN_STATEPROPERTYKEY_TO_VALUE > 0";

        bool is_ACCEPTING_STATE_in =
        		CHECK_post_condition_IN
                         (A_POTENTIAL_ACCEPTING_STATE._SET_IN_POST_STATEPROPERTYKEY_TO_VALUE);

        return is_ACCEPTING_STATE_in;
    }
    else if (A_POTENTIAL_ACCEPTING_STATE._SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.size() > 0)
    {
        //qDebug() << "_SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE > 0";

        bool is_ACCEPTING_STATE_NOT_in =
        		CHECK_post_condition_notIN
                         (A_POTENTIAL_ACCEPTING_STATE._SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE);

        return is_ACCEPTING_STATE_NOT_in;
    }

    return false;
}


bool YR_CPP_MONITOR::
	CHECK_PRE_CONDITION_notIN(QMap<QString, QString> &SET_NOTin_PRE_STATEPROPERTYKEY_TO_VALUE_map)
{
    QList<QString> set_notIN_PRE_KEYS =
                    SET_NOTin_PRE_STATEPROPERTYKEY_TO_VALUE_map.keys();

    //qDebug() << "SET_NOTin_STATEPROPERTYKEY_TO_VALUE_map: "
    //               << SET_NOTin_STATEPROPERTYKEY_TO_VALUE_map;

    QString A_SET_notIN_PRE_PROPERTY_KEY;

    QString A_SET_notIN_PRE_PROPERTY_value;

    for (uint i = 0; i < set_notIN_PRE_KEYS.size(); ++i)
    {
        A_SET_notIN_PRE_PROPERTY_KEY = set_notIN_PRE_KEYS.at(i);

        A_SET_notIN_PRE_PROPERTY_value =
                        SET_NOTin_PRE_STATEPROPERTYKEY_TO_VALUE_map.
                        value(A_SET_notIN_PRE_PROPERTY_KEY);

        if (!is_in_SET_ALGEBRA(A_SET_notIN_PRE_PROPERTY_value,
                               A_SET_notIN_PRE_PROPERTY_KEY))
        {
			//if (debug_MSG)
			//{
				qDebug() << " *[YR_CPP_MONITOR::CHECK_PRE_CONDITION_notIN:] precondition_IS_TRUE: True   **";
			//}
//                      qDebug() << QString("%1 NOT in set %2")
//                                                      .arg(A_SET_notIN_PROPERTY_KEY,
//                                                               A_SET_notIN_PRE_PROPERTY_value);
            return true;
        }
    }
    //if (debug_MSG)
    //{
    	qDebug() << " *[YR_CPP_MONITOR::CHECK_PRE_CONDITION_notIN:] precondition_IS_TRUE: FALSE   **";
    //}

    return false;
}


bool YR_CPP_MONITOR::
	CHECK_PRE_CONDITION_IN(QMap<QString, QString> &SET_in_PRE_STATEPROPERTYKEY_TO_VALUE_map)
{
    QList < QString > set_in_KEYS =
                    SET_in_PRE_STATEPROPERTYKEY_TO_VALUE_map.keys();

    //qDebug() << "SET_in_STATEPROPERTYKEY_TO_VALUE_map: "
    //               << SET_in_STATEPROPERTYKEY_TO_VALUE_map;

    QString A_SET_IN_PRE_PROPERTY_KEY;

    QString A_SET_IN_PRE_PROPERTY_value;

    for (uint i = 0; i < set_in_KEYS.size(); ++i)
    {
        A_SET_IN_PRE_PROPERTY_KEY = set_in_KEYS.at(i);

        A_SET_IN_PRE_PROPERTY_value =
                        SET_in_PRE_STATEPROPERTYKEY_TO_VALUE_map.value(A_SET_IN_PRE_PROPERTY_KEY);

        if (is_in_SET_ALGEBRA(A_SET_IN_PRE_PROPERTY_value, A_SET_IN_PRE_PROPERTY_KEY))
        {
			//if (debug_MSG)
			//{
				qDebug() << " *[YR_CPP_MONITOR::CHECK_PRE_CONDITION_IN:] precondition_IS_TRUE: True   **";
			//}
//                      qDebug() << QString("%1 in set %2")
//                                                      .arg(A_SET_IN_PROPERTY_KEY,
//                                                               A_SET_IN_PROPERTY_value);
            return true;
        }
    }

    //if (debug_MSG)
    //{
    	qDebug() << " *[YR_CPP_MONITOR::CHECK_PRE_CONDITION_IN:] precondition_IS_TRUE: FALSE   **";
    //}
//      qDebug() << QString("%1 NOT in set %2")
//                                      .arg(A_SET_IN_PROPERTY_KEY,
//                                               A_SET_IN_PROPERTY_value);

    return false;
}


bool YR_CPP_MONITOR::
	CHECK_post_condition_notIN(QMap<QString, QString> &SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE_map)
{
    QList < QString > set_notIN_POST_KEYS =
                    SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE_map.keys();

    //qDebug() << "SET_DBnotIN_STATEPROPERTYKEY_TO_VALUE_map: "
    //               << SET_DBnotIN_STATEPROPERTYKEY_TO_VALUE_map;

    QString A_SET_notIN_POST_PROPERTY_KEY;

    QString A_SET_notIN_POST_PROPERTY_value;

    for (uint i = 0; i < set_notIN_POST_KEYS.size(); ++i)
    {
        A_SET_notIN_POST_PROPERTY_KEY = set_notIN_POST_KEYS.at(i);

        A_SET_notIN_POST_PROPERTY_value =
                        SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE_map.
                        value(A_SET_notIN_POST_PROPERTY_KEY);

        if (!is_in_SET_ALGEBRA(A_SET_notIN_POST_PROPERTY_value,
                               A_SET_notIN_POST_PROPERTY_KEY))
        {
			//if (debug_MSG)
			//{
				qDebug() << " *[YR_CPP_MONITOR::CHECK_post_condition_notIN:] postcondition_IS_TRUE: True   **";
			//}
//                      qDebug() << QString("%1 db NOT in set %2")
//                                                                              .arg(A_SET_DBnotIN_PROPERTY_KEY,
//                                                                                       A_SET_DBnotIN_PROPERTY_value);
            return true;
        }
    }

    //if (debug_MSG)
    //{
    	qDebug() << " *[YR_CPP_MONITOR::CHECK_post_condition_notIN:] postcondition_IS_TRUE: FALSE   **";
    //}

    return false;
}


bool YR_CPP_MONITOR::
	CHECK_post_condition_IN(QMap<QString, QString> &SET_IN_POST_STATEPROPERTYKEY_TO_VALUE_map)
{
    QList<QString> set_IN_POST_KEYS = SET_IN_POST_STATEPROPERTYKEY_TO_VALUE_map.keys();

    //qDebug() << "SET_dbIN_STATEPROPERTYKEY_TO_VALUE_map: "
    //               << SET_dbIN_STATEPROPERTYKEY_TO_VALUE_map;

    QString A_SET_IN_POST_PROPERTY_KEY;

    QString A_SET_IN_POST_PROPERTY_value;

    for (uint i = 0; i < set_IN_POST_KEYS.size(); ++i)
    {
        A_SET_IN_POST_PROPERTY_KEY = set_IN_POST_KEYS.at(i);

        A_SET_IN_POST_PROPERTY_value =
        		SET_IN_POST_STATEPROPERTYKEY_TO_VALUE_map.value(A_SET_IN_POST_PROPERTY_KEY);

        if (is_in_SET_ALGEBRA(A_SET_IN_POST_PROPERTY_value,
                              A_SET_IN_POST_PROPERTY_KEY))
        {
			//if (debug_MSG)
			//{
				qDebug() << " *[YR_CPP_MONITOR::CHECK_post_condition_IN:] postcondition_IS_TRUE: True   **";
			//}
//                      qDebug() << QString("%1 db in set %2")
//                                                      .arg(A_SET_dbIN_PROPERTY_KEY,
//                                                               A_SET_dbIN_PROPERTY_value);
            return true;
        }
    }

    //if (debug_MSG)
    //{
    	qDebug() << " *[YR_CPP_MONITOR::CHECK_post_condition_IN:] postcondition_IS_TRUE: FALSE   **";
    //}
//      qDebug() << QString("%1 db NOT in set %2")
//                                      .arg(A_SET_dbIN_PROPERTY_KEY,
//                                               A_SET_dbIN_PROPERTY_value);

    return false;
}


QString YR_CPP_MONITOR::YR_open_HEADER_TEMPLATE_FILE()
{
    QFile a_template_HEADER_FILE_runtime_monitor(FILE_YR_hpp_TEMPLATE_RUNTIME_MONITOR);

    //      qDebug() << "++ 1. YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR: "
    //                               << YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;

    YR_CPP_UTILS::
    YEROTH_READ_FILE_CONTENT(a_template_HEADER_FILE_runtime_monitor,
                             YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR);

    //      qDebug() << "++ 2. YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR: "
    //                               << YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;

    if (!a_template_HEADER_FILE_runtime_monitor.open(QFile::ReadOnly))
    {
        QString errMsg("YR_CPP_MONITOR::YR_open_HEADER_TEMPLATE_FILE: ");

        errMsg.append(" ne peut pas ouvrir pour lecture le fichier ")
        	  .append(FILE_YR_hpp_TEMPLATE_RUNTIME_MONITOR)
			  .append(" . ) !\n\n");

        qDebug() << errMsg;

        return YR_CPP_UTILS::EMPTY_STRING;
    }

    //      qDebug() << "++ 3. YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR: "
    //                       << YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;

    return YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;
}


QString YR_CPP_MONITOR::YR_open_SOURCE_TEMPLATE_FILE()
{
    QFile a_template_SOURCE_FILE_runtime_monitor(FILE_YR_cpp_TEMPLATE_RUNTIME_MONITOR);

    //      qDebug() << "++ 1. YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR: "
    //                               << YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;

    YR_CPP_UTILS::YEROTH_READ_FILE_CONTENT(a_template_SOURCE_FILE_runtime_monitor,
                             	 	 	   YR_CPP_UTILS::YR_SOURCE_cpp_TEMPLATE_RUNTIME_MONITOR);

    //      qDebug() << "++ 2. YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR: "
    //                               << YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;

    if (!a_template_SOURCE_FILE_runtime_monitor.open(QFile::ReadOnly))
    {
        QString errMsg("YR_CPP_MONITOR::YR_open_SOURCE_TEMPLATE_FILE: ");

        errMsg.append(" ne peut pas ouvrir pour lecture le fichier ").
        append(FILE_YR_cpp_TEMPLATE_RUNTIME_MONITOR).append(" . ) !\n\n");

        qDebug() << errMsg;

        return YR_CPP_UTILS::EMPTY_STRING;
    }

//      qDebug() << "++ 3. YR_CPP_UTILS::YR_SOURCE_cpp_TEMPLATE_RUNTIME_MONITOR: "
//                   << YR_CPP_UTILS::YR_SOURCE_cpp_TEMPLATE_RUNTIME_MONITOR;

    return YR_CPP_UTILS::YR_SOURCE_cpp_TEMPLATE_RUNTIME_MONITOR;
}


QString YR_CPP_MONITOR::
    YR_generate_cplusplus_headers_files__AND__SAVE__TO__DISK(QString A_hpp_FILE_NAME,
                                                             QString a_class_NAME /* = "YR_DB_RUNTIME_VERIF_Main" */)
{
	QString header_FILE_content =
                YR_generate_cplusplus_headers_files(A_hpp_FILE_NAME,
                                                    a_class_NAME);

    save_yr_SOURCE_FILES(A_hpp_FILE_NAME,
                         header_FILE_content);

    return header_FILE_content;
}


QString YR_CPP_MONITOR::
            YR_generate_cplusplus_headers_files(QString A_hpp_FILE_NAME,
                                                QString a_class_NAME)
{
    QString EDGES_EVENTS_TOKENS_declarations;


    QString EXPORTED_EDGE_SOURCE_CODE;

    QString EDGE_EVENT_token_with_parenthesis;

    YR_CPP_MONITOR_EDGE *_AN_EDGE = 0;

    for (uint i = 0; i < _EDGES.size(); ++i)
    {
        _AN_EDGE = _EDGES.at(i);

        if (0 != _AN_EDGE && _AN_EDGE != _ROOT_EDGE)
        {
            EDGE_EVENT_token_with_parenthesis =
                            _AN_EDGE->get_EDGE_EVENT_TOKEN();

            EDGE_EVENT_token_with_parenthesis =
                            QString("YR_SQL_%1()").arg(_AN_EDGE->
                                                       get_EDGE_EVENT_TOKEN());

            EDGE_EVENT_token_with_parenthesis =
                            EDGE_EVENT_token_with_parenthesis.replace(".", "_");

            EDGE_EVENT_token_with_parenthesis =
                            EDGE_EVENT_token_with_parenthesis.replace("'", "");

            EDGES_EVENTS_TOKENS_declarations.append(QString("bool %1; ")
                                                     .arg(EDGE_EVENT_token_with_parenthesis));

            EXPORTED_EDGE_SOURCE_CODE
				.append(_AN_EDGE->YR_EXPORT_edge_CLASS_INSTANCE());
        }
    }


    YR_open_HEADER_TEMPLATE_FILE();


    QString YR_TO_EXPORT_SOURCE_CODE_HEADER_FILE =
                    YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;


    YR_TO_EXPORT_SOURCE_CODE_HEADER_FILE
        .replace("_slots_event_declarations_YR_RTM_REPLACEMENT_QSTRING_",
                 EDGES_EVENTS_TOKENS_declarations);


    YR_TO_EXPORT_SOURCE_CODE_HEADER_FILE.replace("_YR_RTM_HEADER_FILE_NAME",
    											 A_hpp_FILE_NAME);


    YR_TO_EXPORT_SOURCE_CODE_HEADER_FILE.replace("_YR_RTM_REPLACEMENT_QSTRING",
    											 a_class_NAME);


    return YR_TO_EXPORT_SOURCE_CODE_HEADER_FILE;
}


QString YR_CPP_MONITOR::
	GENERATE_METHOD_event_call(QString event_METHOD_name,
                               QString STRING_bool_GUARDED_CONDITION /* = YR_CPP_UTILS::EMPTY_STRING */)
{
    QString GENERATE_METHOD_EVENT_CALL;

    QString an_EVENT_METHOD_call;

    if (STRING_bool_GUARDED_CONDITION.isEmpty())
    {
        an_EVENT_METHOD_call
        	.append(QString("YR_trigger_an_edge_event(\"%1\");")
        			.arg(event_METHOD_name));

        GENERATE_METHOD_EVENT_CALL
        	.append(an_EVENT_METHOD_call);
    }

    return GENERATE_METHOD_EVENT_CALL.trimmed();
}


QString YR_CPP_MONITOR::
	YR_GENERATE_FINAL_STATE_auto_CODE(QString 			    &a_last_edge_VARIABLE_STRING_pointer,
                                   	  YR_CPP_MONITOR_EDGE   &_AN_EDGE)
{
    QString return_code;

    YR_CPP_MONITOR_STATE *a_source_state = _AN_EDGE.get_SOURCE_STATE();
    YR_CPP_MONITOR_STATE *a_target_state = _AN_EDGE.get_TARGET_STATE();

    if (0 != a_source_state &&
        0 != a_target_state &&
        a_target_state->is_FINAL_STATE())
    {
        QDEBUG_STRING_OUTPUT_2("* CAN_recover_FROM_THIS_ACCEPTING_ERROR_State",
                                a_target_state->get_MONITOR_STATE_NAME());

        if (CAN_recover_FROM_THIS_ACCEPTING_ERROR_State(a_target_state))
        {
            QDEBUG_STRING_OUTPUT_2("*** CAN_recover_FROM_THIS_ACCEPTING_ERROR_State",
                                   a_target_state->get_MONITOR_STATE_NAME());

            if (!a_target_state->Is_SQL_RECOVERY_QUERY_STRING_Empty())
            {
                return_code =
                    QString("%1->get_TARGET_STATE()->Set_SQL_RECOVERY_QUERY_STRING(\"%2\");\n\n")
                        .arg(a_last_edge_VARIABLE_STRING_pointer,
                             a_target_state->Get_SQL_RECOVERY_QUERY_STRING());
            }

            return_code = return_code
                .append(QString("set_Recovery_action(%1->get_SOURCE_STATE(),\n"
                                "\t\t%2->get_TARGET_STATE());\n")
                            .arg(a_last_edge_VARIABLE_STRING_pointer,
                                 a_last_edge_VARIABLE_STRING_pointer));
        }
    }

    return return_code;
}


QString YR_CPP_MONITOR::
	YR_GENERATE_START_FINAL_STATE_CODE(QString 				&a_last_edge_VARIABLE_STRING_pointer,
                                   	   YR_CPP_MONITOR_EDGE  &_AN_EDGE)
{
    QString return_code;

    YR_CPP_MONITOR_STATE *A_STATE = _AN_EDGE.get_SOURCE_STATE();

    if (0 != A_STATE && A_STATE->is_START_STATE())
    {
        return_code = QString("%1->get_SOURCE_STATE()->set_START_STATE(*this, true);\n")
						.arg(a_last_edge_VARIABLE_STRING_pointer);
    }


    A_STATE = _AN_EDGE.get_TARGET_STATE();

    if (0 != A_STATE && A_STATE->is_FINAL_STATE())
    {
        return_code = return_code.append(
        					QString("%1->get_TARGET_STATE()->set_ERROR_STATE(true);\n")
                        		.arg(a_last_edge_VARIABLE_STRING_pointer));
    }

    return return_code;
}


QString
YR_CPP_MONITOR::
	GENERATE_pre_post_conditions_code(QString 			  &a_last_edge_VARIABLE_STRING_pointer,
                                  	  YR_CPP_MONITOR_EDGE &_AN_EDGE)
{
    QString returned_code;

    if (0 != _AN_EDGE.get_SOURCE_STATE())
    {
        QString PRE_CONDITION_code;

        if (_AN_EDGE.get_SOURCE_STATE()->_SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.size() > 0)
        {
        	PRE_CONDITION_code =
        		QString("%1->get_SOURCE_STATE()->set_PRE_CONDITION_IN(\"%2\", \"%3\");\n")
					.arg(a_last_edge_VARIABLE_STRING_pointer,
						 _AN_EDGE.get_SOURCE_STATE()->_SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.keys().at(0),
						 _AN_EDGE.get_SOURCE_STATE()->_SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.values().at(0));
        }
        else if (_AN_EDGE.get_SOURCE_STATE()->_SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.size() > 0)
        {
        	PRE_CONDITION_code =
        			QString("%1->get_SOURCE_STATE()->set_PRE_CONDITION_notIN(\"%2\", \"%3\");\n")
        			    .arg(a_last_edge_VARIABLE_STRING_pointer,
        			         _AN_EDGE.get_SOURCE_STATE()->_SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.keys().at(0),
        			         _AN_EDGE.get_SOURCE_STATE()->_SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.values().at(0));
        }

        returned_code.append(PRE_CONDITION_code);
    }


    if (0 != _AN_EDGE.get_TARGET_STATE())
    {
        QString POST_CONDITION_code;

        if (_AN_EDGE.get_TARGET_STATE()->_SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.size() > 0)
        {
        	POST_CONDITION_code =
        		QString("%1->get_TARGET_STATE()->set_POST_CONDITION_IN(\"%2\", \"%3\");\n")
					.arg(a_last_edge_VARIABLE_STRING_pointer,
						 _AN_EDGE.get_TARGET_STATE()->_SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.keys().at(0),
						 _AN_EDGE.get_TARGET_STATE()->_SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.values().at(0));
        }
        else if (_AN_EDGE.get_TARGET_STATE()->_SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.size() > 0)
        {
        	POST_CONDITION_code =
        		QString("%1->get_TARGET_STATE()->set_POST_CONDITION_notIN(\"%2\", \"%3\");\n")
					.arg(a_last_edge_VARIABLE_STRING_pointer,
						 _AN_EDGE.get_TARGET_STATE()->_SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.keys().at(0),
						 _AN_EDGE.get_TARGET_STATE()->_SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.values().at(0));
        }

        returned_code.append(POST_CONDITION_code);
    }

    return returned_code;
}


QString YR_CPP_MONITOR::
        YR_generate_cplusplus_sources_files__AND__SAVE__TO__DISK(QString A_cpp_FILE_NAME,
                                                                 QString a_class_NAME /* = "YR_DB_RUNTIME_VERIF_Main" */)
{
    QString A_hpp_FILE_NAME = QString(A_cpp_FILE_NAME);

    A_hpp_FILE_NAME = A_hpp_FILE_NAME.remove((A_hpp_FILE_NAME.length() - 3), 3);


    A_hpp_FILE_NAME.append("hpp");


	QString SOURCE_FILE_content =
        YR_generate_cplusplus_sources_files(A_hpp_FILE_NAME,
                                            a_class_NAME);

	save_yr_SOURCE_FILES(A_cpp_FILE_NAME,
						 SOURCE_FILE_content);

	return SOURCE_FILE_content;
}


QString YR_CPP_MONITOR::
    YR_generate_cplusplus_sources_files(QString A_hpp_FILE_NAME,
                                        QString a_class_NAME)
{
    QString EDGES_EVENTS_TOKENS__DEFINITIONS;


    QString EXPORTED_EDGE_SOURCE_CODE;

    QString EDGE_EVENT_token_with_parenthesis;

    YR_CPP_MONITOR_EDGE *_AN_EDGE = 0;

    for (uint i = 0; i < _EDGES.size(); ++i)
    {
        _AN_EDGE = _EDGES.at(i);

        if (0 != _AN_EDGE && _AN_EDGE != _ROOT_EDGE)
        {
            EDGE_EVENT_token_with_parenthesis =
                            _AN_EDGE->get_EDGE_EVENT_TOKEN();

            EDGE_EVENT_token_with_parenthesis =
                            QString("YR_SQL_%1()").arg(_AN_EDGE->
                                                       get_EDGE_EVENT_TOKEN());

            EDGE_EVENT_token_with_parenthesis =
                            EDGE_EVENT_token_with_parenthesis.replace(".", "_");

            EDGE_EVENT_token_with_parenthesis =
                            EDGE_EVENT_token_with_parenthesis.replace("'", "");

            EDGES_EVENTS_TOKENS__DEFINITIONS
            	.append(QString("bool %1::%2\n" "{ \nreturn " "%3" "\n}\n ")
            				.arg(a_class_NAME,
            					 EDGE_EVENT_token_with_parenthesis,
								 GENERATE_METHOD_event_call(_AN_EDGE->get_EDGE_EVENT_TOKEN())));

            EXPORTED_EDGE_SOURCE_CODE
				.append(_AN_EDGE->YR_EXPORT_edge_CLASS_INSTANCE());
        }
    }


    QString current_event_edge_token;

    QString last_edge_variable_STRING;

    QString START_FINAL__states__preconditions_DEFINITIONS;

    QString FINAL_STATE_AUTO_DEFINITIONS;

    QString EVENT_EDGE_final_states_DEFINITIONS;

    QString EVENT_EDGE_DEFINITIONS;


    EVENT_EDGE_DEFINITIONS.append
		(QString("set_RUNTIME_MONITOR_NAME(\"%1\");\n\n")
			.arg(get_RUNTIME_MONITOR_NAME()));


    for (uint i = 0; i < _EDGES.size(); ++i)
    {
        _AN_EDGE = _EDGES.at(i);

        if (0 != _AN_EDGE && _AN_EDGE != _ROOT_EDGE)
        {
            qDebug() << "_MONITOR_STATE_NAME_string_key: "
                     << _AN_EDGE->get_SOURCE_STATE()->get_MONITOR_STATE_NAME();

            last_edge_variable_STRING =
                            QString("a_last_edge_%1").arg(QString::number(i));

            EVENT_EDGE_DEFINITIONS
				.append(QString("\nYR_CPP_MONITOR_EDGE *%1 = create_yr_monitor_edge (\"%2\", \"%3\");")
                           .arg(last_edge_variable_STRING,
                                _EDGES.at(i)->get_SOURCE_STATE()->get_MONITOR_STATE_NAME(),
                                _EDGES.at(i)->get_TARGET_STATE()->get_MONITOR_STATE_NAME()));

            EVENT_EDGE_DEFINITIONS.append("\n");

            EVENT_EDGE_final_states_DEFINITIONS =
                            YR_GENERATE_START_FINAL_STATE_CODE(last_edge_variable_STRING,
                                                               *_AN_EDGE);

            START_FINAL__states__preconditions_DEFINITIONS =
                            GENERATE_pre_post_conditions_code(last_edge_variable_STRING,
                                                              *_AN_EDGE);

            FINAL_STATE_AUTO_DEFINITIONS =
                            YR_GENERATE_FINAL_STATE_auto_CODE(last_edge_variable_STRING,
                                                               *_AN_EDGE);

            EVENT_EDGE_DEFINITIONS.append(EVENT_EDGE_final_states_DEFINITIONS);

            EVENT_EDGE_DEFINITIONS.append(START_FINAL__states__preconditions_DEFINITIONS);

            EVENT_EDGE_DEFINITIONS.append("\n");

            EVENT_EDGE_DEFINITIONS.append(FINAL_STATE_AUTO_DEFINITIONS);

            _EDGES.at(i)->print();
        }
    }


    qDebug() << "EVENT_EDGE_DEFINITIONS (1): " << EVENT_EDGE_DEFINITIONS;

    EVENT_EDGE_DEFINITIONS.append("\n");

    for (uint i = 0; i < _EDGES.size(); ++i)
    {
        _AN_EDGE = _EDGES.at(i);

        if (0 != _AN_EDGE && _AN_EDGE != _ROOT_EDGE)
        {
            //_EDGES.at(i)->print();

            current_event_edge_token =
                            _AN_EDGE->get_EDGE_EVENT_TOKEN().trimmed();

            YR_CPP_notinset_inset_TRACE_expression *_AN_EDGE_last_guarded_CONDITION_expression =
            		_AN_EDGE->get_guarded_CONDITION_expression();

            if (0 != _AN_EDGE_last_guarded_CONDITION_expression)
            {
                EVENT_EDGE_DEFINITIONS
                	.append(QString("\nYR_CPP_notinset_inset_TRACE_expression *a_last_edge_%1_GUARDED_CONDITION \n"
                					"\t= new YR_CPP_notinset_inset_TRACE_expression(%2,\n"
                					"\t\"%3\",\n"
                					"\t\"%4\");\n\n")
                				.arg(QString::number(i),
                					 _AN_EDGE_last_guarded_CONDITION_expression->IS__Predicate__in_set__TRACE() ? "true" : "false",
									 _AN_EDGE_last_guarded_CONDITION_expression->getDB_SQL_operation__SUT_event(),
									 _AN_EDGE_last_guarded_CONDITION_expression->getRUNTIME__MONITORING__STATE_name()));

                EVENT_EDGE_DEFINITIONS
                	.append(QString("a_last_edge_%1->set_GUARDED_CONDITION(a_last_edge_%2_GUARDED_CONDITION);\n\n")
                				.arg(QString::number(i),
                					 QString::number(i)));
            }


            EVENT_EDGE_DEFINITIONS
            	.append(QString("\nYR_CPP_MONITOR_EVENT *a_last_edge_event_%1 = "
            					"a_last_edge_%2->set_EDGE_EVENT(\"%3\");\n")
            				.arg(QString::number(i),
            					 QString::number(i),
            					 current_event_edge_token));
        }
    }

    EVENT_EDGE_DEFINITIONS
		.append(QString("\n \t//print_TO_dot_FILE();\n\n"));

    EVENT_EDGE_DEFINITIONS
    	.append(QString
           ("YR_register_set_final_state_CALLBACK_FUNCTION(&YR_CALL_BACK_final_state);"));

    qDebug() << "EVENT_EDGE_DEFINITIONS: " << EVENT_EDGE_DEFINITIONS;


    YR_open_SOURCE_TEMPLATE_FILE();


    QString YR_TO_EXPORT_SOURCE_CODE_source_FILE =
                    YR_CPP_UTILS::YR_SOURCE_cpp_TEMPLATE_RUNTIME_MONITOR;


    YR_TO_EXPORT_SOURCE_CODE_source_FILE.
    replace("__event_edge_DEFINITIONSYRRTMREPLACEMENTQSTRING__",
            EVENT_EDGE_DEFINITIONS);


    YR_TO_EXPORT_SOURCE_CODE_source_FILE.
    replace("__slots_event_DEFINITIONS_YR_RTM_REPLACEMENT_QSTRING__",
            EDGES_EVENTS_TOKENS__DEFINITIONS);



    QString A_cpp_FILE_NAME = QString(A_hpp_FILE_NAME);

    A_cpp_FILE_NAME = A_cpp_FILE_NAME.remove((A_cpp_FILE_NAME.length() - 3), 3);


    A_cpp_FILE_NAME.append("cpp");



    YR_TO_EXPORT_SOURCE_CODE_source_FILE
        .replace("_YR_RTM_HEADER_FILE_NAME",
                 A_hpp_FILE_NAME);


    YR_TO_EXPORT_SOURCE_CODE_source_FILE
        .replace("_YR_RTM_IMPLEMENTATION_FILE_NAME",
                 A_cpp_FILE_NAME);


    YR_TO_EXPORT_SOURCE_CODE_source_FILE
        .replace("_YR_RTM_REPLACEMENT_QSTRING",
                 a_class_NAME);



    return YR_TO_EXPORT_SOURCE_CODE_source_FILE;
}



void YR_CPP_MONITOR::save_yr_SOURCE_FILES(QString a_header_OR_SOURCE_file_NAME,
                                          QString a_header_OR_SOURCE_file_CONTENT)
{
    QFile out_file_CONTENT(a_header_OR_SOURCE_file_NAME.trimmed());

    a_header_OR_SOURCE_file_CONTENT = a_header_OR_SOURCE_file_CONTENT.trimmed();

    a_header_OR_SOURCE_file_CONTENT.append("\n\n");

    out_file_CONTENT.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

    out_file_CONTENT.write(a_header_OR_SOURCE_file_CONTENT.toStdString().c_str());

    out_file_CONTENT.flush();

    out_file_CONTENT.close();
}


void YR_CPP_MONITOR::find_yr_monitor_edges(YR_CPP_MONITOR_EDGE &an_edge,
                                           QList<YR_CPP_MONITOR_EDGE *> &resulting_edges)
{
    resulting_edges.clear();

    YR_CPP_MONITOR_EDGE *cur_edge = 0;

    for (uint k = 0; k < _EDGES.size(); ++k)
    {
        cur_edge = _EDGES.at(k);

        if (0 != cur_edge)
        {
            if (an_edge == *cur_edge)
            {
                resulting_edges.append(cur_edge);
            }
        }
    }
}


void YR_CPP_MONITOR::find_yr_monitor_edges(QString start_state_key,
                                           QString end_state_key,
                                           QList<YR_CPP_MONITOR_EDGE *> &resulting_edges)
{
    resulting_edges.clear();

    YR_CPP_MONITOR_EDGE *cur_edge = 0;

    for (uint k = 0; k < _EDGES.size(); ++k)
    {
        cur_edge = _EDGES.at(k);

        if (0 != cur_edge)
        {
            if (YR_CPP_UTILS::isEqualsCaseInsensitive(cur_edge->get_SOURCE_STATE_KEY(),
                                            		  start_state_key))
            {
                if (YR_CPP_UTILS::
                        isEqualsCaseInsensitive(cur_edge->get_TARGET_STATE_KEY(),
                                                end_state_key))
                {
                    resulting_edges.append(cur_edge);
                }
            }
        }
    }
}


YR_CPP_MONITOR_EDGE *YR_CPP_MONITOR::create_yr_monitor_edge(QString source_state_key,
                                                            QString target_state_key)
{
	YR_CPP_MONITOR_EDGE *A_RESULTING_EDGE = 0;

	QList <YR_CPP_MONITOR_EDGE *> resulting_CURRENT_edges;

	find_yr_monitor_edges(source_state_key,
						  target_state_key,
						  resulting_CURRENT_edges);

	if (resulting_CURRENT_edges.size() > 0)
	{
		assert(1 == resulting_CURRENT_edges.size());

		A_RESULTING_EDGE = resulting_CURRENT_edges.at(0);

		return A_RESULTING_EDGE;
	}

    YR_CPP_MONITOR_STATE *A_START_STATE =
    		YR_CPP_MONITOR::create_yr_monitor_state(source_state_key);

    if (0 != A_START_STATE)
    {
        YR_CPP_MONITOR_STATE *AN_END_STATE =
                        YR_CPP_MONITOR::create_yr_monitor_state(target_state_key);

        if (0 != AN_END_STATE)
        {
            A_RESULTING_EDGE = new YR_CPP_MONITOR_EDGE(*A_START_STATE,
            										   *AN_END_STATE);

            AN_END_STATE->set_AN_incoming_edge(A_RESULTING_EDGE);

            A_START_STATE->set_AN_outgoing_edge(A_RESULTING_EDGE);

            _EDGES.append(A_RESULTING_EDGE);

            return A_RESULTING_EDGE;
        }
        else
        {
            YR_CPP_MONITOR::DELETE_yr_monitor_state(A_START_STATE->GET_ID());
        }
    }

    return 0;
}


YR_CPP_MONITOR_EDGE *YR_CPP_MONITOR::create_yr_monitor_edge(QString source_state_key,
                                                            QString target_state_key,
                                                            QString event_string)
{
    YR_CPP_MONITOR_EDGE *AN_EDGE =
                    YR_CPP_MONITOR::create_yr_monitor_edge(source_state_key,
                                                           target_state_key);

    if (0 != AN_EDGE)
    {
        YR_CPP_MONITOR_EVENT *AN_EVENT = AN_EDGE->set_EDGE_EVENT(event_string);

        if (0 != AN_EVENT)
        {
            return AN_EDGE;
        }
        else
        {
            YR_CPP_MONITOR::DELETE_yr_monitor_edge(AN_EDGE);
        }
    }

    return 0;
}


YR_CPP_MONITOR_EDGE *YR_CPP_MONITOR::create_yr_monitor_edge(QString source_state_key,
                                                            QString target_state_key,
                                                            QString event_string,
															YR_CPP_notinset_inset_TRACE_expression *guarded_condition)
{
    YR_CPP_MONITOR_EDGE *AN_EDGE =
                    YR_CPP_MONITOR::create_yr_monitor_edge(source_state_key,
                                                           target_state_key,
                                                           event_string);

    if (0 != AN_EDGE)
    {
        if (0 != guarded_condition)
        {
            AN_EDGE->set_GUARDED_CONDITION(guarded_condition);

            return AN_EDGE;
        }
        else
        {
            YR_CPP_MONITOR::DELETE_yr_monitor_edge(AN_EDGE);
        }
    }

    return 0;
}


YR_CPP_MONITOR_EDGE *YR_CPP_MONITOR::create_yr_monitor_edge(QString source_state_key,
                                                            QString target_state_key,
                                                            QString event_string,
                                                            QString guarded_condition_STRING)
{
    YR_CPP_notinset_inset_TRACE_expression *guarded_condition = 0;





    return YR_CPP_MONITOR::create_yr_monitor_edge(source_state_key,
                                                  target_state_key,
                                                  event_string,
                                                  guarded_condition);
}


bool YR_CPP_MONITOR::DELETE_yr_monitor_edge(YR_CPP_MONITOR_EDGE *an_edge)
{
    QList<YR_CPP_MONITOR_EDGE *> resulting_edges;

    if (0 != an_edge)
    {
        find_yr_monitor_edges(an_edge->get_SOURCE_STATE_KEY(),
                              an_edge->get_TARGET_STATE_KEY(), resulting_edges);

        YR_CPP_MONITOR_EDGE *cur_edge = 0;

        for (uint k = 0; k < resulting_edges.size(); ++k)
        {
            cur_edge = resulting_edges.at(k);

            if (0 != cur_edge)
            {
                _EDGES.removeAll(cur_edge);

                delete cur_edge;
            }
        }

        return true;
    }

    return false;
}


YR_CPP_MONITOR_STATE *YR_CPP_MONITOR::find_yr_monitor_state(QString a_state_key)
{
	QList<YR_CPP_MONITOR_STATE *>::iterator a_state_key_RESULT =
			std::find_if(_STATES.begin(), _STATES.end(), YR_CPP_MONITOR_STATE_functor(a_state_key));

	if (a_state_key_RESULT != _STATES.end())
	{
		return (*a_state_key_RESULT);
	}

	return 0;
}


YR_CPP_MONITOR_STATE *YR_CPP_MONITOR::
	create_yr_monitor_state(QString a_state_key /* = YR_CPP_UTILS::EMPTY_STRING */)
{
	YR_CPP_MONITOR_STATE *a_state_key_RESULT = find_yr_monitor_state(a_state_key);

	if (0 != a_state_key_RESULT)
	{
		if ( !a_state_key.isEmpty() )
		{
			return a_state_key_RESULT;
		}
		else
		{
			static bool first_root_edge_attempt = true;

			if (!first_root_edge_attempt)
			{
				return 0;
			}
			else
			{
				first_root_edge_attempt = false;
			}
		}
	}


    YR_CPP_MONITOR_STATE *A_NEW_STATE = new YR_CPP_MONITOR_STATE(a_state_key);

    _STATES.append(A_NEW_STATE);

    if (1 == _STATES.size())
    {
    	set_current_MONITOR_STATE(A_NEW_STATE);
    }

    return A_NEW_STATE;
}


bool YR_CPP_MONITOR::DELETE_yr_monitor_state(int a_state_ID)
{
	bool remove_current_state = false;

	YR_CPP_MONITOR_STATE *a_cur_state = 0;

	for (uint i = 0; i < _STATES.size(); ++i)
	{
		a_cur_state = _STATES.at(i);

		if (0 != a_cur_state &&
			(a_state_ID == a_cur_state->GET_ID()))
		{
			remove_current_state = true;

			break;
		}
	}

	if (true == remove_current_state)
	{
		_STATES.removeAll(a_cur_state);

		delete a_cur_state;

		if (0 == _STATES.size())
		{
			set_current_MONITOR_STATE(0);
		}

		return true;
	}

    return false;
}


QString YR_CPP_MONITOR::generate_in_DOT_format(const QString &digraph_dot_name,
											   bool 		 PRINT_WITH_SQL_EVENT_LOG_TOKEN)
{
    QString DOT_FILE_CONTENT_FOR_USER_OUTPUT;

    YR_CPP_MONITOR_EDGE *_AN_EDGE = _ROOT_EDGE;


    DOT_FILE_CONTENT_FOR_USER_OUTPUT.append(QString("digraph \"%1\" {\n")
                                             .arg(digraph_dot_name));


    if (0 != _ROOT_EDGE)
    {
        DOT_FILE_CONTENT_FOR_USER_OUTPUT.append(QString("%1\n")
                                                 .arg(_ROOT_EDGE->print_to_dot_file()));
    }

    for (uint i = 0; i < _EDGES.size(); ++i)
    {
        _AN_EDGE = _EDGES.at(i);

        if (0 != _AN_EDGE && _AN_EDGE != _ROOT_EDGE)
        {
            DOT_FILE_CONTENT_FOR_USER_OUTPUT.append(QString("%1\n")
                                                     .arg(_AN_EDGE->print_to_dot_file(PRINT_WITH_SQL_EVENT_LOG_TOKEN)));
        }
    }

    DOT_FILE_CONTENT_FOR_USER_OUTPUT.append("}");

    //QDEBUG_STRING_OUTPUT_2("DOT_FILE_CONTENT_FOR_USER_OUTPUT", DOT_FILE_CONTENT_FOR_USER_OUTPUT);

    return DOT_FILE_CONTENT_FOR_USER_OUTPUT;
}


QString YR_CPP_MONITOR::generate_in_DOT_format(bool PRINT_WITH_SQL_EVENT_LOG_TOKEN /* = false */)
{
    if (!_RUNTIME_MONITOR_NAME.isEmpty())
    {
        return generate_in_DOT_format(_RUNTIME_MONITOR_NAME,
        							  PRINT_WITH_SQL_EVENT_LOG_TOKEN);
    }
    else
    {
        return generate_in_DOT_format("a_runtime_monitor",
        							  PRINT_WITH_SQL_EVENT_LOG_TOKEN);
    }
}


QString YR_CPP_MONITOR::print_TO_dot_FILE(const QString &program_working_directory,
                                          const QString &dot_file_name,
										  bool 			PRINT_WITH_SQL_EVENT_LOG_TOKEN /* = false */,
										  bool          YR_VIEW_RESULTING_PDF_FILE /* = true */,
										  bool          YR_DEBUG_OUTPUT_PARAMETERS /* = true */)
{
    QString dot_file_CONTENT = generate_in_DOT_format(dot_file_name, PRINT_WITH_SQL_EVENT_LOG_TOKEN);


    QString DOT_FILE_NAME = QString("%1.dot")
    							.arg(dot_file_name);

    QFile out_file_DOT_CONTENT(DOT_FILE_NAME);

    out_file_DOT_CONTENT.open(QIODevice::ReadWrite);

    out_file_DOT_CONTENT.write(dot_file_CONTENT.toStdString().c_str());

    out_file_DOT_CONTENT.close();


    QStringList program_executable_args;

    QString DOT_program("/usr/bin/dot");

    program_executable_args << DOT_program
                            << "-Tpdf"
                            << "-o"
							<< QString("%1.pdf")
								.arg(dot_file_name)
							<< DOT_FILE_NAME;

    if (YR_DEBUG_OUTPUT_PARAMETERS)
    {
        QDEBUG_STRING_OUTPUT_2("*-YR_CPP_MONITOR::print_TO_dot_FILE; program_executable_args",
                                program_executable_args);
    }


    int res = YR_CPP_UTILS::start_PROCESS_AND_READ_PROCESS_output_INTO_FILE(DOT_program,
                     	 	 	 	 	 	 	 	 	 	 	 	 	 	program_working_directory,
																			dot_file_name,
																			program_executable_args);

    if (YR_VIEW_RESULTING_PDF_FILE &&
        res >= 0)
    {
        program_executable_args.clear();

        program_executable_args << QString("%1.pdf")
        								.arg(dot_file_name);

        if (YR_DEBUG_OUTPUT_PARAMETERS)
        {
            QDEBUG_STRING_OUTPUT_2("***-YR_CPP_MONITOR::print_TO_dot_FILE; program_executable_args",
                                   program_executable_args);
        }


        QProcess A_YEROTH_PROCESS;

        A_YEROTH_PROCESS.startDetached("evince", program_executable_args);
    }

    return dot_file_CONTENT;
}


void YR_CPP_MONITOR::set_current_MONITOR_STATE(YR_CPP_MONITOR_STATE *a_current_STATE)
{
    if (0 != a_current_STATE)
    {
        _current_STATE = a_current_STATE;

        /*
         * _current_triggered_EDGE is NULL (0) for instance for the start state.
         */
        if (0 != _current_triggered_EDGE)
        {
        	_current_STATE->ADD_RUNTIME_MONITOR_TRACE_EVENT(
        			_current_triggered_EDGE->get_EDGE_EVENT_TOKEN());
        }
    }
}


void YR_CPP_MONITOR::set_current_triggered_EDGE(YR_CPP_MONITOR_EDGE *a_current_triggered_EDGE)
{
    _current_triggered_EDGE = a_current_triggered_EDGE;

    if (0 != a_current_triggered_EDGE)
    {
    	set_current_MONITOR_STATE(_current_triggered_EDGE->get_TARGET_STATE());
    }


}




