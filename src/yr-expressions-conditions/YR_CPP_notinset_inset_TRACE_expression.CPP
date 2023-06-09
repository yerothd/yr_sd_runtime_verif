/*
 * YR_CPP_notinset_inset_TRACE_expression.CPP
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#include "YR_CPP_notinset_inset_TRACE_expression.HPP"
#include "src/YR_CPP_MONITOR_EVENT.hpp"

#include <QtCore/QDebug>


QString YR_CPP_notinset_inset_TRACE_expression::toString__WITH__sql_event_log_SYNTAX()
{
	QString _PRINT_EXPR_OUT = "UNDEFINED predicate expression";

	if (NOT_IN_SET__inset_trace::UNDEFINED_predicate != _predicate__INSET__notinSET_trace)
	{
		QString __runtime__monitoring__STATE__EXPRESSION =
				QString("STATE(%1)").arg(_RUNTIME__MONITORING__STATE_name);

		if (getRUNTIME__MONITOR__start__STATE())
		{
			QString __runtime__monitoring__STATE__EXPRESSION =
					QString("START_STATE(%1)").arg(_RUNTIME__MONITORING__STATE_name);
		}
		else if (getRUNTIME__MONITOR__final__STATE())
		{
			QString __runtime__monitoring__STATE__EXPRESSION =
					QString("ERROR_STATE(%1)").arg(_RUNTIME__MONITORING__STATE_name);
		}

		_PRINT_EXPR_OUT =
			QString("%1 (%2, %3)")
				.arg(NOT_IN_SET__inset_trace::IN_SET_TRACE == _predicate__INSET__notinSET_trace ? "in_sql_event_log"
																		: "not_in_sql_event_log",
					 _DB_SQL_operation__SUT_event,
					 __runtime__monitoring__STATE__EXPRESSION);

		//qDebug() << _PRINT_EXPR_OUT;
	}

	return _PRINT_EXPR_OUT;
}


QString YR_CPP_notinset_inset_TRACE_expression::toString__WITH__standard_trace_syntax()
{
	QString _PRINT_EXPR_OUT = "UNDEFINED predicate expression";

	if (NOT_IN_SET__inset_trace::UNDEFINED_predicate != _predicate__INSET__notinSET_trace)
	{
		QString __runtime__monitoring__STATE__EXPRESSION =
				QString("STATE(%1)").arg(_RUNTIME__MONITORING__STATE_name);

		if (getRUNTIME__MONITOR__start__STATE())
		{
			QString __runtime__monitoring__STATE__EXPRESSION =
					QString("START_STATE(%1)").arg(_RUNTIME__MONITORING__STATE_name);
		}
		else if (getRUNTIME__MONITOR__final__STATE())
		{
			QString __runtime__monitoring__STATE__EXPRESSION =
					QString("ERROR_STATE(%1)").arg(_RUNTIME__MONITORING__STATE_name);
		}

		_PRINT_EXPR_OUT =
			QString("%1 (%2, %3)")
				.arg(NOT_IN_SET__inset_trace::IN_SET_TRACE == _predicate__INSET__notinSET_trace ? "in_set_trace" : "not_in_set_trace",
					 _DB_SQL_operation__SUT_event,
					 __runtime__monitoring__STATE__EXPRESSION);

		//qDebug() << _PRINT_EXPR_OUT;
	}

	return _PRINT_EXPR_OUT;
}


QString YR_CPP_notinset_inset_TRACE_expression::toString()
{
	QString TO_STRING_RESULT;

	if (GET__USE_SQL_SYNTAX_event_logging__FOR_PRINTING())
	{
		TO_STRING_RESULT = toString__WITH__sql_event_log_SYNTAX();
	}
	else
	{
		TO_STRING_RESULT = toString__WITH__standard_trace_syntax();
	}

	return TO_STRING_RESULT;
}


QString YR_CPP_notinset_inset_TRACE_expression::toString(bool PRINT_WITH_STANDARD_trace_syntax)
{
	QString TO_STRING_RESULT;

	if (PRINT_WITH_STANDARD_trace_syntax)
	{
		TO_STRING_RESULT = toString__WITH__standard_trace_syntax();
	}
	else
	{
		TO_STRING_RESULT = toString__WITH__sql_event_log_SYNTAX();
	}

	return TO_STRING_RESULT;
}


bool YR_CPP_notinset_inset_TRACE_expression::evaluate_expression(const QList<QString> &INCOMING_TRACE)
{
	bool EVALUATED_EXPRESSION_value = false;

	if (NOT_IN_SET__inset_trace::UNDEFINED_predicate != _predicate__INSET__notinSET_trace  &&
		!_DB_SQL_operation__SUT_event.isEmpty())
	{
		EVALUATED_EXPRESSION_value =
				IS__Predicate__in_set__TRACE() ?
						(true == INCOMING_TRACE.contains(_DB_SQL_operation__SUT_event)) :
						(false == INCOMING_TRACE.contains(_DB_SQL_operation__SUT_event));
	}

	return EVALUATED_EXPRESSION_value;
}

