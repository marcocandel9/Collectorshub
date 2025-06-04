#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "session.h"

int main() {



    users users_list = NULL;
    user logged_user = NULL;
    collection collection = NULL;
    collections collections = NULL;
    
    //Inizio ciclo del programma: Accedo al menu login, se l'utente desidera uscira dal programma, esco dal ciclo while

    //Menu login (WHILE LOOP 1)
    while (1) {
        if (login_menu_session(&logged_user, &users_list) == 1)
            break;

        while (1) {
            int user_result = user_menu_session(&logged_user, &users_list, &collection, &collections);

            if (user_result == 3) {
                // TODO: admin_menu_session
                break;
            }

            if (user_result == 2 || user_result == 4)
                break; // eliminazione o logout

            while (1) {
                int collection_result = collection_menu_session(&logged_user, &collection);

                if (collection_result == -1)
                    return -1;
                if (collection_result == 2) {
                    // TODO: products_menu_session
                    continue;
                }
                if (collection_result == 4 || collection_result == 5 || collection_result == 6)
                    break;
            }
        }
    }


    //WIP SALVATAGGIO
    return 0;

    
}