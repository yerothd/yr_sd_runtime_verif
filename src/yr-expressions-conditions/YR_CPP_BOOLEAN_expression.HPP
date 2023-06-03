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

	virtual ~YR_CPP_BOOLEAN_expression()
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

	inline virtual QString getCppProgramSetPredicateVariable()
	{
		return _RUNTIME__MONITORING__STATE_name;
	}

	inline virtual void setCppProgramSetPredicateVariable(QString cppProgramSetPredicateVariable)
	{
		_RUNTIME__MONITORING__STATE_name = cppProgramSetPredicateVariable;
	}

	inline virtual QString getDbSqlOperation()
	{
		return _DB_SQL_operation__SUT_event;
	}

	inline virtual void setDbSqlOperation(QString dbSqlOperation)
	{
		_DB_SQL_operation__SUT_event = dbSqlOperation;
	}

	inline virtual QString getPredicateFirstOrderSetOperation()
	{
		return _predicate__INSET__notinSET_trace;
	}

	inline virtual void setPredicateFirstOrderSetOperation(QString predicateFirstOrderSetOperation)
	{
		_predicate__INSET__notinSET_trace = predicateFirstOrderSetOperation;
	}

protected:

	QString _predicate__INSET__notinSET_trace;

	QString _DB_SQL_operation__SUT_event;

	QString _RUNTIME__MONITORING__STATE_name;

private:

};



#endif // _YR_CPP_BOOLEAN_expression_HPP_
