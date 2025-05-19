#include "system.h"




/*
Funzione che implementa il controllo della stringa in input. Controlla i seguenti criteri:
    1) Che la stringa passata in ingresso non sia stata troncata -> input troppo lungo, riprova
    2) Che la stringa passata in ingresso non sia minore di min_len caratteri -> Input troppo corto, riprova
    3) Che la stringa passata in ingresso non sia maggiore di max_len caratteri -> Input troppo lungo, riprova
    4) Se il flag check_space è impostato su true, allora controlla anche che la stringa non contenga spazi.
    3) Rimuove il carattere a capo dalla stringa prelevata dal buffer di input

    Restituisce:
         0 Se la stringa passata in input è stata correttamente inserita e viene passata al chiamante tramite la stringa output_string
         1 Se l'utente immette in input una stringa vuota, indicando l'operazione di ANNULLAMENTO.
         2 In caso di errori di lettura del buffer di input (FATAL ERROR:2)

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
    2 In caso di errori di lettura del buffer di input
    1 Se l'utente inserisce 1
    0 Se l'utente inserisce 0
    
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
Implementa l'I/O per la registrazione di un nuovo utente. Chiede in input da tastiera un nuovo username, controlla che questo username non sia già utilizzato (sia già presente nella lista utenti), controlla che la password sia valida secondo la logica dell'ADT
(utilizzando la funzione validate_password di user.h) e in caso di esito positivo richiama la funzione insert_user_sorted di users.h per inserire il nuovo utente nella struttura dati utenti, con algoritmo di inserimento ordinato alfabeticamente.

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

    
    clear_screen();

  
    //INSERIMENTO NUOVO USERNAME
    while(1){

        printf("\n");
        printf("Inserisci il tuo nuovo username. (Massimo %d caratteri consentiti, minimo %d, spazi non consentiti)\n",MAX_STR_LEN-1,MIN_STR_LEN-1);
        printf("PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n");
        printf("\n");

        string_checker_result = sys_input_string_checker(username_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
        
        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Registrazione annullata correttamente. \n");
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


        //Controllo che l'utente non sia già presente nella lista utenti (DUPLICATI NON CONSENTITI)
        valid_username = user_exists(*users_list_head,username_io_string); 


        //Username disponibile, esce dal ciclo while (valid_username == 2: nessuna corrispondenza trovata nella lista, valid_username == 1: lista vuota, in entrambi casi l'username è disponibile)
        if(valid_username == 2 || valid_username == 1){
            printf("\n");
            printf("L'username e' disponibile.\n");
            printf("\n");
            break;
        }

        //Altrimenti notifica l'utente che l'username e già occupato e ricomincia il ciclo while.
        printf("\n");
        printf("L'username e' già occupato.\n");
        printf("\n");
        continue;
    }
    
        

    //INSERIMENTO NUOVA PASSWORD
    //clear_screen();
    
    //N.B: Nonostante la password NON POSSA CONTENERE SPAZI, disattivo in questo caso il controllo in quanto sarebbe ridondante,
    //Venendo già realizzato dalla funzione validate_password.
    check_space = false;


    
    while(1){
        printf("\n");
        printf("Inserisci la tua nuova password. (Massimo %d caratteri consentiti)\n\n", MAX_STR_LEN-1);
        printf("La password deve contenere:\n");
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
                printf("\n");
                printf("Registrazione annullata correttamente. \n");
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
        
        //Secondo controllo sulla password secondo i criteri dettati da user.h
        string_checker_result = validate_password(password_io_string);
        
        if(string_checker_result == 1) {
            printf("\n");
            printf("Password non valida. Contiene caratteri non ammessi e/o spazi. Riprova \n");
            printf("\n");
            continue;
        }
        if(string_checker_result == 0) break; //altrimenti la password è validata, posso uscire dal ciclo while.
    }

    
    //Una volta validato sia l'username che la nuova password, procedo all'inserimento del nuovo utente nella lista utenti.

    insert_user_sorted(users_list_head, username_io_string, password_io_string, new_user_role);

    search_user(*users_list_head,username_io_string, &new_user);

    printf("\n");
    printf("Registrazione effettuata con successo!\n");
    printf("\n");

    return new_user;
}




/*
Implementa l'I/O Per il login di un utente

Restituisce:
    - un puntatore al nuovo utente creato in caso di corretta autenticazione
    - un puntatore a NULL in caso di errori del buffer o di annullamento da parte dell'utente
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
    
    printf("\n");
    printf("Benvenuto/a nell'area login.\n"); 
    printf("\n");

    //in caso di immissione con successo effettuo il break del ciclo while.
    while(1){

        printf("\n");
        printf("Inserisci il tuo username. \n");
        printf("PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE IL LOGIN.\n");
        printf("\n");
        
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
    printf("Autenticazione effettuata con successo! \n");
    printf("\n");
    //restituisco l'utente loggato.
    return logging_user;
}





/*
Implementa l'I/O per la modifica dell'username di un utente, richiede in ingresso la stringa del nome utente attuale dell'utente e la lista degli utenti
    Restituisce:
        1 In caso di annullamento dell'operazione da parte dell'utente
        2 In caso di errori di lettura del buffer di input
        3 In caso di errori di modifica dell'utente nella struttura dati (FATAL ERROR)
        0 Se tutto va a buon fine
    N.B: La stringa current_username, nel caso di effettuata modifica, viene modificata con il nuovo nome utente inserito dall'user da terminale.
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
Implementa l'I/O per la modifica della password di un utente, richiede in ingresso la stringa del nome utente attuale dell'utente e la lista degli utenti
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
RICHIEDE: 
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
    printf("Benvenuto nell'area di modifica delle credenziali. \n");
    printf("Per poter procedere, e' necessario riconfermare l'autenticazione tramite password. \n");
    printf("\n");

    while(1){

        printf("\n");
        printf("Per annullare la modifica delle tue credenziali, immetti una stringa vuota. \n");
        printf("Inserisci la tua password per procedere con il cambiamento delle credenziali. \n");
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

    printf("Password verificata con successo!\nSi procede con la modifica delle proprie credenziali.\n");
    printf("E' possibile modificare soltanto uno dei campi username/password, immettendo una stringa vuota.\n\n");



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
Implementa l'I/O Per l'eliminazione di un utente. Non effettua la ricerca dell'utente stesso, utile quindi quando
un utente vuole eliminare il proprio profilo. 

Restituisce:
    1: Se l'utente immette una stringa vuota e annulla l'eliminazione del proprio profilo
    2: in caso di errore di lettura del buffer di input
    3: Se non è stato possiible trovare l'utente nella lista utenti
    0: Se l'eliminazione va a buon fine

*/
int sys_delete_user(users* users_list_head, char user_username[MAX_STR_LEN]){


        user user_to_del = NULL;
        char user_password[MAX_STR_LEN];

        int string_checker_result; 
        char password_io_string[MAX_STR_LEN];
        bool check_space = true;

        search_user(*(users_list_head),user_username,&(user_to_del));
        
        get_password(user_to_del,user_password);

        printf("\n");
        printf("Benvenuto nell'area di eliminazione del tuo account utente.\n");
        printf("QUESTA AZIONE SARA' DEFINITIVA. Si consiglia di procedere con cautela.\n");
        printf("\n");

        while(1){

            printf("\n");
            printf("Per procedere all'eliminazione, è' necessario inserire la propria password. ( UNA VOLTA VERIFICATA, NON PUOI TORNARE INDIETRO! )\n");
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
                printf("Password invalida. Riprova.\n");
                continue;
            }
        }
    
        //Se la password è stata verificata con successo, procedo all'operazione di eliminazione
        printf("Password verificata con successo!\n");

        
        int result = remove_user(users_list_head, user_username);

        if(result != 0){
            return 3; //FATAL ERROR 3 (NON È STATO POSSIBILE ACCEDERE ALLA LISTA UTENTI/ L'UTENTE NON È STATO TROVATO)
        }

        printf("L'UTENTE E' STATO DEFINITIVAMENTE ELIMINATO.\n");
        return 0;

}
    




