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
Implementa l'I/O del menù di login

Restituisce:
- 1 Se l'utente desidera effettuare il login
- 2 Se l'utente desidera effettuare una registrazione
- 3 Se l'utente desidera terminare il programma
*/
int login_menu(){

    clear_screen();

    int scelta = 0;
    char ch; //Variabile per resettare il buffer stdin
    int input_validity; //variabile per verificare la validità dell'input inserito

    printf(ANSI_COLOR_RED ANSI_BOLD);
    collectors_hub_header();
    printf(ANSI_COLOR_RESET BOLD_OFF);
    printf("                                                                            Welcome!\n\n" BOLD_OFF);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n");
    printf("                                                                            1) Login\n");
    printf("                                                                            2) Registrazione\n");
    printf("                                                                            3) Esci\n");
    printf("\n");
    printf("\n");
    printf("\n");
    

    //Ciclo do/while che richiede un input dall'utente che sia un intero corrispondente ad una delle opzioni ( 1 - 3 ).
    //Se l'utente inserisce dei caratteri, il ciclo invita a inserire un intero.
    //Se l'utente inserisce un intero non presente tra le opzioni, il ciclo invita a inserire un'opzione valida
    do {
        printf("\n");
        input_validity = scanf("%d",&scelta);
        
        if(input_validity != 1){ //input non valido, non è stato inserito un numero da 1 a 3
            printf("Input invalido, inserisci un intero da 1 a 3 per selezionare l'opzione desiderata.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta < 1 || scelta > 3){
            printf("Opzione non valida, seleziona una delle 3 opzioni.\n");
            while((ch= getchar()) != '\n' && ch != EOF); //buffer reset
            input_validity = 0; //Ripete il ciclo 
        }

        } while (input_validity != 1);
        
    while((ch= getchar()) != '\n' && ch != EOF); //buffer reset
    return scelta;
}





/*
Implementa l'I/O del menù utente

Restituisce:
- 1 Se l'utente desidera accedere al menù collezioni
- 2 Se l'utente desidera modificare le sue credenziali
- 3 Se l'utente desidera cancellarsi dal sistema in via definitiva
- 4 per effettuare il log-out

*/
int user_menu(){

    clear_screen();

    int scelta = 0;
    char ch; //Variabile per resettare il buffer stdin
    int input_validity; //variabile per verificare la validità dell'input inserito

    printf(ANSI_COLOR_RED ANSI_BOLD);
    user_menu_header();
    printf(ANSI_COLOR_RESET);
    printf("                                                                            Benvenuto/a nella tua area utente!\n\n" BOLD_OFF);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n");
    printf("                                                                            1) Accedi al menu' collezioni\n");
    printf("                                                                            2) Modifica le tue credenziali\n");
    printf("                                                                            3) Cancella il tuo utente (DEFINITIVO!)\n");
    printf("                                                                            4) Esci (log-out) \n");
    printf("\n");
    printf("\n");
    printf("\n");
    

    do{
        input_validity = scanf("%d",&scelta);
        if(input_validity != 1){
            printf("Input invalido, inserisci un intero da 1 a 4 per selezionare l'opzione desiderata.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta > 4 || scelta < 1){
            printf("Opzione non valida, seleziona una delle 4 opzioni.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
            input_validity = 0;
        }
    } while (input_validity != 1);

    while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
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

    int scelta = 0;
    char ch; // Variabile per resettare il buffer stdin
    int input_validity; //Variabile per verificare la validità dell'input inserito

    printf(ANSI_COLOR_RED ANSI_BOLD);
    collection_menu_header();
    printf(ANSI_COLOR_RESET);
    printf("                                                                            Benvenuto/a nel menu' collezione!\n\n" BOLD_OFF);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n");
    printf("                                                                            1) Visualizza le tue collezioni\n");
    printf("                                                                            2) Accedi ad una collezione\n");
    printf("                                                                            3) Modifica il nome/tipologia di una collezione\n");
    printf("                                                                            4) Cancella definitivamente una collezione\n");
    printf("                                                                            5) Cancella definitivamente tutte le collezioni\n");
    printf("                                                                            6) Torna al menu' utente\n");
    printf("\n");
    printf("\n");
    printf("\n");
    do{
        input_validity = scanf("%d",&scelta);
        if(input_validity != 1){
            printf("Input invalido, inserisci un intero da 1 a 6 per selezionare l'opzione desiderata.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta > 6 || scelta < 1){
            printf("Opzione non valida, seleziona una delle 6 opzioni.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
            input_validity = 0;
        }
    } while (input_validity != 1);

    while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
    return scelta;
}





/*
Implementa l'I/O del menù prodotti

Restituisce:
- 1 Se l'utente desidera visualizzare tutti i prodotti della collezione
- 2 Se l'utente desidera cercare e modificare un prodotto
- 3 Se l'utente desidera cancellare definitivamente un prodotto
- 4 Se l'utente desidera cancellare definitivamente tutti i prodotti della collezione
- 5 Se l'utente desidera tornare al menù collezioni
*/
int products_menu(){

    clear_screen();

    int scelta = 0;
    char ch; // Variabile per resettare il buffer stdin
    int input_validity; //Variabile per verificare la validità dell'input inserito

    printf(ANSI_COLOR_RED ANSI_BOLD);
    products_menu_header();
    printf(ANSI_COLOR_RESET);
    printf("                                                                            Benvenuto/a nel menu' prodotti!\n\n" BOLD_OFF);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n");
    printf("                                                                            1) Visualizza tutti i prodotti della collezione\n");
    printf("                                                                            2) Cerca e modifica un prodotto\n");
    printf("                                                                            3) Cerca e cancella definitivamente un prodotto\n");
    printf("                                                                            4) Cancella definitivamente tutti i prodotti\n");
    printf("                                                                            5) Torna al menu' collezioni \n");
    printf("\n");
    printf("\n");
    printf("\n");
    do{
        input_validity = scanf("%d",&scelta);
        if(input_validity != 1){
            printf("Input invalido, inserisci un intero da 1 a 5 per selezionare l'opzione desiderata.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta > 5 || scelta < 1){
            printf("Opzione non valida, seleziona una delle 5 opzioni.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
            input_validity = 0;
        }
    } while (input_validity != 1);

    while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
    return scelta;
}




/*
Implementa l'I/O del menù Admin

Restituisce:
- 1 Se l'admin desidera visualizzare tutti gli utenti della lista utenti
- 2 Se l'admin desidera cancellare definitivamente un utente
- 3 Se l'admin desidera promuovere un utente base ad Admin
- 4 Se l'admin desidera accedere al menù collezioni
- 5 Se l'admin desidera effettuare il log - out (torna al menù login)
*/
int admin_menu(){

    clear_screen();

    int scelta = 0;
    char ch; // Variabile per resettare il buffer stdin
    int input_validity; //Variabile per verificare la validità dell'input inserito

    printf(ANSI_COLOR_RED ANSI_BOLD);
    admin_menu_header();
    printf(ANSI_COLOR_RESET);
    printf("                                                                            Benvenuto/a nel menu' ADMIN!\n\n" BOLD_OFF);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n");
    printf("                                                                            1) Visualizza tutti gli utenti\n");
    printf("                                                                            2) Cancella definitivamente un utente\n");
    printf("                                                                            3) Promuovi ad Admin un utente\n");
    printf("                                                                            4) Accedi al menu' collezioni\n");
    printf("                                                                            5) Esci (log-out)\n");
    printf("\n");
    printf("\n");
    printf("\n");
    do{
        input_validity = scanf("%d",&scelta);
        if(input_validity != 1){
            printf("Input invalido, inserisci un intero da 1 a 5 per selezionare l'opzione desiderata.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta > 5 || scelta < 1){
            printf("Opzione non valida, seleziona una delle 5 opzioni.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
            input_validity = 0;
        }
    } while (input_validity != 1);

    while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
    return scelta;
}




/*
Implementa l'I/O del menù Superuser

Restituisce:
- 1 Se il superuser desidera visualizzare tutti gli utenti della lista utenti
- 2 Se il superuser desidera cancellare definitivamente un utente
- 3 Se il superuser desidera mmodificare il ruolo di un utente
- 4 Se il superuser desidera accedere al menu'globale di un utente, per poter visualizzare/modificare/cancellare i suoi dati
- 5 Se il superuser desidera effettuare il log - out (torna al menù login)
*/
int superuser_menu(){

    clear_screen();

    int scelta = 0;
    char ch; // Variabile per resettare il buffer stdin
    int input_validity; //Variabile per verificare la validità dell'input inserito

    printf(ANSI_COLOR_RED ANSI_BOLD);
    superuser_menu_header();
    printf(ANSI_COLOR_RESET);
    printf("                                                                            Benvenuto/a nel menu' SUPERUSER!\n\n" BOLD_OFF);
    printf("                                                                            Seleziona una tra le seguenti opzioni:\n");
    printf("                                                                            1) Visualizza tutti gli utenti\n");
    printf("                                                                            2) Cancella definitivamente un utente\n");
    printf("                                                                            3) Modifica ruolo di un utente\n");
    printf("                                                                            4) Seleziona un utente ed accedi al suo menu' globale \n");
    printf("                                                                            5) Esci (log-out)\n");
    printf("\n");
    printf("\n");
    printf("\n");
    do{
        input_validity = scanf("%d",&scelta);
        if(input_validity != 1){
            printf("Input invalido, inserisci un intero da 1 a 5 per selezionare l'opzione desiderata.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta > 5 || scelta < 1){
            printf("Opzione non valida, seleziona una delle 5 opzioni.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
            input_validity = 0;
        }
    } while (input_validity != 1);

    while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
    return scelta;
}





/*
Implementa l'I/O del SOTTO menù collezioni di un utente (RISERVATO ALLA GESTIONE DI UN SUPERUSER)

Restituisce:
- 1 Se il superuser desidera visualizzare tutte le collezioni di un utente
- 2 Se il superuser desidera modificare una collezione di un utente
- 3 Se il superuser desidera eliminare una collezione dell'utente
- 4 Se il superuser desidera eliminare tutte le collezioni dell'utente
- 5 Se il superuser desidera accedere ad una collezione dell'utente
- 6 Se desidera ritornare al menù superuser
*/
int superuser_collections_submenu(){

    clear_screen();

    int scelta = 0;
    char ch; // Variabile per resettare il buffer stdin
    int input_validity; //Variabile per verificare la validità dell'input inserito

    printf(ANSI_COLOR_RED ANSI_BOLD);
    superuser_menu_header();
    printf(ANSI_COLOR_RESET);
    printf("                                                                            Benvenuto/a nel menu' SU di gestione dei prodotti della collezione utente!\n\n" BOLD_OFF);
    printf("                                                                            Cosa desideri fare con questo utente:\n");
    printf("                                                                            1) Visualizza tutte le sue collezioni\n");
    printf("                                                                            2) Modifica una collezione\n");
    printf("                                                                            3) Elimina definitivamente una collezione\n");
    printf("                                                                            4) Elimina definitivamente tutte le sue collezioni \n");
    printf("                                                                            5) Accedi ad una sua collezione\n");
    printf("                                                                            6) Ritorna al menu' superuser\n");
    printf("\n");
    printf("\n");
    printf("\n");
    do{
        input_validity = scanf("%d",&scelta);
        if(input_validity != 1){
            printf("Input invalido, inserisci un intero da 1 a 6 per selezionare l'opzione desiderata.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta > 6 || scelta < 1){
            printf("Opzione non valida, seleziona una delle 6 opzioni.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
            input_validity = 0;
        }
    } while (input_validity != 1);

    while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
    return scelta;
}





/*
Implementa l'I/O del SOTTO menù prodotti di un utente (RISERVATO ALLA GESTIONE DI UN SUPERUSER)

Restituisce:
- 1 Se il superuser desidera visualizzare tutti i prodotti della collezione dell'utente
- 2 Se il superuser desidera modificare un prodotto dell'utente
- 3 Se il superuser desidera eliminare un prodotto dell'utente
- 4 Se il superuser desidera eliminare tutti i prodotto della collezione dell'utente
- 5 Se il superuser desidera accedere ritornare al sotto menù SU collezioni
*/
int superuser_products_submenu(){

    clear_screen();

    int scelta = 0;
    char ch; // Variabile per resettare il buffer stdin
    int input_validity; //Variabile per verificare la validità dell'input inserito

    printf(ANSI_COLOR_RED ANSI_BOLD);
    superuser_menu_header();
    printf(ANSI_COLOR_RESET);
    printf("                                                                            Benvenuto/a nel menu' SU di gestione dei prodotti della collezione utente!\n\n" BOLD_OFF);
    printf("                                                                            Cosa desideri fare con questo utente:\n");
    printf("                                                                            1) Visualizza tutti i prodotti della collezione dell'utente\n");
    printf("                                                                            2) Modifica un prodotto\n");
    printf("                                                                            3) Elimina definitivamente un prodotto\n");
    printf("                                                                            4) Elimina definitivamente tutti i prodotti \n");
    printf("                                                                            5) Ritorna al sotto-menu' collezioni\n");
    printf("\n");
    printf("\n");
    printf("\n");
    do{
        input_validity = scanf("%d",&scelta);
        if(input_validity != 1){
            printf("Input invalido, inserisci un intero da 1 a 5 per selezionare l'opzione desiderata.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta > 5 || scelta < 1){
            printf("Opzione non valida, seleziona una delle 5 opzioni.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
            input_validity = 0;
        }
    } while (input_validity != 1);

    while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
    return scelta;
}