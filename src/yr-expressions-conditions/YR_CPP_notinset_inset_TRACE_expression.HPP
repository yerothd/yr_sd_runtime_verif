/*
 * YR_CPP_notinset_inset_TRACE_expression.HPP
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUNDOU
 */

#ifndef _YR_CPP_notinset_inset_TRACE_expression_HPP_
#define _YR_CPP_notinset_inset_TRACE_expression_HPP_

#include <QtCore/QList>

#include <QtCore/QString>


class YR_CPP_notinset_inset_TRACE_expression
{
public:

	enum NOT_IN_SET__inset_trace
	{
		IN_SET_TRACE 	 	= 0,
		not_in_set_trace 	= 1,
		UNDEFINED_predicate = 2
	};


	inline YR_CPP_notinset_inset_TRACE_expression()
	:_USE_SQL_SYNTAX_event_logging__FOR_PRINTING(true),
	 _runtime__monitoring__START_STATE(false),
	 _runtime__monitoring__FINAL_STATE(false),
	 _predicate__INSET__notinSET_trace(UNDEFINED_predicate)
	{
	}

	inline
	YR_CPP_notinset_inset_TRACE_expression(enum NOT_IN_SET__inset_trace A_predicate__INSET__notinSET_trace,
							  	  	  	   QString A_DB_SQL_operation__SUT_event,
										   QString A_RUNTIME__MONITORING__STATE_name)
	:_USE_SQL_SYNTAX_event_logging__FOR_PRINTING(true),
	 _runtime__monitoring__START_STATE(false),
	 _runtime__monitoring__FINAL_STATE(false),
	 _predicate__INSET__notinSET_trace(A_predicate__INSET__notinSET_trace),
	 _DB_SQL_operation__SUT_event(A_DB_SQL_operation__SUT_event),
	 _RUNTIME__MONITORING__STATE_name(A_RUNTIME__MONITORING__STATE_name)
	{
	}

	inline
	YR_CPP_notinset_inset_TRACE_expression(bool A_predicate__INSET__notinSET_trace,
							  	  	  	   QString A_DB_SQL_operation__SUT_event,
										   QString A_RUNTIME__MONITORING__STATE_name)
	:YR_CPP_notinset_inset_TRACE_expression
	 	 ((A_predicate__INSET__notinSET_trace ? IN_SET_TRACE : not_in_set_trace),
	 	   A_DB_SQL_operation__SUT_event,
		   A_RUNTIME__MONITORING__STATE_name)
	{
	}

	inline virtual void set__USE_SQL_SYNTAX_event_logging__FOR_PRINTING(
							bool USE_SQL_SYNTAX_event_logging__FOR_PRINTING)
	{
		_USE_SQL_SYNTAX_event_logging__FOR_PRINTING =
					USE_SQL_SYNTAX_event_logging__FOR_PRINTING;
	}

	inline virtual bool GET__USE_SQL_SYNTAX_event_logging__FOR_PRINTING()
	{
		return _USE_SQL_SYNTAX_event_logging__FOR_PRINTING;
	}

	virtual QString toString__WITH__sql_event_log_SYNTAX();

	virtual QString toString__WITH__standard_trace_syntax();

	inline virtual ~YR_CPP_notinset_inset_TRACE_expression()
	{
	}

	virtual QString toString();

	virtual QString toString(bool PRINT_WITH_STANDARD_trace_syntax);

	virtual bool evaluate_expression(const QList<QString> &INCOMING_TRACE);

	inline virtual void setRUNTIME__MONITOR__final__STATE(bool a_RUNTIME__MONITOR__final_state)
	{
		_runtime__monitoring__FINAL_STATE = a_RUNTIME__MONITOR__final_state;
	}

	inline virtual bool getRUNTIME__MONITOR__final__STATE()
	{
		return _runtime__monitoring__FINAL_STATE;
	}

	inline virtual void setRUNTIME__MONITOR__start__STATE(bool a_RUNTIME__MONITOR__start_state)
	{
		_runtime__monitoring__START_STATE = a_RUNTIME__MONITOR__start_state;
	}

	inline virtual bool getRUNTIME__MONITOR__start__STATE()
	{
		return _runtime__monitoring__START_STATE;
	}

	inline virtual QString getRUNTIME__MONITORING__STATE_name()
	{
		return _RUNTIME__MONITORING__STATE_name;
	}

	inline virtual void setRUNTIME__MONITORING__STATE_name(QString a_RUNTIME__MONITORING__STATE_name)
	{
		_RUNTIME__MONITORING__STATE_name = a_RUNTIME__MONITORING__STATE_name;
	}

	inline virtual QString getDB_SQL_operation__SUT_event()
	{
		return _DB_SQL_operation__SUT_event;
	}

	inline virtual void setDB_SQL_operation__SUT_event(QString A_DB_SQL_operation__SUT_event)
	{
		_DB_SQL_operation__SUT_event = A_DB_SQL_operation__SUT_event;
	}

	inline virtual bool IS__Predicate__in_set__TRACE()
	{
		return (IN_SET_TRACE == _predicate__INSET__notinSET_trace);
	}

	inline virtual void setPredicate__INSET__notinset__TRACE(bool A_predicate__INSET__notinSET_trace)
	{
		_predicate__INSET__notinSET_trace =
				A_predicate__INSET__notinSET_trace ? IN_SET_TRACE : not_in_set_trace;
	}

protected:

	bool _USE_SQL_SYNTAX_event_logging__FOR_PRINTING;

	bool _runtime__monitoring__START_STATE;

	bool _runtime__monitoring__FINAL_STATE;

	enum NOT_IN_SET__inset_trace _predicate__INSET__notinSET_trace;

	QString _DB_SQL_operation__SUT_event;

	QString _RUNTIME__MONITORING__STATE_name;
};



#endif // _YR_CPP_notinset_inset_TRACE_expression_HPP_
