/*
 * YR_CPP_MONITOR.hpp
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */


#include "YR_CPP_MONITOR.hpp"

#include "YR_CPP_MONITOR_EDGE.hpp"

#include "YR_CPP_MONITOR_STATE.hpp"


#include "utils/YR_CPP_MONITOR_ERP-database.hpp"

#include "utils/YR_CPP_UTILS.hpp"

#include "yr-expressions-conditions/YR_CPP_BOOLEAN_expression.HPP"


#include <QtCore/QDebug>
#include <QtCore/QProcess>
#include <QtCore/QFile>
#include <QtCore/QTextStream>


YR_CPP_MONITOR *
YR_CPP_MONITOR::

CREATE_MONITOR(QString RUNTIME_MONITOR_NAME  /*= YR_CPP_UTILS::EMPTY_STRING*/
              )
{
    YR_CPP_MONITOR *A_RUNTIME_MONITOR = new YR_CPP_MONITOR;

    if (0 != A_RUNTIME_MONITOR)
    {
        if (!YR_CPP_UTILS::isEqualCaseInsensitive(RUNTIME_MONITOR_NAME,
                                                  YR_CPP_UTILS::EMPTY_STRING))
        {
            A_RUNTIME_MONITOR->set_RUNTIME_MONITOR_NAME(RUNTIME_MONITOR_NAME);
        }
        else
        {
            A_RUNTIME_MONITOR->
            set_RUNTIME_MONITOR_NAME(QString
                                     ("A_YR_RUNTIME_MONITOR_GENERIC_NAME"));
        }
    }

    return A_RUNTIME_MONITOR;
}


