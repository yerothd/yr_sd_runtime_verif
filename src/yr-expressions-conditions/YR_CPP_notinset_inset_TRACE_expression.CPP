/*
 * YR_CPP_notinset_inset_TRACE_expression.CPP
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#include "YR_CPP_notinset_inset_TRACE_expression.HPP"
#include "src/YR_CPP_MONITOR_EVENT.hpp"

#include <QtCore/QDebug>


inline QString YR_CPP_notinset_inset_TRACE_expression::print()
{
	QString _PRINT_EXPR_OUT =
			QString("%1 (%2, %3)")
				.arg(NOT_IN_SET__inset_trace::IN_SET_TRACE == _predicate__INSET__notinSET_trace ? "in_set_trace" : "not_in_set_trace",
					 _DB_SQL_operation__SUT_event,
					 _RUNTIME__MONITORING__STATE_name);

	qDebug() << _PRINT_EXPR_OUT;

	return _PRINT_EXPR_OUT;
}

