
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <mysql/mysql.h>

#include "db.h"
#include "../model/trpdb.h"

void print_stmt_error (MYSQL_STMT *stmt, char *message)
{
	fprintf (stderr, "%s\n", message);
	if (stmt != NULL) {
		fprintf (stderr, "Error %u (%s): %s\n",
			 mysql_stmt_errno (stmt),
			 mysql_stmt_sqlstate(stmt),
			 mysql_stmt_error (stmt));
	}
}

void print_error(MYSQL *conn, char *message)
{
	fprintf (stderr, "%s\n", message);
	if (conn != NULL) {
#if MYSQL_VERSION_ID >= 40101
		fprintf (stderr, "Error %u (%s): %s\n",
			 mysql_errno (conn), mysql_sqlstate(conn), mysql_error (conn));
#else
		fprintf (stderr, "Error %u: %s\n",
		mysql_errno (conn), mysql_error (conn));
#endif
	}
}


bool setup_prepared_stmt(MYSQL_STMT **stmt, char *statement, MYSQL *conn)
{   
	bool update_length = true;

	*stmt = mysql_stmt_init(conn);
	if (*stmt == NULL)
	{
		print_error(conn, "Could not initialize statement handler");
		return false;
	}

	if (mysql_stmt_prepare (*stmt, statement, strlen(statement)) != 0) {
		print_stmt_error(*stmt, "Could not prepare statement");
		return false;
	}
	
	mysql_stmt_attr_set(*stmt, STMT_ATTR_UPDATE_MAX_LENGTH, &update_length);

	return true;
}

void finish_with_error(MYSQL *conn, char *message)
{
	print_error(conn, message);
	mysql_close(conn);
	exit(EXIT_FAILURE);
}

void finish_with_stmt_error(MYSQL *conn, MYSQL_STMT *stmt, char *message, bool close_stmt)
{
	print_stmt_error(stmt, message);
	if(close_stmt)
		mysql_stmt_close(stmt);
	mysql_close(conn);
	exit(EXIT_FAILURE);
}


void set_binding_param(MYSQL_BIND *param, enum enum_field_types type, void *buffer, unsigned long len)
{
	memset(param, 0, sizeof(*param));

	param->buffer_type = type;
	param->buffer = buffer;
	param->buffer_length = len;
}


void date_to_mysql_time(char *str, MYSQL_TIME *time)
{
	memset(time, 0, sizeof(*time));
	sscanf(str, "%4d-%2d-%2d", &time->year, &time->month, &time->day);
	time->time_type = MYSQL_TIMESTAMP_DATE;
}


void time_to_mysql_time(char *str, MYSQL_TIME *time)
{
	memset(time, 0, sizeof(*time));
	sscanf(str, "%02d:%02d", &time->hour, &time->minute);
	time->time_type = MYSQL_TIMESTAMP_TIME;
}

void init_mysql_timestamp(MYSQL_TIME *time)
{
	memset(time, 0, sizeof (*time));
	time->time_type = MYSQL_TIMESTAMP_DATETIME;
}

void init_mysql_date(MYSQL_TIME *time)
{
	memset(time, 0, sizeof (*time));
	time->time_type = MYSQL_TIMESTAMP_DATE;
}


void mysql_timestamp_to_string(MYSQL_TIME *time, char *str)
{
	snprintf(str, DATETIME_LEN, "%4d-%02d-%02d %02d:%02d", time->year, time->month, time->day, time->hour, time->minute);
}

void mysql_time_to_string(MYSQL_TIME *time, char *str)
{
	snprintf(str, TIME_LEN, "%02d:%02d", time->hour, time->minute);
}

void mysql_date_to_string(MYSQL_TIME *date, char *str)
{
	snprintf(str, DATE_LEN, "%4d-%02d-%02d", date->year, date->month, date->day);
}

int exe_proc(MYSQL_STMT *procedure,  char * buff){

if(mysql_stmt_execute(procedure) != 0) {
		printf("Procedura : %s \n", buff);
		print_stmt_error(procedure, "\nImpossibile eseguire execute ");
		return -1;
	}
	return 0; 
}

size_t bind_exe(MYSQL_STMT *procedure, MYSQL_BIND *param, char * buff)
{

if(mysql_stmt_bind_param(procedure, param) != 0) {
		printf("Procedura : %s \n", buff);
		print_stmt_error(procedure, "\nImpossibile eseguire bind param");
		return-1;
	}
	if(mysql_stmt_execute(procedure) != 0) {
		printf("Procedura : %s \n", buff);
		print_stmt_error(procedure, "\nImpossibile eseguire execute ");
		return -1;
	}

	return 0;
}

int take_result(MYSQL_STMT *procedure, MYSQL_BIND *param, char *buff)
{ 	
	int status; 
 
	if(mysql_stmt_bind_result(procedure, param)!=0) {
		printf("Procedura : %s ",buff);
		print_stmt_error(procedure, "\n\n Impossibile eseguire il bind result\n\n");
		return -1; 
	}
	
	
	if( mysql_stmt_store_result(procedure) != 0){
		printf("Procedura : %s", buff); 
		print_stmt_error(procedure, "\nImpossibile eseguire store result");
		return -1;
	}

	while (true) {
		status = mysql_stmt_fetch(procedure);
		if (status == MYSQL_NO_DATA)
			break; 
		if (status == 1 ){
			printf("Procedura : %s", buff);
			print_stmt_error(procedure, "\nImpossibile eseguire fetch ");
			return -1;
			}
	}
	return mysql_stmt_num_rows(procedure);
}

size_t take_rows(MYSQL_STMT *procedure, char *buff)
{
	if(mysql_stmt_execute(procedure) != 0) {
		printf("Procedura : %s", buff);
		print_stmt_error(procedure, " \nImpossibile eseguire execute "); 
		return -1; 
	}
		
	if( mysql_stmt_store_result(procedure) != 0){
		printf("Procedura : %s", buff);
		print_stmt_error(procedure, "\nImpossibile eseguire store result");
		return -1; 
	}
	return mysql_stmt_num_rows(procedure);
}
