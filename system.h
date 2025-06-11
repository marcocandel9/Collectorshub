//Definisce la libreria per le funzioni che implementano l'input/output delle funzionalità della libreria users/user.h.
#ifndef SYSTEM_H
#define SYSTEM_H
#include "menu.h"
#include "users.h"

//////////////////////////////////////////////////////MENÙ UTENTE///////////////////////////////////////////////////////////////////


int sys_input_string_checker(char output_string[MAX_STR_LEN], bool check_space, int max_len, int min_len);

int ask_confirmation();



user sys_register_user(users* users_list_head);

user sys_login_user(users* users_list_head);


int sys_modify_password(char user_username[MAX_STR_LEN], char current_password[MAX_STR_LEN], users* users_list_head);

int sys_modify_credentials(user* my_user, users* users_list_head);

int sys_delete_user(users* users_list_head, char user_username[MAX_STR_LEN]);





//////////////////////////////////////////////////////MENÙ COLLEZIONI///////////////////////////////////////////////////////////////////


int sys_print_user_collections(user logged_user);

int sys_access_user_collection(user logged_user, collection* user_collection);

int sys_insert_collection(user logged_user);

int sys_modify_collection(user logged_user);

int sys_delete_collection(user logged_user);

int sys_delete_collections(user logged_user);

int sys_user_overview(user logged_user);


//////////////////////////////////////////////////////MENÙ PRODOTTI///////////////////////////////////////////////////////////////////
//N.B In queste funzioni il parametro di ingresso user sarebbe superfluo, ma lo passo comunque per aggiungere informazioni degli utenti per l'UI.

int sys_print_user_products(user logged_user, collection user_collection);

int sys_insert_user_product(user logged_user, collection user_collection);

int sys_modify_user_product(user logged_user, collection user_collection);

int sys_delete_user_product(user logged_user, collection user_collection);

int sys_delete_user_products(user logged_user, collection user_collection);



int save_users(users users_list, FILE* fp);
int save_collections(collections collections_list, FILE* fp);
int save_products(products products_list, FILE* fp);

int load_users(users* users_list_head, FILE* fp);
int load_collections(collections* collections_list_head, FILE* fp);
int load_products(products* products_list_head, FILE* fp);

int sys_save_files(users users_list_head);  // apre il file, chiama save_users
int sys_load_files(users* users_list_head); // apre il file, chiama load_users





int sys_access_admin_menu(user logged_user, users* users_list_head);

#endif