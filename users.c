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
    Inserisce un nuovo utente all’interno della lista utenti in modo ordinato alfabeticamente 
    sulla base dell'username. L’inserimento non consente duplicati.

    La funzione alloca dinamicamente un nuovo nodo e una nuova struttura utente tramite `create_user`.
    Se la password fornita non è valida o si verifica un errore di allocazione, la funzione fallisce.  
    L’inserimento avviene in modo ordinato (ordine alfabetico crescente) confrontando gli username.

    Parametri:
        - users_list_head: puntatore alla testa della lista utenti, passato per riferimento.
        - new_username: stringa contenente il nome utente da inserire.
        - new_password: stringa contenente la password dell’utente.
        - new_user_role: ruolo da assegnare al nuovo utente (USER o ADMIN).

    Valori di ritorno:
        - 1 -> errore di allocazione durante la creazione dell’utente
        - 2 -> la password fornita non è valida
        - 3 -> esiste già un utente con lo stesso username (duplicato non ammesso)
        - 0 -> inserimento completato con successo
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
    Inserisce una lista di collezioni all'interno di uno specifico utente già presente nella lista utenti.

    La ricerca dell’utente avviene in modo ordinato alfabeticamente sulla base dello username.  
    Una volta trovato l’utente corrispondente, la funzione associa al suo campo 'collections_list_head'
    la lista di collezioni fornita in ingresso, utilizzando la funzione 'insert_user_collections_list'.

    Parametri:
        - users_list_head: puntatore alla testa della lista utenti (passato per riferimento).
        - key_username: stringa contenente l'username dell’utente da cercare.
        - new_collections_list_head: puntatore alla lista collezioni da assegnare all’utente.

    Valori di ritorno:
        - 1 -> la lista utenti è vuota o non inizializzata
        - 2 -> l’utente specificato non è stato trovato nella lista
        - 0 -> operazione completata con successo
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

    Ricerca un utente all’interno della lista utenti sulla base dello username specificato.

    La funzione effettua una ricerca ordinata alfabeticamente sul campo 'username' 
    all’interno della lista utenti. In caso di corrispondenza, restituisce tramite 
    parametro il puntatore alla struttura 'user' trovata.

    Parametri:
        - users_list_head: puntatore alla testa della lista utenti da scorrere.
        - key_username: stringa contenente lo username da cercare.
        - my_user: parametro di uscita; se la ricerca ha successo, conterrà il puntatore all’utente trovato.

    Valori di ritorno:
        - 1 -> la lista utenti è vuota o non inizializzata
        - 2 -> nessun utente trovato con lo username specificato
        - 0 -> utente trovato correttamente; il puntatore viene restituito tramite `my_user`

    Nota:
        - L’utente viene confrontato utilizzando `strcmp` in modo sensibile al maiuscolo/minuscolo.
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
    Verifica l’esistenza di un utente all’interno della lista utenti, sulla base dello username fornito.

    La funzione esegue una ricerca ordinata alfabeticamente nella lista 'users', confrontando il campo 'username'
    di ciascun nodo con il valore specificato in 'key_username'.

    Parametri:
        - users_list_head: puntatore alla testa della lista utenti da scorrere.
        - key_username: stringa contenente lo username da cercare.

    Valori di ritorno:
        - 1 -> la lista utenti è vuota o non inizializzata
        - 2 -> nessun utente trovato con lo username specificato
        - 0 -> utente presente nella lista
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
    Rimuove un utente dalla lista utenti sulla base dello username e dealloca 
    ricorsivamente tutte le strutture dati ad esso associate.

    La funzione effettua una ricerca ordinata alfabeticamente all'interno della lista 'users'.  
    In caso di corrispondenza, elimina il nodo corrispondente aggiornando i puntatori di lista,
    e invoca 'delete_user'per liberare la memoria associata alla struttura 'user'
    (inclusa la lista di collezioni e i prodotti)

    Parametri:
        - users_list_head: puntatore alla testa della lista utenti (passato per riferimento).
        - key_username: stringa contenente lo username dell’utente da eliminare.

    Valori di ritorno:
        - 1 -> la lista utenti è vuota o non inizializzata
        - 2 -> l’utente non è stato trovato nella lista
        - 0 -> utente rimosso correttamente

    Note:
        - Se l’utente da eliminare si trova in testa alla lista, la funzione aggiorna correttamente la testa.
        - L’ordinamento alfabetico viene utilizzato per interrompere anticipatamente la ricerca in caso di mancata corrispondenza.
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

    Cerca un utente all'interno della lista utenti (ordinata alfabeticamente per username) 
    e ne modifica le credenziali: username e/o password.

    La funzione utilizza `modify_credentials', che gestisce internamente la validazione 
    della nuova password e l'aggiornamento condizionato dei campi.  
    Se una delle stringhe 'new_username' o `new_password` è vuota, il rispettivo campo 
    non viene modificato.

    Parametri:
        - users_list_head: puntatore alla testa della lista utenti (passato per riferimento).
        - key_username: stringa contenente lo username dell’utente da modificare.
        - new_username: nuova stringa per aggiornare lo username (opzionale).
        - new_password: nuova stringa per aggiornare la password (opzionale).

    Valori di ritorno:
        - 0 -> modifica eseguita con successo
        - 1 -> la lista utenti è vuota o non inizializzata
        - 2 -> l’utente non è stato trovato nella lista
        - 3 -> l’utente trovato non è stato inizializzato (caso limite)
        - 4 -> la nuova password non è valida (secondo i criteri definiti)

    Note:
        - Se entrambe le stringhe sono vuote, l’utente resta invariato.
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
    Cerca un utente all’interno della lista utenti (ordinata alfabeticamente per username) 
    e ne aggiorna il ruolo con quello specificato nel parametro 'new_role'.

    La funzione utilizza'`set_user_role' per aggiornare il campo 'role' all’interno della 
    struttura 'user'. La promozione può essere utilizzata, ad esempio, per elevare un utente 
    da USER a ADMIN.

    Parametri:
        - users_list_head: puntatore alla testa della lista utenti (passato per riferimento).
        - key_username: stringa contenente lo username dell’utente da promuovere.
        - new_role: valore della enum `user_role` da assegnare all’utente (es. ADMIN).

    Valori di ritorno:
        - 0 -> aggiornamento del ruolo eseguito correttamente
        - 1 -> la lista utenti è vuota o non inizializzata
        - 2 -> l’utente non è stato trovato nella lista
        - 3 -> l’utente trovato non è stato inizializzato (caso limite)

    Note:
        - La lista utenti deve essere ordinata alfabeticamente affinché la ricerca funzioni correttamente.
        - Nessuna azione viene eseguita se il ruolo specificato è già assegnato all’utente.

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
    Libera completamente la memoria occupata dalla lista utenti.

    La funzione scorre l’intera lista 'users' e, per ciascun nodo, dealloca:
    - la struttura `user` associata (tramite 'delete_user')
    - il nodo della lista stessa

    Alla fine dell'operazione, il puntatore alla testa della lista viene azzerato 
    per evitare dangling pointer.

    Parametri:
        - users_list_head: puntatore alla testa della lista utenti (passato per riferimento).

    Valori di ritorno:
        - 1 -> la lista utenti è già vuota o non inizializzata
        - 0 -> deallocazione completata correttamente

    Nota:
        - Tutte le strutture gerarchicamente inferiori all’utente (collezioni, prodotti, ecc.)
          vengono automaticamente liberate dalla funzione 'delete_user' di user.h.
