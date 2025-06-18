#ifndef USERS_H
#define USERS_H
#include "user.h"

struct users{
    user user_elem;
    struct users* next;
};

typedef struct users* users;

/*
Prende in ingresso il puntatore alla testa della lista utenti e lo inizializza a NULL

Restituisce 0
*/
int create_users_list(users* users_list_head);



/*
Inserisce un nuovo utente con algoritmo di inserimento ordinato alfabeticamente

Restituisce:
- 1 Se la password passata come parametro è non valida (Impossibile aggiungere l'utente)
- 2 Errore di allocazione del nuovo nodo
- 3 In caso di inserimento duplicato (NON CONSENTITO)
- 0 Se tutto va a buon fine
*/
int insert_user_sorted(users* users_list_head, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN], user_role new_user_role); 



/*
Inserisce una lista collezioni all'utente desiderato della lista utenti con INSERIMENTO ORDINATO ALFABETICO sulla base del NOME UTENTE

Prende in ingresso il puntatore alla lista utenti passato per riferimento, il nome dell'utente da ricercare in cui inserire la lista collezioni, il puntatore alla testa della lista collezioni da inserire

Restituisce:
- 1 In caso di lista utenti vuota
- 2 In caso di corrispondenza non trovata
- 0 Se tutto va a buon fine
*/
int insert_sorted_user_collections(users* users_list_head, char key_username[MAX_STR_LEN], collections new_collections_list);



/*
Cerca un utente nella lista utenti sulla base del suo username e restituisce 0 se è presente

Restituisce:
- 1 Se la lista utenti è vuota
- 2 Se non è stata trovata una corrispondenza
- 0 Se l'utente è stato trovato
*/
int user_exists(users users_list_head, char key_username[MAX_STR_LEN]);



/*
Cerca un utente nella lista utenti sulla base del suo username e ne restituisce un puntatore alla struct utente

Restituisce:
- 1 Se la lista utenti è vuota
- 2 Se non è stata trovata una corrispondenza
- 0 Se tutto va a buon fine e restituisce il parametro user my_user con il puntatore alla struct utente
*/
int search_user(users users_list_head, char key_username[MAX_STR_LEN], user* my_user);



/*
Cerca un user da eliminare dalla lista utenti e lo rimuove, deallocando gerarchicamente tutte le strutture dati a lui associate

Restituisce: 

- 1 Se la lista utenti è vuota (Puntatore a NULL)
- 2 Se la corrispondenza non è stata trovata
- 0 Se tutto va a buon fine
*/int remove_user(users* users_list_head, char key_username[MAX_STR_LEN]);



/*
Cerca un utente nella lista utenti con ordinamento alfabetico e ne modifica username,password e ruolo. 
Utilizza la funzione modify user che controlla anche la validità della password

Restituisce:
- 1 Se la lista utenti è vuota
- 2 Se non è stata trovata una corrispondenza
- 3 Utente non inizializzato (Improbabile)
- 4 Se la password non è valida
*/
int search_and_modify_user_credentials(users* users_list_head, char key_username[MAX_STR_LEN], char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN]);


int search_and_promote_user(users* users_list_head, char key_username[MAX_STR_LEN], user_role new_role);



/*
Libera l'intera lista utenti, deallocando completamente anche tutte le strutture dati gerarchicamente inferiori

Restituisce: 
- 1 Se la lista utenti è vuota
- 0 Se tutto va a buon fine
*/
int free_users(users* users_list_head);




/*
Stampa l'username ed il ruolo di ogni utente della lista utenti. 

Prende in ingresso il puntatore alla testa della lista passato come riferimento

Restituisce:
- 1 In casi di lista collezioni non valida o vuota
- 0 In caso di Successo
*/
int print_users(users users_list_head);


//FUNZIONI DI SALVATAGGIO E CARICAMENTO SU FILE

int save_users(FILE *fptr, users users_list_head);

int load_users(FILE *fptr, users* users_list);

#endif