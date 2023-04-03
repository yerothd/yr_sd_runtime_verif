/*
 * YR_CPP_MONITOR_ERP-database.cpp
 *
 *      Author: Dr.-Ing. Xavier Noumbissi Noundou
 */

#include "YR_CPP_MONITOR_ERP-database.hpp"


const QString YR_CPP_MONITOR_ERP_database::MYSQL("MySQL");


QString YR_CPP_MONITOR_ERP_database::_db_type("");

QString YR_CPP_MONITOR_ERP_database::_db_name("");

QString YR_CPP_MONITOR_ERP_database::_db_ip_address("");

QString YR_CPP_MONITOR_ERP_database::_db_user_name("");

QString YR_CPP_MONITOR_ERP_database::_db_user_pwd("");

QString YR_CPP_MONITOR_ERP_database::_db_connection_options("");


YR_CPP_MONITOR_ERP_database::YR_CPP_MONITOR_ERP_database()
{
    set_db_name(YR_CPP_MONITOR_ERP_database::_db_name);
    set_db_ip_address(YR_CPP_MONITOR_ERP_database::_db_ip_address);
    set_db_user_name(YR_CPP_MONITOR_ERP_database::_db_user_name);
    set_db_user_pwd(YR_CPP_MONITOR_ERP_database::_db_user_pwd);
    set_db_type(YR_CPP_MONITOR_ERP_database::_db_type);
    set_db_connection_options(YR_CPP_MONITOR_ERP_database::
                              _db_connection_options);

    if (YR_CPP_UTILS::
            isEqualCaseInsensitive(YR_CPP_MONITOR_ERP_database::MYSQL,
                                   YR_CPP_MONITOR_ERP_database::_db_type))
    {
        //logger << "++ main(): QMYSQL" << "\n";
        _database = QSqlDatabase::addDatabase("QMYSQL");
    }

    _database.setDatabaseName(_db_name);
    _database.setHostName(_db_ip_address);
    _database.setUserName(_db_user_name);
    _database.setPassword(_db_user_pwd);
    _database.setConnectOptions(_db_connection_options);
}


void YR_CPP_MONITOR_ERP_database::set_db_name(const QString &db_name)
{
    _db_name = db_name;
    _database.setDatabaseName(_db_name);
}


void YR_CPP_MONITOR_ERP_database::set_db_ip_address(const QString &db_ip_address)
{
    _db_ip_address = db_ip_address;
    _database.setHostName(_db_ip_address);
}


void YR_CPP_MONITOR_ERP_database::set_db_user_name(const QString &db_user_name)
{
    _db_user_name = db_user_name;
    _database.setUserName(_db_user_name);
}


void YR_CPP_MONITOR_ERP_database::set_db_user_pwd(const QString &db_user_pwd)
{
    _db_user_pwd = db_user_pwd;
    _database.setPassword(_db_user_pwd);
}


void YR_CPP_MONITOR_ERP_database::set_db_connection_options(const QString &
                                                            db_connection_options)
{
    _db_connection_options = db_connection_options;
    _database.setConnectOptions(_db_connection_options);

}


QString YR_CPP_MONITOR_ERP_database::toString()
{
    QString ret;

    if (_database.isValid())
    {
        ret.append(QString("db_type: %1\n"
                           "db_name: %2\n"
                           "db_ip_address: %3\n"
                           "db_connection_options: %4").arg(_db_type,
                                                            _database.
                                                            databaseName(),
                                                            _database.
                                                            hostName(),
                                                            _database.
                                                            connectOptions
                                                            ()));
    }
    else
    {
        ret.append(QString("db_type: %1\n"
                           "db_name: %2\n"
                           "db_ip_address: %3\n"
                           "db_connection_options: %4").arg(_db_type,
                                                            YR_CPP_MONITOR_ERP_database::
                                                            _db_name,
                                                            YR_CPP_MONITOR_ERP_database::
                                                            _db_ip_address,
                                                            YR_CPP_MONITOR_ERP_database::
                                                            _db_connection_options));
    }

    return ret;
}