YR_CPP_MONITOR *YR_CPP_MONITOR::CREATE_MONITOR(QString db_type,
                                               QString db_name,
                                               QString db_ip_address,
                                               QString db_user_name,
                                               QString db_user_pwd,
                                               QString db_connection_options
                                               /* = YR_CPP_UTILS::EMPTY_STRING */,
                                               QString RUNTIME_MONITOR_NAME
                                               /* = YR_CPP_UTILS::EMPTY_STRING */)
{
    YR_CPP_MONITOR *a_new_monitor_FOR_RUNTIME_VERIFICATION =
                    YR_CPP_MONITOR::CREATE_MONITOR(RUNTIME_MONITOR_NAME);

    if (0 != a_new_monitor_FOR_RUNTIME_VERIFICATION)
    {
        a_new_monitor_FOR_RUNTIME_VERIFICATION->SET_DB_CONFIGURATION_PARAMETERS
        (db_type, db_name, db_ip_address, db_user_name, db_user_pwd,
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
    if (0 != ROOT_EDGE)
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


void
YR_CPP_MONITOR::YR_register_set_final_state_CALLBACK_FUNCTION
(void (*CALL_BACK_final_state)(YR_CPP_MONITOR_STATE *))
{
    if (0 != CALL_BACK_final_state)
    {
        _CALL_BACK_final_state = CALL_BACK_final_state;
    }
}


bool YR_CPP_MONITOR::YR_trigger_an_edge_event(QString an_edge_event,
                                              bool debug_MSG /* = false */)
{
    bool cur_GUARDED_CONDITION_TRIGGERED = true;

    bool tmp_yr_cur_edge_GUARDED_CONDITION_trigerred = false;

    YR_CPP_MONITOR_EDGE *cur_edge = 0;

    for (uint k = 0; k < _EDGES.size(); ++k)
    {
        cur_edge = _EDGES.at(k);

        if (0 != cur_edge)
        {
            YR_CPP_MONITOR_STATE *cur_edge_START_STATE =
                            cur_edge->get_START_STATE();

            if (0 != cur_edge_START_STATE)
            {
                tmp_yr_cur_edge_GUARDED_CONDITION_trigerred =
                                cur_edge->evaluate_GUARDED_CONDITION_expression();

                if (cur_GUARDED_CONDITION_TRIGGERED ==
                        tmp_yr_cur_edge_GUARDED_CONDITION_trigerred
                        && YR_CPP_UTILS::isEqualCaseInsensitive(an_edge_event,
                                                                cur_edge->
                                                                get_EDGE_EVENT_TOKEN
                                                                ()))
                {

                    if (debug_MSG)
                    {
                        cur_edge->print_FOR_YEROTH_ERP();

                        qDebug() <<
                                 " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] edge event evaluated triggered guarded condition: "
                                 << cur_GUARDED_CONDITION_TRIGGERED << " **";

                        qDebug() <<
                                 " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] edge event start state: "
                                 << cur_edge_START_STATE->
                                 get_MONITOR_STATE_NAME() << " **";
                    }

                    //check converse condition of pre-condition doesn't apply
                    bool precondition_IS_TRUE =
                                    cur_edge->
                                    CHECK_START_STATE_in_OR_notin_CONDITION
                                    (*cur_edge_START_STATE, *this);

                    if (debug_MSG)
                    {
                        qDebug() <<
                                 " *[YR_CPP_MONITOR::YR_trigger_an_edge_event:] START STATE precondition_IS_TRUE: "
                                 << BOOL_TO_STRING(precondition_IS_TRUE) << " **";
                    }

                    if (precondition_IS_TRUE)
                    {
                        set_current_triggered_EDGE(cur_edge);

                        QList < YR_CPP_MONITOR_STATE * >results_states;

                        cur_edge->GET_error_final_STATES(*this,
                                                         results_states);

                        for (uint k = 0; k < results_states.size(); ++k)
                        {
                            if (0 != _CALL_BACK_final_state)
                            {
                                (*_CALL_BACK_final_state)(results_states.
                                                          at(k));
                            }

                        }

                        return true;
                    }
                }
            }
        }
    }

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
        QDEBUG_STRING_OUTPUT_1
        ("!! YR_CPP_MONITOR::SET_DB_CONFIGURATION_PARAMETERS: "
         "QSqlDatabase object instance NOT INSTANTIATED !!!");

        return false;
    }

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->
    set_db_type(db_type);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->
    set_db_name(db_name);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->
    set_db_ip_address(db_ip_address);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->
    set_db_user_name(db_user_name);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->
    set_db_user_pwd(db_user_pwd);

    _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS->
    set_db_connection_options(db_connection_options);


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

    QStringList SQL_table_column_LIST =
                    a_SET_VARIABLE.split(".", Qt::SkipEmptyParts);


    QString strQuery =
                    QString("select * from %1 WHERE %2 = '%3';").arg(SQL_table_column_LIST.
                                                                     at(0),
                                                                     SQL_table_column_LIST.
                                                                     at(1),
                                                                     a_SUPPOSED_SET_VARIABLE);

    //qDebug() << "strQuery: " << strQuery;

    int rowCount = YR_CPP_UTILS::execQueryRowCount(strQuery, true);

    //qDebug() << "rowCount > 0: " << BOOL_TO_STRING(rowCount > 0);

    return (rowCount > 0);
}


bool YR_CPP_MONITOR::CHECK_PRE_CONDITION_notIN(QMap < QString,
                                               QString >
                                               &SET_NOTin_STATEPROPERTYKEY_TO_VALUE_map)
{
    QList < QString > set_notIN_KEYS =
                    SET_NOTin_STATEPROPERTYKEY_TO_VALUE_map.keys();

    //qDebug() << "SET_NOTin_STATEPROPERTYKEY_TO_VALUE_map: "
    //               << SET_NOTin_STATEPROPERTYKEY_TO_VALUE_map;

    QString A_SET_notIN_PROPERTY_KEY;

    QString A_SET_notIN_PROPERTY_value;

    for (uint i = 0; i < set_notIN_KEYS.size(); ++i)
    {
        A_SET_notIN_PROPERTY_KEY = set_notIN_KEYS.at(i);

        A_SET_notIN_PROPERTY_value =
                        SET_NOTin_STATEPROPERTYKEY_TO_VALUE_map.
                        value(A_SET_notIN_PROPERTY_KEY);

        if (!is_in_SET_ALGEBRA(A_SET_notIN_PROPERTY_value,
                               A_SET_notIN_PROPERTY_KEY))
        {
//                      qDebug() << QString("%1 NOT in set %2")
//                                                      .arg(A_SET_notIN_PROPERTY_KEY,
//                                                               A_SET_notIN_PROPERTY_value);
            return true;
        }
    }

    return false;
}


bool YR_CPP_MONITOR::CHECK_PRE_CONDITION_IN(QMap < QString,
                                            QString >
                                            &SET_in_STATEPROPERTYKEY_TO_VALUE_map)
{
    QList < QString > set_in_KEYS =
                    SET_in_STATEPROPERTYKEY_TO_VALUE_map.keys();

    //qDebug() << "SET_in_STATEPROPERTYKEY_TO_VALUE_map: "
    //               << SET_in_STATEPROPERTYKEY_TO_VALUE_map;

    QString A_SET_IN_PROPERTY_KEY;

    QString A_SET_IN_PROPERTY_value;

    for (uint i = 0; i < set_in_KEYS.size(); ++i)
    {
        A_SET_IN_PROPERTY_KEY = set_in_KEYS.at(i);

        A_SET_IN_PROPERTY_value =
                        SET_in_STATEPROPERTYKEY_TO_VALUE_map.value(A_SET_IN_PROPERTY_KEY);

        if (is_in_SET_ALGEBRA(A_SET_IN_PROPERTY_value, A_SET_IN_PROPERTY_KEY))
        {
//                      qDebug() << QString("%1 in set %2")
//                                                      .arg(A_SET_IN_PROPERTY_KEY,
//                                                               A_SET_IN_PROPERTY_value);
            return true;
        }
    }

//      qDebug() << QString("%1 NOT in set %2")
//                                      .arg(A_SET_IN_PROPERTY_KEY,
//                                               A_SET_IN_PROPERTY_value);

    return false;
}


bool YR_CPP_MONITOR::CHECK_db_post_condition_notIN(QMap < QString,
                                                   QString >
                                                   &SET_DBnotIN_STATEPROPERTYKEY_TO_VALUE_map)
{
    QList < QString > set_DBnotIN_KEYS =
                    SET_DBnotIN_STATEPROPERTYKEY_TO_VALUE_map.keys();

    //qDebug() << "SET_DBnotIN_STATEPROPERTYKEY_TO_VALUE_map: "
    //               << SET_DBnotIN_STATEPROPERTYKEY_TO_VALUE_map;

    QString A_SET_DBnotIN_PROPERTY_KEY;

    QString A_SET_DBnotIN_PROPERTY_value;

    for (uint i = 0; i < set_DBnotIN_KEYS.size(); ++i)
    {
        A_SET_DBnotIN_PROPERTY_KEY = set_DBnotIN_KEYS.at(i);

        A_SET_DBnotIN_PROPERTY_value =
                        SET_DBnotIN_STATEPROPERTYKEY_TO_VALUE_map.
                        value(A_SET_DBnotIN_PROPERTY_KEY);

        if (!is_in_SET_ALGEBRA(A_SET_DBnotIN_PROPERTY_value,
                               A_SET_DBnotIN_PROPERTY_KEY))
        {
			//if (debug_MSG)
			//{
				qDebug() << " *[YR_CPP_MONITOR::CHECK_db_post_condition_notIN:] postcondition_IS_TRUE: True   **";
			//}
//                      qDebug() << QString("%1 db NOT in set %2")
//                                                                              .arg(A_SET_DBnotIN_PROPERTY_KEY,
//                                                                                       A_SET_DBnotIN_PROPERTY_value);
            return true;
        }
    }

    //if (debug_MSG)
    //{
    	qDebug() << " *[YR_CPP_MONITOR::CHECK_db_post_condition_notIN:] postcondition_IS_TRUE: FALSE   **";
    //}

    return false;
}


bool
YR_CPP_MONITOR::CHECK_db_post_condition_IN
(QMap < QString, QString > &SET_dbIN_STATEPROPERTYKEY_TO_VALUE_map)
{
    QList < QString > set_dbIN_KEYS =
                    SET_dbIN_STATEPROPERTYKEY_TO_VALUE_map.keys();

    //qDebug() << "SET_dbIN_STATEPROPERTYKEY_TO_VALUE_map: "
    //               << SET_dbIN_STATEPROPERTYKEY_TO_VALUE_map;

    QString
    A_SET_dbIN_PROPERTY_KEY;

    QString
    A_SET_dbIN_PROPERTY_value;

    for (uint i = 0; i < set_dbIN_KEYS.size(); ++i)
    {
        A_SET_dbIN_PROPERTY_KEY = set_dbIN_KEYS.at(i);

        A_SET_dbIN_PROPERTY_value =
                        SET_dbIN_STATEPROPERTYKEY_TO_VALUE_map.
                        value(A_SET_dbIN_PROPERTY_KEY);

        if (is_in_SET_ALGEBRA(A_SET_dbIN_PROPERTY_value,
                              A_SET_dbIN_PROPERTY_KEY))
        {
			//if (debug_MSG)
			//{
				qDebug() << " *[YR_CPP_MONITOR::CHECK_db_post_condition_IN:] postcondition_IS_TRUE: True   **";
			//}
//                      qDebug() << QString("%1 db in set %2")
//                                                      .arg(A_SET_dbIN_PROPERTY_KEY,
//                                                               A_SET_dbIN_PROPERTY_value);
            return true;
        }
    }

    //if (debug_MSG)
    //{
    	qDebug() << " *[YR_CPP_MONITOR::CHECK_db_post_condition_IN:] postcondition_IS_TRUE: FALSE   **";
    //}
//      qDebug() << QString("%1 db NOT in set %2")
//                                      .arg(A_SET_dbIN_PROPERTY_KEY,
//                                               A_SET_dbIN_PROPERTY_value);

    return false;
}


QString YR_CPP_MONITOR::YR_open_HEADER_TEMPLATE_FILE()
{
    QFile
    a_template_HEADER_FILE_runtime_monitor
    (FILE_YR_hpp_TEMPLATE_RUNTIME_MONITOR);

    //      qDebug() << "++ 1. YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR: "
    //                               << YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;

    YR_CPP_UTILS::
    YEROTH_READ_FILE_CONTENT(a_template_HEADER_FILE_runtime_monitor,
                             YR_CPP_UTILS::
                             YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR);

    //      qDebug() << "++ 2. YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR: "
    //                               << YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;

    if (!a_template_HEADER_FILE_runtime_monitor.open(QFile::ReadOnly))
    {
        QString errMsg("YR_CPP_MONITOR::YR_open_HEADER_TEMPLATE_FILE: ");

        errMsg.append(" ne peut pas ouvrir pour lecture le fichier ").
        append(FILE_YR_hpp_TEMPLATE_RUNTIME_MONITOR).append(" . ) !\n\n");

        qDebug() << errMsg;

        return YR_CPP_UTILS::EMPTY_STRING;
    }

    //      qDebug() << "++ 3. YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR: "
    //                       << YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;

    return YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;
}


QString YR_CPP_MONITOR::YR_open_SOURCE_TEMPLATE_FILE()
{
    QFile
    a_template_SOURCE_FILE_runtime_monitor
    (FILE_YR_cpp_TEMPLATE_RUNTIME_MONITOR);

    //      qDebug() << "++ 1. YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR: "
    //                               << YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;

    YR_CPP_UTILS::
    YEROTH_READ_FILE_CONTENT(a_template_SOURCE_FILE_runtime_monitor,
                             YR_CPP_UTILS::
                             YR_SOURCE_cpp_TEMPLATE_RUNTIME_MONITOR);

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


QString YR_CPP_MONITOR::YR_generate_cplusplus_headers_files()
{
    QString a_yr_rtm_MONITOR_name("a_runtime_monitor");


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

            if (!_AN_EDGE->get_EDGE_EVENT_TOKEN().contains("(") ||
                    !_AN_EDGE->get_EDGE_EVENT_TOKEN().contains(")"))
            {
                EDGE_EVENT_token_with_parenthesis =
                                QString("YR_SQL_%1()").arg(_AN_EDGE->
                                                           get_EDGE_EVENT_TOKEN());

                EDGE_EVENT_token_with_parenthesis =
                                EDGE_EVENT_token_with_parenthesis.replace(".", "_");
            }

            EDGES_EVENTS_TOKENS_declarations.append(QString("void %1; ").
                                                    arg
                                                    (EDGE_EVENT_token_with_parenthesis));

            EXPORTED_EDGE_SOURCE_CODE.append(_AN_EDGE->
                                             YR_EXPORT_edge_CLASS_INSTANCE
                                             (a_yr_rtm_MONITOR_name));
        }
    }


    YR_open_HEADER_TEMPLATE_FILE();


    QString YR_TO_EXPORT_SOURCE_CODE_HEADER_FILE =
                    YR_CPP_UTILS::YR_HEARDER_hpp_TEMPLATE_RUNTIME_MONITOR;


    YR_TO_EXPORT_SOURCE_CODE_HEADER_FILE.
    replace("_slots_event_declarations_YR_RTM_REPLACEMENT_QSTRING_",
            EDGES_EVENTS_TOKENS_declarations);

    YR_TO_EXPORT_SOURCE_CODE_HEADER_FILE.replace("_YR_RTM_REPLACEMENT_QSTRING",
                                                 get_RUNTIME_MONITOR_NAME());


    return YR_TO_EXPORT_SOURCE_CODE_HEADER_FILE;
}


QString YR_CPP_MONITOR::GENERATE_METHOD_event_call(QString a_yr_rtm_MONITOR_name,
                                                   QString event_METHOD_name,
                                                   QString
                                                   STRING_bool_GUARDED_CONDITION
                                                   /* = YR_CPP_UTILS::EMPTY_STRING */
                                                  )
{
    QString GENERATE_METHOD_EVENT_CALL;

    QString an_IF_CONDITION_CHECKING_for_NULL_POINTER;

    QString an_EVENT_METHOD_call;

    if (STRING_bool_GUARDED_CONDITION.isEmpty())
    {
        an_EVENT_METHOD_call.
        append(QString("%1->YR_trigger_an_edge_event(\"%2\");").
               arg(a_yr_rtm_MONITOR_name, event_METHOD_name));


        an_IF_CONDITION_CHECKING_for_NULL_POINTER.
        append(QString("if (0 != %1)\n" "{\n" "%2\n" "}\n").
               arg(a_yr_rtm_MONITOR_name, an_EVENT_METHOD_call));

        GENERATE_METHOD_EVENT_CALL.
        append(an_IF_CONDITION_CHECKING_for_NULL_POINTER);
    }

    return GENERATE_METHOD_EVENT_CALL.trimmed();
}


QString
YR_CPP_MONITOR::

YR_GENERATE_START_FINAL_STATE_CODE(QString &
                                   a_last_edge_VARIABLE_STRING_pointer,
                                   YR_CPP_MONITOR_EDGE &_AN_EDGE)
{
    QString return_code;

    YR_CPP_MONITOR_STATE *A_STATE = _AN_EDGE.get_START_STATE();

    if (0 != A_STATE && A_STATE->is_FINAL_STATE())
    {
        return_code =
                        QString("%1->get_START_STATE()->set_FINAL_STATE(true);\n").
                        arg(a_last_edge_VARIABLE_STRING_pointer);
    }


    A_STATE = _AN_EDGE.get_END_STATE();

    if (0 != A_STATE && A_STATE->is_FINAL_STATE())
    {
        return_code =
                        return_code.
                        append(QString("%1->get_END_STATE()->set_FINAL_STATE(true);\n").
                               arg(a_last_edge_VARIABLE_STRING_pointer));
    }

    return return_code;
}


QString
YR_CPP_MONITOR::

GENERATE_pre_post_conditions_code(QString &
                                  a_last_edge_VARIABLE_STRING_pointer,
                                  YR_CPP_MONITOR_EDGE &_AN_EDGE)
{
    QString returned_code;

    if (0 != _AN_EDGE.get_START_STATE())
    {
        if (_AN_EDGE.get_START_STATE()->_SET_IN_STATEPROPERTYKEY_TO_VALUE.
                size() > 0)
        {
            returned_code.
            append(QString
                   ("%1->get_START_STATE()->set_PRE_CONDITION_IN(\"%2\", \"%3\");\n").
                   arg(a_last_edge_VARIABLE_STRING_pointer,
                       _AN_EDGE.get_START_STATE()->
                       _SET_IN_STATEPROPERTYKEY_TO_VALUE.keys().at(0),
                       _AN_EDGE.get_START_STATE()->
                       _SET_IN_STATEPROPERTYKEY_TO_VALUE.values().at(0)));
        }
        else if (_AN_EDGE.get_START_STATE()->
                 _SET_notIN_STATEPROPERTYKEY_TO_VALUE.size() > 0)
        {
            returned_code.
            append(QString
                   ("%1->get_START_STATE()->set_PRE_CONDITION_notIN(\"%2\", \"%3\");\n").
                   arg(a_last_edge_VARIABLE_STRING_pointer,
                       _AN_EDGE.get_START_STATE()->
                       _SET_notIN_STATEPROPERTYKEY_TO_VALUE.keys().at(0),
                       _AN_EDGE.get_START_STATE()->
                       _SET_notIN_STATEPROPERTYKEY_TO_VALUE.values().
                       at(0)));
        }
    }

    if (0 != _AN_EDGE.get_END_STATE())
    {
        if (_AN_EDGE.get_END_STATE()->_SET_db_IN_STATEPROPERTYKEY_TO_VALUE.
                size() > 0)
        {
            returned_code.
            append(QString
                   ("%1->get_END_STATE()->set_POST_CONDITION_IN(\"%2\", \"%3\");\n").
                   arg(a_last_edge_VARIABLE_STRING_pointer,
                       _AN_EDGE.get_END_STATE()->
                       _SET_db_IN_STATEPROPERTYKEY_TO_VALUE.keys().at(0),
                       _AN_EDGE.get_END_STATE()->
                       _SET_db_IN_STATEPROPERTYKEY_TO_VALUE.values().
                       at(0)));
        }
        else if (_AN_EDGE.get_END_STATE()->
                 _SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE.size() > 0)
        {
            returned_code.
            append(QString
                   ("%1->get_END_STATE()->set_POST_CONDITION_notIN(\"%2\", \"%3\");\n").
                   arg(a_last_edge_VARIABLE_STRING_pointer,
                       _AN_EDGE.get_END_STATE()->
                       _SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE.keys().
                       at(0),
                       _AN_EDGE.get_END_STATE()->
                       _SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE.values().
                       at(0)));
        }
    }

    return returned_code;
}


QString YR_CPP_MONITOR::YR_generate_cplusplus_sources_files()
{
    QString a_yr_rtm_MONITOR_name("_a_runtime_monitor");


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

            if (!_AN_EDGE->get_EDGE_EVENT_TOKEN().contains("(") ||
                    !_AN_EDGE->get_EDGE_EVENT_TOKEN().contains(")"))
            {
                EDGE_EVENT_token_with_parenthesis =
                                QString("YR_SQL_%1()").arg(_AN_EDGE->
                                                           get_EDGE_EVENT_TOKEN());
            }

            EDGE_EVENT_token_with_parenthesis =
                            EDGE_EVENT_token_with_parenthesis.replace(".", "_");

            EDGES_EVENTS_TOKENS__DEFINITIONS.
            append(QString("void yr_rtm_%1::%2\n" "{ \n" "%3" "\n}\n ").
                   arg(get_RUNTIME_MONITOR_NAME(),
                       EDGE_EVENT_token_with_parenthesis,
                       GENERATE_METHOD_event_call(a_yr_rtm_MONITOR_name,
                                                  _AN_EDGE->
                                                  get_EDGE_EVENT_TOKEN
                                                  ())));

            EXPORTED_EDGE_SOURCE_CODE.append(_AN_EDGE->
                                             YR_EXPORT_edge_CLASS_INSTANCE
                                             (a_yr_rtm_MONITOR_name));
        }
    }


    QString current_event_edge_token;

    QString last_edge_variable_STRING;

    QString START_FINAL__states__preconditions_DEFINITIONS;

    QString EVENT_EDGE_final_states_DEFINITIONS;

    QString EVENT_EDGE_DEFINITIONS;

    for (uint i = 0; i < _EDGES.size(); ++i)
    {
        _AN_EDGE = _EDGES.at(i);

        if (0 != _AN_EDGE && _AN_EDGE != _ROOT_EDGE)
        {
            qDebug() << "_MONITOR_STATE_NAME_string_key: "
                     << _AN_EDGE->get_START_STATE()->get_MONITOR_STATE_NAME();

            last_edge_variable_STRING =
                            QString("a_last_edge_%1").arg(QString::number(i));

            EVENT_EDGE_DEFINITIONS.append(QString("YR_CPP_MONITOR_EDGE *%1 = "
                                                  "_a_runtime_monitor->create_yr_monitor_edge (\"%2\", \"%3\");").
                                          arg(last_edge_variable_STRING,
                                              _EDGES.at(i)->
                                              get_START_STATE()->
                                              get_MONITOR_STATE_NAME(),
                                              _EDGES.at(i)->
                                              get_END_STATE()->
                                              get_MONITOR_STATE_NAME()));

            EVENT_EDGE_DEFINITIONS.append("\n");

            EVENT_EDGE_final_states_DEFINITIONS =
                            YR_GENERATE_START_FINAL_STATE_CODE(last_edge_variable_STRING,
                                                               *_AN_EDGE);

            EVENT_EDGE_DEFINITIONS.append(EVENT_EDGE_final_states_DEFINITIONS);


            START_FINAL__states__preconditions_DEFINITIONS =
                            GENERATE_pre_post_conditions_code(last_edge_variable_STRING,
                                                              *_AN_EDGE);


            EVENT_EDGE_DEFINITIONS.
            append(START_FINAL__states__preconditions_DEFINITIONS);

            //_EDGES.at(i)->print();
        }
    }

    EVENT_EDGE_DEFINITIONS.
    append(QString
           ("_a_runtime_monitor->YR_register_set_final_state_CALLBACK_FUNCTION(&YR_CALL_BACK_final_state);"));

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

            EVENT_EDGE_DEFINITIONS.
            append(QString
                   ("YR_CPP_MONITOR_EVENT *a_last_edge_event_%1 = "
                    "a_last_edge_%2->set_EDGE_EVENT (\"%3\");\n").
                   arg(QString::number(i), QString::number(i),
                       current_event_edge_token));
        }
    }


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


    YR_TO_EXPORT_SOURCE_CODE_source_FILE.replace("_YR_RTM_REPLACEMENT_QSTRING",
                                                 get_RUNTIME_MONITOR_NAME());


    return YR_TO_EXPORT_SOURCE_CODE_source_FILE;
}



