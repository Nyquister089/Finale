#pragma once
#include <stdbool.h>
#include <stdlib.h>	

#include "../utils/io.h"


extern bool init_db(void);
extern void fini_db(void);
							
#define DATE_LEN 11
#define TIME_LEN 6
#define DATETIME_LEN (DATE_LEN + TIME_LEN)
#define NUM_LEN 45
#define DEC_LEN 10
#define TEL_LEN 16 
#define TAR_LEN 10
#define BLOB_LEN 45
#define USERNAME_LEN 45
#define PASSWORD_LEN 8
#define PIC 45
#define BIT_LEN 2
#define VARCHAR_LEN 45
#define DES_LEN 5000



struct credentials {
	char username[USERNAME_LEN];
	char password[PASSWORD_LEN];
};

typedef enum {
	LOGIN_ROLE,
	AUTISTA,
	CLIENTE,
	HOSTESS,
	MECCANICO,
	MANAGER,
	QUIT,
	FAILED_LOGIN
} role_t;

extern void db_switch_to_login(void);
extern role_t attempt_login(struct credentials *cred);
extern void db_switch_to_administrator(void);

struct soggiorno{
	int  idsoggiorno; 
	int  cameraprenotata; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  ospite; 						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  albergoinquestione; 			//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  prenotazioneinquestione;
	char datainiziosoggiorno[DATE_LEN]; 
	char datafinesoggiorno[DATE_LEN];
}; 

struct camera {
	int numerocamera;
	int albergo;						//FK
	char tipologia[VARCHAR_LEN];
	float costo ;
};

