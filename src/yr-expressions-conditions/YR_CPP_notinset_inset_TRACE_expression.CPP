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
				.arg(_predicate__INSET__notinSET_trace ? "IN_SET_TRACE" : "NOT_IN_SET_TRACE",
					 _DB_SQL_operation__SUT_event,
					 _RUNTIME__MONITORING__STATE_name);

	qDebug() << _PRINT_EXPR_OUT;

	return _PRINT_EXPR_OUT;
}