/*
Implementa l'I/O per la visualizzazione della lista collezioni di un utente.
Restituisce:
    1: Se la lista è vuota 
    0: Se tutto va a buon fine
*/
int sys_print_user_collections(user logged_user){

    //Controllo che il puntatore non punti a NULL
    if(logged_user == NULL){
        printf("\n");
        printf("FATAL ERROR 1: USER POINTS TO NULL\n");
        printf("\n");
        return 1;
    }

    int result = print_collections(logged_user->collections_list_head);

    //La funzione print collections restituisce 1 se la lista è vuota -> gestisco questo caso:

    if(result == 1){
        printf("\n");
        printf("La tua lista collezioni e' vuota!\n");
        printf("\n");
        return 1;
    }

    //Altrimenti tutto va a buon fine, restituisco 0.
    return 0; 
}



/*
Implementa l'I/O per l'accesso ad una collezione, e il conseguente ingresso nel menù prodotti. 

Restituisce:
    4 Se la lista delle collezioni risulta vuota durante l'accesso ai dati utente.
    3 Se la lista collezioni è vuota', (*user_collection = NULL)
    2 In caso di errore di lettura del buffer di input stdin
    1 Se l'utente annulla l'accesso alla collezione. (*user_collection = NULL)
    0 Se tutto va a buon fine (*user_collection = collezione a cui si vuole accedere)
*/
int sys_access_user_collection(user logged_user, collection* user_collection){

    int string_checker_result;
    char collection_name_io_string[MAX_STR_LEN];
    bool check_space = false;
    *user_collection = NULL;

    if((logged_user->collections_list_head) == NULL){\
        printf("\n");
        printf("Impossibile accedere ad una collezione, la tua lista è vuota. Creane una dal menu' collezioni.\n");
        printf("\n");
        return 3;
    }
    while(1){
        printf("\n");
        printf("Scegli una fra le seguenti collezioni a cui accedere inserendone il nome.\n");
        printf("E'necessario inserire correttamente maiuscole e spazi, per annullare l'accesso ad una collezione inserire una stringa vuota.\n");
        printf("Lista collezioni di %s:\n", logged_user->username);
        printf("\n");
        print_collections(logged_user->collections_list_head);
        printf("\n");

        string_checker_result = sys_input_string_checker(collection_name_io_string, false,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("L'accesso ad una collezione e' stato annullato correttamente.\n");
                printf("\n");
                return 1;
            case 2:
                printf("ERRORE Critico: errore di lettura del buffer di input (codice 2), contattare un amministratore.\n");
                return 2;
            default:
                break;
        }

        int search_result = search_collection(logged_user->collections_list_head,collection_name_io_string,user_collection);

        switch(search_result){
            case 1: 
                printf("\n");
                printf("ERRORE Critico. La lista delle collezioni risulta vuota durante la ricerca della collezione (codice 4). Contattare un amministratore.\n");
                printf("\n");
                return 4;
            case 2:
                printf("\n");
                printf("La collezione non e' stata trovata. Inserire un nome della collezione a cui si desidera accedere valido.\n");
                printf("\n");
                continue;
            default:
                break; 
        }

        break;

    }

    printf("Accesso alla collezione \"%s\" effettuato con successo. Scegli una delle seguenti opzioni del menu' prodotti.\n", collection_name_io_string);
    return 0; //NB adesso *user_collection punterà alla collezione alla quale l'utente desiderava fare l'accesso.
}