*/

int free_users(users* users_list_head){

    if(*users_list_head == NULL) return 1;

    //Puntatori di appoggio per scorrere la lista ordinata
    users r = NULL;
    users q = *users_list_head;

    while(q != NULL){
        r = q;
        q = q -> next;
        delete_user(&(r->user_elem));
        free(r);
    }

    //Azzero il puntatore alla lista
    *users_list_head = NULL;

    return 0; //Success
}


/*
    Stampa le informazioni principali (username e ruolo) di tutti gli utenti presenti nella lista.

    La funzione itera su ciascun nodo della lista 'users' e invoca 'print_user' per stampare 
    le informazioni relative al singolo utente in formato leggibile.

    Parametri:
        - users_list_head: puntatore alla testa della lista utenti.

    Valori di ritorno:
        - 1 -> la lista è vuota o non valida
        - 0 -> stampa eseguita correttamente

    Nota:
        - La funzione stampa il contenuto informativo in maniera molto semplice. È pensata per 
          essere usata come parte di funzioni ad alto livello che gestiscono la formattazione.
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



/*
Scorre la lista degli utenti e per ciascun elemento ne salva il contenuto informativo in un file, incapsulando anche le funzioni di salvataggio delle singole collezioni (e quindi dei prodotti)
[ NOTA BENE: NON SI OCCUPA NÈ DI COLLEGARE IL PUNTATORE AL FILE CORRETTO, NÈ DI DEREFERENZIARE IL PUNTATORE, NÈ 
 DI INIZIALIZZARLO IN MODALITÀ APPEND. SPETTA AL CHIAMANTE PRINCIPALE GESTIRLI. ]

Parametri: 
    - fptr: puntatore al file in cui scrivere i dati
    - users_list_head: puntatore alla testa della lista utenti

Restituisce: 
    - 1: se il puntatore al file è invalido (NULL) 
    - 0: salvataggio avvenuto con successo

#USER
Marco
Prova123!
ADMIN
##Collection
Giochi PS1
Videogiochi
###Product
Silent Hill 2, PAL ITA, Nuovo, 29.99 
###Product
Silent Hill 3, PAL ITA, Nuovo, 29.99 
##Collection
Giochi PS2
Videogiochi

#USER
[...]
*/
int save_users(FILE *fptr, users users_list_head){

    if(fptr == NULL) return 1;

    while(users_list_head != NULL){
        int result = save_user(fptr, users_list_head->user_elem);
        switch(result){
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            case 4: return 4;
            default: break;
        }
        users_list_head = users_list_head->next;
    }

    return 0;
}