struct cliente {
	char emailcliente[VARCHAR_LEN];
	char nomecliente[VARCHAR_LEN];
	char cognomecliente[VARCHAR_LEN];
	char indirizzocliente[VARCHAR_LEN];
	char codicefiscale[VARCHAR_LEN];
	char datadocumentazione[DATE_LEN];
	char recapitotelefonico[TEL_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char fax[TEL_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
};

struct comfort {
	int idcomfort; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomecomfort[VARCHAR_LEN]; 
	char descrizionecomfort[DES_LEN]; 

};

struct comfort_mezzo{
	size_t num_comfort; 
	struct comfort comfort_mezzo[]; 
};

struct competenze {
	char meccanicocompetente[VARCHAR_LEN]; 
	char modelloassociato[VARCHAR_LEN];
	// viariabili d'appoggio
	char nomemeccanico [VARCHAR_LEN]; 
	char telefono[TEL_LEN];
}; 

struct dipendente{
	char emaildipendente[VARCHAR_LEN]; 
	char tipologiadipendente[VARCHAR_LEN];
	char telefonoaziendale [TEL_LEN]; 
	char nomedipendente[VARCHAR_LEN];
	char cognomedipendente[VARCHAR_LEN];
};

struct documentazionefotografica {
	
	 int idfoto; 
	 char foto [BLOB_LEN]; 
	 char descrzione[DES_LEN]; 
	 
};

struct fmo{
	int foto; 
	char modello[VARCHAR_LEN]; 
	//
	char descrizione[DES_LEN];
	char immagine[BLOB_LEN];  
};

struct fme{
	int foto; 
	int meta; 
	//
	char nome[VARCHAR_LEN];
	char descrizione[DES_LEN]; 
	char immagine[BLOB_LEN];
}; 

struct foto_mete {
	size_t num_pic;
	struct documentazionefotografica foto_mete[]; 
}; 

struct localita {
	char nomelocalita[VARCHAR_LEN];
	char regione[VARCHAR_LEN];
	char stato[VARCHAR_LEN];
};

struct mappa {
	int idmappa; //Corretto trasformandolo da carattere a puntatore di carattere
	char citta[VARCHAR_LEN];
	char dettaglio[VARCHAR_LEN];
	char zona[VARCHAR_LEN];
	char immagine[BLOB_LEN]; 
	char localitarappresentata[VARCHAR_LEN]; 		//FK
};

struct meta { 
	int idmeta; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomemeta[VARCHAR_LEN]; 
	char emailmeta[VARCHAR_LEN]; 
	char telefonometa[TEL_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char faxmeta[TEL_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char indirizzo[VARCHAR_LEN]; 
	char tipologiameta[VARCHAR_LEN]; 
	char categoriaalbergo[VARCHAR_LEN]; 
	char orariodiapertura[TIME_LEN]; 
	char localitadiappartenenza[VARCHAR_LEN]; 		//FK
	char regiodiappartenennza[VARCHAR_LEN]; 
};

struct mete_viaggio{	
	size_t num_vme; 
	struct meta mete_viaggio[]; 
}; 

struct mezzo {
	char targa[TAR_LEN];
	char modellomezzo[VARCHAR_LEN]; 
	char dataultimarevisioneinmotorizzazione[DATE_LEN]; 					
	char ingombri[VARCHAR_LEN];	
	int autonomia; //Corretto trasformandolo da carattere a puntatore di carattere
	int valorecontakm; //Corretto trasformandolo da carattere a puntatore di carattere
	char dataimmatricolazione[DATE_LEN]; 
};

struct modello {
	char nomemodello[VARCHAR_LEN];
	char datitecnici[DES_LEN]; 
	char casacostruttrice[VARCHAR_LEN];
	int numeroposti; //Corretto trasformandolo da carattere a puntatore di carattere
	int numeromeccanicicompetenti; 
}; 

struct modelli_comfort {
	char casacostruttrice[VARCHAR_LEN];
	int numeroposti;
	char nomecomfort[VARCHAR_LEN]; 
	char descrizionecomfort[DES_LEN];
	char foto [PIC]; 
	char descrizionefoto[DES_LEN]; 
	int idfoto; 
}; 

struct info_modelli {
	size_t num_modelli; 
	struct modelli_comfort info_modelli[]; 
};

struct offre {
	int idservizio; 
	int albergoofferente; 					

	char servizio[VARCHAR_LEN]; 
	char meta [VARCHAR_LEN]; 
	char descrizione [DES_LEN]; 
}; 

struct postoprenotato {
	int numerodiposto; //Corretto trasformandolo da carattere a puntatore di carattere					//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	int prenotazioneassociata; 				//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	int etapasseggero;  //Corretto trasformandolo da carattere a puntatore di carattere
	char nomepasseggero[VARCHAR_LEN]; 
	char cognomepasseggero[VARCHAR_LEN]; 
}; 

struct prenotazione {
	int numerodiprenotazione;
	int viaggioassociato; 
	int numerodipostiprenotati; 
	char clienteprenotante[VARCHAR_LEN];
	char datadiprenotazione[DATE_LEN]; 
	char datadiconferma[DATE_LEN]; 
	char datasaldo[DATE_LEN]; 
}; 


struct prenotazioni_info{
	size_t num_prenotazioni; 
	struct prenotazione prenotazioni_info[]; 
};

struct presenti {
	int comfortpresenti; //Corretto trasformandolo da carattere a puntatore di carattere
	char modelloassciato[VARCHAR_LEN]; 
};

struct revisione {
	int idrevisione; //Corretto trasformandolo da carattere a puntatore di carattere
	char mezzorevisionato[VARCHAR_LEN]; 			// Fk
	char addettoallarevisione[VARCHAR_LEN];  				// Fk //Corretto trasformandolo da carattere a puntatore di carattere
	char datainizio[DATE_LEN]; 
	char datafine[DATE_LEN]; 
	int chilometraggio;//Corretto trasformandolo da carattere a puntatore di carattere
	char operazionieseguite[DES_LEN]; 
	char motivazione[DES_LEN]; 
};

struct revisioni_scadute {
	size_t num_revisione; 
	struct revisione revisioni_scadute [];
};

struct ricambio {
	char codice [VARCHAR_LEN]; 
	float costounitario; //Corretto trasformandolo da carattere a puntatore di carattere
	int quantitadiriordino; //Corretto trasformandolo da carattere a puntatore di carattere
	char descrizione[DES_LEN]; 
	int scortaminima; //Corretto trasformandolo da carattere a puntatore di carattere
	int quantitainmagazzino;  //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct rt {
	int  revisionerelativa; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  tagliandoassociato; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct servizio {
	int idservizio; 
	char nomeservizio[VARCHAR_LEN];
	char descrizioneservizio[DES_LEN]; 
}; 

struct  servizi_albergo{
	size_t num_servizi; 
	struct servizio servizi_albergo[]; 
};

struct sostituito{
	int revisioneassociata; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char ricambioutilizzato [VARCHAR_LEN]; 			//FK
	int quantitasostituita; 
}; 


struct tagliando {
	int idtagliando; //Corretto trasformandolo da carattere a puntatore di carattere
	char tipologiatagliando[VARCHAR_LEN]; 
	char validitasuperate[DES_LEN];
}; 


struct tour {
	char denominazionetour[VARCHAR_LEN]; 
	char descrizionetour[DES_LEN]; 
	int minimopartecipanti; //Corretto trasformandolo da carattere a puntatore di carattere
	float assicurazionemedica; //Corretto trasformandolo da carattere a puntatore di carattere
	float bagaglio; //Corretto trasformandolo da carattere a puntatore di carattere
	float garanziaannullamento; 
	signed char accompagnatrice; //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct viaggio {
	int idviaggio; //Corretto trasformandolo da carattere a puntatore di carattere
	char tourassociato[VARCHAR_LEN]; 
	char conducente [VARCHAR_LEN]; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char accompagnatrice[VARCHAR_LEN]; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char mezzoimpiegato[TAR_LEN]; 			// FK
	char datadipartenzaviaggio[DATE_LEN]; 
	char datadiritornoviaggio[DATE_LEN]; 
	float costodelviaggio;  //Corretto trasformandolo da carattere a puntatore di carattere
	int numerodikm; //Corretto trasformandolo da carattere a puntatore di carattere
	int postidisponibili; //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiannullamento[DATE_LEN]; 
};

struct tour_viaggi{
	char denominazionetour[VARCHAR_LEN]; 
	char descrizionetour[DES_LEN]; 
	int minimopartecipanti; //Corretto trasformandolo da carattere a puntatore di carattere
	float assicurazionemedica; //Corretto trasformandolo da carattere a puntatore di carattere
	float bagaglio; //Corretto trasformandolo da carattere a puntatore di carattere
	float garanziaannullamento; 
	signed char accompagnatrice;
	char nomemodello[VARCHAR_LEN];
	char datadipartenzaviaggio[DATETIME_LEN]; 
	char datadiritornoviaggio[DATETIME_LEN]; 
	float costodelviaggio;
	int postidisponibili;
	int codiceviaggio; 
}; 

struct tour_info{
	size_t num_tour; 
	struct tour_viaggi tour_info[]; 
}; 

struct utente {
	char email[VARCHAR_LEN];
	char pswrd[PASSWORD_LEN]; 
	int tipo;
};

struct visita {
	int idvisita;  //Corretto trasformandolo da carattere a puntatore di carattere
	int viaggiorelativo; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	int metavisitata; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiarrivo[DATE_LEN]; 
	char datadipartenza[DATE_LEN]; 
	char oradiarrivo[TIME_LEN]; 
	char oradipartenza[TIME_LEN]; 
	signed char guida; //Corretto trasformandolo da carattere a puntatore di carattere
	float supplemento; //Corretto trasformandolo da carattere a puntatore di carattere
	char trattamentoalberghiero[VARCHAR_LEN]; 
	//
	char tour [VARCHAR_LEN]; 
	char meta [VARCHAR_LEN]; 


}; 
struct mete_tour{
	char nome[VARCHAR_LEN];
	char darrivo[DATE_LEN];
	char oarrivo[TIME_LEN];
	char dpartenza[DATE_LEN];
   	char opartenza[TIME_LEN];
   	float supplemento;
	char desfoto[VARCHAR_LEN]; 
	char foto[BLOB_LEN]; 
	char tipologiameta[VARCHAR_LEN];
	signed char guida;
   	char oapertura[TIME_LEN];
   	char trattamento[VARCHAR_LEN];
	char categoriaalbergo[VARCHAR_LEN];
	int codicealbergo; 
}; 

struct info_mete{
	size_t num_mete; 
	struct mete_tour info_mete[]; 
};

struct viaggi_mezzi{
	char tour[VARCHAR_LEN];
	int viaggio; 
	char modello[VARCHAR_LEN];
	char targa[TAR_LEN];
	int autonomia; 
	char ingombri [VARCHAR_LEN]; 
	int contakm; 
	char partenza[DATE_LEN]; 
	char ritorno[DATE_LEN]; 
};

struct viaggi_assegnati{
	size_t num_viaggi; 
	struct viaggi_mezzi viaggi_assegnati[]; 
};

struct meta_visita{
	char nome [VARCHAR_LEN]; 
	char tipologia[VARCHAR_LEN]; 
	char localita[VARCHAR_LEN];
	char regione[VARCHAR_LEN]; 
	char indirizzo[VARCHAR_LEN]; 
	char arrivo[DATE_LEN];
	char ingresso[TIME_LEN]; 
	char partenza[DATE_LEN]; 
	char uscita[TIME_LEN]; 
};

struct mete_visite{
	size_t num_visite; 
	struct meta_visita mete_visite[]; 
};

struct mappa_autista{
	char citta[VARCHAR_LEN];
	char dettaglio[VARCHAR_LEN];
	char zona[VARCHAR_LEN];
	char immagine[VARCHAR_LEN];	
};

struct mappe{
	size_t num_mappe; 
	struct mappa_autista mappe[]; 
};

extern void do_insert_tour(struct tour *tour); 
extern void do_insert_trip(struct viaggio *viaggio); 
extern void do_insert_destination(struct meta *meta); 
extern void do_insert_visit(struct visita *visita); 
extern void do_insert_room(struct camera *camera); 
extern void do_insert_costumer(struct cliente *cliente);
extern void do_insert_costumer_user(struct utente *utente, struct cliente *cliente);
extern void do_insert_reservation(struct prenotazione *prenotazione);
extern void do_insert_seat(struct postoprenotato *postoprenotato);
extern void do_insert_stay(struct soggiorno *soggiorno);
extern void do_insert_review(struct revisione *revisione);
extern void do_insert_sostitution (struct sostituito *sostituito); 
extern void do_insert_location(struct localita *localita); 
extern void do_insert_map(struct mappa *mappa); 
extern void do_insert_picture(struct documentazionefotografica *documentazionefotografica); 
extern void do_insert_employee(struct dipendente *dipendente); 
extern void do_insert_user(struct utente *utente); 
extern void do_insert_offert(struct offre *offre); 
extern void do_insert_service(struct servizio *servizio); 
extern void do_insert_fmo(struct fmo *fmo); 
extern void do_insert_fme(struct fme *fme); 
extern void do_insert_model(struct modello * modello, struct competenze *competenze); 
extern void do_insert_bus(struct mezzo *mezzo); 
extern void do_insert_sparepart(struct ricambio *ricambio);
extern void do_insert_certify(struct tagliando *tagliando); 
extern void do_insert_comfort(struct comfort *comfort); 
extern void do_insert_skills(struct competenze *competenze); 
extern void do_insert_presents(struct presenti *presenti);
extern void do_insert_rt(struct rt *rt); 

extern int do_select_trip(struct viaggio *viaggio);
extern int do_select_costumer(struct cliente *cliente);
extern int do_select_reservation(struct prenotazione *prenotazione);
extern int do_select_tour( struct tour *tour);
extern int do_select_sparepart(struct ricambio *ricambio); 
extern int do_select_review(struct revisione *revisione);
extern int do_select_bus(struct mezzo *mezzo); 
extern int do_select_stay(struct soggiorno *soggiorno); 
extern int do_select_skills(struct competenze *competenze); 
extern int do_select_employee(struct dipendente* dipendente); 
extern int do_select_fmo(struct fmo *fmo); 
extern int do_select_fme(struct fme *fme);
extern int do_select_ofr(struct offre *offre);  
extern int do_select_user(struct utente *utente); 
extern int do_select_seat(struct postoprenotato *postoprenotato); 
extern int do_select_model(struct modello *modello); 
extern int do_select_certify(struct tagliando *tagliando);
extern int do_select_destination(struct meta *meta);  
extern int do_select_visit(struct visita *visita); 
extern int do_select_location(struct localita *localita);
extern int do_select_room(struct camera *camera); 
extern int do_select_map(struct mappa *mappa); 
extern int do_select_picture(struct documentazionefotografica *documentazionefotografica);
extern int do_select_comfort(struct comfort *comfort); 
extern int do_select_service(struct servizio *servizio); 
extern int do_select_sostitution(struct sostituito*sostituito); 
extern int do_select_presents(struct presenti *presenti);
extern int do_select_rt(struct rt *rt); 

extern void do_delete_trip(struct viaggio *viaggio);
extern void do_delete_costumer(struct cliente *cliente);
extern void do_delete_reservation(struct prenotazione *prenotazione);
extern void do_delete_tour( struct tour *tour);
extern void do_delete_sparepart(struct ricambio *ricambio); 
extern void do_delete_review(struct revisione *revisione);
extern void do_delete_bus(struct mezzo *mezzo); 
extern void do_delete_stay(struct soggiorno *soggiorno); 
extern void do_delete_skills(struct competenze *competenze); 
extern void do_delete_employee(struct dipendente* dipendente); 
extern void do_delete_fmo(struct fmo *fmo); 
extern void do_delete_fme(struct fme *fme);
extern void do_delete_ofr(struct offre *offre);  
extern void do_delete_user(struct utente *utente); 
extern void do_delete_seat(struct postoprenotato *postoprenotato); 
extern void do_delete_model(struct modello *modello); 
extern void do_delete_certify(struct tagliando *tagliando);
extern void do_delete_destination(struct meta *meta);  
extern void do_delete_visit(struct visita *visita); 
extern void do_delete_location(struct localita *localita);
extern void do_delete_room(struct camera *camera); 
extern void do_delete_map(struct mappa *mappa); 
extern void do_delete_picture(struct documentazionefotografica *documentazionefotografica);
extern void do_delete_comfort(struct comfort *comfort); 
extern void do_delete_service(struct servizio *servizio); 
extern void do_delete_sostitution(struct sostituito *sostituito); 
extern void do_delete_presents(struct presenti *presenti);
extern void do_delete_rt(struct rt *rt); 

extern void do_insert_sost_review(struct revisione *revisione, struct sostituito *sostituito ); 
extern void do_init_skill(struct competenze *competenze);

extern struct tour_info *get_tour_info (void);
extern struct info_mete *get_mete_info(int idv);
extern struct servizi_albergo *get_servizi_albergo(int idh); 
extern struct info_modelli *get_info_modello(char *nmd);
extern struct revisioni_scadute *get_info_revisioni(void); 
extern struct viaggi_assegnati *get_viaggi_assegnati(char *dvr);
extern struct mete_visite *get_mete_visite(int idv);
extern struct mappe *get_mappe(char* nml); 
extern struct prenotazioni_info *get_reservation_info (char *mlc); 

extern void do_update_user_type(struct utente *utente); 
extern void do_validate_reservation(struct prenotazione *prenotazione);
extern void do_update_spareparts_number(struct ricambio *ricambio); 
extern void do_update_km(struct mezzo *mezzo); 

