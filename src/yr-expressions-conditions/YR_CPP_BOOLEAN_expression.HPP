/*
 * YR_CPP_BOOLEAN_expression.HPP
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
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
	YR_CPP_BOOLEAN_expression(QString A_predicate__FIRST_ORDER__set_OPERATION,
							  QString A_DB_SQL_operation,
							  QString A_CPP_PROGRAM_SET_PREDICATE_variable)
	:_predicate__FIRST_ORDER__set_OPERATION(A_predicate__FIRST_ORDER__set_OPERATION),
	 _DB_SQL_operation(A_DB_SQL_operation),
	 _CPP_PROGRAM_SET_PREDICATE_variable(A_CPP_PROGRAM_SET_PREDICATE_variable)
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
		return _CPP_PROGRAM_SET_PREDICATE_variable;
	}

	inline virtual void setCppProgramSetPredicateVariable(QString cppProgramSetPredicateVariable)
	{
		_CPP_PROGRAM_SET_PREDICATE_variable = cppProgramSetPredicateVariable;
	}

	inline virtual QString getDbSqlOperation()
	{
		return _DB_SQL_operation;
	}

	inline virtual void setDbSqlOperation(QString dbSqlOperation)
	{
		_DB_SQL_operation = dbSqlOperation;
	}

	inline virtual QString getPredicateFirstOrderSetOperation()
	{
		return _predicate__FIRST_ORDER__set_OPERATION;
	}

	inline virtual void setPredicateFirstOrderSetOperation(QString predicateFirstOrderSetOperation)
	{
		_predicate__FIRST_ORDER__set_OPERATION = predicateFirstOrderSetOperation;
	}

protected:

	QString _predicate__FIRST_ORDER__set_OPERATION;

	QString _DB_SQL_operation;

	QString _CPP_PROGRAM_SET_PREDICATE_variable;

private:

};



#endif // _YR_CPP_BOOLEAN_expression_HPP_