int load_users(users* users_list){

    FILE *fptr = fopen("data.txt", "r");
    if(fptr == NULL) return 1;

    /*lista vuota: programma aperto per la prima volta ----------------------------- */
    if(fptr == EOF) return 2;


    /*preparazione buffers lettura file ---------------------------------------------------- */
    char buf[MAX_STR_LEN];
    char username[MAX_STR_LEN];
    char password[MAX_STR_LEN];
    char role[MAX_STR_LEN];

    char coll_name[MAX_STR_LEN];
    char coll_type[MAX_STR_LEN];

    char prod_name[MAX_STR_LEN];
    char prod_type[MAX_STR_LEN];
    char prod_cond[MAX_STR_LEN];
    float buy_price;

    while(fptr != EOF){
        
        int next_user = read_user(fptr,username,password,role);
        if(next_user == 1) return 1;                                         /* dati corrotti: fptr == NULL || ftell fallisce */

        /*lettura utente avvenuta con successo -> passo al caricamento  -------------- */
        if(next_user == 0){
            
            /*caricamento utente nella lista utenti ----------------------------------  */
            user_role user_role;
            if(convert_user_role_to_enum(role, user_role) == 1) return 1;    /* dati corrotti: ruolo invalido */
            int user_insert_result = insert_user_sorted(users_list,username,password,user_role);
            switch(user_insert_result){
                case 1: return 2;                                            /* errore: allocazione dinamica*/
                case 2: return 1;                                            /* dati corrotti: password invalida */
                case 3: return 1;                                            /* dati corrotti: duplicato */
                default: break;
            }

            /* preparo l'utente in questione nel caso in cui debba caricare collezioni e prodotti a lui associati */
            user this_user = NULL;
            int search_result = search_user(*users_list, username, this_user);
            switch(search_result){
                case 1: return 3;                                            /* errore: allocazione inconsistente */
                case 2: return 3;                                            /* errore: allocazione inconsistente */
                default: break;
            }

            /*Salvo la posizione del puntatore nel file, leggo la prossima stringa, se è una collezione continuo a leggere altrimenti passo ai prodotti e ristabilisco la posizione corrente */
            long curr_pos = ftell(fptr);
            if(curr_pos == -1L) return 1;                                   /* dati corrotti: fptr == NULL || ftell fallisce */
            if(fgets(buf,MAX_STR_LEN,fptr) == NULL) return 1;               /* dati corrotti: fptr == NULL || ftell fallisce */

            while((strcmp(buf, "##COLLECTION") == 0)){

                /*ristabilisco la posizione precedente e leggo la collezione, se esistente */
                fseek(fptr,curr_pos,SEEK_SET);          
                int next_collection = read_collection(fptr, coll_name, coll_type);
                if(next_collection == 1) return 1;                              /* dati corrotti: fptr == NULL || ftell fallisce */

                if(next_collection == 0){

                    /*caricamento collezione dell'utente ----------------------------------------*/
                    int ins_coll_result = insert_collection(&(this_user ->collections_list_head),coll_name,coll_type);
                    switch(ins_coll_result){
                        case 1: return 2;                                   /* errore: allocazione dinamica*/
                        case 2: return 2;                                   /* dati corrotti: duplicato */
                        default: break;
                    }

                    /* preparo la collezione in questione nel caso in cui debba caricare prodotti a lei associati */
                    collection this_collection = NULL;
                    int search_result = search_collection(this_user->collections_list_head,coll_name,&(this_collection));
                    switch(search_result){
                        case 1: return 3;                                            /* errore: allocazione inconsistente */
                        case 2: return 3;                                            /* errore: allocazione inconsistente */
                        default: break;
                    }

                    /*Salvo la posizione del puntatore nel file, leggo la prossima stringa, se è una collezione continuo a leggere altrimenti passo ai prodotti e ristabilisco la posizione corrente */
                    long curr_pos = ftell(fptr);
                    if(curr_pos == -1L) return 1;                                   /* dati corrotti: fptr == NULL || ftell fallisce */
                    if(fgets(buf,MAX_STR_LEN,fptr) == NULL) return 1;               /* dati corrotti: fptr == NULL || ftell fallisce */

                    while((strcmp(buf, "#PRODUCT")) == 0){

                        /*ristabilisco la posizione precedente e leggo la collezione, se esistente */
                        fseek(fptr,curr_pos,SEEK_SET);          
                        int next_product = read_product(fptr, prod_name, prod_type,prod_cond,&(buy_price));
                        
                        if(next_product == 1) return 1;                              /* dati corrotti: fptr == NULL || ftell fallisce */

                        if(next_product == 0){

                            /*caricamento collezione dell'utente ----------------------------------------*/
                            int ins_prod_result = insert_product(&(this_collection->products_list_head),prod_name,prod_type,prod_cond,buy_price);
                            switch(ins_coll_result){
                                case 1: return 2;                                   /* errore: allocazione dinamica*/
                                case 2: return 2;                                   /* dati corrotti: duplicato */
                                default: break;
                            }
                        }
                        if(next_product == 3 || next_product == 2) break;
                    }

                if(next_collection == 2 || next_collection == 3) break;
                }
           
        }
        if(next_user == 2 || next_user == 3) break; 
    }
    break;
    }
return 0;
}