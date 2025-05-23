#include "user.h"

const char allowed_symbols[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";


/* 
Crea un nuovo utente allocandone la memoria dinamicamente e associandone un proprio username, ruolo e password, quest'ultima validata 
dalla funzione validate_password.


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
Dati due ruoli in ingresso, ne confronta l'ordine di importanza
Nella logica del programma, un utente base non può compiere azioni da utente di gerarchia superiore (ADMIN o SUPERUSER)
Analogalmente, un ADMIN non può compiere azioni da SUPERUSER. Un SUPERUSER ha piena libertà, e in quel caso il controllo

Restituisce:
- 1 Se il primo ruolo è inferiore al secondo o uguale (accesso negato)
- 0 Se il primo ruolo è superiore al secondo o se sono entrambi di grado massimo (SUPERUSER) (accesso consentito)
*/
int check_user_privilege(user_role this_user_role, user_role that_user_role){
    
     // Se entrambi i ruoli sono SUPERUSER
     if (this_user_role == SUPERUSER && that_user_role == SUPERUSER) {
        return 0;  // Entrambi hanno il massimo livello di privilegio
    }

    // Se il primo ruolo è uguale o inferiore al secondo, restituisce 1 (accesso negato)
    if (this_user_role <= that_user_role) {
        return 1;  // Ruolo inferiore o uguale
    }

    // Se il primo ruolo è superiore al secondo, restituisce 0 (accesso consentito)
    return 0;

}




/*
Verifica che la password abbia le seguenti caratteristiche:
- Lunga almeno 7 caratteri (MIN STR LEN -1)
- Contiene almeno una maiuscola
- Contiene almeno una minuscola
- Contiene almeno un numero
- Contiene almeno un simbolo (SPAZI ESCLUSI), ammessi i seguenti:  (N.B È POSSIBILE MODIFICARE I CARATTERI MODIFICANDO L'ARRAY DI CARATTERI ALLOWED_SYMBOLS IN USER.H)
! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _

Utilizza la libreria <ctype.h> per il controllo dei singoli caratteri

Restituisce:
- 1 Se la password non è valida
- 0 Se la password è validata con successo
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
Aggancia una nuova lista collezioni all'utente

Restituisce:
- 1 Se l'utente è non esistente o non ancora inizializzato
*/
int insert_user_collections_list(user my_user, collections new_collections_list_head){

    if(my_user == NULL) return 1; //Utente non esistente o non ancora inizializzato

    (my_user)->collections_list_head = new_collections_list_head;
    return 0; //Success

}





/*
Modifica le credenziali di un utente già esistente, dopo aver validato la nuova password

Restituisce:
- 1 Se l'utente non è stato ancora inizializzato
- 2 Se la nuova password non è valida
- 0 Se le modifiche vanno a buon fine
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
Dealloca la memoria riservata ad un utente e a tutte le sue strutture dati associate, cancellandolo e impostanto il suo puntatore a NULL

Restituisce:
- 1 Se l'utente non è stato ancora inizializzato e quindi non esiste (puntatore a null)
- 0 Se l'eliminazione va a buon fine
*/
int delete_user(user* my_user){
    
    if(*my_user == NULL) return 1;

    //dealloco gerarchicamente tutte le strutture dati inferiori a user (collezioni, prodotti)
    free_collections(&((*my_user)->collections_list_head));

    free(*my_user);

    *my_user = NULL;

    return 0;
}

