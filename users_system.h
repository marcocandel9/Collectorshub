//Definisce la libreria per le funzioni che implementano l'input/output delle funzionalità della libreria users/user.h.
#ifndef USERS_SYSTEM_H
#define USERS_SYSTEM_H
#include "menu.h"
#include "users.h"



/*
Implementa l'I/O per la registrazione di un nuovo utente. Chiede in input da tastiera un nuovo username, controlla che questo username non sia già utilizzato (sia già presente nella lista utenti), controlla che la password sia valida secondo la logica dell'ADT
(utilizzando la funzione validate_password di user.h) e in caso di esito positivo richiama la funzione insert_user_sorted di users.h per inserire il nuovo utente nella struttura dati utenti, con algoritmo di inserimento ordinato alfabeticamente.
*/

user sys_register_user(users* users_list_head);

/*
Implementa l'I/O per il login di un utente. Chiede in input da tastera l'username utente, controlla che l'username sia esistente nella lista utenti, chiede la password dell'utente, controlla che la password sia valida
*/
user sys_login_user(users* users_list_head);


/*
Implementa l'I/O Per la SOLA modifica dell'username.
*/
int sys_modify_username(char current_username[MAX_STR_LEN], users* users_list_head);

/*
Implementa l'I/O Per la SOLA modifica della password.
*/
int sys_modify_password(char user_username[MAX_STR_LEN], char current_password[MAX_STR_LEN], users* users_list_head);

/*
Implementa l'I/O per la modifica credenziali di un utente.
*/
int sys_modify_credentials(user* my_user, users* users_list_head);


/*
Implementa l'I/O per l'eliminazione di un utente
*/
int sys_delete_user(users* users_list_head, char user_username[MAX_STR_LEN]);


//WIP
int sys_promote_user(users* users_list_head , user user_to_promote);


collections sys_view_user_collection(user logged_user);



#endif