#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

/*  User Authentication - NBMP  */

#include "myheaders.h"
#include <mysql.h>

typedef class DB_CONN{
    private:
        MYSQL *db_conn;
        string con_stat, error_stat;
        /*  User Details  */
        char USER_q_buff[BUFF_SIZE], PASS_q_buff[BUFF_SIZE], REG_q_buff[BUFF_SIZE];
        int user_flag, pass_flag;
        MYSQL_RES *user_res, *pass_res;
        MYSQL_ROW user_row, pass_row;

        /*  Budget Management  */
        char BUD_q_buff[BUFF_SIZE];
        MYSQL_RES *common_res;
        MYSQL_ROW breakup_row;

    public:
        DB_CONN(char _db[]){

            char _host[] = "localhost", _user[] = "root", _pass[] = "DBMS#8848";

            db_conn = mysql_init(NULL);

            if(db_conn)
            {
                db_conn = mysql_real_connect(db_conn, _host, _user, _pass, _db, 3306, NULL, 0);
                con_stat = (db_conn) ? "[ STATUS : Database Connection Successful ]" : "[ STATUS : Database Connection Failed     ]";
            }
            mysql_query(db_conn, "CREATE TABLE IF NOT EXISTS `users` (FNAME VARCHAR(15), LNAME VARCHAR(15), MOBILE VARCHAR(11) NOT NULL UNIQUE, EMAIL VARCHAR(30), USERNAME VARCHAR(20) NOT NULL PRIMARY KEY, PASSWORD VARCHAR(20))");
        }
        MYSQL *conn_id(){   return db_conn;  }

        string ConnectionStatus(){  return con_stat; }

        const char* UserRegistration(char[15], char[15], char[11], char[25], char[20], char[20]);

        int UsernameAuthentication(char[20]), PasswordAuthentication(char[20], char[20]);

        float* BreakupfromDB(int year);
}db_con;

int DB_CONN::UsernameAuthentication(char protected_user[20])
{
    snprintf(USER_q_buff, sizeof(USER_q_buff), "SELECT `username` FROM `users`");

    mysql_query(db_conn, USER_q_buff);

    user_res = mysql_store_result(db_conn);

    while((user_row = mysql_fetch_row(user_res)))

        if(strcmp(protected_user, *user_row) == 0)
        {
            user_flag = 1;
            return 1;
        }
    user_flag = 0;
    mysql_free_result(user_res);

    return 0;
}

int DB_CONN::PasswordAuthentication(char fuser[20], char fpass[20])    // from frontend
{
    /*
        0   -   Username Unmatched
        1   -   Username Matched & Password Unmatched
        2   -   Username & Password Matched
    */
    UsernameAuthentication(fuser);
    if(user_flag)
    {
        snprintf(PASS_q_buff, sizeof(PASS_q_buff), "SELECT `password` FROM `users` WHERE `username` = '%s'", fuser);

        mysql_query(db_conn, PASS_q_buff);

        pass_row = mysql_fetch_row(pass_res = mysql_store_result(db_conn));

        if(strcmp(fpass, *pass_row) == 0) pass_flag = 1;

        mysql_free_result(pass_res);

        return (pass_flag)  ?   2 : 1;
    }
    return 0;
}

const char* DB_CONN::UserRegistration(char fname[15], char lname[15], char mobile[11], char email[25], char username[20], char password[20])
{
    snprintf(REG_q_buff, sizeof(REG_q_buff), "INSERT INTO `users` VALUES ('%s', '%s', '%s', '%s', '%s', '%s')", fname, lname, mobile, email, username, password);

    int status = mysql_query(db_conn, REG_q_buff);

    if(status != 0) {   error_stat = mysql_error(db_conn);  return "Failed";    }

    return "Successful";
}

float* DB_CONN::BreakupfromDB(int year = 2021)
{
    snprintf(BUD_q_buff, sizeof(BUD_q_buff), "SELECT healthcare, states, defence, education, budget FROM `bbreak` WHERE `year` = %d", year);

    int status = mysql_query(db_conn, BUD_q_buff);

    float *break_val_fromDB = (float *)calloc(5, sizeof(float));

    common_res = mysql_store_result(db_conn);

    breakup_row = mysql_fetch_row(common_res);

    for(int i = 0; i < mysql_num_fields(common_res); i++)   break_val_fromDB[i] = atof(breakup_row[i]);

    mysql_free_result(common_res);

    return break_val_fromDB;
}

db_con Implicit("vishal");

#endif // VALIDATION_H_INCLUDED
