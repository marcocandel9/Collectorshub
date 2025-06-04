#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "session.h"

int main() {



    users users_list = NULL;
    user logged_user = NULL;
    collection collection = NULL;
    collections collections = NULL;

 

    int login_session_result = 0;
    int user_session_result = 1;
    
    while(1){
        login_session_result = login_menu_session(&(logged_user),&(users_list));
        if(login_session_result == 1){
            break;
        }
        user_session_result = user_menu_session(&(logged_user),&(users_list),&(collection), &(collections));

        switch(user_session_result){
            case 1:
                return 3; //WIP DEVO ENTRARE NEL MENU COLLEZIONI
            //Eliminazione utente, torno al menu login
            case 2:
                continue; 
            case 3:
                return 4; //WIP DEVO ENTRARE NEL MENU ADMIN
            
            //LOGOUT DEVO TORNARE AL MENU UTENTE
            case 4:
                continue;
        }
    }

    //WIP SALVATAGGIO
    return 0;

    
}