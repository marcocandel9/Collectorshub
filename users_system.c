#include "users_system.h"





void str_len_control(char string_to_input[MAX_STR_LEN]){
    
    //Inizializzo la variabile per lo svuotamento del buffer I/O Stdin
    char ch;
    //array di caratteri temporaneo di dimensione sempre maggiore a MAX STR LEN utile al controllo dell'immissione di stringhe di dimensioni superiori a quella massima
    char temp[MAX_STR_LEN + 2]; 
    int temp_size = MAX_STR_LEN;


    //il ciclo while esce esclusivamente quando l'utente immette una stringa inferiore a 20 caratteri
    while(temp_size >= MAX_STR_LEN){

        scanf("%21s",temp);

        //strlen restituisce il numero di caratteri presenti nella stringa, terminatore escluso (es. ciao\0 restituisce )
        temp_size = strlen(temp);

        //se temp size è minore uguale a 19 (numero massimo consentito) può avvenire la modifica
        if(temp_size <= 19) {
            while((ch= getchar()) != '\n' && ch != EOF); //buffer reset
            strcpy(string_to_input,temp);
            return;
        }

        printf("La stringa inserita eccede il numero di caratteri consentito. Riprova. \n\n");
        while((ch= getchar()) != '\n' && ch != EOF); //buffer reset
    }
}






/*
Implementa l'I/O per la registrazione di un nuovo utente. Chiede in input da tastiera un nuovo username, controlla che questo username non sia già utilizzato (sia già presente nella lista utenti), controlla che la password sia valida secondo la logica dell'ADT
(utilizzando la funzione validate_password di user.h) e in caso di esito positivo richiama la funzione insert_user_sorted di users.h per inserire il nuovo utente nella struttura dati utenti, con algoritmo di inserimento ordinato alfabeticamente.

Restituisce:
- un puntatore al nuovo utente creato
- un puntatore a NULL nel caso in cui la registrazione venga annullata dall'utente
*/
user sys_register_user(users* users_list_head){

    int is_valid;
    int username_available = 0;

    char new_username[MAX_STR_LEN];
    char new_password[MAX_STR_LEN];
    user_role new_user_role = USER;

    user new_user = NULL;

    

    //LOGICA INSERIMENTO USERNAME IN INPUT
    while(username_available == 0){

        printf("Inserisci il tuo nuovo username. (Massimo 19 caratteri consentiti, spazi non consentiti)\n");
        printf("PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n");

        
        //La funzione str_len_control si occupa dell'immissione della stringa in output e del controllo dei caratteri massimi inseriti.
        str_len_control(new_username);
        

        //Se la stringa inserita è VUOTA, annullo la registrazione
        if(strlen(new_username) == 0){
            return NULL; //ritorno NULL ed esco dalla funzione di registrazione
        }


        //Controllo che l'utente non sia già presente nella lista utenti (DUPLICATI NON CONSENTITI)
        username_available = user_exists(*users_list_head,new_username); 


        //Username disponibile, esce dal ciclo while
        if(username_available != 0){
            printf("L'username e' disponibile.\n");
            break;
        }

        //Altrimenti notifica l'utente che l'username e già occupato e ricomincia il ciclo.
        printf("L'username ' già occupato.\n");
    }


    //LOGICA INSERIMENTO PASSWORD IN INPUT
    do{
        printf("Inserisci la tua nuova password. (Massimo 19 caratteri consentiti)\n)");
        printf("   La password deve contenere:\n");
        printf(" - Almeno 8 caratteri \n" );
        printf(" - Almeno una maiuscola \n");
        printf(" - Almeno una minuscola \n");
        printf(" - Almeno un numero \n ");
        printf(" - Almeno un simbolo (SPAZI ESCLUSI)\n)");
        printf(" - PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n)");

        //Immissione nuova password in input e controllo della lunghezza dei caratteri massima
        str_len_control(new_password);


        //Se l'utente inserisce una stringa vuota, annullo la registrazione e restituisco un puntatore a NULL
        if(strlen(new_password) == 0){
            return NULL;
        }

        //Controllo che la password rispetti i requisiti del sistema definiti in validate_password di user.h
        is_valid = validate_password(new_password);

        if(is_valid == 1){
            printf("La password inserita non e' valida.\n");
        };
    }
    while(is_valid != 0);

    //Una volta validato sia l'username che la nuova password, procedo all'inserimento del nuovo utente nella lista utenti.

    insert_user_sorted(users_list_head, new_username, new_password, new_user_role);

    search_user(*users_list_head,new_username, &new_user);

    return new_user;
}




/*
Implementa l'I/O Per il login di un nuovo utente

Restituisce un puntatore al nuovo utente creato



user sys_login_user(users* users_list_head){

    //char per lo svuotamento del buffer
    char ch; 
    char my_username[MAX_STR_LEN];
    int valid_username = 1;

    //

    printf("Inserisci il tuo username:\n");
    scanf("20s",my_username);

    //

    valid_username = user_exists(users_list_head,my_username);


}
*/

    
