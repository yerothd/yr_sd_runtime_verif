/*
 * YR_CPP_MONITOR.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_MONITOR_HPP_
#define _YR_CPP_MONITOR_HPP_


/**
 * TO KEEP EXACTLY AS A RELATIVE PATH
 * SO TO AVOID build errors in
 * 'yr-db-runtime-verif' project.
 */
#include "utils/YR_CPP_UTILS.hpp"

#include "YR_CPP_MONITOR_object.hpp"


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>


class YR_CPP_MONITOR_ERP_database;

class YR_CPP_notinset_inset_TRACE_expression;

class YR_CPP_MONITOR_EDGE;

class YR_CPP_MONITOR_STATE;

class YR_CPP_MONITOR_STATE_PROPERTY_VALUE;


class YR_CPP_MONITOR : public YR_CPP_MONITOR_object
{
	Q_OBJECT

public:

    YR_CPP_CLASS_OPERATORS

    static YR_CPP_MONITOR *CREATE_MONITOR(QString RUNTIME_MONITOR_NAME = YR_CPP_UTILS::EMPTY_STRING);

    static YR_CPP_MONITOR *CREATE_MONITOR(QString db_type,
                                          QString db_name,
                                          QString db_ip_address,
                                          QString db_user_name,
                                          QString db_user_pwd,
                                          QString db_connection_options = YR_CPP_UTILS::EMPTY_STRING,
                                          QString RUNTIME_MONITOR_NAME = YR_CPP_UTILS::EMPTY_STRING);

    virtual ~YR_CPP_MONITOR();

    void set_yr_root_edge(YR_CPP_MONITOR_EDGE *ROOT_EDGE);


    //######################## RUNNING THE RUNTIME MONITOR //########################


    /**
     * function "YR_register_final_state_CALLBACK_FUNCTION"
     * IS CALLED BACK WHENEVER A final state is reached !
     */
    void YR_register_set_final_state_CALLBACK_FUNCTION
			(void (*CALL_BACK_final_state)(YR_CPP_MONITOR 		*a_runtime_monitor,
										   YR_CPP_MONITOR_EDGE 	*an_EDGE_leading_TO_error_FINAL_state));


    /**
     * SETS THE CURRENT STATE TO the start state.
     */
    bool RESET_RUNTIME_MONITOR();


    /**
     * "TRUE" is returned in case an edge event
     * "an_edge_event" was triggered !
     */
    bool YR_trigger_an_edge_event(QString 			an_edge_event,
    							  bool 				debug_MSG = true);


    //######################## CHECKING SET APPARTENANCE (\in, \notin) //########################

    virtual bool SET_DB_CONFIGURATION_PARAMETERS(QString db_type,
                                                 QString db_name,
                                                 QString db_ip_address,
                                                 QString db_user_name,
                                                 QString db_user_pwd,
                                                 QString db_connection_options = YR_CPP_UTILS::EMPTY_STRING);

    virtual bool is_in_SET_ALGEBRA(QString a_SET_VARIABLE,
                                   QString a_SUPPOSED_SET_VARIABLE);

    //########################

    bool CHECK_whether__STATE__is__Accepting(YR_CPP_MONITOR_STATE &A_POTENTIAL_ACCEPTING_STATE);

    //########################

    bool CHECK_PRE_CONDITION_notIN(QMap<QString, QString> &SET_NOTin_PRE_STATEPROPERTYKEY_TO_VALUE_map);

    bool CHECK_PRE_CONDITION_IN(QMap<QString, QString> &SET_in_PRE_STATEPROPERTYKEY_TO_VALUE_map);

    bool CHECK_post_condition_notIN(QMap<QString, QString> &SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE_map);

    bool CHECK_post_condition_IN(QMap<QString, QString> &SET_IN_POST_STATEPROPERTYKEY_TO_VALUE_map);

    //########################


    QString YR_open_HEADER_TEMPLATE_FILE();

    QString YR_open_SOURCE_TEMPLATE_FILE();


    QString YR_generate_cplusplus_headers_files__AND__SAVE__TO__DISK
                (QString A_hpp_FILE_NAME,
                 QString a_class_NAME = "YR_DB_RUNTIME_VERIF_Main");


