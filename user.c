#include "user.h"


const char allowed_symbols[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";


/* 
Crea un nuovo utente allocandone la memoria dinamicamente e associandone un proprio username, ruolo e password, quest'ultima validata 
dalla funzione validate_password.

Parametri:
    - new_user: puntatore passato per riferimento ad una struct user dell'utente che si vuole allocare dinamicamente
    - new_username: array di caratteri contenenti il nuovo username utente
    - new_password: array di caratteri contenente la nuova password utente
    - new_user_role ruolo dell'utente (base o admin)

Restituisce:
    - 1 Se l'utente è già esistente (puntatore a struct user diverso da null quindi già inizializzato)
    - 2 Se la password non è validata correttamente
    - 3 In caso di errori di allocazione del nuovo utente
    - 0 Se tutto va a buon fine

*/
int create_user(user* new_user, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN], user_role new_user_role){

    if((*new_user) != NULL) return 1; //Utente già esistente!

    //Controllo della validità della password, se non è valida, restituisce 2
    int is_valid = validate_password(new_password);
    if(is_valid == 1) return 2; //Password non valida

    *new_user = (user)malloc(sizeof(struct user));
    if (*new_user == NULL) return 3; //Allocation error

    //Popolo la struct user
    
    set_username(*new_user,new_username);
    set_password(*new_user,new_password);
    set_user_role(*new_user, new_user_role);
    (*new_user) ->collections_list_head = NULL;

    return 0; //Success
}






/*
    Confronta due ruoli utente in termini di priorità gerarchica.

    Questa funzione può essere utilizzata sia per confrontare la gerarchia relativa tra due ruoli, 
    sia per verificarne l’uguaglianza. È progettata per essere estendibile nel caso in cui vengano 
    aggiunti nuovi ruoli all’enumerazione `user_role`.

    I ruoli devono essere definiti in ordine crescente di privilegi all'interno della enum `user_role`
    (es. USER < ADMIN < SUPERADMIN ...).

    Parametri:
        - this_user_role: ruolo dell’utente chiamante (chi effettua l’azione)
        - that_user_role: ruolo dell’utente bersaglio (su cui si vuole agire, o ruolo richiesto)

    Valori di ritorno:
        - 0 -> il ruolo del chiamante è gerarchicamente superiore
        - 1 -> il ruolo del chiamante è gerarchicamente inferiore
        - 2 -> i due ruoli sono **equivalenti**

    Esempi:
        - compare_user_privilege(USER, ADMIN)  → 1
        - compare_user_privilege(ADMIN, USER)  → 0
        - compare_user_privilege(ADMIN, ADMIN) → 2
*/

int compare_user_privilege(user_role this_user_role, user_role that_user_role){
    
    // Se il primo ruolo è inferiore al secondo, restituisce 1 
    if (this_user_role < that_user_role) {
        return 1;  // Ruolo inferiore 
    }

    // Se il primo ruolo è uguale al secondo, restituisce 2
    if (this_user_role == that_user_role){
        return 2; // Ruolo uguale
    }

    // Se il primo ruolo è superiore al secondo, restituisce 0 
    return 0;

}





