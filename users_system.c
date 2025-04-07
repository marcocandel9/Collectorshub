#include "users_system.h"









/*
Implementa l'I/O per la registrazione di un nuovo utente. Chiede in input da tastiera un nuovo username, controlla che questo username non sia già utilizzato (sia già presente nella lista utenti), controlla che la password sia valida secondo la logica dell'ADT
(utilizzando la funzione validate_password di user.h) e in caso di esito positivo richiama la funzione insert_user_sorted di users.h per inserire il nuovo utente nella struttura dati utenti, con algoritmo di inserimento ordinato alfabeticamente.

Restituisce:
- un puntatore al nuovo utente creato
- un puntatore a NULL nel caso in cui la registrazione venga annullata dall'utente o ci siano problemi di lettura del buffer stdin
*/
user sys_register_user(users* users_list_head){

    int is_valid;
    int username_available = 0;

    //variabile per lo svuotamento del buffer stdin
    char ch;

    //stringa e int di controllo per la stringa immessa in input dall'utente 
    char buffer[MAX_STR_LEN + 10];
    int buffer_len;

    char new_username[MAX_STR_LEN];
    char new_password[MAX_STR_LEN];
    user_role new_user_role = USER;

    user new_user = NULL;

    

    //LOGICA INSERIMENTO USERNAME IN INPUT (NB FGETS SVUOTA AUTOMATICAMENTE IL BUFFER DOPO L'INPUT)
    while(username_available == 0){

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

        //esempio input fgets: l'utente immette: "prova" e preme invio, il buffer conterrà:
        // 'p','r','o','v','a','\n','\0'//
        //è necessario rimuovere il carattere di newline

        //Rimouvo il carattere di newline dalla stringa ottenuta in input nel buffer
        //strlen conterà da 1 (p) a '\n' restituendo 6
        buffer_len = strlen(buffer);
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


        if(buffer_len > 19){
            printf("Password troppo lunga. Massimo 19 caratteri consentiti. Riprova.\n");
            continue; //riparte il ciclo while
        }

        
        //Controllo che la password rispetti i requisiti del sistema definiti in validate_password di user.h
        is_valid = validate_password(buffer);

        if(is_valid == 1){
            printf("La password inserita non e' valida. Riprova.\n");
        };

        //altrimenti accetto la nuova password
        if(is_valid == 0){
            strcpy(new_password,buffer);
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

    

    printf("Inserisci il tuo username. \n");
    printf("PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n");

    

    valid_username = user_exists(users_list_head,my_username);

}
*/

    