    QString YR_generate_cplusplus_headers_files(QString A_hpp_FILE_NAME,
                                                QString a_class_NAME);


    QString GENERATE_METHOD_event_call(QString _event_METHOD_name,
                                       QString _STRING_bool_GUARDED_CONDITION = YR_CPP_UTILS::EMPTY_STRING);

    QString YR_GENERATE_START_FINAL_STATE_CODE(QString 				&a_last_edge_VARIABLE_STRING_pointer,
                                               YR_CPP_MONITOR_EDGE 	&_AN_EDGE);

    QString GENERATE_pre_post_conditions_code(QString 				&a_last_edge_VARIABLE_STRING_pointer,
                                              YR_CPP_MONITOR_EDGE 	&_AN_EDGE);


    QString YR_generate_cplusplus_sources_files__AND__SAVE__TO__DISK
                (QString A_cpp_FILE_NAME,
                 QString a_class_NAME = "YR_DB_RUNTIME_VERIF_Main");


    QString YR_generate_cplusplus_sources_files(QString A_cpp_FILE_NAME,
                                                QString a_class_NAME);


    void save_yr_SOURCE_FILES(QString a_header_OR_SOURCE_file_NAME,
                              QString a_header_OR_SOURCE_file_CONTENT);

    //########################

    void find_yr_monitor_edges(YR_CPP_MONITOR_EDGE 				&an_edge,
                               QList<YR_CPP_MONITOR_EDGE *> 	&resulting_edges);

    void find_yr_monitor_edges(QString 						start_state_key,
                               QString 						end_state_key,
                               QList<YR_CPP_MONITOR_EDGE *> &resulting_edges);


    //########################

    YR_CPP_MONITOR_EDGE *create_yr_monitor_edge(QString source_state_key,
                                                QString target_state_key);

    YR_CPP_MONITOR_EDGE *create_yr_monitor_edge(QString source_state_key,
                                                QString target_state_key,
                                                QString event_string);

    YR_CPP_MONITOR_EDGE *
		create_yr_monitor_edge(QString source_state_key,
                               QString target_state_key,
                               QString event_string,
							   YR_CPP_notinset_inset_TRACE_expression *guarded_condition);

    YR_CPP_MONITOR_EDGE *create_yr_monitor_edge(QString source_state_key,
                                                QString target_state_key,
                                                QString event_string,
                                                QString guarded_condition_STRING);

    bool DELETE_yr_monitor_edge(YR_CPP_MONITOR_EDGE *an_edge);


    //########################

    YR_CPP_MONITOR_STATE *find_yr_monitor_state(QString a_state_key);

    YR_CPP_MONITOR_STATE *create_yr_monitor_state(QString a_state_key = YR_CPP_UTILS::EMPTY_STRING);

    bool DELETE_yr_monitor_state(int a_state_ID);


    //########################

    inline QList<YR_CPP_MONITOR_EDGE *> &get_EDGES()
    {
        return _EDGES;
    }

    virtual QString generate_in_DOT_format(const QString &digraph_dot_name,
    							   	   	   bool 		 PRINT_WITH_SQL_EVENT_LOG_TOKEN);

    virtual QString generate_in_DOT_format(bool PRINT_WITH_SQL_EVENT_LOG_TOKEN = false);

    virtual QString print_TO_dot_FILE(const QString &program_working_directory,
                                      const QString &dot_file_name,
    						  	  	  bool 			PRINT_WITH_SQL_EVENT_LOG_TOKEN = false,
    						  	  	  bool          YR_VIEW_RESULTING_PDF_FILE = true,
    						  	  	  bool          YR_DEBUG_OUTPUT_PARAMETERS = true);


    inline virtual QString print_TO_dot_FILE(const QString &dot_file_name,
                                             bool 		   PRINT_WITH_SQL_EVENT_LOG_TOKEN = false,
                                             bool          YR_VIEW_RESULTING_PDF_FILE = true,
                                             bool          YR_DEBUG_OUTPUT_PARAMETERS = true)
    {
        return print_TO_dot_FILE(".",
                                 dot_file_name,
                                 PRINT_WITH_SQL_EVENT_LOG_TOKEN,
                                 YR_VIEW_RESULTING_PDF_FILE,
                                 YR_DEBUG_OUTPUT_PARAMETERS);
    }


