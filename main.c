#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "session.h"

int main() {



    users users_list = NULL;
    user logged_user = NULL;
    collection collection = NULL;
    collections collections = NULL;
    product product = NULL;
    products products = NULL;

    bool force_logout = false;
    
    //Inizio ciclo del programma: Accedo al menu login, se l'utente desidera uscira dal programma, esco dal ciclo while

    //Menu login (WHILE LOOP 1)
    while (1) {
        force_logout = false;

        if (login_menu_session(&logged_user, &users_list) == 1) break;

        while (1) {
            int user_result = user_menu_session(&logged_user, &users_list, &collection, &collections);

            if (user_result == 3) {
                int admin_result = admin_menu_session(&(logged_user),&(users_list),&(collection));
                
                if(admin_result == -1)  //Errore critico
                    return -1;
                //if(admin_result == 1)   //Accedo al menu collezioni ( NON DEVO FARE NULLA PER ACCEDERCI, CI ANDRÀ IN AUTOMATICO. LASCIO L'IF COMMENTATO PER CHIAREZZA.)
                
                if(admin_result == 5){  //Forzo il logout per evitare di entrare nel menu collezioni
                    force_logout = true;
                }
            }

            if (user_result == 2 || user_result == 4 || force_logout == true)
                break; // eliminazione o logout

            while (1) {
                int collection_result = collection_menu_session(&logged_user, &collection);
                
                if (collection_result == -1)
                    return -1;
                if (collection_result == 2) { //Accedo al menu prodotti
                    int product_result = products_menu_session(&(logged_user),&(collection));
                    if(product_result == -1) return -1; //errore critico
                    if(product_result == 6) continue; //Altrimenti voglio tornare al menu collezioni, faccio ripartire il ciclo while
                }
                if (collection_result == 4 || collection_result == 5 || collection_result == 6) break;
            }
        }
    }


    //WIP SALVATAGGIO
	free_users(&(users_list));
	return 0;

    
}
