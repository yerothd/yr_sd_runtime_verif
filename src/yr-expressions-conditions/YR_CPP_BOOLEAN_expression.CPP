/*
 * YR_CPP_BOOLEAN_expression.CPP
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#include "YR_CPP_BOOLEAN_expression.HPP"
#include "YR_CPP_MONITOR_EVENT.hpp"

#include <QtCore/QDebug>


inline QString YR_CPP_BOOLEAN_expression::print()
{
	QString _PRINT_EXPR_OUT =
			QString("%1 (%2, %3)")
				.arg(_predicate__FIRST_ORDER__set_OPERATION,
					 _DB_SQL_operation,
					 _CPP_PROGRAM_SET_PREDICATE_variable);

	qDebug() << _PRINT_EXPR_OUT;

	return _PRINT_EXPR_OUT;
}
