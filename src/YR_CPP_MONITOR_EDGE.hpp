/*
 * YR_CPP_MONITOR_EDGE.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_MONITOR_EDGE_HPP_
#define _YR_CPP_MONITOR_EDGE_HPP_


/**
 * TO KEEP EXACTLY AS A RELATIVE PATH
 * SO TO AVOID build errors in
 * 'yr-db-runtime-verif' project.
 */
#include "utils/YR_CPP_UTILS.hpp"

#include "YR_CPP_MONITOR_object.hpp"

#include "YR_CPP_MONITOR.hpp"

#include "YR_CPP_MONITOR_EDGE.hpp"

#include "YR_CPP_MONITOR_EVENT.hpp"


#include <QtCore/QString>


class YR_CPP_notinset_inset_TRACE_expression;

class YR_CPP_MONITOR_EVENT;

class YR_CPP_MONITOR_STATE;


class YR_CPP_MONITOR_EDGE : public YR_CPP_MONITOR_object
{
	Q_OBJECT

public:

    YR_CPP_CLASS_OPERATORS

	YR_CPP_MONITOR_EDGE(QString SOURCE_STATE_KEY,
    					QString TARGET_STATE_KEY);

    YR_CPP_MONITOR_EDGE(YR_CPP_MONITOR_STATE &SOURCE_STATE,
                        YR_CPP_MONITOR_STATE &TARGET_STATE);

protected:

    inline YR_CPP_MONITOR_EDGE()
    :_SOURCE_STATE(0),
     _TARGET_STATE(0),
	 _guarded_CONDITION_expression(0),
	 _EDGE_EVENT(0)
    {
    }

public:

    virtual ~ YR_CPP_MONITOR_EDGE();

    QString YR_EXPORT_edge_CLASS_INSTANCE();

    bool operator== (YR_CPP_MONITOR_EDGE &e1);

    virtual bool evaluate_GUARDED_CONDITION_expression();

    inline virtual void set_GUARDED_CONDITION(YR_CPP_notinset_inset_TRACE_expression *GUARDED_CONDITION)
    {
        _guarded_CONDITION_expression = GUARDED_CONDITION;
    }

    inline virtual YR_CPP_notinset_inset_TRACE_expression *get_guarded_CONDITION_expression()
    {
        return _guarded_CONDITION_expression;
    }

    inline virtual QString get_guarded_CONDITION_expression__TO_STRING(bool PRINT_WITH_STANDARD_trace_syntax = false)
    {
        return (0 == _guarded_CONDITION_expression) ? "" :
        		_guarded_CONDITION_expression->toString(PRINT_WITH_STANDARD_trace_syntax);
    }

    inline virtual YR_CPP_MONITOR_EVENT *get_EDGE_EVENT()
    {
        return _EDGE_EVENT;
    }

    inline virtual QString get_EDGE_EVENT_TOKEN()
    {
        return (0 != _EDGE_EVENT) ?
               _EDGE_EVENT->get_EVENT_TOKEN() : YR_CPP_UTILS::EMPTY_STRING;
    }

    inline virtual QString toString()
    {
    	return QString("[%1] / %2")
    			.arg(get_guarded_CONDITION_expression__TO_STRING(),
    				 get_EDGE_EVENT_TOKEN());
    }

    virtual YR_CPP_MONITOR_EVENT *set_EDGE_EVENT(QString event_token);

    inline virtual QString get_SOURCE_STATE_KEY()
    {
        return _SOURCE_STATE_KEY;
    }

    inline virtual QString get_TARGET_STATE_KEY()
    {
        return _TARGET_STATE_KEY;
    }

    inline virtual YR_CPP_MONITOR_STATE *get_SOURCE_STATE()
    {
        return _SOURCE_STATE;
    }

    inline virtual YR_CPP_MONITOR_STATE *get_TARGET_STATE()
    {
        return _TARGET_STATE;
    }


    virtual QString Get__precondition__STRING_VALUE_EXPRESSION(bool PRINT_WITH_STANDARD_trace_syntax = false);

    virtual QString Get__POSTcondition__STRING_VALUE_EXPRESSION(bool PRINT_WITH_STANDARD_trace_syntax = false);


    virtual
    void set_PRE_CONDITION_notIN(QString DB_VARIABLE,
                                 QString db_query_TABLE__db_query_COLUMN);


    virtual
    void set_PRE_CONDITION_IN(QString DB_VARIABLE,
                              QString db_query_TABLE__db_query_COLUMN);


    virtual
    void set_POST_CONDITION_notIN(QString DB_VARIABLE,
                                  QString db_query_TABLE__db_query_COLUMN);


    virtual
    void set_POST_CONDITION_IN(QString DB_VARIABLE,
                               QString db_query_TABLE__db_query_COLUMN);


    virtual
    bool CHECK_SOURCE_STATE_in_OR_notin_CONDITION(YR_CPP_MONITOR_STATE &a_potential_START_state,
                                                  YR_CPP_MONITOR &a_runtime_monitor);

    virtual
    bool ADDITIONAL_FINAL_STATE_lookup(YR_CPP_MONITOR_STATE &a_potential_final_state,
                                       YR_CPP_MONITOR &a_runtime_monitor);

    virtual
    void GET_error_final_STATES__OVER_EDGES(YR_CPP_MONITOR &a_runtime_monitor,
                                			QList<YR_CPP_MONITOR_STATE *> &results_states);

    virtual void print_FOR_YEROTH_ERP();

    virtual void print();

    virtual QString print_to_dot_file(bool PRINT_WITH_SQL_EVENT_LOG_TOKEN = false);


    QStringList _EVENT_PARAMETERS_LIST;

protected:

    QList < YR_CPP_MONITOR_STATE * >FINAL_ERROR_states;

    YR_CPP_MONITOR_STATE *_SOURCE_STATE;

    YR_CPP_MONITOR_STATE *_TARGET_STATE;

    QString _SOURCE_STATE_KEY;

    QString _TARGET_STATE_KEY;


private:

    YR_CPP_notinset_inset_TRACE_expression *_guarded_CONDITION_expression;

    YR_CPP_MONITOR_EVENT *_EDGE_EVENT;
};


#endif //_YR_CPP_MONITOR_EDGE_HPP_
