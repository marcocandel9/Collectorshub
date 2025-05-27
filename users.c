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

    //Popolo il nuovo nodo users 
    new_user_node ->user_elem = new_user;
    new_user_node->user_elem->collections_list_head = NULL; 
    

    //Inserimento ordinato in lista, caso 0: lista vuota, inserimento testa come primo elemento
    if(*users_list_head == NULL){
        (*users_list_head) = new_user_node;
        (*users_list_head) -> next = NULL;
        return 0;
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





/*
Inserisce una lista collezioni all'utente desiderato della lista utenti con INSERIMENTO ORDINATO ALFABETICO sulla base del NOME UTENTE

Prende in ingresso il puntatore alla lista utenti passato per riferimento, il nome dell'utente da ricercare in cui inserire la lista collezioni, il puntatore alla testa della lista collezioni da inserire

Restituisce:
- 1 In caso di lista utenti vuota
- 2 In caso di corrispondenza non trovata
- 0 Se tutto va a buon fine
*/
int insert_sorted_user_collections(users* users_list_head, char key_username[MAX_STR_LEN], collections new_collections_list_head){

    //Puntatore alla testa della lista utenti uguale a NULL -> lista vuota, restituisce 1
    if(*users_list_head == NULL) return 1;

    //Puntatore di appoggio per scorrere la lista utenti
    users q= *users_list_head;
    char my_username[MAX_STR_LEN];

    //Ricerca ordinata sulla base del nome utente (array di caratteri key_username)
    while(q != NULL){
        get_username(q->user_elem,my_username); 

        //strcmp restituisce:
        // - un valore negativo se key_username è alfabeticamente inferiore al nome dell'utente -> devo interrompere la ricerca
        // - 0 se key_username == username
        // - un valore positivo se key_username è alfabeticamente superiore al nome dell'utente -> devo continuare a cercare
        int is_equal = strcmp(key_username,my_username);

        if(is_equal == 0) break; //Corrispondenza trovata, esco dal ciclo while

        if(is_equal < 0) return 2; //Utente non trovato, restituisci 2

        q= q-> next;
    }

    if(q == NULL) return 2; //Se arrivo alla coda della lista, q sarà uguale a NULL, restituisco 2 (Utente non trovato)

    //Aggancio la lista delle collezioni all'utente trovato
    insert_user_collections_list(q->user_elem,new_collections_list_head);

    return 0; //Success
}





/*
Cerca un utente nella lista utenti sulla base del suo username e ne restituisce un puntatore alla struct utente

Restituisce:
- 1 Se la lista utenti è vuota
- 2 Se non è stata trovata una corrispondenza
- 0 Se tutto va a buon fine e restituisce il parametro user my_user con il puntatore alla struct utente
*/
int search_user(users users_list_head, char key_username[MAX_STR_LEN], user* my_user){

    if(users_list_head == NULL) return 1; //Lista utenti vuota o non inizializzata restituisci 1

    //Puntatore di appoggio per scorrere la lista utenti
    users q = users_list_head;
    char my_username[MAX_STR_LEN];

    //Ricerca ordinata sulla base del nome utente (array di caratteri key_username)
    while(q != NULL){
        get_username(q->user_elem,my_username); 

        //strcmp restituisce:
        // - un valore negativo se key_username è alfabeticamente inferiore al nome dell'utente -> devo interrompere la ricerca
        // - 0 se key_username == username
        // - un valore positivo se key_username è alfabeticamente superiore al nome dell'utente -> devo continuare a cercare
        int is_equal = strcmp(key_username,my_username);

        if(is_equal == 0) break; //Corrispondenza trovata, esco dal ciclo while

        if(is_equal < 0) return 2; //Utente non trovato, restituisci 2

        q= q-> next;
    }

    if(q == NULL) return 2; //Se arrivo alla coda della lista, q sarà uguale a NULL, restituisco 2 (Utente non trovato)

    (*my_user) = q->user_elem;
    return 0; //Success
}





/*
Cerca un utente nella lista utenti sulla base del suo username e restituisce 0 se è presente

Restituisce:
- 1 Se la lista utenti è vuota
- 2 Se non è stata trovata una corrispondenza
- 0 Se l'utente è stato trovato
*/
int user_exists(users users_list_head, char key_username[MAX_STR_LEN]){

    if(users_list_head == NULL) return 1; //Lista utenti vuota o non inizializzata restituisci 1

    //Puntatore di appoggio per scorrere la lista utenti
    users q = users_list_head;
    char my_username[MAX_STR_LEN];

    //Ricerca ordinata sulla base del nome utente (array di caratteri key_username)
    while(q != NULL){
        get_username(q->user_elem,my_username); 

        //strcmp restituisce:
        // - un valore negativo se key_username è alfabeticamente inferiore al nome dell'utente -> devo interrompere la ricerca
        // - 0 se key_username == username
        // - un valore positivo se key_username è alfabeticamente superiore al nome dell'utente -> devo continuare a cercare
        int is_equal = strcmp(key_username,my_username);

        if(is_equal == 0) break; //Corrispondenza trovata, esco dal ciclo while

        if(is_equal < 0) return 2; //Utente non trovato, restituisci 2

        q= q-> next;
    }

    if(q == NULL) return 2; //Se arrivo alla coda della lista, q sarà uguale a NULL, restituisco 2 (Utente non trovato)

    return 0; //Success
}





/*
Cerca un user da eliminare dalla lista utenti e lo rimuove, deallocando gerarchicamente tutte le strutture dati a lui associate

Restituisce: 

- 1 Se la lista utenti è vuota (Puntatore a NULL)
- 2 Se la corrispondenza non è stata trovata
- 0 Se tutto va a buon fine
*/
int remove_user(users* users_list_head, char key_username[MAX_STR_LEN]){

    if(*users_list_head == NULL) return 1; //Lista utenti vuota o non inizializzata

    //Puntatori di appoggio per scorrere la lista ordinata
    users r = NULL;
    users q = *users_list_head;
    char this_username[MAX_STR_LEN];

    while(q != NULL){
        get_username(q->user_elem,this_username);

        //strcmp restituisce:
        // - un valore negativo se key_username è alfabeticamente inferiore al nome dell'utente-> devo interrompere la ricerca
        // - 0 se key_username == this_username
        // - un valore positivo se key_username è alfabeticamente superiore al nome dell'utente -> devo continuare a cercare
        int is_equal = strcmp(key_username,this_username);

        if(is_equal == 0) break; //Corrispondenza trovata esco dal ciclo while

        if(is_equal < 0) return 2; //Corrispondenza non trovata, l'utente cercato non esiste nalla lista -> restituisci 2

        //Incremento i puntatori
        r=q;
        q= q->next;
    }

    //Lo scorrimento è giunto fino alla fine della lista utenti, non è stata trovata una corrispondenza restituisci 2
    if(q == NULL) return 2;

    //Caso 0: l'elemento da cancellare è il primo della lista, devo aggiornare la testa
    if(r==NULL){
        *users_list_head = (*users_list_head) -> next;

        //dealloco il nodo contenente l'utente che desidero eliminare

        //Richiamo la funzione delete user per deallocare la struct utente allocata dinamicamente e tutte le strutture dati gerarchicamente inferiori
        delete_user(&(q->user_elem));
        free(q); //Dealloco il nodo della lista utenti
    } else {
        //Cancellazione intermedia o alpiù in coda (in quel caso q == NULL)
        r->next = q->next;
        delete_user(&(q->user_elem));
        free(q);
    }
    return 0; //success
}





/*
Cerca un utente nella lista utenti con ordinamento alfabetico e ne modifica username,password e ruolo. 
Utilizza la funzione modify user che controlla anche la validità della password

Restituisce:
- 0 Se tutto va a buon fine
- 1 Se la lista utenti è vuota
- 2 Se non è stata trovata una corrispondenza
- 3 Utente non inizializzato (Improbabile)
- 4 Se la password non è valida
*/
int search_and_modify_user_credentials(users* users_list_head, char key_username[MAX_STR_LEN], char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN]){

    if(*users_list_head == NULL) return 1; //Restituisce 1, lista vuota o non inizializzata 

    //Puntatore di appoggio per scorrere la lista utenti
    users q = *users_list_head;
    char my_username[MAX_STR_LEN];

    //Ricerca ordinata sulla base del nome utente (array di caratteri key_username)
    while(q != NULL){
        get_username(q->user_elem,my_username); 

        //strcmp restituisce:
        // - un valore negativo se key_username è alfabeticamente inferiore al nome dell'utente -> devo interrompere la ricerca
        // - 0 se key_username == username
        // - un valore positivo se key_username è alfabeticamente superiore al nome dell'utente -> devo continuare a cercare
        int is_equal = strcmp(key_username,my_username);

        if(is_equal == 0) break; //Corrispondenza trovata, esco dal ciclo while

        if(is_equal < 0) return 2; //Utente non trovato, restituisci 2

        q= q-> next;
    }

    if(q == NULL) return 2; //Se arrivo alla coda della lista, q sarà uguale a NULL, restituisco 2 (Utente non trovato)

    //Modifico le credenziali dell'utente
    int result = modify_credentials(q->user_elem,new_username,new_password);

    if(result == 1) return 3; // Utente non inizializzato (improbabile)
    if(result == 2) return 4; // Password non valida

    return 0; //Success
}





