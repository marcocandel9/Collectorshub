#include "users_system.h"









/*
Implementa l'I/O per la registrazione di un nuovo utente. Chiede in input da tastiera un nuovo username, controlla che questo username non sia già utilizzato (sia già presente nella lista utenti), controlla che la password sia valida secondo la logica dell'ADT
(utilizzando la funzione validate_password di user.h) e in caso di esito positivo richiama la funzione insert_user_sorted di users.h per inserire il nuovo utente nella struttura dati utenti, con algoritmo di inserimento ordinato alfabeticamente.

Restituisce:
- un puntatore al nuovo utente creato
- un puntatore a NULL nel caso in cui la registrazione venga annullata dall'utente o ci siano problemi di lettura del buffer stdin
*/
user sys_register_user(users* users_list_head){

    int valid_password; 
    int valid_username;

    //variabile per lo svuotamento del buffer stdin
    char ch;
    char buffer[MAX_STR_LEN + 10];
    int buffer_len;

    char new_username[MAX_STR_LEN];
    char new_password[MAX_STR_LEN];
    user_role new_user_role = USER;

    user new_user = NULL;

    

    //LOGICA INSERIMENTO USERNAME IN INPUT (NB FGETS SVUOTA AUTOMATICAMENTE IL BUFFER DOPO L'INPUT)
    while(1){

        printf("\n\nInserisci il tuo nuovo username. (Massimo 19 caratteri consentiti, minimo 6, spazi non consentiti)\n");
        printf("PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n\n");

        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            //errore di lettura, restituisco un puntatore a NULL
            return NULL;
        }

        buffer_len = strlen(buffer); 
        //BUGFIX ADDITION
        //SE L'UTENTE INSERIVA UNA STRINGA MOLTO LUNGA, VENIVA ACCETTATA! Ciò è dovuto al comportamento di fgets, che
        //se riceve una stringa di dimensioni superiori alla dimensione massima del buffer (MAX_STR_LEN+10-1 caratteri)
        //TRONCA LA PRIMA PARTE LASCIANDO SOLTANTO LA SECONDA CHE PUÒ ESSERE DI DIMENSIONI INFERIORI A 19.
        //Nel caso in cui avvenga il troncamento l'ultimo carattere non sarà quello di newline.
        if(buffer_len > 0 && buffer[buffer_len-1] != '\n'){ //input troncato, stringa troppo lunga!
            while((ch = getchar()) != '\n' && ch != EOF); //svuoto il buffer (questa volta è necessario, perchè in caso
                                                          //di troncamento il buffer di input conterrà i caratteri residui, compreso
                                                          //il carattere di newline non letto.
            printf("Input troppo lungo! Riprova. \n");
            continue; //Ricomincio il ciclo while
        }



        //esempio input fgets: l'utente immette: "prova" e preme invio, il buffer conterrà:
        // 'p','r','o','v','a','\n','\0'//
        //è necessario rimuovere il carattere di newline
         //strlen conterà da 1 (p) a '\n' restituendo 6

        //Rimouvo il carattere di newline dalla stringa ottenuta in input nel buffer
        if(buffer_len > 0 && buffer[buffer_len - 1] == '\n'){
            //sostituisco il carattere di newline con il terminatore di stringa
            buffer[buffer_len - 1] = '\0';
            //decremento la lunghezza del buffer ottenendo l'effettiva lunghezza della stringa, compreso il terminatore
            buffer_len = buffer_len - 1;
        }


        //Controlli sull'input immesso dall'utente

        //l'utente ha immesso invio, vuole annullare la registrazione
        if(buffer_len == 0){
            printf("\n");
            return NULL; //restituisco un puntatore a NULL ed esco dalla funzione
        }

        //controllo lunghezza username, se inferiore a 6 caratteri riprovo
        if(buffer_len < 6){
            printf("Username troppo corto. Minimo 6 caratteri consentiti. Riprova.\n");
            continue; //riparte il ciclo while
        }

        if(buffer_len > 19){
            printf("Username troppo lungo. Massimo 19 caratteri consentiti. Riprova.\n");
            continue; //riparte il ciclo while
        }

        //controllo siano presenti degli spazi
        bool has_space = false;
        for (int i = 0; i < buffer_len; i++) {
            if (isspace((unsigned char)buffer[i])) {  // cast a unsigned char per sicurezza
            has_space = true;
            break;
        }
        }
        if (has_space) {
        printf("Spazi non consentiti. Riprova.\n");
        continue;  // Riparte il ciclo while per l'username
        }

        //Se la stringa ha superato i vari step di controllo, non contenendo cioè spazi, avendo una lunghezza compresa
        //fra minimo 6 massimo 19 caratteri, procedo al controllo dell'esistenza all'interno della lista utenti (username non disponibile)

        strcpy(new_username,buffer);

        //Controllo che l'utente non sia già presente nella lista utenti (DUPLICATI NON CONSENTITI)
        valid_username = user_exists(*users_list_head,new_username); 


        //Username disponibile, esce dal ciclo while (valid_username == 2: nessuna corrispondenza trovata nella lista, valid_username == 1: lista vuota, in entrambi casi l'username è disponibile)
        if(valid_username == 2 || valid_username == 1){
            printf("L'username e' disponibile.\n");
            break;
        }

        //Altrimenti notifica l'utente che l'username e già occupato e ricomincia il ciclo.
        printf("L'username ' già occupato.\n");
    }


    //LOGICA INSERIMENTO PASSWORD IN INPUT
    do{
        printf("Inserisci la tua nuova password. (Massimo 19 caratteri consentiti)\n\n");
        printf("La password deve contenere:\n");
        printf(" - Almeno 8 caratteri \n" );
        printf(" - Almeno una maiuscola \n");
        printf(" - Almeno una minuscola \n");
        printf(" - Almeno un numero \n");
        printf(" - Almeno un simbolo (SPAZI ESCLUSI)\n");
        printf(" - PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n\n");

        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            //errore di lettura, restituisco un puntatore a NULL
            return NULL;
        }
        
        buffer_len = strlen(buffer);

        if(buffer_len > 0 && buffer[buffer_len-1] != '\n'){ //input troncato, stringa troppo lunga!
            while((ch = getchar()) != '\n' && ch != EOF); //svuoto il buffer (questa volta è necessario, perchè in caso
                                                          //di troncamento il buffer di input conterrà i caratteri residui, compreso
                                                          //il carattere di newline non letto.
            printf("Input troppo lungo! Riprova. \n");
            continue; //Ricomincio il ciclo while
        }

        
        //Rimouvo il carattere di newline dalla stringa ottenuta in input nel buffer
        //strlen conterà da 1 (p) a '\n' restituendo 6
        
        if(buffer_len > 0 && buffer[buffer_len - 1] == '\n'){
            //sostituisco il carattere di newline con il terminatore di stringa
            buffer[buffer_len - 1] = '\0';
            //decremento la lunghezza del buffer ottenendo l'effettiva lunghezza della stringa
            buffer_len = buffer_len - 1;
        }


        //Controlli sull'input immesso dall'utente

        //l'utente ha immesso invio, vuole annullare la registrazione
        if(buffer_len == 0){
            printf("\n");
            return NULL; //restituisco un puntatore a NULL ed esco dalla funzione
        }


         //controllo lunghezza password, se inferiore a 6 caratteri riprovo
         if(buffer_len < 6){
            printf("Password troppo corta. Minimo 6 caratteri consentiti. Riprova.\n");
            continue; //riparte il ciclo while
        }
    
        if(buffer_len > 19){
            printf("Password troppo lunga. Massimo 19 caratteri consentiti. Riprova.\n");
            continue; //riparte il ciclo while
        }


        
        //Controllo che la password rispetti i requisiti del sistema definiti in validate_password di user.h
        valid_password = validate_password(buffer);

        if(valid_password == 1){
            printf("La password inserita non e' valida. Riprova.\n");
        };

        //altrimenti accetto la nuova password
        if(valid_password == 0){
            strcpy(new_password,buffer);
        };
    }
    while(valid_password != 0);

    //Una volta validato sia l'username che la nuova password, procedo all'inserimento del nuovo utente nella lista utenti.

    insert_user_sorted(users_list_head, new_username, new_password, new_user_role);

    search_user(*users_list_head,new_username, &new_user);

    return new_user;
}




