#include "system.h"




/*
Funzione che implementa il controllo della stringa in input. Controlla i seguenti criteri:
    1) Che la stringa passata in ingresso non sia stata troncata -> input troppo lungo, riprova
    2) Che la stringa passata in ingresso non sia minore di min_len caratteri -> Input troppo corto, riprova
    3) Che la stringa passata in ingresso non sia maggiore di max_len caratteri -> Input troppo lungo, riprova
    4) Se il flag check_space è impostato su true, allora controlla anche che la stringa non contenga spazi.
    3) Rimuove il carattere a capo dalla stringa prelevata dal buffer di input

    Parametri:
        output_string: array di caratteri nel quale verrà inserita la stringa una volta superati i controlli
        check_space: valore booleano true o false che attiva o disattiva il controllo sulla presenza di spazi
        min_len_plus1: il numero minimo di caratteri che la stringa immessa in input da utente deve contenere, più 1
        max_len_plus1: il numero massimo di caratteri che la stringa immessa in input da utente deve contenere, più 1

    Restituisce:
         0 -> Se la stringa passata in input è stata correttamente inserita e viene passata al chiamante tramite la stringa output_string
         1 -> Se l'utente immette in input una stringa vuota, indicando l'operazione di ANNULLAMENTO.
         2 -> In caso di errori di lettura del buffer di input (FATAL ERROR:2)

    N.B: max_len_plus1 e min_len_plus1 RAPPRESENTANO LA DIMENSIONE MINIMA E MASSIMA DEGLI ARRAY ACCETTATI IN INPUT, COMPRESO IL TERMINATORE DI STRINGA. 
    //ES. Se MAX_LEN_PLUS1 sarà 20, il numero di caratteri effettivi accettati in input (escludendo il terminatore) saranno 19.
*/ 
int sys_input_string_checker(char output_string[MAX_STR_LEN], bool check_space, int min_len_plus1, int max_len_plus1){

    char ch;
    char buffer[MAX_STR_LEN + 10];
    int buffer_len;
    

    while(1){

        //resetto il flag che segnala che la stringa contiene spazi, utilizzata nel caso in cui il check degli spazi è attivo (check_space == true)
        bool has_space = false;

        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            //errore di lettura, restituisco un puntatore a NULL
            return 2;
        }

        buffer_len = strlen(buffer); 

        if(buffer_len > 0 && buffer[buffer_len-1] != '\n'){ //input troncato, stringa troppo lunga!
            while((ch = getchar()) != '\n' && ch != EOF); //svuoto il buffer (questa volta è necessario, perchè in caso
                                                          //di troncamento il buffer di input conterrà i caratteri residui, compreso
                                                          //il carattere di newline non letto.

            printf("\n");
            printf("Input troppo lungo! Riprova. \n");
            printf("\n");
            continue; //Ricomincio il ciclo while
        }


        //Rimouvo il carattere di newline dalla stringa ottenuta in input nel buffer
        if(buffer_len > 0 && buffer[buffer_len - 1] == '\n'){
            //sostituisco il carattere di newline con il terminatore di stringa
            buffer[buffer_len - 1] = '\0';
            //decremento la lunghezza del buffer ottenendo l'effettiva lunghezza della stringa, compreso il terminatore
            buffer_len = buffer_len - 1;
        }


        //Controlli sull'input immesso dall'utente

        //l'utente ha immesso invio, vuole annullare l'operazione
        if(buffer_len == 0){
            strcpy(output_string,buffer); //output string sarà adesso una stringa vuota
            return 1; //restituisco 1
        }

         //se il flag check_space è settato su true, allora avverrà anche il controllo degli spazi
         if(check_space == true){

            for (int i = 0; i < buffer_len; i++) {
                if (isspace((unsigned char)buffer[i])) {  // cast a unsigned char per sicurezza
                    has_space = true;
                    break;
                    }
                }
                if (has_space) {
                    printf("Spazi non consentiti. Riprova.\n");
                    continue;  // Riparte il ciclo while per la stringa in ingresso.
                    }

        }

        //controllo lunghezza username, se inferiore a 6 caratteri riprovo
        if(buffer_len < min_len_plus1-1){
            printf("\n");
            printf("Stringa troppo corta. Minimo %d caratteri consentiti. Riprova.\n", min_len_plus1-1);
            printf("\n");
            continue; //riparte il ciclo while
        }

        if(buffer_len > max_len_plus1-1){
            printf("\n");
            printf("Stringa troppo lunga. Massimo %d caratteri consentiti. Riprova.\n", max_len_plus1-1);
            printf("\n");
            continue; //riparte il ciclo while
        }

       

        break;

    }

    strcpy(output_string,buffer);
    return 0;

}




