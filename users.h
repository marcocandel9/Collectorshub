#ifndef USERS_H
#define USERS_H
#include "user.h"

struct users{
    user user_elem;
    collections collections_list_head;
    struct users* next;
};

typedef struct users* users;

//Crea una nuova lista utenti vuota
int create_users_list(users* users_list_head);

//Inserisce un nuovo utente con algoritmo di inserimento ordinato alfabeticamente, associando lui una nuova lista collezioni
int insert_user_sorted(users* users_list_head, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN], user_role new_user_role); 

//Aggiunge una nuova lista collezioni vuota associata ad un utente
int insert_user_collections(users* users_list_head, collections new_collections_list);

//Cerca un user da eliminare dalla lista e lo rimuove
int remove_user(users* users_list_head, char key_username[MAX_STR_LEN]);

//Cerca e modifica le credenziali di un user
int search_and_modify_user(users* users_list_head, char key_username[MAX_STR_LEN]);

int free_users(users* users_list_head);

#endif