#include "session.h"




    

/*
Gestisce la sessione del menu di login, permettendo all'utente di effettuare il login, registrarsi o uscire dal programma.

Parametri:
- user: puntatore all'utente che effettua l'accesso (verrà aggiornato all'interno della funzione)
- users_list: lista degli utenti registrati

Restituisce:
- 0 se il login o la registrazione ha avuto successo
- 1 se l'utente vuole uscire dal programma
*/
int login_menu_session(user* user, users* users_list){

    int login_chosen_action = 0;

    while(1){

        login_chosen_action = login_menu();

        switch(login_chosen_action){

            //Scelta 1: LOGIN
            case 1:
                *user = sys_login_user(users_list);
                
                //Login fallito o annullato:
                if(*user == NULL){
                    //ritorno al menu login
                    continue; 
                }

                //Login eseguito correttamente:
                return 0;
            
            case 2:

                *user = sys_register_user(users_list);

                //Registrazione fallita:
                if(*user == NULL){
                    //ritorno al menu login
                    continue; 
                }

                //registrazione effettuata correttamente
                return 0;

            case 3:
                //voglio uscire
                return 1;

        }
    }
}



/*

Restituisce: 
    -1 in caso di errori critici (programma deve arrestarsi)
    1 in caso di accesso alla collezione
    2 in caso di eliminazione dell'utente (torno al menu login)
    3 In caso di accesso al menu admin effettuato con successo
    4 in caso di logout (torno al menu login)

*/
int user_menu_session(user* user, users* users_list, collection* collection, collections* collections){
    
    int user_chosen_action = 0;
    int user_choice_result = 0;
    
    //WHILE LOOP DEL MENU UTENTE
    while(1){
        
        user_chosen_action = user_menu();

        switch(user_chosen_action){
     
            //CASE 1: ACCESSO AL MENU COLLEZIONI
            case 1:
                return 1;

            //CASE 2: MODIFICA CREDENZIALI                    
            case 2:
                user_choice_result = sys_modify_credentials(user,users_list);
                switch(user_choice_result){
                    //L'utente ha annullato l'operazione, torno al menu utenti
                    case 1:
                        //resetto il risultato della scelta per coerenza della logica
                        user_choice_result = 0;
                        //faccio ripartire il ciclo while
                        continue;
                            
                    //errore di lettura del buffer di input
                    case 2:
                        return -1; 
                    case 3:
                        return -1;
                            
                    default:
                        user_choice_result = 0;
                        //Credenziali modificate correttamente, torno al menu utenti
                        continue;
                    }
                break;
            
            //CASO 3: CANCELLAZIONE DELL'UTENTE
            case 3:
                char username[MAX_STR_LEN] = "";
                get_username(*user,username);
                user_choice_result = sys_delete_user(users_list,username);
                switch(user_choice_result){
                    //l'utente ha annullato l'operazione, torno al menu utenti
                    case 1:
                        user_choice_result = 0;
                        continue;
                    //errore di lettura del buffer in input
                    case 2:
                        return -1;
                    //lista inconsistente
                    case 3:
                        return -1;
                    default:
                        //esco dalla funzione restituendo 2 (UTENTE ELIMINATO, DEVO TORNARE AL MENU LOGIN)
                        return 2;
                }
            
            
            case 4:
                user_choice_result = sys_access_admin_menu(*user, users_list);
                switch(user_choice_result){

                    //caso 1: l'utente annulla l'operazione
                    case 1:
                        //torno al menu utenti
                        continue;
                    //caso 2: errore di lettura buffer di input
                    case 2:
                        return -1;
                    //caso 4: errore critico utilizzo funzione di promozione di users.h
                    case 4:
                        return -1;
                    case 0:
                        //restituisco 3, devo entrare nel menu admin
                        return 3;
                }
            
            //effettuo il logout
            case 5:
                return 4;
            case 6: // [PANORAMICA UTENTE]
                int result = sys_user_overview(*user);
                if (result == 2) return -1; //errore critico
                continue; //altrimenti torno al menu utenti dopo aver stampato
        }

    }
}