void YR_CPP_MONITOR::save_yr_SOURCE_FILES(QString a_header_OR_SOURCE_file_NAME,
                                          QString a_header_OR_SOURCE_file_CONTENT)
{
    QFile out_file_CONTENT(a_header_OR_SOURCE_file_NAME.trimmed());

    a_header_OR_SOURCE_file_CONTENT =
                    a_header_OR_SOURCE_file_CONTENT.trimmed();

    a_header_OR_SOURCE_file_CONTENT.append("\n\n");

    out_file_CONTENT.
    open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

    out_file_CONTENT.write(a_header_OR_SOURCE_file_CONTENT.toStdString().
                           c_str());

    out_file_CONTENT.flush();

    out_file_CONTENT.close();
}


void YR_CPP_MONITOR::find_yr_monitor_edges(YR_CPP_MONITOR_EDGE &an_edge,
                                           QList <
                                           YR_CPP_MONITOR_EDGE *
                                           >&resulting_edges)
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
                                           QList <
                                           YR_CPP_MONITOR_EDGE *
                                           >&resulting_edges)
{
    resulting_edges.clear();

    YR_CPP_MONITOR_EDGE *cur_edge = 0;

    for (uint k = 0; k < _EDGES.size(); ++k)
    {
        cur_edge = _EDGES.at(k);

        if (0 != cur_edge)
        {
            if (YR_CPP_UTILS::
                    isEqualCaseInsensitive(cur_edge->get_START_STATE_KEY(),
                                           start_state_key))
            {
                if (YR_CPP_UTILS::
                        isEqualCaseInsensitive(cur_edge->get_END_STATE_KEY(),
                                               end_state_key))
                {
                    resulting_edges.append(cur_edge);
                }
            }
        }
    }
}