    inline virtual QString print_TO_dot_FILE(bool PRINT_WITH_SQL_EVENT_LOG_TOKEN = false,
                                             bool YR_VIEW_RESULTING_PDF_FILE = true)
    {
        return print_TO_dot_FILE(QString("%1")
        							.arg(_RUNTIME_MONITOR_NAME),
                                 PRINT_WITH_SQL_EVENT_LOG_TOKEN,
                                 YR_VIEW_RESULTING_PDF_FILE);
    }


    //########################

    inline void set_RUNTIME_MONITOR_NAME(QString RUNTIME_MONITOR_NAME)
    {
        _RUNTIME_MONITOR_NAME = RUNTIME_MONITOR_NAME.trimmed();
    }

    inline QString get_RUNTIME_MONITOR_NAME()
    {
        return _RUNTIME_MONITOR_NAME.trimmed();
    }


    //########################

    void set_current_MONITOR_STATE(YR_CPP_MONITOR_STATE *a_current_STATE);

    inline YR_CPP_MONITOR_STATE *get_current_MONITOR_STATE()
    {
        return _current_STATE;
    }


    //########################

    inline bool IS_in_TRACE_LOG(QString an_EVENT_TOKEN)
    {
    	return _TRACE_LOG.contains(an_EVENT_TOKEN);
    }

    inline void TRACE_LOG_current_RECEIVED_EVENT_TOKEN(QString a_current_received_EVENT_TOKEN)
    {
    	_TRACE_LOG.append(a_current_received_EVENT_TOKEN);
    }


    //########################

    inline virtual YR_CPP_MONITOR_EDGE *GET_root_edge()
    {
    	return _ROOT_EDGE;
    }

    void set_current_triggered_EDGE(YR_CPP_MONITOR_EDGE *a_current_triggered_EDGE);

    inline YR_CPP_MONITOR_EDGE *get_current_triggered_EDGE()
    {
        return _current_triggered_EDGE;
    }

    inline uint YR_CPP_monitor_edge_count()
    {
    	return (uint) _EDGES.size();
    }

    inline uint YR_CPP_monitor_state_count()
    {
    	return (uint) _STATES.size();
    }

protected:


    inline YR_CPP_MONITOR()
    :_ROOT_EDGE(0),
	 _CALL_BACK_final_state(0),
     _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS(0),
     _RUNTIME_MONITOR_NAME(YR_CPP_UTILS::EMPTY_STRING),
     _current_STATE(0),
	 _current_triggered_EDGE(0)
    {
    }

    inline YR_CPP_MONITOR(QString RUNTIME_MONITOR_NAME)
    :_ROOT_EDGE(0),
	 _CALL_BACK_final_state(0),
	 _yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS(0),
	 _RUNTIME_MONITOR_NAME(RUNTIME_MONITOR_NAME),
	 _current_STATE(0),
	 _current_triggered_EDGE(0)
    {
    }

    QList<QString> _TRACE_LOG;

    YR_CPP_MONITOR_EDGE *_ROOT_EDGE;

private:

    void (*_CALL_BACK_final_state)(YR_CPP_MONITOR 		*a_runtime_monitor,
    							   YR_CPP_MONITOR_EDGE 	*an_EDGE_leading_TO_error_FINAL_state);


    static const char INCOMING_TRACE_EVENT_SEPARATOR_CHARACTER;


    YR_CPP_MONITOR_ERP_database *_yr_SET_ALGEBRA_inclusion_DATABASE_to_query_for_STATUS;

    QString _RUNTIME_MONITOR_NAME;

    YR_CPP_MONITOR_STATE *_current_STATE;

    YR_CPP_MONITOR_EDGE *_current_triggered_EDGE;

    QList<YR_CPP_MONITOR_EDGE *> _EDGES;

    QList<YR_CPP_MONITOR_STATE *> _STATES;
};



#endif // _YR_CPP_MONITOR_HPP_
