/*
 * YR_CPP_MONITOR_STATE.hpp
 *
 *      Author: Dr.-Ing. Xavier Noumbissi Noundou
 */

#ifndef _YR_CPP_MONITOR_STATE_HPP_
#define _YR_CPP_MONITOR_STATE_HPP_


#include "utils/YR_CPP_UTILS.hpp"

#include "YR_CPP_MONITOR_object.hpp"


#include <QtCore/QString>

#include <QtCore/QMap>


class YR_CPP_MONITOR_TRACE_EVENT;

class YR_CPP_MONITOR_STATE_PROPERTY_VALUE;


class YR_CPP_MONITOR_STATE:public YR_CPP_MONITOR_object
{
Q_OBJECT public:

    YR_CPP_CLASS_OPERATORS YR_CPP_MONITOR_STATE(const QString &
                                                MONITOR_STATE_NAME):MONITOR_STATE_NAME
        ("MONITOR_STATE_NAME"), _state_id(-1), _start_state(false),
        _final_state(false), _MONITOR_STATE_TRACE_EVENTS(0)
    {
        _statepropertyKEY_TO_statepropertyVALUE.
        insert(YR_CPP_MONITOR_STATE::MONITOR_STATE_NAME, MONITOR_STATE_NAME);
    }

    YR_CPP_MONITOR_STATE():MONITOR_STATE_NAME("MONITOR_STATE_NAME"),
        _state_id(-1),
        _start_state(false),
        _final_state(false), _MONITOR_STATE_TRACE_EVENTS(0)
    {
    }

    virtual ~ YR_CPP_MONITOR_STATE();

    inline virtual QString get_MONITOR_STATE_NAME()
    {
        return
                        get_MONITOR_STATE_STATEPROPERTYVALUE(_MONITOR_STATE_NAME_string_key);
    }

    inline virtual void set_MONITOR_STATE_NAME(QString a_monitor_state_name)
    {
        _statepropertyKEY_TO_statepropertyVALUE.
        insert(_MONITOR_STATE_NAME_string_key, a_monitor_state_name);
    }

    inline virtual QString GET_IN_STATEPROPERTY_KEY_VALUE(QString
                                                          AN_inset_state_property_key)
    {
        return _SET_IN_STATEPROPERTYKEY_TO_VALUE.
               value(AN_inset_state_property_key, YR_CPP_UTILS::EMPTY_STRING);
    }

    inline virtual QString GET_notIN_STATEPROPERTY_KEY_VALUE(QString
                                                             a_state_property_key)
    {
        return _SET_notIN_STATEPROPERTYKEY_TO_VALUE.value(a_state_property_key,
                                                          YR_CPP_UTILS::
                                                          EMPTY_STRING);
    }

    inline virtual QString GET_db_IN_STATEPROPERTY_KEY_VALUE(QString
                                                             a_state_property_key)
    {
        return _SET_db_IN_STATEPROPERTYKEY_TO_VALUE.value(a_state_property_key,
                                                          YR_CPP_UTILS::
                                                          EMPTY_STRING);
    }

    inline virtual QString GET_db_NOT_IN_STATEPROPERTY_KEY_VALUE(QString
                                                                 a_state_property_key)
    {
        return _SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE.
               value(a_state_property_key, YR_CPP_UTILS::EMPTY_STRING);
    }

    inline virtual void set_IN_STATEPROPERTYKEY__to__VALUE(QString
                                                           a_stateproperty_KEY,
                                                           QString a_VALUE)
    {
        _SET_IN_STATEPROPERTYKEY_TO_VALUE.insert(a_stateproperty_KEY, a_VALUE);
    }

    inline virtual void set_notIN_STATEPROPERTYKEY__to__VALUE(QString
                                                              a_stateproperty_KEY,
                                                              QString a_VALUE)
    {
        _SET_notIN_STATEPROPERTYKEY_TO_VALUE.insert(a_stateproperty_KEY,
                                                    a_VALUE);
    }

    inline virtual void set_db_in_STATEPROPERTYKEY__to__VALUE(QString
                                                              a_stateproperty_KEY,
                                                              QString a_VALUE)
    {
        _SET_db_IN_STATEPROPERTYKEY_TO_VALUE.insert(a_stateproperty_KEY,
                                                    a_VALUE);
    }

