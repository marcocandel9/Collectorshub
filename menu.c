#include "menu.h"

//Parametro che decide di quante linee il terminale viene ripulito nella funzione clear_screen




// Pulisce il terminale stampando un numero di newlines pari a SCREEN_LINES. Permette di compilare il programma sia su sistemi UNIX like (Linux) che Windows, evitando di utilizzare system("clear").
void clear_screen(){
    int i;
    for ( i = 0; i < SCREEN_LINES; i++ ){
    printf("\n");
    }
    return;
}



/*
Prende in ingresso due valori minimi min e max, e implementa il controllo dell'input inserito dall'utente. Se l'utente inserisce un valore non compreso fra min e max o un valore non corrispondente ad un intero, richiede nuovamente l'input.abort

Restituisce l'input corretto inserito dall'utente
*/
int get_valid_input(int min, int max){


    int scelta, input_validity;
    char ch;

    do {
        printf("\n");
        input_validity = scanf("%d",&scelta);
        
        if(input_validity != 1){ //input non valido, non è stato inserito un numero da int min a int max
            printf("Input invalido, inserisci un intero da %d a %d per selezionare l'opzione desiderata.\n", min, max);
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta < min || scelta > max){
            printf("Opzione non valida, seleziona una delle %d opzioni.\n", max);
            while((ch= getchar()) != '\n' && ch != EOF); //buffer reset
            input_validity = 0; //Ripete il ciclo 
        }

        } while (input_validity != 1);
    
    while((ch= getchar()) != '\n' && ch != EOF); //buffer reset
    return scelta;
}





/*
Implementa l'I/O del menù di login

Restituisce:
- 1 Se l'utente desidera effettuare il login
- 2 Se l'utente desidera effettuare una registrazione
- 3 Se l'utente desidera terminare il programma
*/
int login_menu(){

    clear_screen();

    int scelta = 0;
    int min = 1, max = 3;

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    collectors_hub_header();
    printf("                                                                            Welcome in Collectors Hub!\n" );
    printf(ANSI_COLOR_RED);
    printf("\n");
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n"BOLD_OFF);
    printf(ANSI_COLOR_RESET);
    printf("                                                                            1) Login\n");
    printf("                                                                            2) Registrazione\n");
    printf("                                                                            3) Esci\n");
    printf("\n");
    printf("\n");
    printf("\n");
    
    scelta = get_valid_input(min, max);
    return scelta;
}





/*
Implementa l'I/O del menù utente

Restituisce:
- 1 Se l'utente desidera accedere al menù collezioni
- 2 Se l'utente desidera modificare le sue credenziali
- 3 Se l'utente desidera cancellarsi dal sistema in via definitiva
- 4 per accedere al menù admin
- 5 Per effettuare il logout

*/
int user_menu(){

    clear_screen();

    int scelta = 0, min = 1, max = 5;

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    user_menu_header();
    printf("                                                                            Benvenuto/a nella tua area utente!\n\n"  ANSI_COLOR_RESET);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n" BOLD_OFF);
    printf("                                                                            1) Accedi al menu' collezioni\n");
    printf("                                                                            2) Modifica le tue credenziali\n");
    printf("                                                                            3) Cancella il tuo utente (DEFINITIVO!)\n");
    printf("                                                                            4) Accedi al menu' ADMIN\n");
    printf("                                                                            5) Esci (log-out) \n");
    printf("\n");
    printf("\n");
    printf("\n");
    

    scelta = get_valid_input(min,max);
    return scelta;
}





/*
Implementa l'I/O del menù collezione

Restituisce:
- 1 Se l'utente desidera visualizzare le proprie collezioni
- 2 Se l'utente desidera accedere ad una collezione
- 3 Se l'utente desidera  Modificare il nome/tipologia di una collezione
- 4 Se l'utente desidera cancellare definitivamente una collezione
- 5 Se l'utente desidera cancellare definitivamente tutte le sue collezioni
- 6 Per tornare al menù utente

*/
int collection_menu(){

    clear_screen();

    int scelta = 0, min = 1, max = 7;

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    collection_menu_header();
    printf("                                                                            Benvenuto/a nel menu' collezione!\n\n" ANSI_COLOR_RESET BOLD_OFF);
    printf(ANSI_BOLD ANSI_COLOR_RED);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n" ANSI_COLOR_RESET BOLD_OFF);
    printf("                                                                            1) Visualizza le tue collezioni\n");
    printf("                                                                            2) Accedi ad una collezione\n");
    printf("                                                                            3) Crea una nuova collezione\n");
    printf("                                                                            4) Modifica il nome/tipologia di una collezione\n");
    printf("                                                                            5) Cancella definitivamente una collezione\n");
    printf("                                                                            6) Cancella definitivamente tutte le collezioni\n");
    printf("                                                                            7) Torna al menu' utente\n");
    printf("\n");
    printf("\n");
    printf("\n");
 

    scelta = get_valid_input(min,max);
    return scelta;
}





