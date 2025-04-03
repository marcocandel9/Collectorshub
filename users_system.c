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

Restituisce un puntatore al nuovo utente creato
*/
user sys_register_user(users* users_list_head){

    int is_valid;
    bool retry = false;
    int username_available = 0;

    char new_username[MAX_STR_LEN];
    char new_password[MAX_STR_LEN];
    user_role new_user_role = USER;

    user new_user = NULL;

    

    while(username_available == 0){

        printf("Inserisci il tuo nuovo username. (Massimo 19 caratteri consentiti, spazi non consentiti)");

        //La funzione str_len_control si occupa del controllo dei caratteri massimi inseriti.
        str_len_control(new_username);

        //Controllo che l'utente non sia già presente nella lista utenti (DUPLICATI NON CONSENTITI)
        username_available = user_exists(users_list_head,new_username); 

        //Se l'utente esiste già, richiede un nuovo username
        if(username_available != 0){
            printf("L'username è disponibile.\n");
        }
        
        printf("L'username è già occupato.\n");
    }


    printf("Inserisci la tua nuova password. (Massimo 19 caratteri consentiti)\n)");
    printf("   La password deve contenere:\n");
    printf(" - Almeno 8 caratteri \n" );
    printf(" - Almeno una maiuscola \n");
    printf(" - Almeno una minuscola \n");
    printf(" - Almeno un numero \n ");
    printf(" - Almeno un simbolo (SPAZI ESCLUSI)\n)");

    str_len_control(new_password);

    //Controllo sulla validità della nuova password
    do{

        is_valid = validate_password(new_password);

        if(is_valid == 1){
            printf("La password inserita non è valida. Reinserisci una nuova password\n");
            str_len_control(new_password);
        };
    }
    while(is_valid != 0);

    //Una volta validato sia l'username che la nuova password, procedo all'inserimento del nuovo utente nella lista utenti.

    insert_user_sorted(users_list_head, new_username, new_password, new_user_role);

    search_user(*users_list_head,new_username, &new_user);

    return new_user;
}

    


    
