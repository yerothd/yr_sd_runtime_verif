/*
 * YR_CPP_MONITOR_ERP-database.hpp
 *
 *      Author: DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 */

#ifndef SRC_UTILS_YEROTH_DATABASE_HPP_
#define SRC_UTILS_YEROTH_DATABASE_HPP_


#include "src/utils/YR_CPP_UTILS.hpp"


#include <QtCore/QString>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>


class QSqlDatabase;
class QSqlError;

class YR_CPP_MONITOR_ERP_database
{
public:

    YR_CPP_CLASS_OPERATORS YR_CPP_MONITOR_ERP_database();

    inline ~ YR_CPP_MONITOR_ERP_database()
    {
    }

    QString toString();

    inline QSqlDatabase &getDatabase()
    {
        return _database;
    }

    inline bool open()
    {
        return _database.open(_db_user_name, _db_user_pwd);
    }

    inline void close()
    {
        _database.close();
    }

    inline bool transaction()
    {
        return _database.transaction();
    }

    inline QSqlDriver *driver()
    {
        return _database.driver();
    }

    inline bool roolback()
    {
        return _database.rollback();
    }

    inline bool commit()
    {
        return _database.commit();
    }

    inline QSqlError lastError()
    {
        return (_database.isValid())? _database.lastError() : QSqlError("");
    }

    inline void set_db_type(const QString &db_type)
    {
        _db_type = db_type;
    }

    void set_db_name(const QString &db_name);

    void set_db_ip_address(const QString &db_ip_address);

    void set_db_user_name(const QString &db_user_name);

    void set_db_user_pwd(const QString &db_user_pwd);

    void set_db_connection_options(const QString &db_connection_options);

    static inline QString db_type()
    {
        return _db_type;
    }

    static inline QString db_name()
    {
        return _db_name;
    }

    static inline QString db_ip_address()
    {
        return _db_ip_address;
    }

    static inline QString db_user_name()
    {
        return _db_user_name;
    }

    static inline QString db_user_pwd()
    {
        return _db_user_pwd;
    }

    static inline QString db_connection_options()
    {
        return _db_connection_options;
    }

private:

    QSqlDatabase _database;

    static QString _db_type;
    static QString _db_name;
    static QString _db_ip_address;
    static QString _db_user_name;
    static QString _db_user_pwd;
    static QString _db_connection_options;

    static const QString MYSQL;
};

#endif /* SRC_UTILS_YEROTH_DATABASE_HPP_ */
