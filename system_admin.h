#ifndef SYSTEM_ADMIN_H
#define SYSTEM_ADMIN_H
#include "system.h"



sys_admin_priviledge_checker(user logged_user);

sys_admin_print_users(users users_list_head);

sys_admin_delete_user(users* users_list_head, char key_username[MAX_STR_LEN]);

sys_admin_promote_base_user(users users_list_head, char key_username[MAX_STR_LEN]);




#endif