/*
Implementa l'I/O per l'aggiunta di una nuova collezione nella lista delle collezioni di un utente già loggato (Richiede in ingresso il puntatore all'utente loggato.)
Restituisce:
    1: In caso di annullamento da parte dell'utente
    2: In caso di errore di lettura del buffer di input
    4: In caso di errore critico di allocazione di memoria
    0: Se tutto va bene
*/
int sys_insert_collection(user logged_user){

    int string_checker_result;
    char collection_name_io_string[MAX_STR_LEN];
    char collection_type_io_string[MAX_STR_LEN];

    bool check_space = false; //In questo caso, le stringhe possono contenere spazi.

    printf("\n");
    printf("Benvenuto/a nell'area di creazione di una nuova collezione!\n");
    printf("\n");

    while(1){

        printf("\n");
        printf("Per annullare l'inserimento della tua nuova collezione, inserisci una stringa vuota \n");
        printf("Inserisci il nome della tua nuova collezione. \n");
        printf("\n");

        string_checker_result = sys_input_string_checker(collection_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Operazione di aggiunta collezione annullata con successo.\n");
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

            //Verifico che la collezione esiste nella lista, in tal caso ricomincia il ciclo while
            if(collection_exists(logged_user->collections_list_head,collection_name_io_string) == 0){
                printf("\n");
                printf("Hai gia' una collezione con questo nome, non sono consentiti duplicati. Riprova.\n");
                printf("\n");
                continue;
            }

            break;
        }

    //Passo all'inserimento della tipologia della collezione

    printf("\n");

    while(1){

        printf("Per annullare l'inserimento della tua nuova collezione, inserisci una stringa vuota \n");
        printf("Inserisci la tipologia della nuova collezione. \n\n");

        string_checker_result = sys_input_string_checker(collection_type_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Operazione di aggiunta collezione annullata con successo. \n");
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

            break;
        }

        int result = insert_collection(&(logged_user->collections_list_head),collection_name_io_string, collection_type_io_string);
        if (result == 1){
            printf("\n");
            printf("CRITICAL ERROR 4: errore di allocazione di memoria! Contattare un amministratore.\n");
            printf("\n");
            return 4;
        }

        printf("\n");
        printf("La tua nuova collezione: (%s) e' stata aggiunta correttamente.\n\n",collection_name_io_string);
        printf("\n");
        return 0; //Tutto è andato a buon fine
    }
    




/*
Implementa l'I/O Per la modifica della collezione di un utente già loggato.
Restituisce:
    1) In caso di annullamento dell'operazione di modifica della collezione da parte dell'utente
    2) In caso di errore della lettura del buffer di input stdin
    3) Se la lista collezioni dell'utente è vuota (Non c'è alcuna collezione modificabile)
    4) Per errori critici nella modifica finale, RARO!
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

    //Ricerca della collezione che l'utente desidera modificare
    while(1){

        printf("Benvenuto/a nell'area di modifica collezione.\n");
        printf("Inserisci il nome della collezione che vuoi modificare, (Attenzione, il nome deve essere lo stesso, comprese maiuscole e spazi.\n");
        printf("Se vuoi annullare la modifica, inserisci una stringa vuota.\n");
        printf("\n");
        string_checker_result = sys_input_string_checker(collection_name_io_string, check_space,MIN_STR_LEN,MAX_STR_LEN);
        printf("\n");
        switch(string_checker_result){
            case 1:
                printf("Modifica della collezione annullata con successo.\n");
                return 1;
            case 2:
                printf("FATAL ERROR 2: errore della lettura buffer di input. Contattare un amministartore.\n");
                return 2;
            default:
                //verifico che la collezione esista nella lista collezioni dell'utente loggato
                int collection_found = collection_exists(logged_user->collections_list_head, collection_name_io_string);
                
                switch(collection_found){
                    case 1:
                        printf("\n");
                        printf("La tua lista collezioni è vuota, non e' presente alcuna collezione da modificare!\n");
                        printf("\n");
                        return 3;
                    case 2:
                        printf("\n");
                        printf("Non e' stata trovata una corrispondenza. Riprova. \n");
                        printf("\n");
                        continue;
                    default:
                        printf("\n");
                        printf("Collezione (%s) trovata! Si procede con la modifica...\n",collection_name_io_string);
                        printf("\n");
                        break;
                }        
            }
        break;
        }

    
    //Procedo con la modifica del nome della collezione
    while(1){

        printf("\n");
        printf("Inserisci un nuovo nome per la tua collezione. Deve essere differente da (%s) e dal nome delle tue altre collezioni.\n", collection_name_io_string);
        printf("Se vuoi lasciare invariato il nome della collezione e modificarne solo il tipo, immetti una stringa vuota.\n");
        printf("\n");

        string_checker_result = sys_input_string_checker(collection_new_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1: 

                printf("\n");
                printf("Il nome della collezione rimarra' invariato.\n");
                printf("\n");

                break;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: errore della lettura buffer di input. Contattare un amministartore.\n");
                printf("\n");
                return 2;
            default: 
                if(strcmp(collection_new_name_io_string,collection_name_io_string) == 0){
                    printf("\n");
                    printf("Inserisci un nome per la tua collezione differente da quello precedente.\n");
                    printf("Se desideri lasciare invariato il nome della tua collezione e modificarne solo il tipo, inserisci una stringa vuota, altrimenti riprova.\n");
                    printf("\n");
                    continue;
                }
                //se il nuovo nome è differente da quello precedente, allora verifico che sia univoco nella lista delle collezioni dell'utente.
                int collection_found = collection_exists(logged_user->collections_list_head, collection_new_name_io_string); 
                
                if(collection_found == 0){
                    printf("\n");
                    printf("E'gia' presente una collezione con il seguente nome :(%s). Riprova.\n",collection_new_name_io_string);
                    printf("\n");
                    continue;
                }
                //altrimenti posso procedere con la modifica del tipo.
                printf("\n");
                printf("Il nuovo nome: (%s) e' valido. Si procede con la modifica della tipologia.\n",collection_new_name_io_string	);
                printf("\n");
                break;
            }
        break;
    }

    //Procedo con la modifica del tipo della collezione
    while(1){

        printf("\n");
        printf("Inserisci una nuova tipologia per la tua collezione.\n");
        printf("Se vuoi lasciare invariata la tipologia della collezione, inserisci una stringa vuota.\n");
        printf("\n");
        string_checker_result = sys_input_string_checker(collection_new_type_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("La tipologia della collezione rimarra' invariata.\n");
                printf("\n");
                break;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: errore della lettura dle buffer di input. Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default:
                printf("\n");
                printf("La tipologia inserita è valida.\n");
                printf("\n");
                break;
        }

        break;
    }

    int final_res = search_and_modify_collection(logged_user->collections_list_head,collection_name_io_string,collection_new_name_io_string,collection_new_type_io_string);

    switch(final_res){
        case 1: 
            printf("ERRORE CRITICO: La lista collezioni risulta vuota al momento della modifica. Contattare un amministratore.\n");
            return 4;
        case 2:
            printf("ERRORE CRITICO: Collezione da modificare non trovata. Contattare un amministratore.\n");
            return 4;
        default: 
            printf("La tua collezione e' stata modificata con successo in:\n");
            printf("Nome: %s\n", (strlen(collection_new_name_io_string) > 0 ? collection_new_name_io_string : collection_name_io_string));
            printf("Tipo: %s\n", (strlen(collection_new_type_io_string) > 0 ? collection_new_type_io_string : "Invariata"));
            break;
    }   
    return 0; //Tutto è andato a buon fine
}
    
    

    

/*
Implementa l'I/O Per la eliminazione di UNA collezione da parte di un utente loggato.

Restituisce:
    1 In caso di annullamento dell'operazione da parte dell'utente
    2 In caso di errore critico di lettura del buffer di input stdin
    3 Se la lista collezioni dell'utente è vuota.
    4 In caso di errori critici durante l'eliminazione della collezione (RARI!)
    0 Se tutto va a buon fine
*/
int sys_delete_collection(user logged_user){

    int string_checker_result;

    //Stringa utilizzata per l'inserimento del nome della collezione che l'utente desidera eliminare
    char collection_name_io_string[MAX_STR_LEN];

    bool check_space = false;

    if((logged_user->collections_list_head) == NULL){

        printf("\n");
        printf("Impossibile eliminare una collezione dell'utente poichè non possiede nessuna collezione.\n");
        printf("\n");
        return 3;
    }

    while(1){

        printf("\n");
        printf("Inserisci il nome della collezione che desideri eliminare.\n");
        printf("Se vuoi annullare la modifica, inserisci una stringa vuota.\n");
        printf("\n");
        string_checker_result = sys_input_string_checker(collection_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Eliminazione della collezione annullata correttamente. \n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default:
                break;
        }

        int exists = collection_exists(logged_user->collections_list_head,collection_name_io_string);

        switch(exists){
            case 1:
                printf("\n");
                printf("La lista delle collezioni dell'utente è vuota. Impossibile eliminare la collezione richiesta.\n");
                printf("\n");
                return 3;
        
            case 2: 
                printf("\n");
                printf("La collezione: (%s) , non e' stata trovata. Riprova inserendo un nome collezione adeguato.\n",collection_name_io_string);
                printf("\n");
                continue;
            default:
                printf("\n");
                printf("Corrispondenza trovata...\n");
                printf("\n");
                break;
        }

        break;

    }

    //Blocco di conferma ulteriore per la cancellazione della collezione
    while (1){

        printf("\n");
        printf("Confermi di voler eliminare la collezione \"%s\"? (Azione definitiva)\n", collection_name_io_string);
        printf("Inserisci 0 per confermare, 1 per annullare.\n");        
        printf("\n");

        int confirm = ask_confirmation();


        switch(confirm){
            case 1:
                printf("\n");
                printf("L'operazione è stata annullata. La collezione non verra' elimianta.\n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("ERRORE Critico: 2 errore lettura del buffer di input stdin, contattare un admin.\n");
                printf("\n");
                return 2;
            default:
                printf("\n");
                printf("Eliminazione confermata.\n");
                printf("\n");
                break;
        }
    }



    int result = remove_collection(&(logged_user->collections_list_head),collection_name_io_string);

    switch(result){
        case 1:
            printf("\n");
            printf("ERRORE CRITICO: la lista collezioni durante la fase di eliminazione e' risultata vuota. Contattare un admin.\n");
            printf("\n");
            return 4;
        case 2:
            printf("\n");
            printf("ERRORE CRITICO: la lista collezioni durante la fase di eliminazione non possedeva la collezione ricercata. Contattare un admin.\n");
            printf("\n");
            return 4;
        default:
            printf("\n");
            printf("La collezione (%s) e' stata definitivamente cancellata dalla lista collezioni.\n",collection_name_io_string);
            printf("\n");
            break;
    }
    //l'eliminazione è andata a buon fine, restituisco 0.
    return 0;
}



   

/*
Implementa l'I/O Per la eliminazione di TUTTE le collezioni da parte di un utente.

Restituisce:
    1 In caso di annullamento dell'operazione da parte dell'utente
    2 In caso di errore critico di lettura del buffer di input stdin
    3 Se la lista collezioni dell'utente è vuota.
    4 In caso di errori critici durante l'eliminazione delle collezioni (RARI!)
    0 Se tutto va a buon fine
*/
int sys_delete_collections(user logged_user){

    if((logged_user->collections_list_head) == NULL){
        printf("\n");
        printf("L'utente possiede già una lista collezioni vuota.\n");
        printf("\n");
        return 3;
    }


    printf("\n");
    printf("Confermi di voler eliminare tutte le tue collezioni? (Azione definitiva)\n");
    printf("Inserisci 0 per confermare, 1 per annullare.\n");     
    printf("\n");

    int confirm = ask_confirmation();
    
    switch(confirm){
        case 1:
            printf("\n");
            printf("L'operazione e' stata annullata. Le tue collezioni non verranno eliminate.\n");
            printf("\n");
            return 1;
        case 2:
            printf("\n");
            printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
            printf("\n");
            return 2;
        default:
            printf("\n");
            printf("Operazione confermata...\n");
            printf("\n");
            break;
    }

    int result = free_collections(&(logged_user->collections_list_head));

    if(result == 1){
        
        printf("\n");
        printf("ERRORE Critico: la lista collezioni dell'utente e' vuota (codice 4). Contattare un amministratore.");
        printf("\n");
        return 4;
    }

    printf("\n");
    printf("Tutte le tue collezioni sono state eliminate.\n");
    printf("\n");
    return 0;
}





/*
Funzione che implementa l'I/O della stampa della lista prodotti di una collezione di un utente. 

Restituisce:
    1 Se la lista prodotti della collezione è vuota.
    0 Se tutto va a buon fine
    4 Se al momento della chiamata della funzione print_products risulta vuota (non dovrebbe accadere, raro, codice 4)
*/
int sys_print_user_products(user logged_user, collection user_collection){

    if(user_collection->products_list_head == NULL){
        printf("\n");
        printf("%s , la tua lista collezioni \"%s\" e' vuota.\n",logged_user->username, user_collection->collection_name);
        printf("\n");
        return 1;
    }

    int result = print_products(user_collection->products_list_head);

    if(result == 1){
        printf("\n");
        printf("ERRORE Critico: la lista dei prodotti risulta vuota (codice 04). Contattare un amministratore.\n");
        printf("\n");
        return 4;
    }

    return 0;

}


/*
@implementa l'I/O Per l'inserimento di un nuovo prodotto in una determinata collezione passata in ingresso

    Restituisce:
        0 Se tutto va a buon fine
        1 In caso di annullamento da parte dell'utente
        2 In caso di errori di lettura del buffer di input (codice 2)
        4 In caso di errori di accesso alla memoria (Codice 4)
*/
int sys_insert_user_product(user logged_user, collection user_collection){

    int string_checker_result;

    char product_name_io_string[MAX_STR_LEN];

    char product_type_io_string[MAX_STR_LEN];

    char product_condition_io_string[MAX_STR_LEN];

    float product_buyprice;

    bool check_space = false; //spazi consentiti

    printf("\n");
    printf("%s, stai inserendo un nuovo prodotto alla collezione \"%s\" \n",logged_user->username, user_collection->collection_name);
    printf("\n");

    /* CICLO NOME PRODOTTO */
    while (1){

        printf("Inserisci un nome per il tuo nuovo prodotto. Duplicati non consentiti. \n");
        printf("Puoi annullare il processo in qualsiasi momento inserendo una stringa vuota.\n");
        string_checker_result = sys_input_string_checker(product_name_io_string, check_space, MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1: 
                printf("\n");
                printf("Operazione di inserimento prodotto annullata...\n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default:
                int exists = exist_sorted(user_collection->products_list_head, product_name_io_string);

                if (exists == 0){
                    printf("\n");
                    printf("E'Gia' presente un prodotto nella collezione \"%s\" con questo nome. I duplicati non sono consentiti. Riprova.\n",user_collection->collection_name);
                    printf("\n");
                    continue;
                } else {
                    printf("\n");
                    printf("Il nome e' disponibile! Si procede con l'inserimento della tipologia del prodotto... \n");
                    printf("\n");
                    break;
                    }
                break;
        }
    break;
    }

    /* CICLO TIPOLOGIA PRODOTTO */

    while (1){

        printf("Inserisci una tipologia per il tuo nuovo prodotto.\n");
        printf("Puoi annullare il processo in qualsiasi momento inserendo una stringa vuota.\n");
        string_checker_result = sys_input_string_checker(product_type_io_string, check_space, MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1: 
                printf("\n");
                printf("Operazione di inserimento prodotto annullata...\n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default:
                printf("\n");
                printf("Tipologia del prodotto correttamente inserita. \n");
                printf("\n");
                break;
                }
        break;
    }


    /* CICLO CONDIZIONI PRODOTTO*/

    while (1){

        printf("Inserisci le condizioni per il tuo nuovo prodotto.\n");
        printf("Puoi annullare il processo in qualsiasi momento inserendo una stringa vuota.\n");
        string_checker_result = sys_input_string_checker(product_condition_io_string, check_space, MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1: 
                printf("\n");
                printf("Operazione di inserimento prodotto annullata...\n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default:
                printf("\n");
                printf("Condizioni del prodotto correttamente inserite. \n");
                printf("\n");
                break;
                }
        break;
    }

    /* CICLO PREZZO DI ACQUISTO PRODOTTO*/

     //in questo caso, occorre utilizzare una stringa di appoggio per contenere la cifra inserita dall'utente, tale cifra verrà poi
     //controllata (devono essere numeri e non caratteri) ed eventualmente convertita (casting) a float.
    char temp_buyprice[MAX_STR_LEN];

    while(1){

        printf("Inserisci il prezzo di acquisto per il tuo nuovo prodotto. (Non si accettano numeri negativi o uno zero!) \n");
        printf("Puoi annullare il processo premendo invio. \n");


        //in questo caso non può contenere spazi, avrò in questo modo un controllo in meno da svolgere seguentem.
        string_checker_result = sys_input_string_checker(temp_buyprice,true,0,10);

        switch(string_checker_result){
            case 1: 
                printf("\n");
                printf("Operazione di inserimento prodotto annullata...\n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n");
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
            printf("Hai inserito dei caratteri, non sono validi. Si accettano cifre positive non nulle. Riprova.\n");
            continue;
        } else if(*endptr != '\0'){
            printf("Hai inserito in parte dei caratteri superflui non validi. Si accettano cifre positive non nulle. Riprova.\n");
            continue;
        } else if (product_buyprice <= 0){
            printf("Hai inserito un numero negativo o nullo non valido. Si accettano cifre positive non nulle. Riprova.\n");
            continue;
        } else {
            printf("Numero valido correttamente inserito...\n");
        }

        printf("Il prezzo di acquisto inserito e' il seguente: %.2f \n",product_buyprice); //stampo 2 cifre decimali
        printf("Premi 0 per confermarlo, 1 per modificarne il valore.\n");
        int confirm = ask_confirmation();
        
        switch (confirm){
            case 1: continue;
            case 2: printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n"); return 2;
            default: break;
        }
    
    printf("Inserimento del prodotto \"%s\" in corso...\n",product_name_io_string);
    break; 
    }

    int result = insert_product(&(user_collection->products_list_head),product_name_io_string,product_type_io_string,product_condition_io_string,product_buyprice);

    switch(result){
        case 1: 
            printf("ERRORE Critico: errore di allocazione della memoria (codice 4). Contattare un amministratore.\n");
            return 4;
        case 2:
            printf("ERRORE Critico: rilevato duplicato quando non dovrebbe (codice 4). Contattare un amministratore.\n");
            return 4;
        default:
            break;
    }

    printf("Il seguente prodotto e' stato correttamente inserito nella collezione \"%s\": \n",user_collection->collection_name);
    printf("Nome prodotto: %s\n", product_name_io_string);
    printf("Tipologia: %s\n", product_type_io_string);
    printf("Condizioni: %s\n",product_condition_io_string);
    printf("Prezzo di acquisto: %.2f\n",product_buyprice);
    return 0;
}




/*
@Implementa l'I/O per la modifica di un prodotto di un utente, a partire dalla collezione dell'utente passata in ingresso.

    Restituisce:
        0 Se tutto va a buon fine
        1 In caso di annullamento da parte dell'utente
        2 in caso di errori di lettura del buffer di input stdin (codice 2)
        3 In caso di lista prodotti dell'utente vuota.
        4 In caso di errori logici di accesso alla struttura dati in memoria (codice 4)
        5 In caso di errori di modifica del prodotto durante la chiamata alla funzione search_and_modify_products (libreria products.h) (codice 5)
*/
int sys_modify_user_product(user logged_user, collection user_collection){

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

    //stampo la lista dei prodotti della collezione dell'utente
    printf("\nI prodotti nella tua collezione sono i seguenti:\n");
    int result = sys_print_user_products(logged_user, user_collection);
    if(result == 4){
        return 4;  //errore critico di accesso alla struttura dati, la lista risulta vuota quando non dovrebbe (codice 4)
    }
    if(result == 1){
        printf("Lista vuota! Nessun prodotto modificabile.\n");
        return 3; //Lista vuota, restituisco 3
    }


    ////////////////////////////////////////////////////CICLO DI RICERCA PRODOTTO DA MODIFICARE/////////////////////////////////////////////////
    while(1){
        //altrimenti stampa la lista dei prodotti
        printf("\n");
        printf("Inserisci il nome del prodotto della collezione \"%s\" che desideri modificare. \n",logged_user->username, user_collection->collection_name);
        printf("Inserisci una stringa vuota per annullare l'operazione di modifica. \n");
        printf("\n");

        string_checker_result = sys_input_string_checker(product_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Modifica del prodotto annullata correttamente. \n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default:
                break;
        }

        //controllo se il nome del prodotto inserito in input esista nella lista dei prodotti
        int exists = exist_sorted(user_collection->products_list_head, product_name_io_string);

        switch (exists) {
            case 1: 
                printf("Lista vuota quando non dovrebbe. Errore critico di lettura dati in memeria (Codice 4). Contattare un'amministratore. \n");
                return 4;
            case 2: 
                printf("Non e' stato trovato il prodotto nella lista. Assicurati di aver inserito correttamente spazi/maiuscole. Riprova.\n");
                continue;
            default:
                printf("Prodotto trovato, si procede con la modifica...\n");
                break;
        }
        break;
    }

    ///PRODUCT_NAME_IO_STRING CONTIENE IL NOME DEL PRODOTTO CORRETTO E PRESENTE IN LISTA DEL PRODOTTO DA MODIFICARE.

    ////////////////////////////////////////////CICLO DI MODIFICA NOME DEL PRODOTTO///////////////////////////////////////////////////////////
    while(1){
        
        printf("\n");
        printf("Inserisci un nuovo nome per il tuo prodotto. Deve essere differente dai prodotti nella tua lista e da \"%s\"\n", product_name_io_string);
        printf("Se vuoi mantenere invariato il nome del prodotto, inserisci una stringa vuota.\n");
        printf("\n");

        string_checker_result = sys_input_string_checker(new_product_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        //controllo validità input, se lo è, nel default controllo che non sia occupato. Se non lo è, -> new_product_name_io_string è il nuovo nome validitato.
        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Il nome del prodotto rimarra' invariato, si procede con la modifica della tipologia...\n");
                printf("\n");
                unchanged_name = true;
                break;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default: 
                int exists = exist_sorted(user_collection->products_list_head,new_product_name_io_string); //controllo che l'input valido non sia occupato
                switch(exists) {
                    case 1: 
                        printf("La lista e' vuota quando non dovrebbe. Errore critico di lettura dati in memeria (Codice 4). Contattare un'amministratore. \n");
                        return 4;
                    case 2: 
                        printf("Il nuovo nome prodotto inserito e' disponibile. Si procede con la modifica della tipologia...\n");
                        break;
                    default:
                        printf("Il nuovo nome prodotto non e' disponibile. Riprova.\n");
                        continue;
                    }
        }
        break;
    }


    ////////////////////////////////////////////CICLO DI MODIFICA TIPOLOGIA DEL PRODOTTO///////////////////////////////////////////////////////////
    while(1){

        printf("\n");
        printf("Inserisci una nuova tipologia per il tuo prodotto.\n");
        printf("Se vuoi mantenere invariata la tipologia del prodotto, inserisci una stringa vuota.\n");
        printf("\n");

        string_checker_result = sys_input_string_checker(new_product_type_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        //controllo validità input inserito.   Default:  new_product_type_io_string conterrà la nuova tipologia valida.
        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("La tipologia del prodotto rimarra' invariata, si procede con la modifica della tipologia...\n");
                printf("\n");
                unchanged_type = true;
                break;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default: 
                printf("La tipologia inserita e' valida. Si procede con la modifica delle condizioni...\n");
                break;
        }
        break;
    }



    /////////////////////////////////////////////CICLO DI MODIFICA CONDIZIONI DEL PRODOTTO////////////////////////////////////////////////////
    while(1){

        printf("\n");
        printf("Inserisci una nuova condizione per il tuo prodotto.\n");
        printf("Se vuoi mantenere invariate le condizioni del prodotto, inserisci una stringa vuota.\n");
        printf("\n");

        string_checker_result = sys_input_string_checker(new_product_condition_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        //controllo validità input inserito.   Default:  new_product_type_io_string conterrà la nuova tipologia valida.
        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Le condizioni del prodotto rimarranno invariate, si procede con la modifica del prezzo di acquisto...\n");
                printf("\n");
                unchanged_condition = true;
                break;
            case 2:
                printf("\n");
                printf("FATAL ERROR 2: errore della lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default: 
                printf("Le condizioni inserite sono valide. Si procede con la modifica del prezzo di acquisto...\n");
                break;
        }
        break;
    }



    ////////////////////////////////////////////////////CICLO DI MODIFICA PREZZO DI ACQUISTO DEL PRODOTTO////////////////////////////////////////////


    char temp_buyprice[MAX_STR_LEN];

    while(1){

        printf("Inserisci il prezzo di acquisto per il tuo nuovo prodotto. (Non si accettano numeri negativi o uno zero!) \n");
        printf("Puoi annullare il processo premendo invio. \n");


        //in questo caso non può contenere spazi, avrò in questo modo un controllo in meno da svolgere seguentem.
        string_checker_result = sys_input_string_checker(temp_buyprice,true,0,10);

        switch(string_checker_result){
            case 1: 
                printf("\n");
                printf("Il prezzo di acquisto rimarra' invariato, si procede alla conferma della modifica...\n");
                printf("\n");
                unchanged_buyprice = true;
                break;
            case 2:
                printf("\n");
                printf("ERRORE CRITICO: lettura del buffer di input fallita (codice 2). Contattare un amministratore.\n");
                printf("\n");
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
            printf("Hai inserito dei caratteri, non sono validi. Si accettano cifre positive non nulle. Riprova.\n");
            continue;
        } else if(*endptr != '\0'){
            printf("Hai inserito in parte dei caratteri superflui non validi. Si accettano cifre positive non nulle. Riprova.\n");
            continue;
        } else if (new_product_buyprice <= 0){
            printf("Hai inserito un numero negativo o nullo non valido. Si accettano cifre positive non nulle. Riprova.\n");
            continue;
        } else {
            printf("Numero valido correttamente inserito...\n");
        }

        break;
    }




    //////////////////////////////////////////////////////////CONFERMA NUOVO PRODOTTO INSERITO/////////////////////////////////////////
    printf("Il prodotto modificato sara' il seguente:\n\n");

    printf("Nome: %s\n", unchanged_name ? "Invariato" : new_product_name_io_string);
    printf("Tipologia: %s\n", unchanged_type ? "Invariato" : new_product_type_io_string);
    printf("Condizioni: %s\n", unchanged_condition ? "Invariato" : new_product_condition_io_string);
    
    if (unchanged_buyprice) printf("Prezzo di acquisto: Invariato\n\n");
    else printf("Prezzo di acquisto: %.2f\n\n", new_product_buyprice);


    printf("Confermi di voler procedere alla modifica? Inserisci 0 per confermare, 1 per annullare.\n");
    int confirm = ask_confirmation();

    if(confirm == 2){
        printf("Errore del buffer di input (codice 2). Contattare un amministratore.\n");
        return 2;
    }
    if(confirm == 1){
        printf("La modifica del prodotto e' stata annullata correttamente.\n");
        return 1;
    }

    //altrimenti, se result == 0 modifico il prodotto.

    int final_result = search_and_modify_product(&(user_collection->products_list_head), product_name_io_string,new_product_name_io_string, new_product_type_io_string, new_product_condition_io_string,new_product_buyprice);

    switch (final_result) {
        case 1:
            printf("ERRORE CRITICO: lista vuota quando non dovrebbe, errore di accesso alla struttura dati in memoria. (errore 4). Contattare un amministratore.\n");
            return 4;
        case 2:
            printf("ERRORE CRITICO: Prodotto non trovato, mentre precedentemente lo è stato. Errore critico (codice 4), contattare un amministratore.\n");
            return 2;
        case 3:
            printf("ERRORE CRITICO: errore nella modifica del prodotto durante la chiamata a search_and_modify_product. Contattare un amministratore (codice 5)\n");
            return 5;
        default: 
            printf("Prodotto correttamente modificato!\n");
    }

    return 0;

}




/*
Implementa l'I/O Per l'eliminazione di un prodotto data una collezione passata in ingresso. 

    Restituisce: 
        0 In caso di eliminazione avvenuta con successo
        1 In caso di annullamento da parte dell'utente
        2 In caso di errore di lettura del buffer di input stdin
        3 Se la lista dei prodotti della collezione dell'utente e' gia' vuota. 
        4 Se la lista risulta vuota quando non dovrebbe durante l'accesso alla struttura dati in memoria, codice 4
*/
int sys_delete_user_product(user logged_user, collection user_collection){

    int string_checker_result;
    char product_name_io_string[MAX_STR_LEN];
    bool check_space = false;
    

    //se la lista prodotti è vuota, restituisco 3
    if(user_collection -> products_list_head == NULL){
        printf("La collezione \"%s\" e' gia' vuota. Non e' presente alcun prodotto da eliminare.\n",user_collection->collection_name);
        return 3;
    }

    while(1){

        printf("I prodotti all'interno della tua collezione \"%s\" sono i seguenti:\n\n",user_collection->collection_name);
        int print_result = print_products(user_collection->products_list_head);

        if(print_result == 1){
            printf("ERRORE Critico, la lista risulta vuota durante l'accesso in memoria quando non dovrebbe esserlo. Codice 4. Contattare un amministratore.\n");
            return 4;
        }
        
        //altrimenti stampo correttamente i prodotti della lista.

        printf("Digita il prodotto che desideri eliminare. Assicurati di inserire correttamente maiuscole/spazi.\n");
        printf("Per annullare l'operazione inserisci una stringa vuota. \n\n");

        string_checker_result = sys_input_string_checker(product_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
        switch(string_checker_result){
            case 1:
                printf("\n");
                printf("Eliminazione annullata correttamente. \n");
                printf("\n");
                return 1;
            case 2:
                printf("\n");
                printf("Errore durante la lettura del buffer di input stdin. Contattare un amministratore.\n");
                printf("\n");
                return 2;
            default: 
                printf("\n");
                printf("Ricerca del prodotto \"%s\" in corso...\n",product_name_io_string);
                break;
        }

        int exists = exist_sorted(user_collection->products_list_head,product_name_io_string);

        switch(exists){
            case 1:
                printf("ERRORE Critico, la lista risulta vuota durante l'accesso in memoria quando non dovrebbe esserlo. Codice 4. Contattare un amministratore.\n");
                return 4;
            case 2:
                printf("Il prodotto non e' stato trovato all'interno della lista. Riprova.\n");
                continue;
            default:
                printf("Corrispondenza trovata!\n");
                break;
        }
        break;
    }

    printf("Il prodotto che eliminerai e' il seguente: \n");
    search_and_print_product(user_collection->products_list_head, product_name_io_string);
    printf("Confermi di volerlo eliminare? Inserisci 0 per confermare, 1 per annullarne l'eliminazione.\n");
    int result = ask_confirmation();

    if(result == 1){
        printf("Operazione annullata correttamente. Il tuo prodotto non verra' eliminato. \n");
        return 1;
    }

    int final_result = remove_product(&(user_collection->products_list_head), product_name_io_string);

    if(final_result == 1){
        printf("ERRORE Critico, la lista dei prodotti risulta vuota quando non dovrebbe. (codice 4). Contattare un amministratore. \n");
        return 4;
    } else if (final_result == 2){
        printf("ERRORE Critico, non e' stata trovata una corrispondenza durante l'eliminazione anche se non dovrebbe accadere (codice 4). Contattare un amministratore.\n");
        return 4;
    }
    
    //altrimenti il prodotto e' stato correttamente eliminato.

    printf("Il prodotto \"%s\" e'stato correttamente eliminato\n",product_name_io_string);
    return 0;
}




/*
Implementa l'I/O Per l'eliminazione di tutti i prodotti di una lista prodotti di una collezione di un utente. 

    Restituisce:
        1 In caso di annullamento da parte dell'utente
        2 in caso di errori di lettura del buffer di input stdin
        4 In caso di errore critico durante l'eliminazione dei prodotti, in particolare se la lista risulta vuota quando non dovrebbe. 
*/
int sys_delete_user_products(user logged_user, collection user_collection){

    int string_checker_result;

    if(user_collection->products_list_head == NULL){
        printf("La tua collezione \"%s\" e' gia' vuota, non e' presente alcun prodotto da eliminare.\n",user_collection->collection_name);
        return 3;
    }

    printf("Attenzione %s, stai per eliminare tutti i prodotti dalla collezione \"%s\" definitivamente. \n",logged_user->username, user_collection->collection_name);
    printf("Sei sicuro di voler procedere? Inserisci 0 per confermare, 1 per annullare l'eliminazione.\n");
    int decision = ask_confirmation();
    if(decision == 1){
        printf("\n");
        printf("Hai annullato correttamente l'operazione.\n");
        printf("\n");
        return 1;
    }

    if(decision == 2){
        printf("\n");
        printf("Errore lettura del buffer di input. (codice 2). Contattare un amministartore.\n");
        printf("\n");
        return 2;
    }

    //altrimenti procedo all'eliminazione.
    printf("Hai confermato correttamente l'eliminazione...\n");
    int result = free_products(&(user_collection->products_list_head));
    
    switch(result){
        case 1:
            printf("La lista risulta vuota quando non dovrebbe. Errore critico (codice 4). Contattare un amministratore.\n");
            return 4;
        default:
            printf("La lista prodotti della tua collezione e' stata correttamente svuotata.\n");
            break;
         }

    return 0;
    
}