/*
    Verifica la validità della password secondo i criteri di sicurezza predefiniti.

    Una password è considerata valida se rispetta tutte le seguenti condizioni:
    - Lunghezza minima di (MIN_STR_LEN - 1) caratteri
    - Presenza di almeno una lettera maiuscola
    - Presenza di almeno una lettera minuscola
    - Presenza di almeno una cifra numerica
    - Presenza di almeno un simbolo tra quelli consentiti (escludendo spazi)

    L’elenco dei simboli ammessi è definito nel file user.h, tramite la stringa:
        `const char allowed_symbols[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_";`
    È possibile personalizzare i simboli modificando direttamente questo array.

    La funzione utilizza <ctype.h> per l’analisi carattere per carattere:
    - `isupper`, `islower`, `isdigit` per controlli su lettere e cifre
    - `ispunct` e `isspace` per isolare i simboli ammessi
    - `strchr` per verificare la presenza del simbolo nella stringa allowed_symbols

    Parametri:
        - password: array di caratteri contenente la password da validare

    Valori di ritorno:
        - 0 → la password è valida
        - 1 → la password non rispetta almeno uno dei requisiti
*/
int validate_password(char password[MAX_STR_LEN]){

    //strlen controlla la dimensione LOGICA della stringa, non quella fisica, quindi conta il numero di caratteri fino al terminatore \0 (null terminator)
    int length = strlen(password);
    if (length < MIN_STR_LEN-1) return 1; //Password invalida

    //Inizializzo delle variabili booleane di supporto per il controllo delle condizioni
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_symbol = false;

    //Controllo dei singoli caratteri della password, termina al raggiungimento dell'ultimo carattere utile (il precedente al null terminator \0)
    for(int i = 0; i < length; i++){

        if(isupper(password[i])) has_upper = true;
        if(islower(password[i])) has_lower = true;
        if(isdigit(password[i])) has_digit = true;
        
        // Controllo che il simbolo sia tra quelli ammessi e sia diverso dallo spazio
        if(ispunct(password[i]) && !isspace(password[i])) {
            //strchr cerca la prima occorrenza di un carattere in una stringa
            //Ricerca il carattere password[i] all'interno della stringa allowed symbols
            //Restituisce un puntatore alla prima occorrenza di password[i] in allowed_symbols, null altrimenti
            //if interpreta il puntatore a null come false e il puntatore non nullo come vero
            if(strchr(allowed_symbols, password[i])) {
                has_symbol = true;
            }
        }
    }

    if(has_upper && has_lower && has_digit && has_symbol) return 0; //Success

    return 1; //Password non valida, restituisce 1
}





/*
Imposta un nuovo username alla struct utente

Restituisce:
- 1 Se l'utente non è stato ancora inizializzato (puntatore a NULL)
- 0 Se tutto va a buon fine
*/
int set_username(user my_user, char new_username[MAX_STR_LEN]){

    if(my_user == NULL) return 1; //Utente non inizializzato

    strcpy(my_user->username,new_username);

    return 0; //Success
}





/*
Imposta una nuova password alla struct utente

Restituisce:
- 1 Se l'utente non è stato ancora inizializzato (puntatore a NULL)
- 0 Se tutto va a buon fine
*/
int set_password(user my_user, char new_password[MAX_STR_LEN]){

    if(my_user == NULL) return 1; //Utente non inizializzato

    strcpy(my_user->password,new_password);

    return 0; //Success
}





/*
Imposta un nuovo ruolo alla struct utente

Restituisce
- 1 Se l'utente non è stato ancora inizializzato (puntatore a NULL)
- 0 Se tutto va a buon fine
*/
int set_user_role(user my_user, user_role new_user_role){

    if(my_user == NULL) return 1; //utente non inizializzato

    my_user ->role = new_user_role;

    return 0; //Success
}





/*
    Associa una nuova lista di collezioni a un utente esistente.

    La funzione aggiorna il campo 'collections_list_head' della struttura 'user', 
    assegnandogli il puntatore alla nuova lista di collezioni fornita in ingresso.  
    È utilizzata in fase di inizializzazione dell’utente o quando si 
    vuole sovrascrivere la sua lista di collezioni con una nuova.

    Parametri:
        - my_user: puntatore alla struttura utente a cui associare la lista.
        - new_collections_list_head: puntatore alla lista di collezioni da assegnare.

    Valori di ritorno:
        - 1 -> l’utente non è stato inizializzato (my_user == NULL)
        - 0 -> operazione completata con successo

*/
int insert_user_collections_list(user my_user, collections new_collections_list_head){

    if(my_user == NULL) return 1; //Utente non esistente o non ancora inizializzato

    (my_user)->collections_list_head = new_collections_list_head;
    return 0; //Success

}




