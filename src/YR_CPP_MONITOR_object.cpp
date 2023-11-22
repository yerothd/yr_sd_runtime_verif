/*
 * YR_CPP_MONITOR_object.cpp
 *
 *      Author: DR.-ING. DIPL.-INF. XAVIER NOUNDOU
 */


#include "YR_CPP_MONITOR_object.hpp"


uint
YR_CPP_MONITOR_object::MONITOR_OBJECTS_CURRENT_ID_GENERATOR = 0;


YR_CPP_MONITOR_object::~YR_CPP_MONITOR_object()
{
    _MONITOR_OBJECT_ID = -1;
}
