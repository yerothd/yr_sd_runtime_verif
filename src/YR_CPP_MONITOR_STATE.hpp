/*
 * YR_CPP_MONITOR_STATE.hpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_MONITOR_STATE_HPP_
#define _YR_CPP_MONITOR_STATE_HPP_


#include "utils/YR_CPP_UTILS.hpp"

#include "YR_CPP_MONITOR_object.hpp"

#include <algorithm>

#include <QtCore/QString>

#include <QtCore/QMap>


class YR_CPP_MONITOR;

class YR_CPP_MONITOR_EDGE;

class YR_CPP_MONITOR_TRACE_EVENT;

class YR_CPP_MONITOR_STATE_PROPERTY_VALUE;


class YR_CPP_MONITOR_STATE:public YR_CPP_MONITOR_object
{
	Q_OBJECT

public:

    YR_CPP_CLASS_OPERATORS

	inline YR_CPP_MONITOR_STATE(const QString &MONITOR_STATE_NAME)
    :MONITOR_STATE_NAME("MONITOR_STATE_NAME"),
	 _AN_INCOMING_EDGE(0),
	 _AN_OUTGOING_EDGE(0),
	 _state_id(-1),
	 _start_state(false),
	 _final_state(false),
	 _MONITOR_STATE_TRACE_EVENTS(0)
    {
        _statepropertyKEY_TO_statepropertyVALUE.
        	insert(YR_CPP_MONITOR_STATE::MONITOR_STATE_NAME, MONITOR_STATE_NAME);
    }


    inline YR_CPP_MONITOR_STATE()
    :MONITOR_STATE_NAME("MONITOR_STATE_NAME"),
	 _AN_INCOMING_EDGE(0),
	 _AN_OUTGOING_EDGE(0),
     _state_id(-1),
     _start_state(false),
     _final_state(false),
	 _MONITOR_STATE_TRACE_EVENTS(0)
    {
    }

    inline virtual ~YR_CPP_MONITOR_STATE()
    {
        _state_id = -1;
    }

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

    inline virtual YR_CPP_MONITOR_EDGE *get_AN_incoming_edge()
    {
    	return _AN_INCOMING_EDGE;
    }

    inline virtual YR_CPP_MONITOR_EDGE *get_AN_outgoing_edge()
    {
    	return _AN_OUTGOING_EDGE;
    }

    inline virtual void set_AN_incoming_edge(YR_CPP_MONITOR_EDGE *AN_INCOMING_EDGE)
    {
    	_AN_INCOMING_EDGE = AN_INCOMING_EDGE;
    }

    inline virtual void set_AN_outgoing_edge(YR_CPP_MONITOR_EDGE *AN_OUTGOING_EDGE)
    {
    	_AN_OUTGOING_EDGE = AN_OUTGOING_EDGE;
    }

    inline virtual QString GET_IN_STATEPROPERTY_KEY_VALUE(QString AN_inset_state_property_key)
    {
        return _SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.
               value(AN_inset_state_property_key, YR_CPP_UTILS::EMPTY_STRING);
    }

    inline virtual QString GET_notIN_STATEPROPERTY_KEY_VALUE(QString a_state_property_key)
    {
        return _SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.value(a_state_property_key,
                                                          YR_CPP_UTILS::
                                                          EMPTY_STRING);
    }

    inline virtual QString GET_db_IN_STATEPROPERTY_KEY_VALUE(QString a_state_property_key)
    {
        return _SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.value(a_state_property_key,
                                                          YR_CPP_UTILS::
                                                          EMPTY_STRING);
    }

    inline virtual QString GET_db_NOT_IN_STATEPROPERTY_KEY_VALUE(QString a_state_property_key)
    {
        return _SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.
               value(a_state_property_key, YR_CPP_UTILS::EMPTY_STRING);
    }

    inline virtual void set_IN_PRE_STATEPROPERTYKEY__to__VALUE(QString
                                                           a_stateproperty_KEY,
                                                           QString a_VALUE)
    {
        _SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE.insert(a_stateproperty_KEY, a_VALUE);
    }

    inline virtual
		void set_notIN_PRE_STATEPROPERTYKEY__to__VALUE(QString a_stateproperty_KEY,
                                                       QString a_VALUE)
    {
        _SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE.insert(a_stateproperty_KEY,
                                                    a_VALUE);
    }

    inline virtual
		void set_in_post_STATEPROPERTYKEY__to__VALUE(QString a_stateproperty_KEY,
                                                     QString a_VALUE)
    {
        _SET_IN_POST_STATEPROPERTYKEY_TO_VALUE.insert(a_stateproperty_KEY,
                                                    a_VALUE);
    }

    inline virtual
		void set_notin_POST_STATEPROPERTYKEY__to__VALUE(QString a_stateproperty_KEY,
                                                        QString a_VALUE)
    {
        _SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE.insert(a_stateproperty_KEY,
                                                        a_VALUE);
    }

    void set_PRE_CONDITION_notIN(QString DB_VARIABLE,
                                 QString db_query_TABLE__db_query_COLUMN);


    void set_PRE_CONDITION_IN(QString DB_VARIABLE,
                              QString db_query_TABLE__db_query_COLUMN);


    void set_POST_CONDITION_notIN(QString DB_VARIABLE,
                                  QString db_query_TABLE__db_query_COLUMN);


    void set_POST_CONDITION_IN(QString DB_VARIABLE,
                               QString db_query_TABLE__db_query_COLUMN);

    inline virtual QString get_MONITOR_STATE_STATEPROPERTYVALUE(QString a_state_property_key)
    {
        return _statepropertyKEY_TO_statepropertyVALUE.
               value(a_state_property_key, YR_CPP_UTILS::EMPTY_STRING);
    }

    inline virtual YR_CPP_MONITOR_TRACE_EVENT *get_MONITOR_TRACE_EVENTS()
    {
        return _MONITOR_STATE_TRACE_EVENTS;
    }


    /**
     * !!! SHALL BE CALLED whenever this SUT state
     * couldn't trigger a state diagram transition
     * event !!!
     */
    inline void remove_RUNTIME_MONITOR_INCOMING_TRACE_EVENT()
    {
    	_TRACE.clear();
    }

    /**
     * !!! SHALL BE CALLED just before triggering
     * any SUT event from this runtime monitor
     * state !!!
     */
    const QStringList &ADD_RUNTIME_MONITOR_INCOMING_TRACE_EVENT(QList<QString> &a_runtime_monitor_trace_event);


    const QStringList &ADD_RUNTIME_MONITOR_TRACE_EVENT(QString a_runtime_monitor_trace_event);

    inline const QStringList &GET_TRACE_OF_THIS_RUNTIME_MONITOR_STATE() const
    {
        return _TRACE;
    }

    inline QString bool_To_String(bool a_boolean_VALUE)
    {
        return (true == a_boolean_VALUE) ? QString("TRUE") : QString("FALSE");
    }

    inline virtual void CLEAR_INCOMING_trace_event_log()
    {
    	_TRACE.clear();
    }

    virtual void set_START_STATE(YR_CPP_MONITOR 	&A_RUNTIME_MONITOR,
    							 bool 				is_start_state);

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

    QMap <QString, QString> _SET_IN_PRE_STATEPROPERTYKEY_TO_VALUE;

    QMap <QString, QString> _SET_notIN_PRE_STATEPROPERTYKEY_TO_VALUE;

    QMap <QString, QString> _SET_IN_POST_STATEPROPERTYKEY_TO_VALUE;

    QMap <QString, QString> _SET_notIN_POST_STATEPROPERTYKEY_TO_VALUE;

    QMap <QString, QString> _statepropertyKEY_TO_statepropertyVALUE;


    YR_CPP_MONITOR_EDGE *_AN_INCOMING_EDGE;

    YR_CPP_MONITOR_EDGE *_AN_OUTGOING_EDGE;


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

    inline YR_CPP_MONITOR_STATE_functor(QString a_state_name)
    :_a_state_name_TO_FIND(a_state_name)
    {
    }

    inline bool operator()(YR_CPP_MONITOR_STATE *a_state) const
    {
        return (0 != a_state) ?
                ( YR_CPP_UTILS::isEqualsCaseInsensitive(_a_state_name_TO_FIND,
            	   a_state->get_MONITOR_STATE_STATEPROPERTYVALUE
    				  	  (YR_CPP_MONITOR_STATE::_MONITOR_STATE_NAME_string_key)) ) : false;
    }

private:

    QString _a_state_name_TO_FIND;
};



#endif // _YR_CPP_MONITOR_STATE_HPP_
