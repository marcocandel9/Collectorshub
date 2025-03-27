#include "users.h"


/*
Prende in ingresso il puntatore alla testa della lista utenti e lo inizializza a NULL

Restituisce 0
*/
int create_users_list(users* users_list_head){

    (*users_list_head) = NULL;

    return 0;
}





/*
Inserisce un nuovo utente con algoritmo di inserimento ordinato alfabeticamente

Restituisce:
- 1 Se la password passata come parametro è non valida (Impossibile aggiungere l'utente)
- 2 Errore di allocazione del nuovo nodo
- 3 In caso di inserimento duplicato (NON CONSENTITO)
- 0 Se tutto va a buon fine
*/
int insert_user_sorted(users* users_list_head, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN], user_role new_user_role){

    //Alloco il nuovo nodo utente
    users new_user_node = (users)malloc(sizeof(struct users));
    if(new_user_node == NULL) return 2; //Errore di allocazione

    //Creo il nuovo utente che verrà anch'esso allocato dinamicamente
    user new_user = NULL;
    int success = create_user(&(new_user),new_username,new_password,new_user_role);
    
    //Create_user restituisce 2: la password non è valida. Restituisce 1. 
    //Create_user restituisce 1: errore di allocazione nuovo utente
    if(success == 2){
        free(new_user_node);
        return 2; //Password non valida
    }
    else if(success == 1){
        free(new_user_node);
        return 1; //Errore di allocazione
    }

    //Popolo il nuovo nodo users (N.B inizialmente il nuovo nodo utenti non è agganciato a nessuna lista collezioni)
    new_user_node ->user_elem = new_user;
    new_user_node->collections_list_head = NULL; 
    

    //Inserimento ordinato in lista, caso 0: lista vuota, inserimento testa come primo elemento
    if(*users_list_head == NULL){
        (*users_list_head) = new_user_node;
        (*users_list_head) -> next = NULL;
        (*users_list_head) ->collections_list_head = NULL;
    }

    //Altrimenti devo ricercare il punto di inserimento con ordinamento alfabetico sulla base dell'username, preparo stringa e puntatori di appoggio
    char this_username[MAX_STR_LEN];
    users r = NULL;
    users q = *(users_list_head);

    while(q != NULL){

        //strcmp restituisce:
        // - un valore negativo se new_username è alfabeticamente inferiore all'username del nodo osservato-> devo interrompere lo scorrimento e inserire il nodo
        // - 0 se new_username == this_username
        // - un valore positivo se new_username è alfabeticamente superiore all'username del nodo osservato -> devo continuare a scorrere la lista
        get_username(q->user_elem,this_username);
        int caso = strcmp(new_username,this_username);

        //In caso di duplicati libera il nuovo noto e restituisce 3 (DUPLICATI NON CONSENTITI)
        if(caso == 0){
            free(new_user_node);
            return 3; //Duplicati non consentiti
        }

        //Trovata la corretta posizione di inserimento ordinaot, esco dal ciclo while
        if(caso < 0){
            break;
        }

        //Altrimenti passo al nodo successivo
        r = q;
        q = q->next;
    }

    //Caso 1: l'elemento da inserire è il primo della lista, inserimento testa (Non mi sono mosso dalla testa della lista)
    if(r == NULL){
        new_user_node -> next = (*users_list_head); 
        (*users_list_head) = new_user_node; //Aggiorno la testa
    } else { //Caso 2 inserimento intermedio o alpiù in coda(N.B se inserisco in coda q == NULL)
        r->next = new_user_node;
        new_user_node ->next = q;
    }

    return 0; //Success
}