/*
Gestisce la sessione del menu collezioni per l’utente attualmente loggato.

La funzione presenta all’utente il menu collezioni e gestisce le diverse operazioni possibili:
- Visualizzazione delle collezioni
- Accesso a una collezione (per entrare nel menu prodotti)
- Modifica nome o tipologia di una collezione
- Eliminazione singola o completa delle collezioni
- Ritorno al menu utente

Parametri:
- user: puntatore all’utente loggato
- users_list: puntatore alla lista utenti (non usata direttamente qui, ma utile per coerenza e possibili estensioni)

Valori di ritorno:
- -1 → errore critico (es. lettura fallita, struttura dati incoerente)
-  2 → accesso a una collezione richiesto (prosegue al menu prodotti)
-  4 → eliminazione singola collezione eseguita con successo (torna al menu utente)
-  5 → eliminazione di tutte le collezioni eseguita (torna al menu utente)
-  6 → l’utente ha scelto di tornare al menu utente

Note:
- Le funzioni I/O collegate sono: sys_print_user_collections, sys_modify_collection, sys_delete_collection, sys_delete_collections, sys_access_user_collection.
*/
int collection_menu_session(user* user,  collection* collection){

    int user_chosen_action = 0;
    int user_choice_result = 0;

    //WHILE LOOP DEL MENU COLLEZIONI
    while(1){
        
        user_choice_result = 0; //Inizializzazione difensiva a 0 delle variabile di risultato della scelta dell'utente (superflua ma per sicurezza inserita)

        user_chosen_action = collection_menu();

        switch(user_chosen_action){
            //L'utente desidera visualizzare le proprie collezioni
            case 1:
                user_choice_result = sys_print_user_collections(*user);
                user_choice_result = 0;
                continue; //torno al menu collezioni
            //CASO 2: L'UTENTE DESIDERA ACCEDERE AD UNA COLLEZIONE (E Quindi al menu prodotti)
            case 2:
                user_choice_result = sys_access_user_collection(*user, collection);
                if(user_choice_result == 1) return 1;
                if(user_choice_result == 2 || user_choice_result == 4 || user_choice_result == 3) return -1; 
                return 2; //altrimenti devo accedere al menu prodotti
              
            //CASO 3: L'utente desidera creare una nuova collezione
            case 3:
                user_choice_result = sys_insert_collection(*user);

                switch(user_choice_result){
                    
                    //Caso 3.1 : l'utente vuole annullare l'operazione, ritorno al menu collezioni
                    case 1:
                        continue;
                    
                    //caso 3.2 : errore di lettura del buffer di input
                    case 2:
                        return -1;

                    //caso 3.4 : lista inconsistente, errore critico
                    case 4:
                        return -1;

                    //caso 0: Collezione aggiunta con successo. Torno al menu collezioni
                    default:
                        continue;
                }

            //CASO 4: L'utente desidera modificare il nome/tipologia di una collezione
            case 4:
                user_choice_result = sys_modify_collection(*user);

                switch(user_choice_result){
                    
                    //Caso 3.1 : l'utente vuole annullare l'operazione, ritorno al menu collezioni
                    case 1:
                        continue;
                    
                    //caso 3.2 : errore di lettura del buffer di input
                    case 2:
                        return -1;
                    
                    //Caso 3.3 : lista inconsistente, errore critico
                    case 3:
                        return -1;

                    //caso 3.4 : lista inconsistente, errore critico
                    case 4:
                        return -1;

                    //caso 0: modifica effettuata con successo. Torno al menu collezioni
                    default:
                        continue;
                }

            //CASO 5: L'utente desidera cancellare una collezione
            case 5:
                user_choice_result = sys_delete_collection(*user);
                switch(user_choice_result){
                    
                    //Caso 3.1 : l'utente vuole annullare l'operazione, ritorno al menu collezioni
                    case 1:
                        continue;
                    
                    //caso 3.2 : errore di lettura del buffer di input
                    case 2:
                        return -1;
                    
                    //Caso 3.3 : lista inconsistente, errore critico
                    case 3:
                        return -1;

                    //caso 3.4 : lista inconsistente, errore critico
                    case 4:
                        return -1;

                    //caso 0: eliminazione effettuata con successo. Torno al menu UTENTE
                    default:
                        return 4;
                }                
            
            //CASO 6: L'utente desidera eliminare tutte le sue collezioni
            case 6:
                user_choice_result = sys_delete_collections(*user);
                switch(user_choice_result){
                    
                    //Caso 3.1 : l'utente vuole annullare l'operazione, ritorno al menu collezioni
                    case 1:
                        continue;
                    
                    //caso 3.2 : errore di lettura del buffer di input
                    case 2:
                        return -1;
                    
                    //Caso 3.3 : lista inconsistente, errore critico
                    case 3:
                        return -1;

                    //caso 3.4 : lista inconsistente, errore critico
                    case 4:
                        return -1;

                    //caso 0: eliminazione effettuata con successo. Torno al menu UTENTE
                    default:
                        return 5;
                }

            //CASO 7: L'utente vuole tornare al menu utenti
            case 7:
                return 6;
        }
    }
}



