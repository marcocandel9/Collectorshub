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
    

    do{
        input_validity = scanf("%d",&scelta);
        if(input_validity != 1){
            printf("Input invalido, inserisci un intero da 1 a 3 per selezionare l'opzione desiderata.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
        } else if (scelta > 3 || scelta < 1){
            printf("Opzione non valida, seleziona una delle 3 opzioni.\n");
            while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
            input_validity = 0;
        }
    } while (input_validity != 1);

    while((ch = getchar()) != '\n' && ch != EOF); //Buffer reset
    return scelta;
}




