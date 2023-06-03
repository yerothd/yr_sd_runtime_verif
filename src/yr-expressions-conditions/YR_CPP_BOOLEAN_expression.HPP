/*
 * YR_CPP_BOOLEAN_expression.HPP
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_BOOLEAN_expression_HPP_
#define _YR_CPP_BOOLEAN_expression_HPP_


#include <QtCore/QString>


class YR_CPP_BOOLEAN_expression
{
public:

	inline YR_CPP_BOOLEAN_expression()
	{
	}

	inline
	YR_CPP_BOOLEAN_expression(QString A_predicate__INSET__notinSET_trace,
							  QString A_DB_SQL_operation__SUT_event,
							  QString A_RUNTIME__MONITORING__STATE_name)
	:_predicate__INSET__notinSET_trace(A_predicate__INSET__notinSET_trace),
	 _DB_SQL_operation__SUT_event(A_DB_SQL_operation__SUT_event),
	 _RUNTIME__MONITORING__STATE_name(A_RUNTIME__MONITORING__STATE_name)
	{
	}

	virtual QString print();

	inline virtual ~YR_CPP_BOOLEAN_expression()
	{
	}

	inline virtual QString toString()
	{
		return "";
	}

	inline virtual bool evaluate_expression()
	{
		return false;
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

	inline virtual QString getPredicate__INSET__notinset__TRACE()
	{
		return _predicate__INSET__notinSET_trace;
	}

	inline virtual void setPredicate__INSET__notinset__TRACE(QString A_predicate__INSET__notinSET_trace)
	{
		_predicate__INSET__notinSET_trace = A_predicate__INSET__notinSET_trace;
	}

protected:

	QString _predicate__INSET__notinSET_trace;

	QString _DB_SQL_operation__SUT_event;

	QString _RUNTIME__MONITORING__STATE_name;

private:

};



#endif // _YR_CPP_BOOLEAN_expression_HPP_
