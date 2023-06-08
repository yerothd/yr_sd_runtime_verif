/*
 * yr-db-runtime-verif-main-GENERATED.hpp
 *
 */

#ifndef _YR_DB_VERIF_RUNTIME_MONITOR__YR_RTM_REPLACEMENT_QSTRING_HPP_
#define _YR_DB_VERIF_RUNTIME_MONITOR__YR_RTM_REPLACEMENT_QSTRING_HPP_

#include "include/yr-db-runtime-verif-MONITOR.hpp"

#include "yr_sd_runtime_verif/utils/YR_CPP_UTILS.hpp"

#include "yr_sd_runtime_verif/YR_CPP_MONITOR_object.hpp"


#include <QtCore/QDebug>


class YR_CPP_MONITOR_EDGE;
class YR_CPP_MONITOR;


class _YR_RTM_REPLACEMENT_QSTRING : public YR_DB_RUNTIME_VERIF_Monitor
{
    Q_OBJECT

public:

    static void YR_CALL_BACK_final_state(YR_CPP_MONITOR 			*a_runtime_monitor,
																				 YR_CPP_MONITOR_EDGE 	*an_EDGE_leading_TO_error_FINAL_state);

    _YR_RTM_REPLACEMENT_QSTRING();

    _YR_RTM_REPLACEMENT_QSTRING(YR_DB_RUNTIME_VERIF_Logger *logger);

    inline virtual ~_YR_RTM_REPLACEMENT_QSTRING()
    {
    }

public slots:

    /**
     * THIS METHOD PERFORMS EFFECTIVE TEMPORAL LINEAR
     * LOGIC CHECK AFTER A STATE EVENT (or system event)
     * could be achieved by the runtime monitor system !
     *
     * A SERIOUS VERIFICATION CLIENT MUST OVERRIDE THIS
     * METHOD !
     */
    virtual bool DO_VERIFY_AND_or_CHECK_ltl_PROPERTY(
        QString sql_table_ADDED_with_file_AND_line_number,
        uint	sql_record_qty_MODIFIED,
        YR_CPP_UTILS::SQL_CONSTANT_IDENTIFIER cur_SQL_command =
            YR_CPP_UTILS::SQL_CONSTANT_IDENTIFIER::UNDEFINED_SQL_COMMAND);


    _slots_event_declarations_YR_RTM_REPLACEMENT_QSTRING_

};


#endif /* _YR_DB_VERIF_RUNTIME_MONITOR__YR_RTM_REPLACEMENT_QSTRING_HPP_ */
