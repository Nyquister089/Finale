#pragma once
#include <string.h>
#include <mysql/mysql.h>
#include <assert.h>

#include "../model/trpdb.h"

typedef enum{
	INFO_PRENOTAZIONI,
	INSERT_CLIENTE,
	INSERT_PRENOTAZIONE,
	CONFERMA_PRENOTAZIONE, 
	QUIT_HSST
} hstss_act;
 


extern void run_hstss_interface (void);
