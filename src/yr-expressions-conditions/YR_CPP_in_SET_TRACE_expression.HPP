/*
 * YR_CPP_in_SET_TRACE_expression.HPP
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_in_SET_TRACE_expression_HPP_
#define _YR_CPP_in_SET_TRACE_expression_HPP_


#include "YR_CPP_BOOLEAN_expression.HPP"



class YR_CPP_MONITOR_TRACE_EVENT;

class YR_CPP_MONITOR_EVENT;


/**
 * E.G.: select_event IN trace(d)
 */

class YR_CPP_in_SET_TRACE_expression : public YR_CPP_BOOLEAN_expression
{
public:

	YR_CPP_in_SET_TRACE_expression()
	{
	}

	virtual ~YR_CPP_in_SET_TRACE_expression()
	{
	}

	inline virtual bool evaluate_expression()
	{
		return false;
	}

	virtual bool evaluate_expression(YR_CPP_MONITOR_TRACE_EVENT *_right_value_database_TRACE_events);

protected:

	QString _left_value_database_event;

};



#endif // _YR_CPP_in_SET_TRACE_expression_HPP_