/*
Cerca un utente nella lista utenti con ordinamento alfabetico e ne promuove il ruolo a quello specificato nel parametro di ingresso
Utilizza la funzione set_user_role di user.h 

Restituisce:
- 0 Se tutto va a buon fine
- 1 Se la lista utenti è vuota
- 2 Se non è stata trovata una corrispondenza
- 3 Utente non inizializzato (Improbabile)
*/
int search_and_promote_user(users* users_list_head, char key_username[MAX_STR_LEN], user_role new_role){

    if(*users_list_head == NULL) return 1; //Restituisce 1, lista vuota o non inizializzata 

    //Puntatore di appoggio per scorrere la lista utenti
    users q = *users_list_head;
    char my_username[MAX_STR_LEN];

    //Ricerca ordinata sulla base del nome utente (array di caratteri key_username)
    while(q != NULL){
        get_username(q->user_elem,my_username); 

        //strcmp restituisce:
        // - un valore negativo se key_username è alfabeticamente inferiore al nome dell'utente -> devo interrompere la ricerca
        // - 0 se key_username == username
        // - un valore positivo se key_username è alfabeticamente superiore al nome dell'utente -> devo continuare a cercare
        int is_equal = strcmp(key_username,my_username);

        if(is_equal == 0) break; //Corrispondenza trovata, esco dal ciclo while

        if(is_equal < 0) return 2; //Utente non trovato, restituisci 2

        q= q-> next;
    }

    if(q == NULL) return 2; //Se arrivo alla coda della lista, q sarà uguale a NULL, restituisco 2 (Utente non trovato)

    //Modifico le credenziali dell'utente
    int result = set_user_role(q->user_elem, new_role);

    if(result == 1) return 3; // Utente non inizializzato (improbabile)

    return 0; //Success
}





