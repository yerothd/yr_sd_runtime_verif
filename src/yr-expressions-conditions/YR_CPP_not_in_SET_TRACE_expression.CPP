/*
 * YR_CPP_not_in_SET_TRACE_expression.HPP
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU, Ph.D (ABD)
 */

#include "YR_CPP_not_in_SET_TRACE_expression.HPP"

#include "src/YR_CPP_MONITOR_TRACE_EVENT.hpp"

#include "src/YR_CPP_MONITOR_EVENT.hpp"



bool YR_CPP_not_in_SET_TRACE_expression::evaluate_expression(YR_CPP_MONITOR_TRACE_EVENT *_right_value_database_TRACE_events)
{
	return YR_CPP_in_SET_TRACE_expression::
			evaluate_expression(_right_value_database_TRACE_events);
}
