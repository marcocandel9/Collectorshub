#include "system_admin.h"


/*
Stampa l'intera lista degli utenti, associati al proprio ruolo. 

Parametri: 
    - logged_user: ruolo dell'utente loggato, chiamante, viene effettuato un controllo sui privilegi dell'utente che vuole utilizzare questa funzione
    - users_list_head: puntatore alla testa della lista degli utenti

Restituisce: 
    - 1 in caso di errore critico: utente non admin (non dovrebbe accadere)
    - 2 lista risulta vuota quando non dovrebbe (non dovrebbe accadere)
    - 0 in caso di successo e stampa la lista utenti
*/
int sys_admin_print_users(user logged_user, users users_list_head) {

    user_role logged_user_role = USER; 
    get_user_role_enum(logged_user, &(logged_user_role));
    char username[MAX_STR_LEN];
    get_username(logged_user,username);

    
    printf(ANSI_COLOR_BLUE ANSI_BOLD);
    division_break_lines("ADMIN: LISTA UTENTI", 60);
    printf(ANSI_COLOR_RESET BOLD_OFF);

    // Controllo su logged_user
    if (logged_user == NULL) {
        printf(ANSI_COLOR_RED "\nErrore critico: utente loggato non valido (NULL).\n" ANSI_COLOR_RESET);
        return 1;
    }

    // Controllo sul privilegio

    int is_admin = compare_user_privilege(logged_user_role, ADMIN);
    
    if (is_admin != 2) {
        printf("\n" ANSI_COLOR_RED);
        printf("Errore critico, l'utente loggato non e' admin! Contattare un amministratore.\n");
        printf("\n" ANSI_COLOR_RESET);
        return 1;
    }

    // Controllo su lista utenti
    if (users_list_head == NULL) {
        printf(ANSI_COLOR_RED "\nErrore critico: lista utenti non inizializzata.\n" ANSI_COLOR_RESET);
        return 2;
    }

    // Stampa lista
    printf("\nAdmin %s, ecco di seguito la lista degli utenti e i loro ruoli.\n", username);

    printf(ANSI_COLOR_CYAN);
    int print_result = print_users(users_list_head);
    printf(ANSI_COLOR_RESET);

    if (print_result == 1) {
        printf("\n" ANSI_COLOR_RED);
        printf("Errore critico, la lista utenti e' vuota quando non dovrebbe!\n");
        printf("\n" ANSI_COLOR_RESET);
        return 2;
    }

    return 0;
}