YR_CPP_MONITOR_EDGE *YR_CPP_MONITOR::create_yr_monitor_edge(QString start_state_key,
                                                            QString end_state_key)
{
    YR_CPP_MONITOR_STATE *A_START_STATE =
                    YR_CPP_MONITOR::create_yr_monitor_state(start_state_key);

    if (0 != A_START_STATE)
    {
        YR_CPP_MONITOR_STATE *AN_END_STATE =
                        YR_CPP_MONITOR::create_yr_monitor_state(end_state_key);

        if (0 != AN_END_STATE)
        {
            YR_CPP_MONITOR_EDGE *AN_EDGE =
                            new YR_CPP_MONITOR_EDGE(*A_START_STATE, *AN_END_STATE);

            _EDGES.append(AN_EDGE);

            return AN_EDGE;
        }
        else
        {
            YR_CPP_MONITOR::DELETE_yr_monitor_state(A_START_STATE->
                                                    get_MONITOR_STATE_NAME());
        }
    }

    return 0;
}


YR_CPP_MONITOR_EDGE *YR_CPP_MONITOR::create_yr_monitor_edge(QString start_state_key,
                                                            QString end_state_key,
                                                            QString event_string)
{
    YR_CPP_MONITOR_EDGE *AN_EDGE =
                    YR_CPP_MONITOR::create_yr_monitor_edge(start_state_key,
                                                           end_state_key);

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


YR_CPP_MONITOR_EDGE *YR_CPP_MONITOR::create_yr_monitor_edge(QString start_state_key,
                                                            QString end_state_key,
                                                            QString event_string,
                                                            YR_CPP_BOOLEAN_expression *
                                                            guarded_condition)
{
    YR_CPP_MONITOR_EDGE *AN_EDGE =
                    YR_CPP_MONITOR::create_yr_monitor_edge(start_state_key,
                                                           end_state_key,
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


YR_CPP_MONITOR_EDGE *YR_CPP_MONITOR::create_yr_monitor_edge(QString start_state_key,
                                                            QString end_state_key,
                                                            QString event_string,
                                                            QString guarded_condition_STRING)
{
    YR_CPP_BOOLEAN_expression *guarded_condition = 0;





    return YR_CPP_MONITOR::create_yr_monitor_edge(start_state_key,
                                                  end_state_key,
                                                  event_string,
                                                  guarded_condition);
}


bool YR_CPP_MONITOR::DELETE_yr_monitor_edge(YR_CPP_MONITOR_EDGE *an_edge)
{
    QList < YR_CPP_MONITOR_EDGE * >resulting_edges;

    if (0 != an_edge)
    {
        find_yr_monitor_edges(an_edge->get_START_STATE_KEY(),
                              an_edge->get_END_STATE_KEY(), resulting_edges);

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


YR_CPP_MONITOR_STATE *
YR_CPP_MONITOR::

create_yr_monitor_state(QString start_state_key
                        /* = YR_CPP_UTILS::EMPTY_STRING */)
{
    YR_CPP_MONITOR_STATE *A_NEW_STATE =
                    new YR_CPP_MONITOR_STATE(start_state_key);

    _STATES.append(A_NEW_STATE);

    return A_NEW_STATE;
}


YR_CPP_MONITOR_STATE *YR_CPP_MONITOR::DELETE_yr_monitor_state(QString start_state_key)
{


    return 0;
}


QString YR_CPP_MONITOR::generate_in_DOT_format(const QString &digraph_dot_name)
{
    QString DOT_FILE_CONTENT_FOR_USER_OUTPUT;

    YR_CPP_MONITOR_EDGE *_AN_EDGE = _ROOT_EDGE;


    DOT_FILE_CONTENT_FOR_USER_OUTPUT.append(QString("digraph \"%1\" {\n").
                                            arg(digraph_dot_name));


    if (0 != _ROOT_EDGE)
    {
        DOT_FILE_CONTENT_FOR_USER_OUTPUT.append(QString("%1\n").
                                                arg(_ROOT_EDGE->
                                                    print_to_dot_file()));
    }

    for (uint i = 0; i < _EDGES.size(); ++i)
    {
        _AN_EDGE = _EDGES.at(i);

        if (0 != _AN_EDGE && _AN_EDGE != _ROOT_EDGE)
        {
            DOT_FILE_CONTENT_FOR_USER_OUTPUT.append(QString("%1\n").
                                                    arg(_AN_EDGE->
                                                        print_to_dot_file
                                                        ()));
        }
    }

    DOT_FILE_CONTENT_FOR_USER_OUTPUT.append("}");

    //QDEBUG_STRING_OUTPUT_2("DOT_FILE_CONTENT_FOR_USER_OUTPUT", DOT_FILE_CONTENT_FOR_USER_OUTPUT);

    return DOT_FILE_CONTENT_FOR_USER_OUTPUT;
}


QString YR_CPP_MONITOR::generate_in_DOT_format()
{
    if (!_RUNTIME_MONITOR_NAME.isEmpty())
    {
        return generate_in_DOT_format(_RUNTIME_MONITOR_NAME);
    }
    else
    {
        return generate_in_DOT_format("a_runtime_monitor");
    }
}


QString YR_CPP_MONITOR::print_TO_dot_FILE(const QString &dot_file_name)
{
    QString dot_file_CONTENT = generate_in_DOT_format(dot_file_name);


    QString DOT_FILE_NAME = QString("%1.dot").arg(dot_file_name);

    QFile out_file_DOT_CONTENT(DOT_FILE_NAME);

    out_file_DOT_CONTENT.open(QIODevice::ReadWrite);

    out_file_DOT_CONTENT.write(dot_file_CONTENT.toStdString().c_str());

    out_file_DOT_CONTENT.close();


    QStringList program_executable_args;

    QString DOT_program("/usr/bin/dot");

    program_executable_args << DOT_program
                            << "-Tpdf"
                            << "-o" << QString("%1.pdf").arg(dot_file_name) << DOT_FILE_NAME;

    //QDEBUG_STRING_OUTPUT_2("program_executable_args", program_executable_args);


    int res =
                    YR_CPP_UTILS::start_PROCESS_AND_READ_PROCESS_output_INTO_FILE
                    (DOT_program,
                     ".",
                     dot_file_name,
                     program_executable_args);

    if (res >= 0)
    {
        program_executable_args.clear();

        program_executable_args << QString("%1.pdf").arg(dot_file_name);

        QDEBUG_STRING_OUTPUT_2("EVINCE. program_executable_args",
                               program_executable_args);

        QProcess A_YEROTH_PROCESS;

        A_YEROTH_PROCESS.startDetached("evince", program_executable_args);
    }

    return dot_file_CONTENT;
}


void YR_CPP_MONITOR::set_current_MONITOR_STATE(YR_CPP_MONITOR_STATE *
                                               a_current_STATE)
{
    if (0 != _current_STATE)
    {
        _current_STATE = a_current_STATE;

        _current_STATE->ADD_RUNTIME_MONITOR_TRACE_EVENT(_current_STATE->
                                                        get_MONITOR_STATE_NAME
                                                        ());
    }
}


void YR_CPP_MONITOR::set_current_triggered_EDGE(YR_CPP_MONITOR_EDGE *
                                                a_current_triggered_EDGE)
{
    _current_triggered_EDGE = a_current_triggered_EDGE;

    set_current_MONITOR_STATE(_current_triggered_EDGE->get_END_STATE());
}