/*
Gestisce la sessione del menu admin, permettendo all’amministratore di:

- Visualizzare la lista degli utenti
- Eliminare un utente
- Promuovere un utente base ad admin
- Accedere al menu collezioni
- Effettuare il logout

Parametri:
- user: puntatore all’utente attualmente loggato con privilegi admin
- users_list: puntatore alla lista completa degli utenti
- collection: puntatore alla collezione selezionata (in caso di accesso al menu collezioni)

Restituisce:
- -1 in caso di errore critico
-  4 in caso di accesso al menu collezioni
-  5 in caso di logout
*/
int admin_menu_session(user* user, users* users_list, collection* collection){

    int user_chosen_action = 0;
    int user_choice_result = 0;

    //WHILE LOOP DEL MENU ADMIN
    while(1){

        user_chosen_action = admin_menu();
        switch(user_chosen_action){
                //CASO 1: [VISUALIZZAZIONE LISTA UTENTI]
                case 1:
                    user_choice_result = sys_admin_print_users(*user, *users_list);
                    if(user_choice_result == 1 || user_choice_result == 2) return -1; //ERRORE CRITICO
                    //Altrimenti ritorno al menu admin
                    continue;
                //CASO 2: [CANCELLAZIONE UTENTE]
                case 2:
                    user_choice_result = sys_admin_delete_user(*user, users_list);
                    if(user_choice_result == 1 || user_choice_result == 2 || user_choice_result == 4) return -1; //ERRORE CRITICO
                    //ALTRIMENTI, sia nel caso di eliminazione avvenuta correttamente sia nel caso di annullamento da parte dell'utente, ritorno al menu admin
                    continue;
                //CASO 3: [PROMOZIONE AD ADMIN]
                case 3:
                    user_choice_result = sys_admin_promote_base_user(*user, users_list);
                    if(user_choice_result == 1 || user_choice_result == 2 || user_choice_result == 4) return -1; //ERRORE CRITICO
                    //ALTRIMENTI, sia nel caso di promozione avvenuta correttamente, sia nel caso di annullamento da parte dell'utente, ritorno al menu admin
                    continue;
                //CASO 4: [ACCESSO AL MENU COLLEZIONI]
                case 4:
                    return 4;
                //CASO 5: [LOGOUT]
                case 5:
                    return 5;
                default:
                    continue; //difensivo
                
        }
    }
}




/*
Gestisce la sessione del menu prodotti

Parametri:
- user: puntatore all’utente attualmente loggato con privilegi admin
- collection: puntatore alla collezione selezionata (in caso di accesso al menu collezioni)

Restituisce:
- -1 in caso di errore critico
-  6 in caso di accesso al menu collezioni
*/
int products_menu_session(user* user, collection* collection){

    int user_chosen_action = 0;
    int user_choice_result = 0;
    
    while(1){

        user_chosen_action = products_menu();

        switch(user_chosen_action){
            //CASO 1: [STAMPA DEI PRODOTTI DELLA COLLEZIONE]
            case 1:
                user_choice_result = sys_print_user_products(*user,*collection);
                if(user_choice_result ==  4) return -1; //errore critico
                continue; //altrimenti torno al menu prodotti facendo ripartire il ciclo while
            //CASO 2: [AGGIUNTA PRODOTTO ALLA COLLEZIONE]
            case 2:
                user_choice_result = sys_insert_user_product(*user,*collection);
                if(user_choice_result == 2 || user_choice_result == 4) return -1; //Errore critico
                continue; //altrimenti torno al menu prodotti sia in caso di annullamento sia in caso di aggiunta riuscita
            //CASO 3: [MODIFICA DI UN PRODOTTO]
            case 3:
                user_choice_result = sys_modify_user_product(*user,*collection);
                if(user_choice_result == 0 || user_choice_result == 1 || user_choice_result == 3) continue;
                return -1; //altrimenti ho un errore critico, restituisco -1
            //CASO 4: [CANCELLAZIONE DI UN PRODOTTO]
            case 4:
                user_choice_result = sys_delete_user_product(*user,*collection);
                if(user_choice_result == 0 || user_choice_result == 1 || user_choice_result == 3) continue;
                return -1; //Altrimenti ho un errore critico, restituisco -1
            //CASO 5: [ELIMINAZIONE DI TUTTI I PRODOTTI]
            case 5:
                user_choice_result = sys_delete_user_products(*user,*collection);
                if(user_choice_result == 0 || user_choice_result == 1 || user_choice_result == 3) continue;
                return -1; //Altrimenti ho un errore critico, restituisco -1
            case 6:
                *collection = NULL; //inizializzo a NULL il puntatore collezione (devo annullare l'accesso a questa collezione!)
                return 6; //desidero tornare al menu collezioni
        }
    }
}













