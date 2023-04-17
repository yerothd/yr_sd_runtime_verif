/*
 * YR_CPP_expression.HPP
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef _YR_CPP_expression_HPP_
#define _YR_CPP_expression_HPP_


#include <QtCore/QString>


class YR_CPP_expression
{
public:

	YR_CPP_expression()
	{
	}

	virtual ~YR_CPP_expression()
	{
	}

	inline virtual QString toString()
	{
		return "";
	}

	virtual bool evaluate_expression() = 0;


protected:


private:

};



#endif // _YR_CPP_expression_HPP_