/*
Implementa l'I/O del menù prodotti

    Restituisce:
        1 Se l'utente desidera visualizzare tutti i prodotti della collezione
        2 Se l'utente desidera aggiungere un nuovo prodotto alla sua collezione
        3 Se l'utente desidera cercare e modificare un prodotto
        4 Se l'utente desidera cancellare definitivamente un prodotto
        5 Se l'utente desidera cancellare definitivamente tutti i prodotti della collezione
        6 Se l'utente desidera tornare al menù collezioni
*/
int products_menu(){

    clear_screen();

    int scelta = 0, min = 1, max = 6;

    printf(ANSI_COLOR_CYAN ANSI_BOLD);
    products_menu_header();
    printf("                                                                            Benvenuto/a nel menu' prodotti!\n\n" BOLD_OFF);
    printf(ANSI_COLOR_RED ANSI_BOLD);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n" ANSI_COLOR_RESET BOLD_OFF);
    printf("                                                                            1) Visualizza tutti i prodotti della collezione\n");
    printf("                                                                            2) Aggiungi un nuovo prodotto alla collezione\n");
    printf("                                                                            3) Cerca e modifica un prodotto\n");
    printf("                                                                            4) Cerca e cancella definitivamente un prodotto\n");
    printf("                                                                            5) Cancella definitivamente tutti i prodotti\n");
    printf("                                                                            6) Torna al menu' collezioni \n");
    printf("\n");
    printf("\n");
    printf("\n");

    scelta = get_valid_input(min,max);
    return scelta;
}




/*
Implementa l'I/O del menù Admin

Restituisce:
- 1 Se l'admin desidera visualizzare tutti gli utenti della lista utenti
- 2 Se l'admin desidera cancellare definitivamente un utente (solo utenti base possono essere eliminati)
- 3 Se l'admin desidera promuovere un utente base ad Admin
- 4 Se l'admin desidera accedere al menù collezioni
- 5 Se l'admin desidera effettuare il log - out (torna al menù login)
*/
int admin_menu(){

    clear_screen();

    int scelta = 0, min = 1, max = 5;

    printf(ANSI_COLOR_YELLOW ANSI_BOLD);
    admin_menu_header();
    printf(ANSI_COLOR_YELLOW ANSI_BOLD);
    printf("                                                                            Benvenuto/a nel menu' ADMIN!\n\n" );
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n"BOLD_OFF);
    printf("                                                                            1) Visualizza tutti gli utenti\n");
    printf("                                                                            2) Cancella definitivamente un utente\n");
    printf("                                                                            3) Promuovi ad Admin un utente\n");
    printf("                                                                            4) Accedi al menu' collezioni\n");
    printf("                                                                            5) Esci (log-out)\n");
    printf("\n");
    printf("\n");
    printf("\n");


    scelta = get_valid_input(min,max);
    return scelta;
}




/*
Implementa l'I/O del menù Superuser   (NON UTILIZZATO NELLA VERSIONE 1.0)

Restituisce:
- 1 Se il superuser desidera visualizzare tutti gli utenti della lista utenti
- 2 Se il superuser desidera cancellare definitivamente un utente
- 3 Se il superuser desidera mmodificare il ruolo di un utente
- 4 Se il superuser desidera accedere al menu' collezioni di un utente, per poter visualizzare/modificare/cancellare le sue collezioni
- 5 Se il superuser desidera effettuare il log - out (torna al menù login)
*/
int superuser_menu(){

    clear_screen();

    int scelta = 0, min = 1, max = 5;

    printf(ANSI_COLOR_RED ANSI_BOLD);
    superuser_menu_header();
    printf(ANSI_COLOR_RESET);
    printf("                                                                            Benvenuto/a nel menu' SUPERUSER!\n\n" BOLD_OFF);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n");
    printf("                                                                            1) Visualizza tutti gli utenti\n");
    printf("                                                                            2) Cancella definitivamente un utente\n");
    printf("                                                                            3) Modifica ruolo di un utente\n");
    printf("                                                                            4) Seleziona un utente ed accedi al suo menu' collezioni \n");
    printf("                                                                            5) Esci (log-out)\n");
    printf("\n");
    printf("\n");
    printf("\n");

    scelta = get_valid_input(min,max);
    return scelta;
}




