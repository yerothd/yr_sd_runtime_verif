/*
 * YR_CPP_MONITOR_EDGE.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_MONITOR_EDGE_HPP_
#define _YR_CPP_MONITOR_EDGE_HPP_


#include "utils/YR_CPP_UTILS.hpp"

#include "YR_CPP_MONITOR_object.hpp"

#include "YR_CPP_MONITOR.hpp"

#include "YR_CPP_MONITOR_EVENT.hpp"


#include <QtCore/QString>


class YR_CPP_MONITOR_EVENT;

class YR_CPP_MONITOR_STATE;


class YR_CPP_MONITOR_EDGE:public YR_CPP_MONITOR_object
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

    QString YR_EXPORT_edge_CLASS_INSTANCE(QString &a_yr_rtm_MONITOR_name);

    bool operator== (YR_CPP_MONITOR_EDGE &e1);

    bool evaluate_GUARDED_CONDITION_expression();

    inline void set_GUARDED_CONDITION(YR_CPP_BOOLEAN_expression *
                                      GUARDED_CONDITION)
    {
        _guarded_CONDITION_expression = GUARDED_CONDITION;
    }

    inline YR_CPP_BOOLEAN_expression *get_guarded_CONDITION_expression()
    {
        return _guarded_CONDITION_expression;
    }

    inline YR_CPP_MONITOR_EVENT *get_EDGE_EVENT()
    {
        return _EDGE_EVENT;
    }

    inline QString get_EDGE_EVENT_TOKEN()
    {
        return (0 != _EDGE_EVENT) ?
               _EDGE_EVENT->get_EVENT_TOKEN() : YR_CPP_UTILS::EMPTY_STRING;
    }

    YR_CPP_MONITOR_EVENT *set_EDGE_EVENT(QString event_token);

    inline virtual QString get_SOURCE_STATE_KEY()
    {
        return _SOURCE_STATE_KEY;
    }

    inline virtual QString get_TARGET_STATE_KEY()
    {
        return _TARGET_STATE_KEY;
    }

    inline virtual YR_CPP_MONITOR_STATE *get_START_STATE()
    {
        return _SOURCE_STATE;
    }

    inline virtual YR_CPP_MONITOR_STATE *get_END_STATE()
    {
        return _TARGET_STATE;
    }

    void set_PRE_CONDITION_notIN(QString DB_VARIABLE,
                                 QString db_query_TABLE__db_query_COLUMN);


    void set_PRE_CONDITION_IN(QString DB_VARIABLE,
                              QString db_query_TABLE__db_query_COLUMN);


    void set_POST_CONDITION_notIN(QString DB_VARIABLE,
                                  QString db_query_TABLE__db_query_COLUMN);


    void set_POST_CONDITION_IN(QString DB_VARIABLE,
                               QString db_query_TABLE__db_query_COLUMN);

    bool CHECK_SOURCE_STATE_in_OR_notin_CONDITION(YR_CPP_MONITOR_STATE &
                                                 a_potential_START_state,
                                                 YR_CPP_MONITOR &
                                                 a_runtime_monitor);

    bool ADDITIONAL_FINAL_STATE_lookup(YR_CPP_MONITOR_STATE &
                                       a_potential_final_state,
                                       YR_CPP_MONITOR &a_runtime_monitor);

    void GET_error_final_STATES(YR_CPP_MONITOR &a_runtime_monitor,
                                QList <
                                YR_CPP_MONITOR_STATE * >&results_states);

    virtual void print_FOR_YEROTH_ERP();

    virtual void print();

    virtual QString print_to_dot_file();


    QStringList _EVENT_PARAMETERS_LIST;

protected:

    QList < YR_CPP_MONITOR_STATE * >FINAL_ERROR_states;

    YR_CPP_MONITOR_STATE *_SOURCE_STATE;

    YR_CPP_MONITOR_STATE *_TARGET_STATE;

    QString _SOURCE_STATE_KEY;

    QString _TARGET_STATE_KEY;


private:

    YR_CPP_BOOLEAN_expression *_guarded_CONDITION_expression;

    YR_CPP_MONITOR_EVENT *_EDGE_EVENT;
};


#endif //_YR_CPP_MONITOR_EDGE_HPP_
