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

    FILE *fptr = fopen("data.txt", "r");
    if (fptr == NULL) {
        printf("File non trovato, lo creo nuovo...\n");
        fptr = fopen("data.txt", "w");
        if (fptr == NULL) {
            perror("Impossibile creare il file");
            return -2;          /*errore critico: errore apertura file*/
        }   
    }

    printf("Caricamento dati in corso...\n");
    int load_res = load_users(fptr,&(users_list));

    switch (load_res) {
        case 1:
            printf("[ERRORE] Errore critico: apertura file o ftell fallito.\n");
            return -2;

        case 2:
            printf("[ERRORE] Struttura dati del file non valida (errore di parsing).\n");
            return -3;

        case 3:
            printf("Caricamento completato correttamente [Raggiunto EOF].\n");
            break;

        case 4:
            printf("[ERRORE] Allocazione dinamica fallita durante l’inserimento.\n");
            return -4;

        case 5:
            printf("[ERRORE] Dati corrotti nel file di input.\n");
            return -5;

        case 6:
            printf("[ERRORE] Struttura dati inconsistente.\n");
            return -6;

        default:
            printf("Caricamento completato.\n");
            break;
    }

    fclose(fptr);
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
    fptr = fopen("data.txt", "w");
    if (fptr == NULL) {
    perror("Errore nell'apertura del file");
    return -1;
    }

    printf("Salvataggio dati in corso...\n");
    int save_res = save_users(fptr,users_list);
    if(save_res == 1) return -1; /*errore critico: errore apertura file / funzioni ftell falliscono */
    fclose(fptr);
	free_users(&(users_list));

    printf("Salvataggio dati completato! Arrivederci.\n");
	return 0;

}