/*
Semplice funzione che restituisce 0 se l'utente immette 0 in input, restituisce 1 se l'utente inserisce 1 in input.

Restituisce:
    2 -> In caso di errori di lettura del buffer di input
    1 -> Se l'utente inserisce 1
    0 -> Se l'utente inserisce 0
    
*/
int ask_confirmation(){

    char ch;
    char buffer[4];
    int buffer_len;

    while(1){

        if(fgets(buffer,sizeof(buffer),stdin)==NULL){
            return 2; //ERRORE di lettura buffer di input
        }

        buffer_len = strlen(buffer);

        //controllo sul troncamento in input
        if(buffer[buffer_len - 1] != '\n'){
            printf("\n");
            printf("Input troppo lungo. Inserisci una sola cifra: 0 o 1.\n");
            printf("\n");
            while((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        //rimuovo il newline
        buffer[buffer_len - 1] = '\0';
        buffer_len = buffer_len - 1;
        
        if(buffer_len > 1){
            printf("\n");
            printf("Input troppo lungo. Inserisci una sola cifra: 0 o 1.\n");
            printf("\n");
            continue;
        }

        if(buffer_len == 0){
            printf("\n");
            printf("Input invalido in quanto hai inserito una stringa vuota. Inserisci una sola cifra: 0 o 1.\n");
            printf("\n");
            continue;
        }

        if(strcmp(buffer, "0") == 0) return 0;
        if(strcmp(buffer, "1") == 0) return 1;

        printf("\n");
        printf("Input invalido. Inserisci una sola cifra: 0 o 1.\n");
        printf("\n");
        continue;
    }
}
       




/*
Implementa l'I/O per la registrazione di un nuovo utente. Chiede in input da tastiera un nuovo username invocando la funzione
sys_input_string_checker, controlla che questo username non sia già utilizzato (sia già presente nella lista utenti), 
controlla che la password sia valida secondo la logica dell'ADT (utilizzando la funzione validate_password di user.h) e 
in caso di esito positivo richiama la funzione insert_user_sorted di users.h per inserire il nuovo utente nella struttura dati utenti, 
con algoritmo di inserimento ordinato alfabeticamente.

Restituisce:
- un puntatore al nuovo utente creato
- un puntatore a NULL nel caso in cui la registrazione venga annullata dall'utente o ci siano problemi di lettura del buffer stdin
*/
user sys_register_user(users* users_list_head){

    int valid_password; 
    int valid_username;

    //variabili per il controllo della stringa in input
    char username_io_string[MAX_STR_LEN];
    char password_io_string[MAX_STR_LEN];
    bool check_space = true; //l'username non può contenere spazi, effettuo il controllo sulla stringa in input.
    int string_checker_result;


    user_role new_user_role = USER;

    user new_user = NULL;

    printf(ANSI_BOLD ANSI_COLOR_BLUE"\n");
    division_break_lines("AREA REGISTRAZIONE",60);
    printf( ANSI_COLOR_CYAN);
    printf("\nBenvenuto/a nell'area registrazione!\n");
    printf(BOLD_OFF ANSI_COLOR_RESET);
    
    //INSERIMENTO NUOVO USERNAME
    while(1){

        printf("\n" ANSI_BOLD);
        printf("Inserisci il tuo nuovo username. (Massimo %d caratteri consentiti, minimo %d, spazi non consentiti)\n",MAX_STR_LEN-1,MIN_STR_LEN-1);
        printf("PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n");
        printf("\n" BOLD_OFF);

        string_checker_result = sys_input_string_checker(username_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
        
        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD );
                printf("Registrazione annullata correttamente. \n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return NULL;
            case 2:
                printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return NULL;
            default: 
                break;
        }


        //Controllo che l'utente non sia già presente nella lista utenti (DUPLICATI NON CONSENTITI)
        valid_username = user_exists(*users_list_head,username_io_string); 


        //Username disponibile, esce dal ciclo while (valid_username == 2: nessuna corrispondenza trovata nella lista, valid_username == 1: lista vuota, in entrambi casi l'username è disponibile)
        if(valid_username == 2 || valid_username == 1){
            printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
            printf("L'username e' disponibile.\n");
            printf("\n"ANSI_COLOR_RESET BOLD_OFF);
            break;
        }

        //Altrimenti notifica l'utente che l'username e già occupato e ricomincia il ciclo while.
        printf("\n"ANSI_COLOR_RED ANSI_BOLD);
        printf("L'username e' gia' occupato.\n");
        printf("\n"ANSI_COLOR_RESET BOLD_OFF);
        continue;
    }
    
        

    //INSERIMENTO NUOVA PASSWORD
    //clear_screen();
    
    //N.B: Nonostante la password NON POSSA CONTENERE SPAZI, disattivo in questo caso il controllo in quanto sarebbe ridondante,
    //Venendo già realizzato dalla funzione validate_password.
    check_space = false;


    
    while(1){
        printf("\n" ANSI_BOLD ANSI_COLOR_MAGENTA);
        printf("Inserisci la tua nuova password. (Massimo %d caratteri consentiti)\n\n", MAX_STR_LEN-1);
        printf(ANSI_COLOR_RESET ANSI_BOLD);
        printf("La password deve contenere:\n" BOLD_OFF);
        printf(" - Almeno %d caratteri \n", MIN_STR_LEN-1 );
        printf(" - Almeno una maiuscola \n");
        printf(" - Almeno una minuscola \n");
        printf(" - Almeno un numero \n");
        printf(" - Almeno un simbolo (SPAZI ESCLUSI)\n");
        printf(" - PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n");
        printf("\n");

        //Controllo che la password rispetti i requisiti del sistema definiti in validate_password di user.h
        string_checker_result = sys_input_string_checker(password_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("Registrazione annullata correttamente. \n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return NULL;
            case 2:
                printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return NULL;
            default: 
                break;
        }
        
        //Secondo controllo sulla password secondo i criteri dettati da user.h
        string_checker_result = validate_password(password_io_string);
        
        if(string_checker_result == 1) {
            printf("\n" ANSI_COLOR_RED);
            printf("Password non valida. Contiene caratteri non ammessi e/o spazi. Riprova \n");
            printf("\n" ANSI_COLOR_RESET);
            continue;
        }
        if(string_checker_result == 0) break; //altrimenti la password è validata, posso uscire dal ciclo while.
    }

    
    //Una volta validato sia l'username che la nuova password, procedo all'inserimento del nuovo utente nella lista utenti.

    insert_user_sorted(users_list_head, username_io_string, password_io_string, new_user_role);

    search_user(*users_list_head,username_io_string, &new_user);

    printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
    printf("Registrazione effettuata con successo!\n");
    printf("\n" ANSI_COLOR_RESET BOLD_OFF);

    return new_user;
}





/*
Gestisce la procedura di login da terminale per un utente registrato.

La funzione richiede all’utente l’inserimento dello username e della password,
validando l’input tramite sys_input_string_checker.  
Se l' username esiste nella lista utenti, la funzione confronta la password 
inserita con quella associata all’utente nella struttura user.

Utilizza:
- division_break_lines() per la stampa grafica dell’intestazione
- user_exists() per verificare la presenza dell’utente
- search_user() e get_password() per il recupero delle credenziali
- strcmp() per il confronto diretto tra stringhe di password

Parametri:
- users_list_head: puntatore alla testa della lista degli utenti registrati.

Valori di ritorno:
- Puntatore all’utente autenticato (struttura user) se login corretto
- NULL se l’utente annulla il login o si verifica un errore di input

Note:
- Il login è case-sensitive per username e password.
- L’annullamento può essere effettuato in qualsiasi fase (username o password).
*/


user sys_login_user(users* users_list_head){

    int valid_username;
    int valid_password;

    bool check_space = true; //la password in input non può contenere spazi, effettuo il controllo sulla stringa in input.
    int string_checker_result;
    
    char username_io_string[MAX_STR_LEN];
    char password_io_string[MAX_STR_LEN];

    user logging_user = NULL;
    char user_password[MAX_STR_LEN];
    
    printf(ANSI_COLOR_BLUE ANSI_BOLD);
    division_break_lines("AREA LOGIN", 60);
    printf(ANSI_COLOR_RESET BOLD_OFF);
    printf("\n");
    printf(ANSI_BOLD ANSI_COLOR_CYAN "Benvenuto/a nell'area login!\n" ANSI_COLOR_RESET BOLD_OFF); 
    printf("\n");

    //in caso di immissione con successo effettuo il break del ciclo while.
    while(1){

        printf(ANSI_BOLD);
        printf("\n");
        printf("Inserisci il tuo username. \n");
        printf("Inserisci una stringa vuota premendo invio per annullare il login.\n");
        printf("\n");
        printf(BOLD_OFF);
        
        string_checker_result = sys_input_string_checker(username_io_string, check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Login annullato correttamente. \n");
                printf("\n");
                return NULL;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                printf("\n");
                return NULL;
            default: 
                break;
        }


        //controllo che l'username esista nella lista utenti
        valid_username = user_exists(*users_list_head,username_io_string);

        //se valid_úsername diverso da 0, utente non presente nella lista. Riprova
        if(valid_username != 0){
            printf("\nL'username non esiste. Riprova.\n\n");
            continue; //riparte il ciclo while
        }

        //altrimenti accede al contenuto informativo dell'utente prelevando la password e preparandola al confronto con il successivo input da terminale.
    
        //adesso il puntatore ad user logging_user punterà all'utente trovato
        search_user(*users_list_head,username_io_string,&logging_user);
        get_password(logging_user,user_password);
        break; 
    }

    //A QUESTO PUNTO USER_PASSWORD CONTERRÀ LA PASSWORD DELL'UTENTE DA CONFRONTARE CON L'INPUT DA TERMINALE.
    //VERIFICA PASSWORD

    while(1){
        
        printf("\n");
        printf("Inserisci la tua password. \n");
        printf("\n");

        string_checker_result = sys_input_string_checker(password_io_string, check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Login annullato correttamente. \n");
                printf("\n");
                return NULL;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                printf("\n");
                return NULL;
            default: 
                break;
        }


        //superato il controllo di validità della stringa, confronto con la password dell'utente.
        valid_password = strcmp(user_password,password_io_string);

        //Se la password è valida, esco dal ciclo while
        if(valid_password == 0){
            break;
        } else {         //Altrimenti, riparte il ciclo while e l'utente riprova l'inserimento della password
            printf("\n");
            printf("Password invalida. Riprova.\n");
            printf("\n");
            continue;
        }
    }
    
    printf("\n");
    printf(ANSI_COLOR_GREEN "Autenticazione effettuata con successo! \n"ANSI_COLOR_RESET);
    printf("\n");
    //restituisco l'utente loggato.
    return logging_user;
}




/*
Gestisce l’I/O per la modifica dello username di un utente registrato.

L’utente inserisce un nuovo username da terminale. Se lo username è valido e disponibile,
viene modificato all’interno della struttura dati mediante la funzione 
search_and_modify_user_credentials.

Utilizza:
- sys_input_string_checker() per validare l’input da terminale
- user_exists() per verificare la disponibilità del nuovo username
- search_and_modify_user_credentials() per aggiornare lo username all’interno della lista utenti
- strcpy() per aggiornare la variabile current_username con il nuovo valore

Parametri:
- current_username: stringa contenente lo username attuale. Se la modifica ha successo, viene aggiornato con il nuovo valore.
- users_list_head: puntatore alla testa della lista utenti (passato per riferimento).

Valori di ritorno:
- 1 -> operazione annullata dall’utente (username lasciato invariato)
- 2 -> errore di lettura del buffer di input
- 3 -> errore interno nella modifica dello username (utente non trovato)
- 0 -> modifica completata correttamente

Note:
- Se l’utente inserisce una stringa vuota, l' username resta invariato.
- Lo username non può contenere spazi e deve rispettare i limiti di lunghezza MIN/MAX.
*/

int sys_modify_username(char current_username[MAX_STR_LEN], users* users_list_head){

    
    char empty_string[MAX_STR_LEN] = "";

    int string_checker_result;

    int valid_username;

    char username_io_string[MAX_STR_LEN];

    bool check_space = true; //l'username in input non può contenere spazi, effettuo il controllo sulla stringa in input.

    while(1){

        printf("\n");
        printf("Inserisci il tuo nuovo username. \n");
        printf("Se vuoi lasciare invariato il tuo username, inserisci una stringa vuota. \n");
        printf("\n");
        
        string_checker_result = sys_input_string_checker(username_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("L'username rimarra' invariato.\n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                printf("\n");
                return 2;
            default: 
                break;
        }


       

        //utilizzo la funzione user_exists per cercare il nome utente in lista. Se il nome utente è disponibile, proseguo alla modifica dell'username, altrimenti riprovo
        valid_username = user_exists(*(users_list_head),username_io_string);
        if(valid_username  == 0){
            printf("Il nome utente non e' disponibile. Riprova.\n");
            continue;
        }


        //chiamo la funzione search_and_modify_user_Credentials per modificarne l'username.
        int result = search_and_modify_user_credentials(users_list_head, current_username, username_io_string, empty_string);

        if(result == 0){
            break;
        }

        //altrimenti restituisco errore di modifica dell'utente in lista.
        printf("FATAL ERROR 3: USER NOT FOUND\n\n");
        return 3;
    }

    //Tutto è andato a buon fine
    //aggiorno il current username passato dal chiamante
    strcpy(current_username, username_io_string);
    return 0;

}





/*
Analogo a sys_modify_username, con aggiuntiva chiamata alla funzione validate_password di user.h.
    Restituisce:
        1 In caso di annullamento dell'operazione da parte dell'utente
        2 In caso di errori di lettura del buffer di input
        3 In caso di errori di modifica dell'utente nella struttura dati (ES. UTENTE NON TROVATO O LISTA VUOTA)
        0 Se tutto va a buon fine
    N.B: La stringa current_password, nel caso di effettuata modifica, viene aggiornata con la nuova password inserita dall'utente.
*/
int sys_modify_password(char user_username[MAX_STR_LEN], char current_password[MAX_STR_LEN], users* users_list_head){

    char empty_string[MAX_STR_LEN] = "";

    int string_checker_result;

    char password_io_string[MAX_STR_LEN];

    bool check_space = true;

    int valid_password;



    while(1){

        printf("\n");
        printf("Inserisci la tua nuova password. \n");
        printf("Se vuoi lasciare invariata la tua password, inserisci una stringa vuota. \n");
        printf("\n");

        string_checker_result = sys_input_string_checker(password_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
        
        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("La password rimarra' invariata.\n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                printf("\n");
                return 2;
            default: 
                break;
        }

        //Validazione nuova password tramite la funzione validate_password
        
        valid_password = validate_password(password_io_string);

        if(valid_password == 1){
            printf("\n");
            printf("La password non e' valida, deve contenere i seguenti requisiti:\n");
            printf("- Lunga almeno 8 caratteri\n");
            printf("- Contiene almeno una maiuscola\n");
            printf("- Contiene almeno una minuscola\n");
            printf("- Contiene almeno un numero\n");
            printf("- Contiene almeno un simbolo (SPAZI ESCLUSI)\n");
            printf("Riprova.\n");
            printf("\n");
            continue;
        }
        //altrimenti, la password è stata correttamente validata, esco dal ciclo while e procedo alla modifica
        break;
    }


    int result = search_and_modify_user_credentials(users_list_head, user_username, empty_string, password_io_string);

    if(result == 1 || result == 2 || result == 3){
        printf("FATAL ERROR 3: USER NOT FOUND ");
        return 3;
    }

    //Tutto è andato a buon fine, restituisco 0.

    strcpy(current_password, password_io_string);
    return 0;
}





/*
Implementa l'I/O Per la modifica delle credenziali di un utente. 
Parametri: 
Il puntatore passato per riferimento all'utente GIÀ LOGGATO
Il puntatore alla testa della lista utenti

Restituisce:
  0 Se tutto va a buon fine
  1 In caso di annullamento della modifica delle credenziali
  2 In caso di errori di lettura del buffer di input (FATAL ERROR 2)
  3 In caso di errori di lettura dell'utente in lista (FATAL ERROR 3)
*/
int sys_modify_credentials(user* my_user, users* users_list_head){

    
    int string_checker_result;
    int auth_username;
    int auth_password;

    char password_io_string[MAX_STR_LEN];
    char username_io_string[MAX_STR_LEN];

    bool check_space = true;

    char user_username[MAX_STR_LEN];
    char user_password[MAX_STR_LEN];

    //copio le stringhe username e password dell'utente passato in ingresso nelle variabili temporanee valid_username e valid_password utilizzate per l'autenticazione
    get_username(*my_user, user_username);
    get_password(*my_user, user_password);

    printf("\n");
    printf(ANSI_BOLD ANSI_COLOR_BLUE);
    division_break_lines("MODIFICA CREDENZIALI",44);
    printf("\n"ANSI_COLOR_RESET);
    printf("Benvenuto nell'area di modifica delle credenziali. \n");
    printf("Per poter procedere, e' necessario riconfermare l'autenticazione tramite password. \n" BOLD_OFF);
    

    while(1){

        printf("\n");
        printf(ANSI_BOLD);
        printf("Per annullare la modifica delle tue credenziali, immetti una stringa vuota. \n");
        printf("Inserisci la tua password per procedere con il cambiamento delle credenziali. \n");
        printf(BOLD_OFF);
        printf("\n");

        string_checker_result = sys_input_string_checker(password_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
        
        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Operazione di modifica credenziali annullata correttamente.\n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                printf("\n");
                return 2;
            default: 
                break;
        }


        //superato il controllo di validità della stringa, confronto con la password dell'utente.
        auth_password = strcmp(user_password,password_io_string);

        //Se la password è valida, esco dal ciclo while
        if(auth_password == 0){
            break;
        } else {         //Altrimenti, riparte il ciclo while e l'utente riprova l'inserimento della password
            printf("Password invalida. Riprova.\n");
            continue;
        }
    }

    //Se la password è stata verificata con successo, procedo alla modifica delle credenziali

    //chiamo le funzioni system_modify_username e system_modify_password:

    printf(ANSI_COLOR_GREEN"\nPassword verificata con successo!\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"\nSi procede con la modifica delle proprie credenziali.\n"ANSI_COLOR_RESET);
    printf("E' possibile modificare soltanto uno dei campi username/password, immettendo una stringa vuota.\n");



    int temp_case_1 = 0;

    temp_case_1 = sys_modify_username(user_username, users_list_head);

    switch(temp_case_1) {
        case(0):
            printf("Username modificato con successo. \n\n");
            break;
        case(1):
            printf("Il nome utente rimarra' invariato. Si procede con la modifica della password.\n\n");
            break;
        case(2):
            printf("Errore lettura buffer di input! (FATAL ERROR: 2)\n\n");
            return 2;
            break;
        case(3):
            printf("Errore lettura dell'utente nella lista utenti! (FATAL ERROR:3)\n\n");
            return 3;
    }



    int temp_case_2 = 0;

    temp_case_2 = sys_modify_password(user_username, user_password, users_list_head);

    switch(temp_case_2) {
        case(0):
            printf("Password modificata con successo. \n\n");
            break;
        case(1):
            printf("\n\n");
            break;
        case(2):
            printf("Errore lettura buffer di input! (FATAL ERROR: 2)\n\n");
            return 2;
        case(3):
            printf("Errore lettura dell'utente nella lista utenti! (FATAL ERROR:3)\n\n");
            return 3;
    }

    if (temp_case_1 == 0) {
        set_username(*(my_user), user_username);
    }
    if (temp_case_2 == 0) {
        set_password(*(my_user), user_password);
    }
    

    return 0;
}




/*
Gestisce l'I/O per l'eliminazione dell’account da parte di un utente loggato.

La funzione non esegue la ricerca dell' username, ma assume che il nome utente 
sia già noto (es. utente attualmente loggato).  
Richiede all’utente di confermare l’operazione inserendo la propria password.  
Solo dopo verifica della correttezza della password, l’eliminazione viene eseguita
tramite la funzione remove_user.

Utilizza:
- sys_input_string_checker() per acquisire e validare la password da terminale
- search_user() per ottenere il puntatore alla struttura user corrispondente
- get_password() per recuperare la password dell’utente
- remove_user() per effettuare la rimozione effettiva dalla lista utenti
- strcmp() per confrontare le password

Parametri:
- users_list_head: puntatore alla testa della lista utenti (passato per riferimento)
- user_username: stringa contenente lo username dell’utente da eliminare

Valori di ritorno:
- 1 -> l’utente ha annullato volontariamente l’eliminazione
- 2 -> errore di lettura del buffer di input
- 3 -> utente non trovato o errore nella rimozione dalla lista
- 0 -> eliminazione eseguita correttamente
*/
int sys_delete_user(users* users_list_head, char user_username[MAX_STR_LEN]){


        user user_to_del = NULL;
        char user_password[MAX_STR_LEN];

        int string_checker_result; 
        char password_io_string[MAX_STR_LEN];
        bool check_space = true;

        search_user(*(users_list_head),user_username,&(user_to_del));
        
        get_password(user_to_del,user_password);

        printf(ANSI_BOLD ANSI_COLOR_CYAN);
        printf("\n");
        division_break_lines("AREA ELIMINAZIONE UTENTE",60);
        printf("\n");
        printf("Benvenuto nell'area di eliminazione del tuo account utente.\n");
        printf(ANSI_COLOR_MAGENTA "QUESTA AZIONE SARA' DEFINITIVA. Si consiglia di procedere con cautela.\n" ANSI_COLOR_RESET);
        printf("\n");

        while(1){

            printf("\n");
            printf("Per procedere all'eliminazione, e' necessario inserire la propria password.");
            printf(ANSI_COLOR_RED ANSI_BOLD" UNA VOLTA VERIFICATA, NON PUOI TORNARE INDIETRO!\n");
            printf(ANSI_COLOR_RESET BOLD_OFF);

            printf("Se si vuole annullare l'eliminazione del proprio profilo, inserire una stringa vuota.\n");
            printf("\n");

            string_checker_result = sys_input_string_checker(password_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
            
            switch(string_checker_result){
                case 1:
                    printf("\n");
                    printf("Eliminazione del proprio profilo annullata correttamente.\n\n");
                    printf("\n");
                    return 1;
                case 2:
                    printf("\n");
                    printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n\n");
                    printf("\n");
                    return 2;
                default: 
                    break;
            }
            
            //superato il controllo di validità della stringa, confronto con la password dell'utente.
            
            int auth_password = strcmp(user_password, password_io_string);
    
            //Se la password è valida, esco dal ciclo while
            if(auth_password == 0){
                break;
            } else {         //Altrimenti, riparte il ciclo while e l'utente riprova l'inserimento della password
                printf(ANSI_COLOR_RED);
                printf("\nPassword invalida. Riprova.\n");
                printf(ANSI_COLOR_RESET);
                continue;
            }
        }
    
        //Se la password è stata verificata con successo, procedo all'operazione di eliminazione
        printf(ANSI_COLOR_GREEN ANSI_BOLD);
        printf("\nPassword verificata con successo!\n");
        printf(ANSI_COLOR_RESET BOLD_OFF);
        
        int result = remove_user(users_list_head, user_username);

        if(result != 0){
            return 3; //FATAL ERROR 3 (NON È STATO POSSIBILE ACCEDERE ALLA LISTA UTENTI/ L'UTENTE NON È STATO TROVATO)
        }

        printf(ANSI_COLOR_GREEN ANSI_BOLD);
        printf("\nL'UTENTE E' STATO DEFINITIVAMENTE ELIMINATO.\n");
        printf(ANSI_COLOR_RESET ANSI_BOLD);
        return 0;

}
    




/*
Gestisce l’I/O per la visualizzazione della lista delle collezioni associate a un utente.

La funzione verifica che l’utente loggato sia valido e utilizza print_collections per stampare 
a terminale tutte le collezioni a lui associate.  
In caso di lista vuota o utente non inizializzato, viene restituito un codice di errore.

Utilizza:
- division_break_lines() per stampare l’intestazione decorativa della sezione
- print_collections() per stampare la lista delle collezioni associate all’utente

Parametri:
- logged_user: puntatore alla struttura user attualmente loggata

Valori di ritorno:
- 1 -> l’utente è NULL o non possiede alcuna collezione
- 0 -> stampa effettuata correttamente
*/
int sys_print_user_collections(user logged_user){

    //Controllo che il puntatore non punti a NULL
    if(logged_user == NULL){
        printf("\n");
        printf("FATAL ERROR 1: USER POINTS TO NULL\n");
        printf("\n");
        return 1;
    }

    printf(ANSI_COLOR_BLUE ANSI_BOLD "\n");
    division_break_lines("LISTA COLLEZIONI",60);
    printf(ANSI_COLOR_RESET BOLD_OFF);

    printf(ANSI_BOLD);
    char username[MAX_STR_LEN];
    get_username(logged_user,username);
    printf("Lista delle collezioni di %s:\n",username);
    printf(BOLD_OFF ANSI_COLOR_CYAN);
    collections user_collections = NULL;
    get_collection_list(logged_user,&(user_collections));
    int result = print_collections(user_collections);
    printf(ANSI_COLOR_RESET);

    //La funzione print collections restituisce 1 se la lista è vuota -> gestisco questo caso:

    if(result == 1){
        printf("\n" ANSI_COLOR_RED ANSI_BOLD);
        printf("La tua lista collezioni e' vuota!\n");
        printf("\n"ANSI_COLOR_RESET BOLD_OFF);
        return 1;
    }

    //Altrimenti tutto va a buon fine, restituisco 0.
    return 0; 
}




/*
Gestisce l'I/O per l’accesso a una collezione dell’utente loggato e, in caso di successo,
prepara l’ingresso al menù prodotti collegando il puntatore user_collection 
alla collezione selezionata.

Utilizza:
- sys_input_string_checker() per validare l’input da terminale
- sys_print_user_collections() per stampare le collezioni disponibili
- search_collection() per cercare la collezione richiesta

Parametri:
- logged_user: puntatore alla struttura user attualmente loggata
- user_collection: parametro di uscita; se l’operazione va a buon fine, punterà alla collezione selezionata

Valori di ritorno:
- 4 -> errore durante l’accesso ai dati utente (lista collezioni inconsistente)
- 2 -> errore di lettura del buffer di input
- 1 -> l’utente ha annullato volontariamente l’accesso alla collezione
- 0 -> accesso alla collezione eseguito con successo

Note:
- L’input richiede corrispondenza esatta con il nome della collezione (inclusi spazi e maiuscole).
- In caso di annullamento o errore, *user_collection resta NULL.
*/
int sys_access_user_collection(user logged_user, collection* user_collection){

    int string_checker_result;
    char collection_name_io_string[MAX_STR_LEN];
    bool check_space = false;
    *user_collection = NULL;

    collections collections_list = NULL;
    get_collection_list(logged_user,&(collections_list));
    if(collections_list == NULL){
        printf("\n" ANSI_COLOR_MAGENTA);
        printf("Impossibile accedere ad una collezione, la tua lista e' vuota, devi prima crearne una. L'operazione verra' annullata.\n");
        printf("\n" ANSI_COLOR_RESET);
        return 1; }
    
    while(1){
        printf("\n");
        sys_print_user_collections(logged_user);
        printf(ANSI_COLOR_MAGENTA ANSI_BOLD"Scegli una fra le seguenti collezioni a cui accedere inserendone il nome.\n");
        printf("E'necessario inserire correttamente maiuscole e spazi, per annullare l'accesso ad una collezione inserire una stringa vuota.\n" ANSI_COLOR_RESET BOLD_OFF);
  
        string_checker_result = sys_input_string_checker(collection_name_io_string, false,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("L'accesso ad una collezione e' stato annullato correttamente.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 1;
            case 2:
                printf(ANSI_COLOR_RED ANSI_BOLD "ERRORE Critico: errore di lettura del buffer di input (codice 2), contattare un amministratore.\n" ANSI_COLOR_RESET BOLD_OFF);
                return 2;
            default:
                break;
        }

        collections collections_list = NULL;
        get_collection_list(logged_user,&(collections_list));
        
        int search_result = search_collection(collections_list,collection_name_io_string,user_collection);

        switch(search_result){
            case 1: 
                printf("\n");
                printf(ANSI_COLOR_RED ANSI_BOLD "ERRORE Critico. La lista delle collezioni risulta vuota durante la ricerca della collezione (codice 4). Contattare un amministratore.\n"ANSI_COLOR_RESET BOLD_OFF);
                printf("\n");
                return 4;
            case 2:
                printf("\n");
                printf(ANSI_COLOR_RED ANSI_BOLD "La collezione non e' stata trovata. Inserire un nome valido della collezione a cui si desidera accedere.\n"ANSI_COLOR_RESET BOLD_OFF);
                printf("\n");
                continue;
            default:
                break; 
        }

        break;

    }

    printf(ANSI_BOLD ANSI_COLOR_GREEN "Accesso alla collezione \"%s\" effettuato con successo. Verrai reindirizzato al menu' prodotti...\n", collection_name_io_string);
    printf( ANSI_COLOR_RESET BOLD_OFF);
    return 0; //NB adesso *user_collection punterà alla collezione alla quale l'utente desiderava fare l'accesso.
}




/*
Gestisce l’I/O per la creazione e l’inserimento di una nuova collezione 
nella lista dell’utente attualmente loggato.

La funzione richiede all’utente di inserire un nome per la collezione e una tipologia.
Effettua controlli di validità sull’input e verifica che non esistano collezioni con lo stesso nome
(per evitare duplicati).  
Se tutti i controlli vengono superati, chiama insert_collection per aggiungere
la nuova collezione alla lista.

Utilizza:
- division_break_lines() per l’intestazione dell’interfaccia
- sys_input_string_checker() per acquisire e validare input da terminale
- collection_exists() per verificare l’assenza di duplicati
- insert_collection() per inserire la nuova collezione nella lista dell’utente

Parametri:
- logged_user: puntatore alla struttura user attualmente loggata

Valori di ritorno:
- 1 -> l’utente ha annullato l’operazione (in una qualsiasi fase dell’inserimento)
- 2 -> errore nella lettura del buffer di input
- 4 -> errore critico in fase di allocazione memoria (in insert_collection)
- 0 -> collezione aggiunta correttamente
*/
int sys_insert_collection(user logged_user){

    int string_checker_result;
    char collection_name_io_string[MAX_STR_LEN];
    char collection_type_io_string[MAX_STR_LEN];

    bool check_space = false; //In questo caso, le stringhe possono contenere spazi.

    printf("\n");
    printf(ANSI_BOLD ANSI_COLOR_BLUE);
    division_break_lines("AREA CREAZIONE NUOVA COLLEZIONE",54);
    printf("\n");
    printf("Benvenuto/a nell'area di creazione di una nuova collezione!\n");
    printf(ANSI_COLOR_RESET BOLD_OFF);

    while(1){

        printf("\n" ANSI_BOLD);
        printf("Inserisci il nome della tua nuova collezione. \n");
        printf("Per annullare l'inserimento della tua nuova collezione, inserisci una stringa vuota \n");
        printf("\n" BOLD_OFF);

        string_checker_result = sys_input_string_checker(collection_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("Operazione di aggiunta collezione annullata con successo.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 1;
            case 2: 
                printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 2;
            default: 
                break;
            }

            //Verifico che la collezione esiste nella lista, in tal caso ricomincia il ciclo while
            collections collections_list = NULL;
            get_collection_list(logged_user,&(collections_list));
            if(collection_exists(collections_list,collection_name_io_string) == 0){
                printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                printf("Hai gia' una collezione con questo nome, non sono consentiti duplicati. Riprova.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                continue;
            }

            break;
        }

    //Passo all'inserimento della tipologia della collezione

    printf("\n");

    while(1){

        printf(ANSI_BOLD);
        printf("Inserisci la tipologia della nuova collezione. \n");
        printf("Per annullare l'inserimento della tua nuova collezione, inserisci una stringa vuota \n\n");
        printf(BOLD_OFF);

        string_checker_result = sys_input_string_checker(collection_type_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("Operazione di aggiunta collezione annullata con successo. \n");
                printf("\n"ANSI_COLOR_RESET BOLD_OFF);
                return 1;
            case 2: 
                printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 2;
            default: 
                break;
            }

            break;
        }

        int result = insert_user_collection(logged_user,collection_name_io_string, collection_type_io_string);
        if (result == 3){
            printf("\n" ANSI_COLOR_RED ANSI_BOLD);
            printf("CRITICAL ERROR 4: errore di allocazione di memoria! Contattare un amministratore.\n");
            printf("\n" ANSI_COLOR_RESET BOLD_OFF);
            return 4;
        }

        printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
        printf("La tua nuova collezione: (%s) e' stata aggiunta correttamente.\n\n",collection_name_io_string);
        printf("\n" ANSI_COLOR_RESET BOLD_OFF);
        return 0; //Tutto è andato a buon fine
    }
    




/*
Gestisce l’I/O per la modifica del nome e/o della tipologia di una collezione
associata all’utente attualmente loggato.

Utilizza:
- division_break_lines() per la stampa dell’intestazione grafica
- sys_print_user_collections() per visualizzare l’elenco delle collezioni disponibili
- sys_input_string_checker() per validare l’input utente
- collection_exists() per verificare che la collezione da modificare esista
- search_and_modify_collection() per applicare le modifiche

Parametri:
- logged_user: puntatore alla struttura user loggata, su cui si opera

Valori di ritorno:
- 1 -> l’utente ha annullato la modifica
- 2 -> errore nella lettura del buffer di input
- 3 -> lista collezioni vuota o collezione non trovata  (ERRORE CRITICO! LISTA INCONSISTENTE)
- 4 -> errore critico nella modifica (caso raro)
- 0 -> modifica effettuata con successo 
*/
int sys_modify_collection(user logged_user){

    int string_checker_result;

    //Stringa utilizzata per l'inserimento del nome della collezione che l'utente desidera modificare
    char collection_name_io_string[MAX_STR_LEN];
    char collection_type_io_string[MAX_STR_LEN];

    //Sringhe utilizzate per l'inserimento del NUOVO nome e NUOVO tipo della collezione che l'utente desidera modificare
    char collection_new_name_io_string[MAX_STR_LEN];
    char collection_new_type_io_string[MAX_STR_LEN];

    bool check_space = false; //In questo caso, le stringhe possono contenere spazi.

    collections user_collections = NULL;
    get_collection_list(logged_user,&(user_collections));

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    division_break_lines("AREA MODIFICA COLLEZIONE", 56);
    printf("Benvenuto/a nell'area di modifica collezione.\n");
    printf(ANSI_COLOR_RESET BOLD_OFF);

    int isempty = sys_print_user_collections(logged_user);
    if(isempty == 1) return 3;
    printf("\n");

    //Ricerca della collezione che l'utente desidera modificare
    while(1){

        printf( ANSI_BOLD);
        printf("Inserisci il nome della collezione che vuoi modificare, (Attenzione, il nome deve essere lo stesso, comprese maiuscole e spazi!)\n");
        printf("Se vuoi annullare la modifica, inserisci una stringa vuota.\n");
        printf("\n"  BOLD_OFF);
        string_checker_result = sys_input_string_checker(collection_name_io_string, check_space,MIN_STR_LEN,MAX_STR_LEN);
        printf("\n");
        switch(string_checker_result){
            case 1:
                printf(ANSI_COLOR_GREEN ANSI_BOLD);
                printf("Modifica della collezione annullata con successo.\n");
                printf(ANSI_COLOR_RESET BOLD_OFF);
                return 1;
            case 2:
                printf(ANSI_COLOR_RED ANSI_BOLD);
                printf("FATAL ERROR 2: errore della lettura buffer di input. Contattare un amministartore.\n");
                printf(ANSI_COLOR_RED BOLD_OFF);
                return 2;
            default:
                //verifico che la collezione esista nella lista collezioni dell'utente loggato
                

                int collection_found = collection_exists(user_collections, collection_name_io_string);
                
                switch(collection_found){
                    case 1:
                        printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                        printf("La tua lista collezioni e' vuota, non e' presente alcuna collezione da modificare!\n");
                        printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                        return 3;
                    case 2:
                        printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                        printf("Non e' stata trovata una corrispondenza. Riprova. \n");
                        printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                        continue;
                    default:
                        printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                        printf("Collezione (%s) trovata! Si procede con la modifica...\n",collection_name_io_string);
                        printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                        break;
                }        
            }
        break;
        }

    
    //Procedo con la modifica del nome della collezione
    while(1){

        printf("\n" ANSI_BOLD);
        printf("Inserisci un nuovo nome per la tua collezione. Deve essere differente da (%s) e dal nome delle tue altre collezioni.\n", collection_name_io_string);
        printf("Se vuoi lasciare invariato il nome della collezione e modificarne solo il tipo, immetti una stringa vuota.\n");
        printf("\n"  BOLD_OFF);

        string_checker_result = sys_input_string_checker(collection_new_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1: 

                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("Il nome della collezione rimarra' invariato.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);

                break;
            case 2:
                printf("\n"ANSI_COLOR_RED ANSI_BOLD);
                printf("FATAL ERROR 2: errore della lettura buffer di input. Contattare un amministartore.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 2;
            default: 
                if(strcmp(collection_new_name_io_string,collection_name_io_string) == 0){
                    printf("\n"ANSI_COLOR_RED ANSI_BOLD);
                    printf("Inserisci un nome per la tua collezione differente da quello precedente.\n");
                    printf("Se desideri lasciare invariato il nome della tua collezione e modificarne solo il tipo, inserisci una stringa vuota, altrimenti riprova.\n");
                    printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                    continue;
                }
                //se il nuovo nome è differente da quello precedente, allora verifico che sia univoco nella lista delle collezioni dell'utente.
                int collection_found = collection_exists(user_collections, collection_new_name_io_string); 
                
                if(collection_found == 0){
                    printf("\n"ANSI_COLOR_RED ANSI_BOLD);
                    printf("E'gia' presente una collezione con il seguente nome :(%s). Riprova.\n",collection_new_name_io_string);
                    printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                    continue;
                }
                //altrimenti posso procedere con la modifica del tipo.
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("Il nuovo nome: (%s) e' valido. Si procede con la modifica della tipologia...\n",collection_new_name_io_string	);
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                break;
            }
        break;
    }

    //Procedo con la modifica del tipo della collezione
    while(1){

        printf("\n"  ANSI_BOLD);
        printf("Inserisci una nuova tipologia per la tua collezione.\n");
        printf("Se vuoi lasciare invariata la tipologia della collezione, inserisci una stringa vuota.\n");
        printf("\n" BOLD_OFF);
        string_checker_result = sys_input_string_checker(collection_new_type_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("La tipologia della collezione rimarra' invariata.\n");
                printf("\n"ANSI_COLOR_RESET BOLD_OFF);
                break;
            case 2:
                printf("\n"ANSI_COLOR_RED ANSI_BOLD);;
                printf("FATAL ERROR 2: errore della lettura dle buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 2;
            default:
                printf("\n"ANSI_COLOR_GREEN ANSI_BOLD);
                printf("La tipologia inserita è valida.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                break;
        }

        break;
    }

    int final_res = modify_user_collection(logged_user,collection_name_io_string,collection_new_name_io_string,collection_new_type_io_string);

    switch(final_res){
        case 1: 
            printf(ANSI_COLOR_RED ANSI_BOLD);
            printf("ERRORE CRITICO: Utente non inizializzato. Contattare un amministratore.\n");
            printf(ANSI_COLOR_RESET BOLD_OFF);
            return 4;
        case 2: 
            printf(ANSI_COLOR_RED ANSI_BOLD);
            printf("ERRORE CRITICO: La lista collezioni risulta vuota al momento della modifica. Contattare un amministratore.\n");
            printf(ANSI_COLOR_RESET BOLD_OFF);
            return 4;
        case 3:
            printf(ANSI_COLOR_RED ANSI_BOLD);
            printf("ERRORE CRITICO: Collezione da modificare non trovata. Contattare un amministratore.\n");
            printf(ANSI_COLOR_RESET BOLD_OFF);
            return 4;
        default: 
            printf(ANSI_COLOR_GREEN ANSI_BOLD);
            printf("La tua collezione e' stata modificata con successo in:\n");
            printf(BOLD_OFF ANSI_COLOR_CYAN);
            printf("Nome: %s\n", (strlen(collection_new_name_io_string) > 0 ? collection_new_name_io_string : collection_name_io_string));
            printf("Tipo: %s\n", (strlen(collection_new_type_io_string) > 0 ? collection_new_type_io_string : "Invariata"));
            printf(ANSI_COLOR_RESET);
            break;
    }   
    return 0; //Tutto è andato a buon fine
}
    
    

    

/*
Gestisce l’I/O per l’eliminazione di una singola collezione dalla lista collezioni 
dell’utente attualmente loggato.

Utilizza:
- division_break_lines() per stampare l’intestazione decorativa
- sys_print_user_collections() per visualizzare le collezioni attuali
- sys_input_string_checker() per validare l’input da terminale
- collection_exists() per verificare che la collezione sia presente
- ask_confirmation() per chiedere conferma prima della rimozione
- remove_collection() per eseguire l’eliminazione

Parametri:
- logged_user: puntatore all’utente attualmente loggato

Valori di ritorno:
- 1 -> l’utente ha annullato l’eliminazione / non ha ancora creato nessuna collezione
- 2 -> errore critico di lettura dal buffer di input
- 3 -> la lista collezioni dell’utente è vuota
- 4 -> errore critico durante la rimozione (collezione non trovata o lista incoerente)
- 0 -> eliminazione eseguita correttamente -> È NECESSARIO ESSERE REINDIRIZZATI IN QUESTO CASO AL MENU UTENTI VEDI NOTA

N.B: PER LA SEMPLICITÀ DELLA FUNZIONE, NON È STATO IMPLEMENTATO UN CONTROLLO NEL CASO IN CUI L'UTENTE DESIDERI CANCELLARE LA COLLEZIONE A CUI HA CORRETTAMENTE FATTO ACCESSO. 
Motivo per cui è necessario che l'utente venga reindirizzato al menu utente dopo ogni cancellazione di una delle sue collezioni. 
*/
int sys_delete_collection(user logged_user){

    int string_checker_result;

    //Stringa utilizzata per l'inserimento del nome della collezione che l'utente desidera eliminare
    char collection_name_io_string[MAX_STR_LEN];

    bool check_space = false;

    collections user_collections = NULL;
    get_collection_list(logged_user,&(user_collections));

    printf(ANSI_COLOR_CYAN,ANSI_BOLD);
    division_break_lines("AREA CANCELLAZIONE COLLEZIONE", 54);
    printf(ANSI_COLOR_RESET, BOLD_OFF);

    if((user_collections) == NULL){

        printf("\n" ANSI_BOLD ANSI_COLOR_RED);
        printf("Non hai ancora creato nessuna collezione.\n");
        printf("\n" BOLD_OFF ANSI_COLOR_RESET);
        return 1;
    }

    sys_print_user_collections(logged_user);

    while(1){

        printf("\n" ANSI_BOLD);
        printf("Inserisci il nome della collezione che desideri eliminare.\n");
        printf("Se vuoi annullare la modifica, inserisci una stringa vuota.\n");
        printf("\n" BOLD_OFF);
        string_checker_result = sys_input_string_checker(collection_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("Eliminazione della collezione annullata correttamente. \n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 1;
            case 2:
                printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 2;
            default:
                break;
        }

        int exists = collection_exists(user_collections,collection_name_io_string);

        switch(exists){
            case 1:
                printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                printf("La lista delle collezioni dell'utente e' vuota. Impossibile eliminare la collezione richiesta.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 3;
        
            case 2: 
                printf("\n" ANSI_COLOR_MAGENTA ANSI_BOLD);
                printf("La collezione: (%s) , non e' stata trovata. Riprova inserendo un nome collezione adeguato.\n",collection_name_io_string);
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                continue;
            default:
                printf("\n" ANSI_COLOR_GREEN );
                printf("Corrispondenza trovata...\n");
                printf("\n" ANSI_COLOR_RESET);
                break;
        }

        break;

    }

    //Blocco di conferma ulteriore per la cancellazione della collezione
    while (1){

        printf("\n" ANSI_COLOR_MAGENTA);
        printf("Confermi di voler eliminare la collezione \"%s\"? (Azione definitiva)\n", collection_name_io_string);
        printf("Inserisci 0 per confermare, 1 per annullare.\n");        
        printf("\n" ANSI_COLOR_RESET);

        int confirm = ask_confirmation();


        switch(confirm){
            case 1:
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("L'operazione e' stata annullata. La collezione non verra' elimianta.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 1;
            case 2:
                printf("\n" ANSI_COLOR_RED ANSI_BOLD);
                printf("ERRORE Critico: 2 errore lettura del buffer di input stdin, contattare un admin.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                return 2;
            default:
                printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
                printf("Eliminazione confermata.\n");
                printf("\n" ANSI_COLOR_RESET BOLD_OFF);
                break;
        }
        break;
    }



    int result = delete_user_collection(logged_user, collection_name_io_string);

    switch(result){
        case 1:
            printf("\n" ANSI_COLOR_RED ANSI_BOLD);
            printf("ERRORE CRITICO: la lista collezioni durante la fase di eliminazione e' risultata vuota. Contattare un admin.\n");
            printf("\n" ANSI_COLOR_RESET BOLD_OFF);
            return 4;
        case 2:
            printf("\n"ANSI_COLOR_RED ANSI_BOLD);
            printf("ERRORE CRITICO: la lista collezioni durante la fase di eliminazione non possedeva la collezione ricercata. Contattare un admin.\n");
            printf("\n"ANSI_COLOR_RESET BOLD_OFF);
            return 4;
        default:
            printf("\n"ANSI_COLOR_GREEN ANSI_BOLD);
            printf("La collezione (%s) e' stata definitivamente cancellata dalla lista collezioni.\n",collection_name_io_string);
            printf("\n"ANSI_COLOR_RESET BOLD_OFF);
            break;
    }
    //l'eliminazione è andata a buon fine, restituisco 0.

    printf(ANSI_BOLD ANSI_COLOR_MAGENTA"Verrai reindirizzato al menu utente da cui puoi riaccedere ad una delle tue collezioni...\n"BOLD_OFF ANSI_COLOR_RESET);
    return 0;
}



   


/*
Gestisce l’I/O per l’eliminazione di TUTTE LE collezioni dalla lista collezioni 
dell’utente attualmente loggato.

Utilizza:
- division_break_lines() per stampare l’intestazione decorativa
- sys_print_user_collections() per visualizzare le collezioni attuali
- sys_input_string_checker() per validare l’input da terminale
- ask_confirmation() per chiedere conferma prima della rimozione
- remove_collection() per eseguire l’eliminazione

Parametri:
- logged_user: puntatore all’utente attualmente loggato

Valori di ritorno:
- 1 -> l’utente ha annullato l’eliminazione / non è ancora stata creata nessuna collezione
- 2 -> errore critico di lettura dal buffer di input
- 3 -> la lista collezioni dell’utente è vuota (ERRORE CRITICO: LISTA INCONSISTENTE)
- 4 -> errore critico durante la rimozione (LISTA INCONSISTENTE) 
- 0 -> eliminazione eseguita correttamente
*/
int sys_delete_collections(user logged_user){

    collections user_collections = NULL;
    get_collection_list(logged_user,&(user_collections));

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    division_break_lines("AREA CANCELLAZIONE LISTA COLLEZIONI",54);
    printf(ANSI_COLOR_RESET BOLD_OFF);

    if((user_collections) == NULL){
        printf("\n" ANSI_COLOR_RED);
        printf("Non hai ancora creato nessuna collezione.\n");
        printf("\n" ANSI_COLOR_RED);
        return 1;
    }


    printf("\n" ANSI_COLOR_MAGENTA);
    printf("Confermi di voler eliminare tutte le tue collezioni? (Azione definitiva)\n");
    printf("Inserisci 0 per confermare, 1 per annullare.\n");     
    printf("\n" ANSI_COLOR_RESET);

    int confirm = ask_confirmation();
    
    switch(confirm){
        case 1:
            printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
            printf("L'operazione e' stata annullata. Le tue collezioni non verranno eliminate.\n");
            printf("\n" ANSI_COLOR_RESET BOLD_OFF);
            return 1;
        case 2:
            printf("\n" ANSI_COLOR_RED ANSI_BOLD);
            printf("ERRORE CRITICO: lettura del buffer di input fallit. Contattare un amministratore.\n");
            printf("\n" ANSI_COLOR_RED BOLD_OFF);
            return 2;
        default:
            printf("\n" ANSI_COLOR_GREEN);
            printf("Operazione confermata...\n");
            printf("\n"ANSI_COLOR_RESET);
            break;
    }

    int result = delete_user_collections(logged_user);
    
    if(result == 1){
        printf("\n" ANSI_COLOR_RED ANSI_BOLD);
        printf("ERRORE Critico: utente non inizializzato e/o lista risulta vuota quando non dovrebbe (Lista inconsistente). Contattare un amministratore");
        printf("\n" ANSI_COLOR_RESET BOLD_OFF);
        return 4;
    }
    if(result == 2){
        
        printf("\n" ANSI_COLOR_RED ANSI_BOLD);
        printf("ERRORE Critico: la lista collezioni dell'utente e' vuota (Lista inconsistente)). Contattare un amministratore.");
        printf("\n" ANSI_COLOR_RESET BOLD_OFF);
        return 4;
    }

    printf("\n" ANSI_COLOR_GREEN ANSI_BOLD);
    printf("Tutte le tue collezioni sono state eliminate.\n");
    printf("\n" ANSI_COLOR_GREEN BOLD_OFF);
    return 0;
}





/*
Gestisce l’I/O per la stampa della lista dei prodotti contenuti in una specifica collezione
dell’utente attualmente loggato.

Utilizza:
- division_break_lines() per stampare l’intestazione visiva
- print_products() per effettuare la stampa effettiva della lista prodotti

Parametri:
- logged_user: puntatore all’utente attualmente loggato (utilizzato per stampare il nome)
- user_collection: puntatore alla collezione di cui si vogliono visualizzare i prodotti

Valori di ritorno:
- 1 -> la lista prodotti della collezione è vuota
- 4 -> errore critico: la funzione print_  ha rilevato lista incoerente (raro)
- 0 -> la stampa è andata a buon fine
*/
int sys_print_user_products(user logged_user, collection user_collection){

    char username[MAX_STR_LEN];
    char collection_name[MAX_STR_LEN];
    get_username(logged_user,username);
    get_collection_name(user_collection,collection_name);

    products products_list = NULL;
    get_products_list(user_collection,&(products_list));

    printf(ANSI_COLOR_BLUE ANSI_BOLD);
    division_break_lines("LISTA PRODOTTI", 60);
    printf(ANSI_COLOR_RESET BOLD_OFF);
    

    
    if(products_list == NULL){
        printf("\n" ANSI_COLOR_RED);
        printf("%s , la tua lista collezioni \"%s\" e' vuota.\n",username, collection_name);
        printf("\n" ANSI_COLOR_RESET);
        return 1;
    }

    printf("La lista prodotti della tua collezione \"%s\" e' la seguente:\n", collection_name);
    printf(ANSI_BOLD);
    printf("| NOME | TIPO | CONDIZIONI | PREZZO DI ACQUISTO |\n");
    printf(BOLD_OFF);
    printf(ANSI_COLOR_CYAN);
    int result = print_products(products_list);
    printf(ANSI_COLOR_RESET);

    if(result == 1){
        printf("\n" ANSI_COLOR_RED);
        printf("ERRORE Critico: la lista dei prodotti risulta vuota (codice 04). Contattare un amministratore.\n");
        printf("\n" ANSI_COLOR_RESET);
        return 4;
    }

    return 0;

}


/*
Gestisce l’interfaccia I/O per l’inserimento di un nuovo prodotto nella collezione di un utente loggato.

Il flusso della funzione guida l’utente attraverso la compilazione dei campi informativi del prodotto:
- nome
- tipologia
- condizioni
- prezzo di acquisto

Parametri:
- logged_user: puntatore all’utente attualmente loggato
- user_collection: puntatore alla collezione nella quale si desidera inserire il prodotto

Utilizza:
- sys_input_string_checker
- exist_sorted
- strtof
- ask_confirmation
- insert_product
- division_break_lines (per interfaccia grafica)

Valori di ritorno:
- 1 -> l’utente ha annullato l’operazione
- 2 -> errore di lettura del buffer di input
- 3 -> errore di allocazione dinamica
- 4 -> struttura dati inconsistente (duplicato rilevato quando non previsto)
- 0 -> inserimento effettuato correttamente
*/
int sys_insert_user_product(user logged_user, collection user_collection){

    char username[MAX_STR_LEN];
    char collection_name[MAX_STR_LEN];
    get_username(logged_user,username);
    get_collection_name(user_collection, collection_name);
    products products_list = NULL;
    get_products_list(user_collection,&(products_list));

    int string_checker_result;
    char product_name_io_string[MAX_STR_LEN];
    char product_type_io_string[MAX_STR_LEN];
    char product_condition_io_string[MAX_STR_LEN];

    float product_buyprice;

    bool check_space = false; //spazi consentiti

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    division_break_lines("AREA INSERIMENTO PRODOTTO",56);
    printf(ANSI_COLOR_RESET BOLD_OFF);

    printf("\n" ANSI_COLOR_MAGENTA);
    printf("%s, stai inserendo un nuovo prodotto alla collezione \"%s\" \n",username, collection_name);
    printf("\n" ANSI_COLOR_RESET);

    /* CICLO NOME PRODOTTO */
    while (1){

        printf(ANSI_BOLD);
        printf("Inserisci un nome per il tuo nuovo prodotto. Duplicati non consentiti. \n");
        printf("Puoi annullare il processo in qualsiasi momento inserendo una stringa vuota.\n" BOLD_OFF);
        string_checker_result = sys_input_string_checker(product_name_io_string, check_space, MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1: 
                printf("\n" ANSI_COLOR_GREEN);
                printf("Operazione di inserimento prodotto annullata...\n");
                printf("\n" ANSI_COLOR_RESET);
                return 1;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 2;
            default:
                int exists = exist_sorted(products_list, product_name_io_string);

                if (exists == 0){
                    printf("\n" ANSI_COLOR_MAGENTA);
                    printf("E'Gia' presente un prodotto nella collezione \"%s\" con questo nome. I duplicati non sono consentiti. Riprova.\n",collection_name);
                    printf("\n"ANSI_COLOR_RESET);
                    continue;
                } else {
                    printf("\n" ANSI_COLOR_GREEN);
                    printf("Il nome e' disponibile! Si procede con l'inserimento della tipologia del prodotto... \n");
                    printf("\n" ANSI_COLOR_RESET);
                    break;
                    }
                break;
        }
    break;
    }

    /* CICLO TIPOLOGIA PRODOTTO */

    while (1){

        printf(ANSI_BOLD);
        printf("Inserisci una tipologia per il tuo nuovo prodotto.\n");
        printf("Puoi annullare il processo in qualsiasi momento inserendo una stringa vuota.\n"BOLD_OFF);
        string_checker_result = sys_input_string_checker(product_type_io_string, check_space, MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1: 
                printf("\n" ANSI_COLOR_GREEN);
                printf("Operazione di inserimento prodotto annullata...\n");
                printf("\n" ANSI_COLOR_RESET);
                return 1;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 2;
            default:
                printf("\n" ANSI_COLOR_GREEN);
                printf("Tipologia del prodotto correttamente inserita. \n");
                printf("\n"ANSI_COLOR_RESET);
                break;
                }
        break;
    }


    /* CICLO CONDIZIONI PRODOTTO*/

    while (1){

        printf(ANSI_BOLD);
        printf("Inserisci le condizioni per il tuo nuovo prodotto.\n");
        printf("Puoi annullare il processo in qualsiasi momento inserendo una stringa vuota.\n"BOLD_OFF);
        string_checker_result = sys_input_string_checker(product_condition_io_string, check_space, MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1: 
                printf("\n" ANSI_COLOR_GREEN);
                printf("Operazione di inserimento prodotto annullata...\n");
                printf("\n"ANSI_COLOR_RESET);
                return 1;
            case 2:
                printf("\n"ANSI_COLOR_RED);
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n"ANSI_COLOR_RESET);
                return 2;
            default:
                printf("\n"ANSI_COLOR_GREEN);
                printf("Condizioni del prodotto correttamente inserite. \n");
                printf("\n"ANSI_COLOR_RESET);
                break;
                }
        break;
    }

    /* CICLO PREZZO DI ACQUISTO PRODOTTO*/

     //in questo caso, occorre utilizzare una stringa di appoggio per contenere la cifra inserita dall'utente, tale cifra verrà poi
     //controllata (devono essere numeri e non caratteri) ed eventualmente convertita (casting) a float.
    char temp_buyprice[MAX_STR_LEN];

    while(1){

        printf(ANSI_BOLD);
        printf("Inserisci il prezzo di acquisto per il tuo nuovo prodotto. (Non si accettano numeri negativi o uno zero!) \n");
        printf("Puoi annullare il processo premendo invio. \n" BOLD_OFF);


        //in questo caso non può contenere spazi, avrò in questo modo un controllo in meno da svolgere seguentem.
        string_checker_result = sys_input_string_checker(temp_buyprice,true,0,10);

        switch(string_checker_result){
            case 1: 
                printf("\n" ANSI_COLOR_GREEN);
                printf("Operazione di inserimento prodotto annullata...\n");
                printf("\n" ANSI_COLOR_RESET);
                return 1;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 2;
            default: 
                break;
        }

        /*srtof è una funzione della libreria stdlib.h
        * converte una stringa in un float. In caso di corretta conversione, restituisce il float. Altrimenti restituisce 0.0.
        */

        char *endptr;

        product_buyprice = strtof(temp_buyprice,&endptr);
        
        //se endptr punta alla stessa area di memoria della stringa (puntatore) temp buy price, vuol dire che il primo elemento era un carattere.
        if(endptr == temp_buyprice){
            printf(ANSI_COLOR_MAGENTA);
            printf("Hai inserito dei caratteri, non sono validi. Si accettano cifre positive non nulle. Riprova.\n");
            printf(ANSI_COLOR_RESET);
            continue;
        } else if(*endptr != '\0'){
            printf(ANSI_COLOR_MAGENTA);
            printf("Hai inserito in parte dei caratteri superflui non validi. Si accettano cifre positive non nulle. Riprova.\n");
            printf(ANSI_COLOR_RESET);
            continue;
        } else if (product_buyprice <= 0){
            printf(ANSI_COLOR_MAGENTA);
            printf("Hai inserito un numero negativo o nullo non valido. Si accettano cifre positive non nulle. Riprova.\n");
            printf(ANSI_COLOR_RESET);
            continue;
        } else {
            printf(ANSI_COLOR_GREEN);
            printf("Numero valido correttamente inserito...\n");
            printf(ANSI_COLOR_RESET);
        }

        printf(ANSI_BOLD);
        printf("Il prezzo di acquisto inserito e' il seguente: %.2f \n",product_buyprice); //stampo 2 cifre decimali
        printf(ANSI_COLOR_MAGENTA"Premi 0 per confermarlo, 1 per modificarne il valore.\n" ANSI_COLOR_RESET BOLD_OFF);
        int confirm = ask_confirmation();
        
        switch (confirm){
            case 1: continue;
            case 2: printf(ANSI_COLOR_RED"ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n"ANSI_COLOR_RESET); return 2;
            default: break;
        }
    
    printf(ANSI_COLOR_GREEN"Inserimento del prodotto \"%s\" in corso...\n"ANSI_COLOR_RESET,product_name_io_string);
    break; 
    }

    int result = insert_collection_product(user_collection,product_name_io_string,product_type_io_string,product_condition_io_string,product_buyprice);

    switch(result){
        case 1: 
            printf(ANSI_COLOR_RED"ERRORE Critico: La collezione risulta non inizializzata. (Dati inconsistenti). Contattare un amministratore.\n"ANSI_COLOR_RESET);
            return 4;
        case 2:
            printf(ANSI_COLOR_RED"ERRORE Critico: rilevato duplicato quando non dovrebbe. Contattare un amministratore.\n"ANSI_COLOR_RESET);
            return 4;
        case 3:
            printf(ANSI_COLOR_RED"ERRORE Critico: errore di allocazione dinamica della memoria. Contattare un amministratore.\n"ANSI_COLOR_RESET);
            return 3;
        default:
            break;
    }

    printf(ANSI_COLOR_GREEN ANSI_BOLD"Il seguente prodotto e' stato correttamente inserito nella collezione \"%s\": \n" ANSI_COLOR_RESET BOLD_OFF,collection_name);
    printf(ANSI_COLOR_CYAN);
    printf("Nome prodotto: %s\n", product_name_io_string);
    printf("Tipologia: %s\n", product_type_io_string);
    printf("Condizioni: %s\n",product_condition_io_string);
    printf("Prezzo di acquisto: %.2f\n",product_buyprice);
    printf(ANSI_COLOR_RESET);
    return 0;
}




/*
Gestisce l’I/O per la modifica di un prodotto appartenente ad una collezione di un utente loggato.
La funzione guida l’utente attraverso:
- Selezione del prodotto da modificare
- Modifica facoltativa di nome, tipologia, condizioni e prezzo di acquisto
- Verifica dell’esistenza del prodotto e della validità dei dati inseriti
- Conferma finale della modifica prima dell’applicazione
I campi non modificati possono essere lasciati invariati tramite stringa vuota, e la modifica avviene tramite la funzione `search_and_modify_product`.

Parametri:
- logged_user: utente attualmente loggato
- user_collection: collezione da cui prelevare il prodotto da modificare

Utilizza:
- sys_input_string_checker
- sys_print_user_products
- exist_sorted
- strtof
- ask_confirmation
- search_and_modify_product
- division_break_lines 

Valori di ritorno:
- 0 -> modifica eseguita con successo
- 1 -> operazione annullata dall’utente
- 2 -> errore di lettura del buffer di input (codice 2)
- 3 -> lista prodotti vuota
- 4 -> errore logico/strutturale durante l’accesso ai dati
- 5 -> errore nella modifica del prodotto (ritorno dalla funzione `search_and_modify_product`)
*/
int sys_modify_user_product(user logged_user, collection user_collection){

    char username[MAX_STR_LEN];
    char collection_name[MAX_STR_LEN];
    get_username(logged_user,username);
    get_collection_name(user_collection,collection_name);
    products products_list = NULL;
    get_products_list(user_collection, &(products_list));


    int string_checker_result;

    //informazioni prodotto prima della modifica
    char product_name_io_string[MAX_STR_LEN];

    //informazioni prodotto dopo la modifica
    char new_product_name_io_string[MAX_STR_LEN];
    char new_product_type_io_string[MAX_STR_LEN];
    char new_product_condition_io_string[MAX_STR_LEN];
    float new_product_buyprice;
    
    bool check_space = false; //spazi consentiti

    //se rimangono invariati, imposto a true in modo tale da printare il prodotto corretto per la conferma finale in I/O.
    bool unchanged_name = false;
    bool unchanged_type = false;
    bool unchanged_condition = false;
    bool unchanged_buyprice = false;

    printf(ANSI_BOLD ANSI_COLOR_CYAN);
    division_break_lines("AREA MODIFICA PRODOTTO", 54);
    printf("\n"ANSI_COLOR_RESET BOLD_OFF);
    int result = sys_print_user_products(logged_user, user_collection);
    if(result == 4){
        return 4;  //errore critico di accesso alla struttura dati, la lista risulta vuota quando non dovrebbe (codice 4)
    }
    if(result == 1){
        printf(ANSI_COLOR_RED);
        printf("Lista vuota! Nessun prodotto modificabile.\n");
        printf(ANSI_COLOR_RESET);
        return 3; //Lista vuota, restituisco 3
    }


    ////////////////////////////////////////////////////CICLO DI RICERCA PRODOTTO DA MODIFICARE/////////////////////////////////////////////////
    while(1){
        //altrimenti stampa la lista dei prodotti
        printf("\n" ANSI_BOLD);
        printf("Inserisci il nome del prodotto della collezione \"%s\" che desideri modificare. \n",username, collection_name);
        printf("Inserisci una stringa vuota per annullare l'operazione di modifica. \n");
        printf("\n" BOLD_OFF);

        string_checker_result = sys_input_string_checker(product_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n"ANSI_COLOR_GREEN);
                printf("Modifica del prodotto annullata correttamente. \n");
                printf("\n" ANSI_COLOR_RESET);
                return 1;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 2;
            default:
                break;
        }

        //controllo se il nome del prodotto inserito in input esista nella lista dei prodotti
        int exists = exist_sorted(products_list, product_name_io_string);

        switch (exists) {
            case 1: 
                printf(ANSI_COLOR_RED);
                printf("Lista vuota quando non dovrebbe. Errore critico di lettura dati in memeria (Codice 4). Contattare un'amministratore. \n");
                printf(ANSI_COLOR_RESET);
                return 4;
            case 2: 
                printf(ANSI_COLOR_MAGENTA);
                printf("Non e' stato trovato il prodotto nella lista. Assicurati di aver inserito correttamente spazi/maiuscole. Riprova.\n");
                printf(ANSI_COLOR_RESET);
                continue;
            default:
                printf(ANSI_COLOR_GREEN);
                printf("Prodotto trovato, si procede con la modifica...\n");
                printf(ANSI_COLOR_RESET);
                break;
        }
        break;
    }

    ///PRODUCT_NAME_IO_STRING CONTIENE IL NOME DEL PRODOTTO CORRETTO E PRESENTE IN LISTA DEL PRODOTTO DA MODIFICARE.

    ////////////////////////////////////////////CICLO DI MODIFICA NOME DEL PRODOTTO///////////////////////////////////////////////////////////
    while(1){
        
        printf("\n" ANSI_BOLD);
        printf("Inserisci un nuovo nome per il tuo prodotto. Deve essere differente dai prodotti nella tua lista e da \"%s\"\n", product_name_io_string);
        printf("Se vuoi mantenere invariato il nome del prodotto, inserisci una stringa vuota.\n");
        printf("\n" BOLD_OFF);

        string_checker_result = sys_input_string_checker(new_product_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        //controllo validità input, se lo è, nel default controllo che non sia occupato. Se non lo è, -> new_product_name_io_string è il nuovo nome validitato.
        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN);
                printf("Il nome del prodotto rimarra' invariato, si procede con la modifica della tipologia...\n");
                printf("\n" ANSI_COLOR_RESET);
                unchanged_name = true;
                break;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 2;
            default: 
                int exists = exist_sorted(products_list,new_product_name_io_string); //controllo che l'input valido non sia occupato
                switch(exists) {
                    case 1:
                        printf("\n" ANSI_COLOR_RED);
                        printf("La lista e' vuota quando non dovrebbe. Errore critico di lettura dati in memeria (Codice 4). Contattare un'amministratore. \n");
                        printf("\n" ANSI_COLOR_RESET);
                        return 4;
                    case 2: 
                        printf("\n" ANSI_COLOR_GREEN);
                        printf("Il nuovo nome prodotto inserito e' disponibile. Si procede con la modifica della tipologia...\n");
                        printf("\n" ANSI_COLOR_RESET);
                        break;
                    default:
                        printf("\n" ANSI_COLOR_MAGENTA);
                        printf("Il nuovo nome prodotto non e' disponibile. Riprova.\n");
                        printf("\n" ANSI_COLOR_RESET);
                        continue;
                    }
        }
        break;
    }


    ////////////////////////////////////////////CICLO DI MODIFICA TIPOLOGIA DEL PRODOTTO///////////////////////////////////////////////////////////
    while(1){

        printf("\n" ANSI_BOLD);
        printf("Inserisci una nuova tipologia per il tuo prodotto.\n");
        printf("Se vuoi mantenere invariata la tipologia del prodotto, inserisci una stringa vuota.\n");
        printf("\n" BOLD_OFF);

        string_checker_result = sys_input_string_checker(new_product_type_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        //controllo validità input inserito.   Default:  new_product_type_io_string conterrà la nuova tipologia valida.
        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN);
                printf("La tipologia del prodotto rimarra' invariata, si procede con la modifica della tipologia...\n");
                printf("\n" ANSI_COLOR_RESET);
                unchanged_type = true;
                break;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 2;
            default: 
                printf("\n" ANSI_COLOR_GREEN);
                printf("La tipologia inserita e' valida. Si procede con la modifica delle condizioni...\n");
                printf("\n" ANSI_COLOR_RESET);
                break;
        }
        break;
    }



    /////////////////////////////////////////////CICLO DI MODIFICA CONDIZIONI DEL PRODOTTO////////////////////////////////////////////////////
    while(1){

        printf("\n" ANSI_BOLD);
        printf("Inserisci una nuova condizione per il tuo prodotto.\n");
        printf("Se vuoi mantenere invariate le condizioni del prodotto, inserisci una stringa vuota.\n");
        printf("\n" BOLD_OFF);

        string_checker_result = sys_input_string_checker(new_product_condition_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        //controllo validità input inserito.   Default:  new_product_type_io_string conterrà la nuova tipologia valida.
        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN);
                printf("Le condizioni del prodotto rimarranno invariate, si procede con la modifica del prezzo di acquisto...\n");
                printf("\n" ANSI_COLOR_RESET);
                unchanged_condition = true;
                break;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 2;
            default: 
                printf("\n" ANSI_COLOR_GREEN);
                printf("Le condizioni inserite sono valide. Si procede con la modifica del prezzo di acquisto...\n");
                printf("\n" ANSI_COLOR_RESET);
                break;
        }
        break;
    }



    ////////////////////////////////////////////////////CICLO DI MODIFICA PREZZO DI ACQUISTO DEL PRODOTTO////////////////////////////////////////////


    char temp_buyprice[MAX_STR_LEN];

    while(1){

        printf(ANSI_BOLD);
        printf("Inserisci il prezzo di acquisto per il tuo nuovo prodotto. (Non si accettano numeri negativi o uno zero!) \n");
        printf("Puoi annullare il processo premendo invio. \n");
        printf(ANSI_COLOR_RESET);


        //in questo caso non può contenere spazi, avrò in questo modo un controllo in meno da svolgere seguentem.
        string_checker_result = sys_input_string_checker(temp_buyprice,true,0,10);

        switch(string_checker_result){
            case 1: 
                printf("\n" ANSI_COLOR_GREEN);
                printf("Il prezzo di acquisto rimarra' invariato, si procede alla conferma della modifica...\n");
                printf("\n" ANSI_COLOR_RESET);
                unchanged_buyprice = true;
                break;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n"ANSI_COLOR_RESET);
                return 2;
            default: 
                break;
        }

        //se l'utente vuole mantenere invariato il prezzo di acquisto, imposto il valore sentinella per mantenere invariato il float, ed esco dal ciclo while.
        if(unchanged_buyprice == true) {
            //N.B search_and_modify_product, se riceve in ingresso  stringhe vuote o un valore di float pari a quello sentinella (-1.0f), non modifica quel contenuto del prodotto
            new_product_buyprice = -1.0f; 
            break;
        }

        /*srtof è una funzione della libreria stdlib.h
        * converte una stringa in un float. In caso di corretta conversione, restituisce il float. Altrimenti restituisce 0.0.
        */

        char *endptr;

        new_product_buyprice = strtof(temp_buyprice,&endptr);
        
        //se endptr punta alla stessa area di memoria della stringa (puntatore) temp buy price, vuol dire che il primo elemento era un carattere.
        if(endptr == temp_buyprice){
            printf(ANSI_COLOR_MAGENTA"Hai inserito dei caratteri, non sono validi. Si accettano cifre positive non nulle. Riprova.\n"ANSI_COLOR_RESET);
            continue;
        } else if(*endptr != '\0'){
            printf(ANSI_COLOR_MAGENTA"Hai inserito in parte dei caratteri superflui non validi. Si accettano cifre positive non nulle. Riprova.\n"ANSI_COLOR_RESET);
            continue;
        } else if (new_product_buyprice <= 0){
            printf(ANSI_COLOR_MAGENTA"Hai inserito un numero negativo o nullo non valido. Si accettano cifre positive non nulle. Riprova.\n"ANSI_COLOR_RESET);
            continue;
        } else {
            printf("\n" ANSI_COLOR_GREEN);
            printf("Numero valido correttamente inserito...\n");
            printf("\n"ANSI_COLOR_RESET);
        }

        break;
    }




    //////////////////////////////////////////////////////////CONFERMA NUOVO PRODOTTO INSERITO/////////////////////////////////////////
    printf(ANSI_COLOR_CYAN ANSI_BOLD"Il prodotto modificato sara' il seguente:\n\n" ANSI_COLOR_RESET BOLD_OFF);

    printf("Nome: %s\n", unchanged_name ? "Invariato" : new_product_name_io_string);
    printf("Tipologia: %s\n", unchanged_type ? "Invariato" : new_product_type_io_string);
    printf("Condizioni: %s\n", unchanged_condition ? "Invariato" : new_product_condition_io_string);
    
    if (unchanged_buyprice) printf("Prezzo di acquisto: Invariato\n\n");
    else printf("Prezzo di acquisto: %.2f\n\n", new_product_buyprice);


    printf(ANSI_COLOR_MAGENTA ANSI_BOLD"Confermi di voler procedere alla modifica? Inserisci 0 per confermare, 1 per annullare.\n" ANSI_COLOR_RESET BOLD_OFF);
    int confirm = ask_confirmation();

    if(confirm == 2){
        printf("\n" ANSI_COLOR_RED);
        printf("Errore del buffer di input (codice 2). Contattare un amministratore.\n");
        printf("\n"ANSI_COLOR_RESET);
        return 2;
    }
    if(confirm == 1){
        printf(ANSI_COLOR_GREEN);
        printf("La modifica del prodotto e' stata annullata correttamente.\n");
        printf(ANSI_COLOR_RESET);
        return 1;
    }

    //altrimenti, se result == 0 modifico il prodotto.

    int final_result = modify_collection_product(user_collection, product_name_io_string,new_product_name_io_string, new_product_type_io_string, new_product_condition_io_string,new_product_buyprice);

    switch (final_result) {
        case 1:
            printf("\n" ANSI_COLOR_RED);
            printf("ERRORE CRITICO: Lista inconsistente, collezione risulta == NULL. Contattare un amministratore.\n");
            printf(ANSI_COLOR_RESET);
            return 4;
        case 2:
            printf("\n" ANSI_COLOR_RED);
            printf("ERRORE CRITICO: Prodotto non trovato, mentre precedentemente lo è stato. Errore critico (codice 4), contattare un amministratore.\n");
            printf(ANSI_COLOR_RESET);
            return 2;
        case 3:
            printf("\n" ANSI_COLOR_RED);
            printf("ERRORE CRITICO: Lista inconsistente, collezione risulta == NULL. Contattare un amministratore.\n");
            printf(ANSI_COLOR_RESET);
            return 4;
        case 4:
            printf("\n" ANSI_COLOR_RED);
            printf("ERRORE CRITICO: errore nella modifica del prodotto durante la chiamata a search_and_modify_product. Contattare un amministratore (codice 5)\n");
            printf(ANSI_COLOR_RESET);
            return 5;
        default: 
            printf("\n" ANSI_COLOR_GREEN);
            printf("Prodotto correttamente modificato!\n");
            printf(ANSI_COLOR_RESET);
    }

    return 0;

}




/*
Gestisce l’I/O per la cancellazione definitiva di un prodotto da una collezione appartenente a un utente loggato.
La funzione:
- Mostra i prodotti esistenti nella collezione selezionata
- Richiede il nome del prodotto da eliminare
- Verifica l'esistenza del prodotto
- Chiede conferma definitiva prima di procedere con la rimozione

Parametri:
- logged_user: utente attualmente loggato
- user_collection: collezione da cui eliminare il prodotto

Utilizza:
- sys_input_string_checker
- sys_print_user_products
- exist_sorted
- ask_confirmation
- remove_product
- division_break_lines 

Valori di ritorno:
- 0 -> prodotto eliminato correttamente
- 1 -> operazione annullata dall’utente
- 2 -> errore di lettura del buffer di input
- 3 -> lista prodotti vuota  (errore critico, lista inconsistente)
- 4 -> errore critico durante l’accesso alla memoria (struttura dati incoerente)
*/
int sys_delete_user_product(user logged_user, collection user_collection){

    char username[MAX_STR_LEN];
    char collection_name[MAX_STR_LEN];
    get_username(logged_user,username);
    get_collection_name(user_collection,collection_name);
    products products_list = NULL;
    get_products_list(user_collection, &(products_list));

    int string_checker_result;
    char product_name_io_string[MAX_STR_LEN];
    bool check_space = false;
    

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    division_break_lines("AREA ELIMINAZIONE PRODOTTO",56);
    printf("\n" ANSI_COLOR_RESET BOLD_OFF);

    //se la lista prodotti è vuota, restituisco 3
    if(user_collection -> products_list_head == NULL){
        printf(ANSI_COLOR_RED);
        printf("La collezione \"%s\" e' vuota. Non e' presente alcun prodotto da eliminare.\n",collection_name);
        printf(ANSI_COLOR_RESET);
        return 3;
    }

    while(1){

        printf(ANSI_COLOR_MAGENTA);
        printf("I prodotti della collezione \"%s\" sono i seguenti:\n\n",collection_name);
        printf(ANSI_COLOR_CYAN);
        int print_result = print_products(products_list);
        printf(ANSI_COLOR_RESET);

        if(print_result == 1){
            printf(ANSI_COLOR_RED);
            printf("ERRORE Critico, la lista risulta vuota durante l'accesso in memoria quando non dovrebbe esserlo. Codice 4. Contattare un amministratore.\n");
            printf(ANSI_COLOR_RESET);
            return 4;
        }
        
        //altrimenti stampo correttamente i prodotti della lista.

        printf("\n"ANSI_BOLD);
        printf("Digita il prodotto che desideri eliminare. Assicurati di inserire correttamente maiuscole/spazi.\n");
        printf("Per annullare l'operazione inserisci una stringa vuota. \n\n");
        printf(BOLD_OFF);

        string_checker_result = sys_input_string_checker(product_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
        switch(string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN);
                printf("Eliminazione annullata correttamente. \n");
                printf("\n" ANSI_COLOR_RESET);
                return 1;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("Errore durante la lettura del buffer di input stdin. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 2;
            default: 
                printf("\n" ANSI_COLOR_MAGENTA);
                printf("Ricerca del prodotto \"%s\" in corso...\n",product_name_io_string);
                printf(ANSI_COLOR_RESET);
                break;
        }

        int exists = exist_sorted(products_list,product_name_io_string);

        switch(exists){
            case 1:
                printf(ANSI_COLOR_RED"ERRORE Critico, la lista risulta vuota durante l'accesso in memoria quando non dovrebbe esserlo. Codice 4. Contattare un amministratore.\n"ANSI_COLOR_RESET);
                return 4;
            case 2:
                printf(ANSI_COLOR_MAGENTA"Il prodotto non e' stato trovato all'interno della lista. Riprova.\n"ANSI_COLOR_RESET);
                continue;
            default:
                printf(ANSI_COLOR_GREEN"Corrispondenza trovata!\n"ANSI_COLOR_RESET);
                break;
        }
        break;
    }

    printf("\n");
    printf(ANSI_COLOR_MAGENTA"Il prodotto che eliminerai e' il seguente: \n"ANSI_COLOR_RESET);

    printf(ANSI_COLOR_CYAN);
    search_and_print_product(products_list, product_name_io_string);
    printf(ANSI_COLOR_RESET);

    printf("\n");
    printf(ANSI_COLOR_MAGENTA"Confermi di volerlo eliminare? Inserisci 0 per confermare, 1 per annullarne l'eliminazione.\n"ANSI_COLOR_RESET);
    int result = ask_confirmation();

    if(result == 1){
        printf(ANSI_COLOR_GREEN"\nOperazione annullata correttamente. Il tuo prodotto non verra' eliminato. \n"ANSI_COLOR_RESET);
        return 1;
    }

    int final_result = delete_collection_product(user_collection, product_name_io_string);

    if(final_result == 1 || final_result == 3){
        printf(ANSI_COLOR_RED"ERRORE Critico, la collezione risulta non inizializzata (lista inconsistente) o non è stato trovato il prodotto. Contattare un amministratore. \n"ANSI_COLOR_RESET);
        return 4;
    } else if (final_result == 2){
        printf(ANSI_COLOR_RED"ERRORE Critico, non e' stata trovata una corrispondenza durante l'eliminazione anche se non dovrebbe accadere. Contattare un amministratore.\n"ANSI_COLOR_RESET);
        return 4;
    }
    
    //altrimenti il prodotto e' stato correttamente eliminato.

    printf(ANSI_COLOR_GREEN"\nIl prodotto \"%s\" e'stato correttamente eliminato\n"ANSI_COLOR_RESET,product_name_io_string);
    return 0;
}




/*
Gestisce l'I/O per la cancellazione definitiva di tutti i prodotti presenti nella collezione di un utente loggato.

La funzione:
- Verifica se la lista prodotti è già vuota
- Chiede conferma all'utente prima di procedere all'eliminazione
- In caso di conferma, svuota la lista prodotti associata alla collezione

Parametri:
- logged_user: utente attualmente loggato
- user_collection: collezione da cui eliminare tutti i prodotti

Utilizza:
- division_break_lines
- ask_confirmation
- free_products

Restituisce:
- 0 -> eliminazione completata con successo
- 1 -> operazione annullata dall’utente
- 2 -> errore di lettura del buffer di input
- 3 -> lista già vuota, nessun prodotto da eliminare
- 4 -> errore critico durante la deallocazione della lista prodotti
*/
int sys_delete_user_products(user logged_user, collection user_collection){

    char username[MAX_STR_LEN];
    get_username(logged_user,username);
    char collection_name[MAX_STR_LEN];
    get_collection_name(user_collection,collection_name);

    int string_checker_result;

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    division_break_lines("AREA ELIMINAZIONE PRODOTTI",54);
    printf(ANSI_COLOR_RESET BOLD_OFF);

    if(user_collection->products_list_head == NULL){
        printf("\n"ANSI_COLOR_RED);
        printf("La tua collezione \"%s\" e' vuota, non e' presente alcun prodotto da eliminare.\n",collection_name);
        printf("\n"ANSI_COLOR_RESET);
        return 3;
    }

    printf("\n" ANSI_COLOR_MAGENTA);
    printf("Attenzione %s, stai per eliminare tutti i prodotti dalla collezione \"%s\" definitivamente. \n",username, collection_name);
    printf("Sei sicuro di voler procedere? Inserisci 0 per confermare, 1 per annullare l'eliminazione.\n" ANSI_COLOR_RESET);
    int decision = ask_confirmation();
    if(decision == 1){
        printf("\n" ANSI_COLOR_GREEN);
        printf("Hai annullato correttamente l'operazione.\n");
        printf("\n" ANSI_COLOR_RESET);
        return 1;
    }

    if(decision == 2){
        printf("\n"ANSI_COLOR_RED);
        printf("Errore lettura del buffer di input. (codice 2). Contattare un amministartore.\n");
        printf("\n"ANSI_COLOR_RESET);
        return 2;
    }

    //altrimenti procedo all'eliminazione.
    printf(ANSI_COLOR_MAGENTA"\nHai confermato l'eliminazione...\n"ANSI_COLOR_RESET);
    int result = delete_collection_products(user_collection);
    
    switch(result){
        case 1:
            printf(ANSI_COLOR_RED"\nLa lista risulta vuota quando non dovrebbe. Errore critico (codice 4). Contattare un amministratore.\n"ANSI_COLOR_RESET);
            return 4;
        default:
            printf(ANSI_COLOR_GREEN"\nLa lista prodotti della tua collezione e' stata correttamente svuotata.\n"ANSI_COLOR_RESET);
            break;
         }

    return 0;
    
}



/*
Gestisce l'accesso al menù admin da parte di un utente.

Funzionalità:
- Se l’utente è già un ADMIN, accede direttamente al menù.
- Se l’utente ha ruolo BASE, può accedere al menù admin solo previa verifica di una chiave segreta.
  In caso di verifica superata, viene promosso ad ADMIN tramite `search_and_promote_user`.

 Sicurezza: la chiave segreta è attualmente hardcoded nel codice (come stringa "admin_access_secret_string").
In una soluzione reale andrebbe letta da una sorgente sicura (file crittografato)

Parametri:
- logged_user: puntatore alla struct dell’utente loggato
- users_list_head: riferimento alla testa della lista utenti (per promozione)

Utilizza:
- division_break_lines
- sys_input_string_checker
- get_username
- search_and_promote_user

Restituisce:
- 0 -> accesso admin eseguito con successo
- 1 -> operazione annullata dall’utente
- 2 -> errore di lettura del buffer di input
- 4 -> errore critico durante la promozione a ruolo ADMIN (funzione `search_and_promote_user`)
*/
int sys_access_admin_menu(user logged_user, users* users_list_head){

    char username[MAX_STR_LEN];
    get_username(logged_user,username);


    int string_checker_result;
    char input_string[MAX_STR_LEN];
    char admin_access_secret_string[MAX_STR_LEN] = "SecretAdminPass";   ///LA CHIAVE DI ACCESSO NON DOVREBBE ESSERE OVVIAMENTE HARDCODED, ANDREBBE LETTA DA UN FILE CRITTOGRAFATO. È A SCOPO DIMOSTRATIVO.

    printf(ANSI_COLOR_GREEN ANSI_BOLD);
    division_break_lines("AREA ACCESSO AI PRIVILEGI DI ADMIN",54);
    printf(ANSI_COLOR_RESET BOLD_OFF);

    //Se l'utente loggato è già un ADMIN, allora la funzione restituirà 0.
    if(logged_user->role == ADMIN){
        printf(ANSI_BOLD ANSI_COLOR_CYAN"/n Benvenuto/a Admin! Verrai reindirizzato al menù...\n"BOLD_OFF ANSI_COLOR_RESET);
        return 0;
    }

    printf("%s, attualmente disponi soltanto dei privilegi base. Inserisci la ", username);
    printf(ANSI_COLOR_MAGENTA"chiave segreta di accesso "ANSI_COLOR_RESET);
    printf("per ottenerne i privilegi e accedere al menu.\n");
    printf("Puoi inserire una stringa vuota premendo invio per annullare l'operazione.\n");
        
    while(1){
        //Altrimenti devo effettuare il controllo sull'accesso ai privilegi da admin e cambiare il ruolo dell'utente da base ad ADMIN.

        string_checker_result = sys_input_string_checker(input_string,true,MIN_STR_LEN,MAX_STR_LEN);
        switch(string_checker_result){
            case 1:
                printf("\n"ANSI_COLOR_GREEN);
                printf("Hai annullato correttamente l'operazione...\n");
                printf("\n"ANSI_COLOR_RESET);
                return 1;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("Errore Critico (codice 2): errore di lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 2;
            case 0:
                int is_equal = strcmp(input_string,admin_access_secret_string);
                if(is_equal != 0){
                    printf(ANSI_COLOR_RED"Chiave di accesso errata. Riprova.\n"ANSI_COLOR_RESET);
                    continue;
                }
                break; //altrimenti la chiave è corretta esco dallo switch case
        }
    
        printf(ANSI_COLOR_GREEN"\nHai inserito la chiave di accesso corretta!\n"ANSI_COLOR_RESET);
        break;
    }


    int result = search_and_promote_user(users_list_head, username, ADMIN);

    if(result != 0){
        printf( "ERORRE CRITICO: (codice 4), errore di utilizzo funzione search and promote user. Contattare un amministratore.\n");
        return 4;
    }

    printf(ANSI_COLOR_MAGENTA"Adesso il tuo utente gode dei privilegi admin. Verrai reindirizzato al menu richiesto...\n"ANSI_COLOR_RESET);
    return 0;

}




/*
Stampa la panoramica completa di un utente, cioè la lista delle collezioni e per ciascuna collezione stampa la lista dei prodotti associata alla collezione stessa
Restituisce:
- 2 -> In caso di errore critico (lista inconsistente)
- 1 -> Lista delle collezioni vuota. 
- 0 -> Panoramica collezioni/prodotti stampata correttamente. 
*/
int sys_user_overview(user logged_user){

    char collection_name[MAX_STR_LEN];
    
    printf(ANSI_COLOR_MAGENTA ANSI_BOLD);
    division_break_lines("PANORAMICA UTENTE", 56);
    printf(ANSI_COLOR_RESET BOLD_OFF);

    if(logged_user == NULL) return 2; //Errore critico

    printf(ANSI_COLOR_CYAN"La tua panoramica dati e' la seguente:\n\n"ANSI_COLOR_RESET);

    
    user_overview(logged_user);

    return 0; //Success, overview printato correttamente
}