/*
Inserisce una nuova collezione alla lista collezioni di un utente. 

Restituisce: 
    - 1: L'utente non è stato ancora correttamente inizializzato
    - 2: La collezione è già presente all'interno della lista
    - 3: Errore di allocazione dinamica
    - 0 Se tutto va a buon fine
*/
int insert_user_collection(user my_user, char collection_name[MAX_STR_LEN], char collection_type[MAX_STR_LEN]){

    if(my_user == NULL) return 1; //Utente non esistente o non ancora inizializzato

    int exists = collection_exists(my_user->collections_list_head, collection_name);
    if(exists == 0) return 2; //La collezione esiste già!

    int result = insert_collection(&(my_user->collections_list_head), collection_name,collection_type);
    if (result == 1) return 3;
    
    return 0;
}





/*
    Modifica le credenziali (username e/o password) di un utente esistente.

    La funzione aggiorna i dati sensibili della struttura 'user' solo se i nuovi valori 
    passati come parametro non sono stringhe vuote. In particolare:
    - Se 'new_password' non è una stringa vuota, la password viene prima validata tramite `validate_password()`.
      Se la validazione ha esito positivo, viene aggiornata.
    - Se 'new_username' non è una stringa vuota, l username viene aggiornato direttamente.

    Parametri:
        - my_user: puntatore alla struttura utente da modificare.
        - new_username: nuova stringa per lo username (se vuota, non viene modificato).
        - new_password: nuova stringa per la password (se vuota, non viene modificata).

    Valori di ritorno:
        - 1 -> l’utente non è stato ancora inizializzato (my_user == NULL)
        - 2 -> la nuova password non è valida (secondo i criteri di sicurezza)
        - 0 -> modifiche eseguite correttamente
*/

int modify_credentials(user my_user, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN]){

    if(my_user == NULL) return 1; //Utente non ancora inizializzato

    //Modifico il nuovo username e la nuova password (N.B se le stringhe passate in ingresso sono vuote, non modifica quel campo informativo)
    if(new_password[0] != '\0'){
        int is_valid = validate_password(new_password);
        if(is_valid == 1) return 2; //Password non valida
        set_password(my_user, new_password);
    }
    
    if(new_username[0] != '\0'){
        set_username(my_user, new_username);
    }

    return 0; //Success
}




/*
Funzione che copia l'username dell'utente passato in ingresso all'interno dell'array di caratteri passato in ingresso my_username

Restituisce:
- 1 Se l'utente non è stato ancora inizializzato e quindi non esiste (puntatore a null)
- 0 Se tutto va a buon fine
*/
int get_username(user my_user, char my_username[MAX_STR_LEN]){

    if(my_user == NULL) return 1;

    strcpy(my_username,my_user->username);

    return 0; //Success
}





/*
Funzione che copia la password dell'utente passato in ingresso all'interno dell'array di caratteri passato in ingresso my_password

Restituisce:
- 1 Se l'utente non è stato ancora inizializzato e quindi non esiste (puntatore a null)
- 0 Se tutto va a buon fine
*/
int get_password(user my_user, char my_password[MAX_STR_LEN]){

    if(my_user == NULL) return 1;

    strcpy(my_password,my_user->password);

    return 0; //Success

}



/*
Restituisce, tramite il parametro in ingresso user_collection, la lista delle collezioni associata all'utente, anch'esso passato come parametro.

Restituisce: 
- 1 Se l'utente non è stato ancora inizializzato e quindi non esiste (puntatore a null)
= 0 Se tutto va a buon fine
*/
int get_collection_list(user my_user, collections* user_collection){

    if(my_user == NULL) return 1;

    *user_collection = my_user->collections_list_head;
    return 0;
}