    inline virtual void set_db_NOT_IN_STATEPROPERTYKEY__to__VALUE(QString
                                                                  a_stateproperty_KEY,
                                                                  QString
                                                                  a_VALUE)
    {
        _SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE.insert(a_stateproperty_KEY,
                                                        a_VALUE);
    }

    inline void set_PRE_CONDITION_notIN(QString DB_VARIABLE,
                                        QString
                                        db_query_TABLE__db_query_COLUMN)
    {
        set_notIN_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                              db_query_TABLE__db_query_COLUMN);
    }


    inline void set_PRE_CONDITION_IN(QString DB_VARIABLE,
                                     QString db_query_TABLE__db_query_COLUMN)
    {
        set_IN_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                           db_query_TABLE__db_query_COLUMN);
    }


    inline void set_POST_CONDITION_notIN(QString DB_VARIABLE,
                                         QString
                                         db_query_TABLE__db_query_COLUMN)
    {
        set_db_NOT_IN_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                                  db_query_TABLE__db_query_COLUMN);
    }


    inline void set_POST_CONDITION_IN(QString DB_VARIABLE,
                                      QString db_query_TABLE__db_query_COLUMN)
    {
        set_db_in_STATEPROPERTYKEY__to__VALUE(DB_VARIABLE,
                                              db_query_TABLE__db_query_COLUMN);
    }

    inline virtual QString get_MONITOR_STATE_STATEPROPERTYVALUE(QString
                                                                a_state_property_key)
    {
        return _statepropertyKEY_TO_statepropertyVALUE.
               value(a_state_property_key, YR_CPP_UTILS::EMPTY_STRING);
    }

    inline virtual YR_CPP_MONITOR_TRACE_EVENT *get_MONITOR_TRACE_EVENTS()
    {
        return _MONITOR_STATE_TRACE_EVENTS;
    }

    const QStringList &ADD_RUNTIME_MONITOR_TRACE_EVENT(QString
                                                       a_runtime_monitor_trace_event);

    inline const QStringList &GET_TRACE_OF_THIS_RUNTIME_MONITOR_STATE() const
    {
        return _TRACE;
    }

    inline QString bool_To_String(bool a_boolean_VALUE)
    {
        return (true == a_boolean_VALUE) ? QString("TRUE") : QString("FALSE");
    }

    inline virtual void set_START_STATE(bool is_start_state)
    {
        _start_state = is_start_state;
    }

    virtual void set_FINAL_STATE(bool is_final_state);

    virtual inline bool is_START_STATE()
    {
        return _start_state;
    }

    virtual inline bool is_FINAL_STATE()
    {
        return _final_state;
    }

    virtual void print();


    QString MONITOR_STATE_NAME;

    static const QString _MONITOR_STATE_NAME_string_key;

    QMap < QString, QString > _SET_IN_STATEPROPERTYKEY_TO_VALUE;

    QMap < QString, QString > _SET_notIN_STATEPROPERTYKEY_TO_VALUE;

    QMap < QString, QString > _SET_db_IN_STATEPROPERTYKEY_TO_VALUE;

    QMap < QString, QString > _SET_db_NOT_IN_STATEPROPERTYKEY_TO_VALUE;

    QMap < QString, QString > _statepropertyKEY_TO_statepropertyVALUE;

protected:

    int _state_id;

    bool _start_state;

    bool _final_state;

    QStringList _TRACE;

    YR_CPP_MONITOR_TRACE_EVENT *_MONITOR_STATE_TRACE_EVENTS;
};



class YR_CPP_MONITOR_STATE_functor
{
public:
    inline YR_CPP_MONITOR_STATE_functor(QString
                                        a_state_name):_a_state_name_TO_FIND
        (a_state_name)
    {
    }

    inline bool operator()(YR_CPP_MONITOR_STATE *a_state) const
    {
        return (0 != a_state) ?
               (0 !=
                a_state->
                get_MONITOR_STATE_STATEPROPERTYVALUE(_a_state_name_TO_FIND)) : false;
    }

private:

    QString _a_state_name_TO_FIND;
};


#endif // _YR_CPP_MONITOR_STATE_HPP_
