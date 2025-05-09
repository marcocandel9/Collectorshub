#include "users_system.h"




/*
Funzione che implementa il controllo della stringa in input. Controlla i seguenti criteri:
    1) Che la stringa passata in ingresso non sia stata troncata -> input troppo lungo, riprova
    2) Che la stringa passata in ingresso non sia minore di min_len caratteri -> Input troppo corto, riprova
    3) Che la stringa passata in ingresso non sia maggiore di max_len caratteri -> Input troppo lungo, riprova
    4) Se il flag check_space è impostato su true, allora controlla anche che la stringa non contenga spazi.
    3) Rimuove il carattere a capo dalla stringa prelevata dal buffer di input

    Restituisce:
    - 0 Se la stringa passata in input è stata correttamente inserita e viene passata al chiamante tramite la stringa output_string
    - 1 Se l'utente immette in input una stringa vuota, indicando l'operazione di ANNULLAMENTO.
    - 2 In caso di errori di lettura del buffer di input (FATAL ERROR:2)

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


        //Controlli sull'input immesso dall'utente

        //l'utente ha immesso invio, vuole annullare la registrazione
        if(buffer_len == 0){
            printf("\n");
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
            printf("Stringa troppo corta. Minimo %d caratteri consentiti. Riprova.\n", min_len_plus1-1);
            continue; //riparte il ciclo while
        }

        if(buffer_len > max_len_plus1-1){
            printf("Stringa troppo lunga. Massimo %d caratteri consentiti. Riprova.\n", max_len_plus1-1);
            continue; //riparte il ciclo while
        }

       

        break;

    }

    strcpy(output_string,buffer);
    return 0;

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

        printf("Inserisci il tuo nuovo username. (Massimo %d caratteri consentiti, minimo %d, spazi non consentiti)\n",MAX_STR_LEN-1,MIN_STR_LEN-1);
        printf("PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n\n");


        string_checker_result = sys_input_string_checker(username_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
        
        switch(string_checker_result){
            case 1:
                printf("Registrazione annullata correttamente. \n");
                return NULL;
            case 2:
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                return NULL;
            default: 
                break;
        }


        //Controllo che l'utente non sia già presente nella lista utenti (DUPLICATI NON CONSENTITI)
        valid_username = user_exists(*users_list_head,username_io_string); 


        //Username disponibile, esce dal ciclo while (valid_username == 2: nessuna corrispondenza trovata nella lista, valid_username == 1: lista vuota, in entrambi casi l'username è disponibile)
        if(valid_username == 2 || valid_username == 1){
            printf("L'username e' disponibile.\n");
            break;
        }

        //Altrimenti notifica l'utente che l'username e già occupato e ricomincia il ciclo while.
        printf("L'username e' già occupato.\n");
        continue;
    }
    
        

    //INSERIMENTO NUOVA PASSWORD
    //clear_screen();
    
    //N.B: Nonostante la password NON POSSA CONTENERE SPAZI, disattivo in questo caso il controllo in quanto sarebbe ridondante,
    //Venendo già realizzato dalla funzione validate_password.
    check_space = false;


    
    while(1){
        printf("Inserisci la tua nuova password. (Massimo %d caratteri consentiti)\n\n", MAX_STR_LEN-1);
        printf("La password deve contenere:\n");
        printf(" - Almeno %d caratteri \n", MIN_STR_LEN-1 );
        printf(" - Almeno una maiuscola \n");
        printf(" - Almeno una minuscola \n");
        printf(" - Almeno un numero \n");
        printf(" - Almeno un simbolo (SPAZI ESCLUSI)\n");
        printf(" - PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE LA REGISTRAZIONE.\n\n");

        //Controllo che la password rispetti i requisiti del sistema definiti in validate_password di user.h
        string_checker_result = sys_input_string_checker(password_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("Registrazione annullata correttamente. \n");
                return NULL;
            case 2:
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                return NULL;
            default: 
                break;
        }
        
        //Secondo controllo sulla password secondo i criteri dettati da user.h
        string_checker_result = validate_password(password_io_string);
        
        if(string_checker_result == 1) {
            printf("Password non valida. Contiene caratteri non ammessi e/o spazi. Riprova \n");
            continue;
        }
        if(string_checker_result == 0) break; //altrimenti la password è validata, posso uscire dal ciclo while.
    }

    
    //Una volta validato sia l'username che la nuova password, procedo all'inserimento del nuovo utente nella lista utenti.

    insert_user_sorted(users_list_head, username_io_string, password_io_string, new_user_role);

    search_user(*users_list_head,username_io_string, &new_user);

    printf("Registrazione effettuata con successo!\n\n");

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
    
    
    printf("Benvenuto/a nell'area login.\n\n"); 

    //in caso di immissione con successo effettuo il break del ciclo while.
    while(1){

        printf("Inserisci il tuo username. \n");
        printf("PREMI INVIO PER INSERIRE UNA STRINGA VUOTA E ANNULLARE IL LOGIN.\n\n");
        
        string_checker_result = sys_input_string_checker(username_io_string, check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("Login annullato correttamente. \n\n");
                return NULL;
            case 2:
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n\n");
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

        printf("Inserisci la tua password. \n\n");

        string_checker_result = sys_input_string_checker(password_io_string, check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("Login annullato correttamente. \n\n");
                return NULL;
            case 2:
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n\n");
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
            printf("\nPassword invalida. Riprova.\n");
            continue;
        }
    }
    
    printf("Autenticazione effettuata con successo! \n\n");
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

        printf("Inserisci il tuo nuovo username. \n");
        printf("Se vuoi lasciare invariato il tuo username, inserisci una stringa vuota. \n\n");
        
        string_checker_result = sys_input_string_checker(username_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("L'username rimarra' invariato.\n\n");
                return 1;
            case 2:
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n\n");
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

        printf("Inserisci la tua nuova password. \n");
        printf("Se vuoi lasciare invariata la tua password, inserisci una stringa vuota. \n\n");

        string_checker_result = sys_input_string_checker(password_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
        
        switch(string_checker_result){
            case 1:
                printf("La password rimarra' invariata.\n");
                return 1;
            case 2:
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                return 2;
            default: 
                break;
        }

        //Validazione nuova password tramite la funzione validate_password
        
        valid_password = validate_password(password_io_string);

        if(valid_password == 1){
            printf("La password non e' valida, deve contenere i seguenti requisiti:\n");
            printf("- Lunga almeno 8 caratteri\n");
            printf("- Contiene almeno una maiuscola\n");
            printf("- Contiene almeno una minuscola\n");
            printf("- Contiene almeno un numero\n");
            printf("- Contiene almeno un simbolo (SPAZI ESCLUSI)\n");
            printf("Riprova.\n");
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

    printf("Benvenuto nell'area di modifica delle credenziali. \n");
    printf("Per poter procedere, e' necessario riconfermare l'autenticazione tramite password. \n");
    while(1){

        printf("Per annullare la modifica delle tue credenziali, immetti una stringa vuota. \n");
        printf("Inserisci la tua password per procedere con il cambiamento delle credenziali. \n\n");

        string_checker_result = sys_input_string_checker(password_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
        
        switch(string_checker_result){
            case 1:
                printf("Operazione di modifica credenziali annullata correttamente.\n");
                return 1;
            case 2:
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
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

        printf("Benvenuto nell'area di eliminazione del tuo account utente.\n");
        printf("QUESTA AZIONE SARA' DEFINITIVA. Si consiglia di procedere con cautela.\n");

        while(1){

            printf("Per procedere all'eliminazione, è' necessario inserire la propria password. ( UNA VOLTA VERIFICATA, NON PUOI TORNARE INDIETRO! )\n");
            printf("Se si vuole annullare l'eliminazione del proprio profilo, inserire una stringa vuota.\n");

            string_checker_result = sys_input_string_checker(password_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);
            
            switch(string_checker_result){
                case 1:
                    printf("Eliminazione del proprio profilo annullata correttamente.\n\n");
                    return 1;
                case 2:
                    printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n\n");
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
        printf("FATAL ERROR 1: USER POINTS TO NULL\n");
        return 1;
    }

    int result = print_collections(logged_user->collections_list_head);

    //La funzione print collections restituisce 1 se la lista è vuota -> gestisco questo caso:

    if(result == 1){
        printf("La tua lista collezioni e' vuota!\n");
        return 1;
    }

    //Altrimenti tutto va a buon fine, restituisco 0.
    return 0; 
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

    printf("Benvenuto/a nell'area di creazione di una nuova collezione!\n\n");

    while(1){

        printf("Per annullare l'inserimento della tua nuova collezione, inserisci una stringa vuota \n");
        printf("Inserisci il nome della tua nuova collezione. \n\n");

        string_checker_result = sys_input_string_checker(collection_name_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("Operazione di aggiunta collezione annullata con successo.\n");
                return 1;
            case 2: 
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                return 2;
            default: 
                break;
            }

            //Verifico che la collezione esiste nella lista, in tal caso ricomincia il ciclo while
            if(collection_exists(logged_user->collections_list_head,collection_name_io_string) == 0){
                printf("Hai gia' una collezione con questo nome, non sono consentiti duplicati. Riprova.\n");
                continue;
            }

            break;
        }

    //Passo all'inserimento della tipologia della collezione

    printf("\n");
    printf("\n");

    while(1){

        printf("Per annullare l'inserimento della tua nuova collezione, inserisci una stringa vuota \n");
        printf("Inserisci la tipologia della nuova collezione. \n\n");

        string_checker_result = sys_input_string_checker(collection_type_io_string,check_space,MIN_STR_LEN,MAX_STR_LEN);

        switch(string_checker_result){
            case 1:
                printf("Operazione di aggiunta collezione annullata con successo. \n");
                return 1;
            case 2: 
                printf("FATAL ERROR 2: Errore lettura buffer di input! Contattare un amministratore\n");
                return 2;
            default: 
                break;
            }

            break;
        }

        int result = insert_collection(&(logged_user->collections_list_head),collection_name_io_string, collection_type_io_string);
        if (result == 1){
            printf("CRITICAL ERROR 4: errore di allocazione di memoria! Contattare un amministratore.\n");
            return 4;
        }

        //Tutto è andato a buon fine
        printf("La tua nuova collezione: (%s) e' stata aggiunta correttamente.\n",collection_name_io_string);
        return 0;
    }
    