/*
Funzione che copia il ruolo dell'utente nell'array di caratteri my_user_role passato in ingresso

Restituisce:
- 1 Se l'utente non è stato ancora inizializzato e quindi non esiste (puntatore a null)
- 0 Se tutto va a buon fine
*/
int get_user_role(user my_user, char my_user_role[MAX_STR_LEN]){
    
    if(my_user == NULL) return 1;

    switch(my_user->role) {
        case USER:
            strcpy(my_user_role, "USER");
            break;
        case ADMIN:
            strcpy(my_user_role, "ADMIN");
            break;
        default:
            strcpy(my_user_role, "ERRORE");
            break;
    }

    return 0;
}




/*
    Verifica che l'utente specificato abbia esattamente il ruolo richiesto.

    La funzione controlla che il ruolo associato alla struttura 'user' corrisponda
    esattamente al ruolo specificato nel parametro 'required_role'.  
    Non viene considerata la gerarchia tra ruoli, ma l'equivalenza esatta.

    Parametri:
        - my_user: puntatore alla struttura utente da verificare.
        - required_role: ruolo richiesto per il confronto (es. ADMIN, USER).

    Valori di ritorno:
        - 1 -> l'utente non è stato inizializzato (my_user == NULL o invalido)
        - 2 -> il ruolo dell'utente è diverso da quello richiesto
        - 0 -> l'utente ha esattamente il ruolo richiesto

*/
int role_checker(user my_user, user_role required_role){

    char my_user_role[MAX_STR_LEN];
    
    int result = get_user_role (my_user, my_user_role);

    if(result == 1) return 1; //Utente non inizializzato, errore

    //Altrimenti controlla che l'utente abbia quel ruolo specifico
    
    result = compare_user_privilege(my_user->role , required_role);

    if (result == 2) return 0; // Ruolo corrispondente
    return 2; // Ruolo diverso

}





/*
    Dealloca completamente la memoria associata a un utente e a tutte le sue strutture dati collegate.

    La funzione libera prima la memoria riservata alla lista di collezioni dell'utente, 
    e successivamente libera la struttura `user` stessa, impostando il puntatore a `NULL`
    per evitare dangling pointer.

    Parametri:
        - my_user: doppio puntatore alla struttura utente da eliminare (passato per riferimento).

    Valori di ritorno:
        - 1 -> l’utente non è stato inizializzato (puntatore nullo)
        - 0 -> eliminazione completata con successo
*/
int delete_user(user* my_user){
    
    if(*my_user == NULL) return 1;

    //dealloco gerarchicamente tutte le strutture dati inferiori a user (collezioni, prodotti)
    free_collections(&((*my_user)->collections_list_head));

    free(*my_user);

    *my_user = NULL;

    return 0;
}


/*
    Stampa le informazioni principali di un utente: username e ruolo.

    Utilizza le funzioni getter per estrarre i dati dalla struttura `user` 
    e stampa una riga in formato: `<username>, <ruolo>`.

    Parametri:
        - my_user: puntatore alla struttura utente da stampare.

    Valori di ritorno:
        - 0 → operazione completata con successo

    Nota:
        La funzione assume che l’utente sia già stato inizializzato.
        Nessun controllo su `NULL` viene effettuato internamente.
*/

int print_user(user my_user){

    char my_user_username[MAX_STR_LEN];
    char my_user_role[MAX_STR_LEN];

    //Passa agli array di caratteri nome e ruolo alle funzioni getter
    get_username(my_user, my_user_username);
    get_user_role(my_user, my_user_role);


    printf("%s, %s\n", my_user_username, my_user_role);
    return 0; //Success
}




