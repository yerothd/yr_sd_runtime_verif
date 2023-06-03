/*
 * YR_CPP_BOOLEAN_expression.CPP
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#include "YR_CPP_BOOLEAN_expression.HPP"
#include "src/YR_CPP_MONITOR_EVENT.hpp"

#include <QtCore/QDebug>


inline QString YR_CPP_BOOLEAN_expression::print()
{
	QString _PRINT_EXPR_OUT =
			QString("%1 (%2, %3)")
				.arg(_predicate__INSET__notinSET_trace,
					 _DB_SQL_operation__SUT_event,
					 _RUNTIME__MONITORING__STATE_name);

	qDebug() << _PRINT_EXPR_OUT;

	return _PRINT_EXPR_OUT;
}