/*
Libera l'intera lista utenti, deallocando completamente anche tutte le strutture dati gerarchicamente inferiori

Restituisce: 
- 1 Se la lista utenti è vuota
- 0 Se tutto va a buon fine
*/
int free_users(users* users_list_head){

    if(*users_list_head == NULL) return 1;

    //Puntatori di appoggio per scorrere la lista ordinata
    users r = NULL;
    users q = *users_list_head;
    char my_username[MAX_STR_LEN];

    while(q != NULL){
        r = q;
        q = q -> next;
        delete_user(&(q->user_elem));
        free(r);
    }

    //Azzero il puntatore alla lista
    *users_list_head = NULL;

    return 0; //Success
}


/*
Stampa l'username ed il ruolo di ogni utente della lista utenti. 

Prende in ingresso il puntatore alla testa della lista passato come riferimento

Restituisce:
- 1 In casi di lista utenti non valida o vuota
- 0 In caso di Successo
*/
int print_users(users users_list_head){

     //Puntatore alla testa della lista utenti uguale a NULL -> Lista vuota , restitusisce 1
    if(users_list_head == NULL) return 1;

    //Altrimenti stampa la lista
    while(users_list_head != NULL){
        print_user((users_list_head)->user_elem);
        users_list_head = users_list_head->next;
    }
    return 0; //Success, lista printata
}
