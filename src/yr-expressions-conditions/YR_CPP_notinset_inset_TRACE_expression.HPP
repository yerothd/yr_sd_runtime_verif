/*
 * YR_CPP_notinset_inset_TRACE_expression.HPP
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
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
	:_predicate__INSET__notinSET_trace(UNDEFINED_predicate)
	{
	}

	inline
	YR_CPP_notinset_inset_TRACE_expression(enum NOT_IN_SET__inset_trace A_predicate__INSET__notinSET_trace,
							  	  	  	   QString A_DB_SQL_operation__SUT_event,
										   QString A_RUNTIME__MONITORING__STATE_name)
	:_predicate__INSET__notinSET_trace(A_predicate__INSET__notinSET_trace),
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

	virtual QString print();

	inline virtual ~YR_CPP_notinset_inset_TRACE_expression()
	{
	}

	inline virtual QString toString()
	{
		return print();
	}

	virtual bool evaluate_expression(const QList<QString> &INCOMING_TRACE);

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

	enum NOT_IN_SET__inset_trace _predicate__INSET__notinSET_trace;

	QString _DB_SQL_operation__SUT_event;

	QString _RUNTIME__MONITORING__STATE_name;

private:

};



#endif // _YR_CPP_notinset_inset_TRACE_expression_HPP_
