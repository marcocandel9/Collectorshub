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
    int user_choose_result = 0;
    
    //WHILE LOOP DEL MENU UTENTE
    while(1){
        
        user_chosen_action = user_menu();

        switch(user_chosen_action){
     
            //CASE 1: ACCESSO AL MENU COLLEZIONI
            case 1:
                user_choose_result = sys_access_user_collection(*user, collection);
                switch(user_choose_result){
                    //L'utente ha annullato l'operazione, torno al menu utenti
                    case 1:
                        //resetto il risultato della scelta per coerenza della logica
                        user_choose_result = 0;
                        //faccio ripartire il ciclo while
                        continue;

                    //errore di lettura del buffer di input
                    case 2:
                        return -1;
                        
                    //lista delle collezioni vuota, riparte il ciclo while
                    case 3:
                        continue;

                    //errore durante l'accesso alla memoria (errore logico dati, lista inconsistente)
                    case 4:
                        return -1;

                    //accesso eseguito correttamente
                    default:
                        //ACCESSO ALLA COLLEZIONE RIUSCITO
                        return 1;
                    }
                break;

            //CASE 2: MODIFICA CREDENZIALI                    
            case 2:
                user_choose_result = sys_modify_credentials(user,users_list);
                switch(user_choose_result){
                    //L'utente ha annullato l'operazione, torno al menu utenti
                    case 1:
                        //resetto il risultato della scelta per coerenza della logica
                        user_choose_result = 0;
                        //faccio ripartire il ciclo while
                        continue;
                            
                    //errore di lettura del buffer di input
                    case 2:
                        return -1; 
                    case 3:
                        return -1;
                            
                    default:
                        user_choose_result = 0;
                        //Credenziali modificate correttamente, torno al menu utenti
                        continue;
                    }
                break;
            
            //CASO 3: CANCELLAZIONE DELL'UTENTE
            case 3:
                char username[MAX_STR_LEN] = "";
                get_username(*user,username);
                user_choose_result = sys_delete_user(users_list,username);
                switch(user_choose_result){
                    //l'utente ha annullato l'operazione, torno al menu utenti
                    case 1:
                        user_choose_result = 0;
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
                user_choose_result = sys_access_admin_menu(*user, users_list);
                switch(user_choose_result){

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
        }

    }
}




