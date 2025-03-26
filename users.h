#ifndef USERS_H
#define USERS_H
#include "user.h"

struct users{
    user user_elem;
    collections collections_list_head;
};

typedef struct users* users;

//Crea una nuova lista utenti a partire dal primo utente
int create_users_list(users* users_list_head, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN]);

//Inserisce un nuovo utente con algoritmo di inserimento ordinato alfabeticamente 
int insert_user_sorted(users* users_list_head, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN]); 

//Cerca un user da eliminare dalla lista e lo rimuove
int remove_user(users* users_list_head, char key_username[MAX_STR_LEN]);

//Cerca e modifica le credenziali di un user
int search_and_modify_user(users* users_list_head, char key_username[MAX_STR_LEN]);

int free_users(users* users_list_head);

#endif