/*
Implementa l'I/O per l'eliminazione di un utente da parte di un amministratore. Un amministratore non può eliminare altri amministratori. 
Verrà stampata all'utente admin la lista degli utenti, lui potrà inserire poi da terminale l'username dell'utente che desidera eliminare.

Parametri: 
    - logged_user: ruolo dell'utente loggato, chiamante, viene effettuato un controllo sui privilegi dell'utente che vuole utilizzare questa funzione
    - *users_list_head: puntatore alla testa della lista degli utenti passata come riferimento

Restituisce: 
    - 1 in caso di errore critico: utente non admin (non dovrebbe accadere)
    - 2 lista risulta vuota quando non dovrebbe (non dovrebbe accadere)
    - 3 In caso di annullamento dell'operazione da parte dell'utente
    - 4 In caso di errore di lettura del buffer di input stdin
    - 0 in caso di eliminazione dell'utente inserito in input avvenuta con successo
*/
int sys_admin_delete_user(user logged_user, users* users_list_head){

    user_role logged_user_role = USER;
    get_user_role_enum(logged_user,&(logged_user_role));

    int string_checker_result;
    char objuser_io_string[MAX_STR_LEN];

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    division_break_lines("ADMIN: AREA ELIMINAZIONE UTENTE", 60);
    printf(ANSI_COLOR_RESET BOLD_OFF);

    //Stampo la lista utenti
    int print_result = sys_admin_print_users(logged_user, *users_list_head);
    if(print_result != 0) return print_result; //Se dovessero esserci degli errori imprevisti, sono gestiti dalla funzione print
    //altrimenti stampa e print_result==0

    while(1){
        printf("\nDigita l'username dell'utente che desideri eliminare definitivamente dalla memoria. Non ti e' consentito eliminare altri amministratori.\n");
        printf("Puoi annullare l'operazione inserendo una stringa vuota.\n");
        printf(ANSI_COLOR_MAGENTA"Nota bene, questa azione e' definiva!\n"ANSI_COLOR_RESET);

        string_checker_result = sys_input_string_checker(objuser_io_string, true, MIN_STR_LEN,MAX_STR_LEN);

        switch (string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN);
                printf("Operazione annullata correttamente. Verrai reindirizzato al menu admin...\n");
                printf("\n" ANSI_COLOR_RESET);
                return 3;
            case 2: 
                printf("\n" ANSI_COLOR_RED);
                printf("Errore critico! Errore di lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 4;
            default:
                int exists = user_exists(*users_list_head, objuser_io_string);
                if (exists != 0){
                    printf(ANSI_COLOR_MAGENTA);
                    printf("L'utente non e' stato trovato all'interno della lista utenti. Riprova.\n" ANSI_COLOR_RESET);
                    continue;
                }
                //altrimenti è stato trovato, esco dallo switch case
                break;
        }

        //controllo che l'utente che è stato trovato non sia un admin.
        user found_user = NULL;
        int found = search_user(*users_list_head, objuser_io_string, &(found_user));
        if(found!= 0) return 2; //ERRORE CRITICO

        //Prelevo il ruolo e l'username dell'utente trovato per il successivo utilizzo
        user_role found_user_role = USER;
        char found_username[MAX_STR_LEN];
        get_username(found_user,found_username);
        get_user_role_enum(logged_user,&(found_user_role));


        int compare_privilege = compare_user_privilege(logged_user_role, found_user_role);


        switch(compare_privilege){
            case 1: 
                printf("\n" ANSI_COLOR_RED);
                printf("Impossibile procede all'eliminazione. Il ruolo dell'utente e' gerarchicamente superiore al tuo. Riprova. \n");
                printf("\n" ANSI_COLOR_RESET);
                continue; // Riparte il ciclo while
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("Impossibile eliminare l'utente %s, e' un amministratore! Inserisci un nuovo utente o annulla l'operazione.\n", found_username);
                printf("\n" ANSI_COLOR_RESET);
                continue;
            default:
                printf("\n");
                break; //procedo con l'eliminazione, esco dallo switch case
        }


        printf(ANSI_COLOR_MAGENTA"Stai per eliminare definitivamente l'utente %s, e tutti i dati a lui associati. Sei sicuro di voler proseguire?\n", found_username );
        printf("Inserisci 0 per confermare, 1 per annullare l'operazione.\n");
        printf(ANSI_COLOR_RESET);
        int confirm = ask_confirmation();

        switch(confirm){
            case 1:
                printf("\n");
                printf(ANSI_COLOR_GREEN"Hai annullato correttamente l'operazione.\n"ANSI_COLOR_RESET);
                return 3;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("Errore critico! Errore di lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);           
                return 4;     
            default: 
                printf("Eliminazione in corso...\n");
                break;
        }
        break;
    }

    int final_result = remove_user(users_list_head, objuser_io_string);

    if (final_result == 0){
        printf("\n"ANSI_COLOR_GREEN);
        printf("Hai eliminato definitivamente l'utente %s.\n" ,objuser_io_string);
        printf(ANSI_COLOR_RESET);
        return 0; //success, restituisco 0.
    }

    return 2; //errore critico inaspettato
}



/*
Implementa l'I/O per la promozione di un utente da parte di un amministratore. Un amministratore non può promuovere ovviaemnte altri amministratori. 
Verrà stampata all'utente admin la lista degli utenti, lui potrà inserire poi da terminale l'username dell'utente che desidera promuovere 

Parametri: 
    - logged_user: ruolo dell'utente loggato, chiamante, viene effettuato un controllo sui privilegi dell'utente che vuole utilizzare questa funzione
    - *users_list_head: puntatore alla testa della lista degli utenti passata come riferimento

Restituisce: 
    - 1 in caso di errore critico: utente non admin (non dovrebbe accadere)
    - 2 lista risulta vuota quando non dovrebbe (non dovrebbe accadere)
    - 3 In caso di annullamento dell'operazione da parte dell'utente
    - 4 In caso di errore di lettura del buffer di input stdin
    - 0 in caso di promozione dell'utente inserito in input avvenuta con successo

*/
int sys_admin_promote_base_user(user logged_user, users* users_list_head){
    
    user_role logged_user_role;
    char username[MAX_STR_LEN];
    get_user_role_enum(logged_user, &(logged_user_role));
    get_username(logged_user,username);
    

    int string_checker_result;
    char objuser_io_string[MAX_STR_LEN];

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    division_break_lines("ADMIN: AREA PROMOZIONE UTENTE", 60);
    printf(ANSI_COLOR_RESET BOLD_OFF);

    //Stampo la lista utenti
    int print_result = sys_admin_print_users(logged_user, *users_list_head);
    if(print_result != 0) return print_result; //Se dovessero esserci degli errori imprevisti, sono gestiti dalla funzione print
    //altrimenti stampa e print_result==0

    while(1){
        printf("\nDigita l'username dell'utente che desideri promuovere ad admin.\n");
        printf("Puoi annullare l'operazione inserendo una stringa vuota.\n");

        string_checker_result = sys_input_string_checker(objuser_io_string, true, MIN_STR_LEN,MAX_STR_LEN);

        switch (string_checker_result){
            case 1:
                printf("\n" ANSI_COLOR_GREEN);
                printf("Operazione annullata correttamente. Verrai reindirizzato al menu admin...\n");
                printf("\n" ANSI_COLOR_RESET);
                return 3;
            case 2: 
                printf("\n" ANSI_COLOR_RED);
                printf("Errore critico! Errore di lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);
                return 4;
            default:
                int exists = user_exists(*users_list_head, objuser_io_string);
                if (exists != 0){
                    printf(ANSI_COLOR_MAGENTA);
                    printf("L'utente non e' stato trovato all'interno della lista utenti. Riprova.\n" ANSI_COLOR_RESET);
                    continue;
                }
                //altrimenti è stato trovato, esco dallo switch case
                break;
        }

        //controllo che l'utente che è stato trovato non sia un admin.
        user found_user = NULL;
        int found = search_user(*users_list_head, objuser_io_string, &(found_user));
        if(found!= 0) return 2; //errore critico

        //prelevo i dati dell'utente trovato per utilizzo successivo
        char found_username[MAX_STR_LEN];
        user_role found_user_role = USER;
        get_username(found_user,found_username);
        get_user_role_enum(found_user,&(found_user_role));

        int compare_privilege = compare_user_privilege(logged_user_role, found_user_role);

        switch(compare_privilege){
            case 1: 
                printf("\n" ANSI_COLOR_RED);
                printf("Impossibile procede all'eliminazione. Il ruolo dell'utente e' gerarchicamente superiore al tuo. Riprova. \n");
                printf("\n" ANSI_COLOR_RESET);
                continue; // Riparte il ciclo while
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("Impossibile promuovere l'utente %s, e' gia' un amministratore! Inserisci un nuovo utente o annulla l'operazione.\n", found_username);
                printf("\n" ANSI_COLOR_RESET);
                continue;
            default:
                printf("\n");
                break; //procedo con la promozione, esco dallo switch case
        }


        printf(ANSI_COLOR_MAGENTA"Stai per promuovere l'utente %s. Sei sicuro di voler proseguire?\n", found_username );
        printf("Inserisci 0 per confermare, 1 per annullare l'operazione.\n");
        printf(ANSI_COLOR_RESET);
        int confirm = ask_confirmation();

        switch(confirm){
            case 1:
                printf("\n");
                printf(ANSI_COLOR_GREEN"Hai annullato correttamente l'operazione.\n"ANSI_COLOR_RESET);
                return 3;
            case 2:
                printf("\n" ANSI_COLOR_RED);
                printf("Errore critico! Errore di lettura del buffer di input. Contattare un amministratore.\n");
                printf("\n" ANSI_COLOR_RESET);           
                return 4;     
            default: 
                printf("Promozione in corso...\n");
                break;
        }
        break;
    }

    int final_result = search_and_promote_user(users_list_head, objuser_io_string, ADMIN);

    if (final_result == 0){
        printf("\n"ANSI_COLOR_GREEN);
        printf("Hai promosso ad ADMIN l'utente %s.\n" ,objuser_io_string);
        printf(ANSI_COLOR_RESET);
        return 0; //success, restituisco 0.
    }

    return 2; //errore critico inaspettato
}