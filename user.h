#ifndef USER_H
#define USER_H
#include "collections.h"
#include <stdbool.h>
//Permette di utilizzare un set di funzioni che permette di verificare la natura di un carattere (es: se è upper o lower case...)
#include <ctype.h>        


struct user{
    char username[MAX_STR_LEN];
    char password[MAX_STR_LEN];
};

typedef struct user* user;

int create_user(user* new_user, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN]);

int validate_password(char password[MAX_STR_LEN]);

int modify_credentials(user my_user, char my_username[MAX_STR_LEN], char my_password[MAX_STR_LEN]);

int get_username(user my_user, char my_username[MAX_STR_LEN]);

int get_password(user my_user, char my_password[MAX_STR_LEN]);

int set_username(user my_user, char new_username[MAX_STR_LEN]);

int set_password(user my_user, char new_password[MAX_STR_LEN]);

int save_credentials(user my_user);

#endif