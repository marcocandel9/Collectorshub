#ifndef USER_H
#define USER_H
#include "collections.h"
#include <stdbool.h>
//Permette di utilizzare un set di funzioni che permette di verificare la natura di un carattere (es: se è upper o lower case...)
#include <ctype.h>        



/*definizione tipo di dato enum per il ruolo di ciascun utente
Un utente BASE (USER) può solo accedere al menù di base, menù nel quale sarà possibile:
- Creare e modificare le proprie collezioni
- Creare e modificare i propri prodotti per ciascuna collezione
- Modificare username e password 
- cancellare il proprio profilo utente

Un utente ADMIN può accedere al menù ADMIN, menù nel quale sarà possibile:
- Avere pieno controllo di tutti gli utenti (promozione ad admin o superuser, eliminazione)
- Cancellazione della lista collezioni di ciascun utente
- Cancellazione della lista prodotti di ciascuna collezione di ciascun utente

*/
typedef enum {
    USER,   //0
    ADMIN,  //1 
} user_role;



struct user{
    char username[MAX_STR_LEN];
    char password[MAX_STR_LEN];
    user_role role;
    collections collections_list_head;
};




typedef struct user* user;


int create_user(user* new_user, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN], user_role new_user_role);

int compare_user_privilege(user_role this_user_role, user_role that_user_role);

int validate_password(char password[MAX_STR_LEN]);

int set_username(user my_user, char new_username[MAX_STR_LEN]);

int set_password(user my_user, char new_password[MAX_STR_LEN]);

int set_user_role(user my_user, user_role new_user_role);

int insert_user_collections_list(user my_user, collections new_collections_list_head);

int modify_credentials(user my_user, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN]);

int get_username(user my_user, char my_username[MAX_STR_LEN]);

int get_password(user my_user, char my_password[MAX_STR_LEN]);

int get_user_role(user my_user, char my_user_role[MAX_STR_LEN]);

int role_checker(user my_user, user_role required_role);

int delete_user(user* my_user); 

int print_user(user my_user);



#endif