/*
Modifica il nome e/o il tipo di una collezione appartenente all’utente specificato

Parametri:
- my_user: puntatore alla struttura utente
- key_collection_name: nome attuale della collezione da modificare
- new_collection_name: nuovo nome da assegnare alla collezione (stringa vuota per non modificarlo)
- new_collection_type: nuovo tipo da assegnare alla collezione (stringa vuota per non modificarlo)

Valori di ritorno:
- 1 -> utente non inizializzato
- 2 -> lista collezioni vuota o non valida
- 3 -> collezione non trovata
- 0 -> modifica avvenuta con successo
*/
int modify_user_collection(user my_user, char key_collection_name[MAX_STR_LEN], char new_collection_name[MAX_STR_LEN], char new_collection_type[MAX_STR_LEN]){

    if(my_user == NULL) return 1;

    int modify_result = search_and_modify_collection(my_user->collections_list_head,key_collection_name,new_collection_name,new_collection_type);

    switch(modify_result){
        case 1: return 2; //lista vuota o non valida
        case 2: return 3; //non è stata trovata una corrispondenza
        default: return 0; //tutto va a buon fine
    }
}

 



/*
Elimina una collezione appartenente all’utente specificato, sulla base del nome fornito

Parametri:
- my_user: puntatore alla struttura utente
- key_collection_name: nome della collezione da eliminare

Valori di ritorno:
- 1 -> utente non inizializzato o lista collezioni vuota/non valida
- 2 -> collezione non trovata
- 0 -> eliminazione avvenuta con successo
*/
int delete_user_collection(user my_user, char key_collection_name[MAX_STR_LEN]){

    if(my_user == NULL) return 1;

    int del_result = remove_collection(&(my_user->collections_list_head),key_collection_name);
    switch(del_result){
        case 1: return 1; // lista vuota/non valida
        case 2: return 2; // non è stata trovata una corrispondenza
        default: return 0; //eliminazione effettuata con successo
    }
}




/*
Elimina una collezione appartenente all’utente specificato, sulla base del nome fornito

Parametri:
- my_user: puntatore alla struttura utente

Valori di ritorno:
- 1 -> utente non inizializzato o lista collezioni vuota/non valida
- 2 -> lista collezioni dell'utente già vuota
- 0 -> eliminazione totale avvenuta con successo
*/
int delete_user_collections(user my_user){
    if(my_user == NULL) return 1;

    int del_result = free_collections(&(my_user->collections_list_head));
    if(del_result == 1) return 2;
    return 0;
}




/*
Stampa una panoramica di tutte le collezioni e tutti i prodotti ad esse associati di un utente. Se l'utente non ha creato alcuna collezione, stamperà
"Non hai ancora creato nessuna collezione. Non c'è nulla da visualizzare nella tua panoramica."

Restituisce: 
- 1: utente non inizializzato
- 0: Stampando correttamente la panoramica
*/
int user_overview(user my_user){

    if(my_user == NULL) return 1;
    collections collections_list_head = my_user->collections_list_head;
    
    if(collections_list_head == NULL){
        printf("\x1b[35m" "Non hai ancora creato nessuna collezione. Non c'e' nulla da visualizzare nella tua panoramica.\n" "\x1b[0m");
        printf("\n");
        return 1;
    }
   
    int collection_counter = 1;
    //Stampa la panoramica: Per ogni collezione, stampa la lista dei prodotti. Se la collezione è ancora vuota, verrà stampata la stringa informativa apposita.
    while(collections_list_head != NULL){
        
        char collection_name[MAX_STR_LEN];
        get_collection_name(collections_list_head->collection_elem, collection_name);
        

        printf("\x1b[34m");
        printf("================================ [ %d: %s ] ================================\n", collection_counter, collection_name);
        printf("\x1b[0m");

        printf("\x1b[36m");
        print_collection(collections_list_head->collection_elem);
        printf("\x1b[0m");
            
        if(collections_list_head->collection_elem->products_list_head == NULL){
           printf("La collezione non contiene ancora alcun prodotto.\n");
        }
            
        else print_products(collections_list_head->collection_elem->products_list_head);
        printf("\n");
        collection_counter = collection_counter + 1;
        collections_list_head = collections_list_head->next;
    }

    return 0;

}