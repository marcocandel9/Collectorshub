#ifndef SYSTEM_ADMIN_H
#define SYSTEM_ADMIN_H
#include "system.h"




int sys_admin_print_users(user logged_user, users users_list_head);

int sys_admin_delete_user(user logged_user, users* users_list_head);

int sys_admin_promote_base_user(user logged_user, users* users_list_head);





#endif