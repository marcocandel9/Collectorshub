#ifndef SESSION_H
#define SESSION_H
#include "system.h"
#include "system_admin.h"

int login_menu_session(user* user, users* users_list);

int user_menu_session(user* user, users* users_list, collection* collection, collections* collections);

#endif