/*
Implementa l'I/O Per il login di un utente

Restituisce:
- un puntatore al nuovo utente creato in caso di corretta autenticazione
- un puntatore a NULL in caso di errori del buffer o di annullamento da parte dell'utente
*/


user sys_login_user(users* users_list_head){

    //char per lo svuotamento del buffer
    char ch; 
    char buffer[MAX_STR_LEN+10];
    int buffer_len;


    int valid_username;
    int valid_password;

    user logging_user = NULL;
    char user_username[MAX_STR_LEN];
    char user_password[MAX_STR_LEN];



    
    //in caso di immissione con successo effettuo il break del ciclo while.
    while(1){

        printf("Inserisci il tuo username. \n");
        printf("PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n");
        
        if(fgets(buffer,sizeof(buffer),stdin)==NULL){
            //errore di lettura, restituisco un puntatore a NULL
            return NULL;
        }

        buffer_len = strlen(buffer);
        
        if(buffer_len > 0 && buffer[buffer_len-1] != '\n'){ //input troncato, stringa troppo lunga!
            while((ch = getchar()) != '\n' && ch != EOF); //svuoto il buffer (questa volta è necessario, perchè in caso
                                                          //di troncamento il buffer di input conterrà i caratteri residui, compreso
                                                          //il carattere di newline non letto.
            printf("Input troppo lungo! Riprova. \n");
            continue; //Ricomincio il ciclo while
        }


        //Rimouvo il carattere di newline dalla stringa ottenuta in input nel buffer
        if(buffer_len > 0 && buffer[buffer_len - 1] == '\n'){
            //sostituisco il carattere di newline con il terminatore di stringa
            buffer[buffer_len - 1] = '\0';
            //decremento la lunghezza del buffer ottenendo l'effettiva lunghezza della stringa, compreso il terminatore
            buffer_len = buffer_len - 1;
        }

        ///CONTROLLI STRINGA INSERITA IN INPUT///

        //l'utente ha immesso invio, vuole annullare la registrazione
        if(buffer_len == 0){
            printf("\n");
            return NULL; //restituisco un puntatore a NULL ed esco dalla funzione
        }
        
        //controllo lunghezza username, se inferiore a 6 caratteri riprovo
        if(buffer_len < 6){
            printf("Username troppo corto. Minimo 6 caratteri consentiti. Riprova.\n");
            continue; //riparte il ciclo while
        }
    
        if(buffer_len > 19){
            printf("Username troppo lungo. Massimo 19 caratteri consentiti. Riprova.\n");
            continue; //riparte il ciclo while
        }



        //controllo che l'username esista nella lista utenti
        valid_username = user_exists(*users_list_head,buffer);

        //se valid_úsername diverso da 0, utente non presente nella lista. Riprova
        if(valid_username != 0){
            printf("L'username non esiste. Riprova.\n");
            continue; //riparte il ciclo while
        }

        //altrimenti accede al contenuto informativo dell'utente prelevando la password e preparandola al confronto con il successivo input da terminale.
        

        //adesso il puntatore ad user logging_user punterà all'utente trovato
        strcpy(user_username,buffer);
        search_user(*users_list_head,user_username,&logging_user);
        get_password(logging_user,user_password);
        break; 
    }

    //A QUESTO PUNTO USER_PASSWORD CONTERRÀ LA PASSWORD DELL'UTENTE DA CONFRONTARE CON L'INPUT DA TERMINALE.
    //VERIFICA PASSWORD

    while(1){

        printf("Inserisci la tua password. \n\n");

        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            //errore di lettura, restituisco un puntatore a NULL
            return NULL;
        }

        buffer_len=strlen(buffer);


        if(buffer_len > 0 && buffer[buffer_len-1] != '\n'){ //input troncato, stringa troppo lunga!
            while((ch = getchar()) != '\n' && ch != EOF); //svuoto il buffer 
            printf("Input troppo lungo! Riprova. \n");
            continue; //Ricomincio il ciclo while
        }


        //rimouvo il carattere di newline
        if(buffer_len > 0 && buffer[buffer_len - 1] == '\n'){
            //sostituisco il carattere di newline con il terminatore di stringa
            buffer[buffer_len - 1] = '\0';
            //decremento la lunghezza del buffer ottenendo l'effettiva lunghezza della stringa, compreso il terminatore
            buffer_len = buffer_len - 1;
        }

        //se l'utente immette una stringa vuota, la funzione esce e restitusice NULL
        if(buffer_len == 0){
            logging_user = NULL;
            return NULL;
        }

         //controllo lunghezza password

         if(buffer_len < 6){
            printf("Password troppo corta. Minimo 6 caratteri consentiti. Riprova.\n");
            continue; //riparte il ciclo while
        }
    
        if(buffer_len > 19){
            printf("Password troppo lunga. Massimo 19 caratteri consentiti. Riprova.\n");
            continue; //riparte il ciclo while
        }


        //superato il controllo di validità della stringa, confronto con la password dell'utente.
        valid_password = strcmp(user_password,buffer);

        //Se la password è valida, esco dal ciclo while
        if(valid_password == 0){
            printf("Autenticazione effettuata con successo! \n");
            break;
        } else {         //Altrimenti, riparte il ciclo while e l'utente riprova l'inserimento della password
            printf("Password invalida. Riprova.\n");
            continue;
        }
    }

    //restituisco l'utente loggato.
    return logging_user;
}


    
