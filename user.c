#include "user.h"




/* 
Crea un nuovo utente allocandone la memoria dinamicamente e associandone un proprio username e password, quest'ultima validata 
dalla funzione validate_password.abort

Restituisce:
- 1 Se l'utente è già esistente (puntatore a struct user diverso da null quindi già inizializzato)
- 2 In caso di errori di allocazione

*/
int create_user(user* new_user, char new_username[MAX_STR_LEN], char new_password[MAX_STR_LEN]){

    if((*new_user) != NULL) return 1; //Utente già esistente!

    user new_user = (user)malloc(sizeof(struct user*));
    if (new_user == NULL) return 2; //Allocation error

    int is_valid = validate_password(new_password);

    /////DA COMPLETARE/////
}





/*
Verifica che la password abbia le seguenti caratteristiche:
- Lunga almeno 8 caratteri
- Contiene almeno una maiuscola
- Contiene almeno una minuscola
- Contiene almeno un numero
- Contiene almeno un simbolo (SPAZI ESCLUSI), ammessi i seguenti:
! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _

Utilizza la libreria <ctype.h> per il controllo dei singoli caratteri

Restituisce:
- 1 Se la password non è valida
- 0 Se la password è validata con successo
*/
int validate_password(char password[MAX_STR_LEN]){

    //strlen controlla la dimensione LOGICA della stringa, non quella fisica, quindi conta il numero di caratteri fino al terminatore \0 (null terminator)
    int length = strlen(password);
    if (length < 8) return 1; //Password invalida

    //Inizializzo delle variabili booleane di supporto per il controllo delle condizioni
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_symbol = false;

    //Lista dei simboli ammessi
    char allowed_symbols[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    //Controllo dei singoli caratteri della password, termina al raggiungimento dell'ultimo carattere utile (il precedente al null terminator \0)
    for(int i = 0; i < length; i++){

        if(isupper(password[i])) has_upper = true;
        if(islower(password[i])) has_lower = true;
        if(isdigit(password[i])) has_digit = true;
        
        // Controllo che il simbolo sia tra quelli ammessi e sia diverso dallo spazio
        if(ispunct(password[i]) && !isspace(password[i])) {
            if(strchr(allowed_symbols, password[i])) {
                has_symbol = true;
            }
        }
    }

    if(has_upper && has_lower && has_digit && has_symbol) return 0; //Success

    return 1; //Password non valida, restituisce 1
}