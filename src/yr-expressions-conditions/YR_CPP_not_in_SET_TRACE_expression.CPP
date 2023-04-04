/*
 * YR_CPP_not_in_SET_TRACE_expression.HPP
 *
 *      Author: Dr.-Ing. Dipl.-Inf. Xavier Noumbissi Noundou, Ph.D (ABD)
 */

#include "YR_CPP_not_in_SET_TRACE_expression.HPP"

#include "YR_CPP_MONITOR_TRACE_EVENT.hpp"

#include "YR_CPP_MONITOR_EVENT.hpp"



bool YR_CPP_not_in_SET_TRACE_expression::evaluate_expression(YR_CPP_MONITOR_TRACE_EVENT *_right_value_database_TRACE_events)
{
	return YR_CPP_in_SET_TRACE_expression::
			evaluate_expression(_right_value_database_TRACE_events);
}
