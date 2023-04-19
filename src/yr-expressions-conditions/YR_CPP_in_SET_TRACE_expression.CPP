/*
 * YR_CPP_in_SET_TRACE_expression.CPP
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#include "YR_CPP_in_SET_TRACE_expression.HPP"

#include "src/YR_CPP_MONITOR_TRACE_EVENT.hpp"

#include "src/YR_CPP_MONITOR_EVENT.hpp"



bool YR_CPP_in_SET_TRACE_expression::evaluate_expression(YR_CPP_MONITOR_TRACE_EVENT *_right_value_database_TRACE_events)
{
	if (0 != _right_value_database_TRACE_events)
	{
		_right_value_database_TRACE_events
			->is_in_TRACE_EVENT(_left_value_database_event);
	}

	return false;
}
