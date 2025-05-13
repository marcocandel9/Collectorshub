//Definisce la libreria per le funzioni che implementano l'input/output delle funzionalità della libreria users/user.h.
#ifndef USERS_SYSTEM_H
#define USERS_SYSTEM_H
#include "menu.h"
#include "users.h"

//////////////////////////////////////////////////////MENÙ UTENTE///////////////////////////////////////////////////////////////////

/*
Funzione che implementa il controllo della stringa in input. Controlla i seguenti criteri:
    1) Che la stringa passata in ingresso non sia stata troncata -> input troppo lungo, riprova
    2) Che la stringa passata in ingresso non sia minore di MIN LEN  -> Input troppo corto, riprova
    3) Che la stringa passata in ingresso non sia maggiore di MAX LEN -> Input troppo lungo, riprova
    3) Rimuove il carattere a capo dalla stringa prelevata dal buffer di input

    Restituisce:
    - 0 Se la stringa passata in input è stata correttamente inserita e viene passata al chiamante tramite la stringa output_string
    - 1 Se l'utente immette in input una stringa vuota, indicando l'operazione di ANNULLAMENTO.
*/ 
int sys_input_string_checker(char output_string[MAX_STR_LEN], bool check_space, int max_len, int min_len);


/*
Semplice funzione che restituisce 0 se l'utente immette 0 in input, restituisce 1 se l'utente inserisce 1 in input.
*/
int ask_confirmation();


/*
Implementa l'I/O per la registrazione di un nuovo utente. Chiede in input da tastiera un nuovo username, controlla che questo username non sia già utilizzato (sia già presente nella lista utenti), controlla che la password sia valida secondo la logica dell'ADT
(utilizzando la funzione validate_password di user.h) e in caso di esito positivo richiama la funzione insert_user_sorted di users.h per inserire il nuovo utente nella struttura dati utenti, con algoritmo di inserimento ordinato alfabeticamente.

Restituisce:
- un puntatore al nuovo utente creato
- un puntatore a NULL nel caso in cui la registrazione venga annullata dall'utente o ci siano problemi di lettura del buffer stdin
*/
user sys_register_user(users* users_list_head);


/*
Implementa l'I/O Per il login di un utente

Restituisce:
    - un puntatore al nuovo utente creato in caso di corretta autenticazione
    - un puntatore a NULL in caso di errori del buffer o di annullamento da parte dell'utente
*/
user sys_login_user(users* users_list_head);


/*
Implementa l'I/O per la modifica dell'username di un utente, richiede in ingresso la stringa del nome utente attuale dell'utente e la lista degli utenti
    Restituisce:
        1 In caso di annullamento dell'operazione da parte dell'utente
        2 In caso di errori di lettura del buffer di input
        3 In caso di errori di modifica dell'utente nella struttura dati (FATAL ERROR)
        0 Se tutto va a buon fine
    N.B: La stringa current_username, nel caso di effettuata modifica, viene modificata con il nuovo nome utente inserito dall'user da terminale.
*/
int sys_modify_username(char current_username[MAX_STR_LEN], users* users_list_head);


/*
Implementa l'I/O Per la SOLA modifica della password.
*/
int sys_modify_password(char user_username[MAX_STR_LEN], char current_password[MAX_STR_LEN], users* users_list_head);


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
int sys_modify_credentials(user* my_user, users* users_list_head);


/*
Implementa l'I/O Per l'eliminazione di un utente. Non effettua la ricerca dell'utente stesso, utile quindi quando
un utente vuole eliminare il proprio profilo. 

Restituisce:
    1: Se l'utente immette una stringa vuota e annulla l'eliminazione del proprio profilo
    2: in caso di errore di lettura del buffer di input
    3: Se non è stato possiible trovare l'utente nella lista utenti
    0: Se l'eliminazione va a buon fine
*/
int sys_delete_user(users* users_list_head, char user_username[MAX_STR_LEN]);


//WIP
int sys_promote_user(users* users_list_head , user user_to_promote);


//////////////////////////////////////////////////////MENÙ COLLEZIONI///////////////////////////////////////////////////////////////////

/*
Implementa l'I/O per la visualizzazione della lista collezioni di un utente.
Restituisce:
    1: Se la lista è vuota 
    0: Se tutto va a buon fine
*/
int sys_print_user_collections(user logged_user);


/*
Implementa l'I/O per l'accesso ad una collezione, e il conseguente ingresso nel menù prodotti. 

Restituisce:
    4 Se la lista delle collezioni risulta vuota durante l'accesso ai dati utente.
    3 Se la lista collezioni è vuota', (*user_collection = NULL)
    2 In caso di errore di lettura del buffer di input stdin
    1 Se l'utente annulla l'accesso alla collezione. (*user_collection = NULL)
    0 Se tutto va a buon fine (*user_collection = collezione a cui si vuole accedere)
*/
int sys_access_user_collection(user logged_user, collection* user_collection);


/*
Implementa l'I/O per l'aggiunta di una nuova collezione nella lista delle collezioni di un utente già loggato (Richiede in ingresso il puntatore all'utente loggato.)
Restituisce:
    1: In caso di annullamento da parte dell'utente
    2: In caso di errore di lettura del buffer di input
    4: In caso di errore critico di allocazione di memoria
    0: Se tutto va bene
*/
int sys_insert_collection(user logged_user);


/*
Implementa l'I/O per l'aggiunta di una nuova collezione nella lista delle collezioni di un utente già loggato (Richiede in ingresso il puntatore all'utente loggato.)
Restituisce:
    1: In caso di annullamento da parte dell'utente
    2: In caso di errore di lettura del buffer di input
    4: In caso di errore critico di allocazione di memoria
    0: Se tutto va bene
*/
int sys_modify_collection(user logged_user);


/*
Implementa l'I/O Per la eliminazione di UNA collezione da parte di un utente loggato.

Restituisce:
    1 In caso di annullamento dell'operazione da parte dell'utente
    2 In caso di errore critico di lettura del buffer di input stdin
    3 Se la lista collezioni dell'utente è vuota.
    4 In caso di errori critici durante l'eliminazione della collezione (RARI!)
    0 Se tutto va a buon fine
*/
int sys_delete_collection(user logged_user);


/*
Implementa l'I/O Per la eliminazione di TUTTE le collezioni da parte di un utente loggato.

Restituisce:
    1 In caso di annullamento dell'operazione da parte dell'utente
    2 In caso di errore critico di lettura del buffer di input stdin
    3 Se la lista collezioni dell'utente è vuota.
    4 In caso di errori critici durante l'eliminazione delle collezioni (RARI!)
    0 Se tutto va a buon fine
*/
int sys_delete_collections(user logged_user);


//////////////////////////////////////////////////////MENÙ PRODOTTI///////////////////////////////////////////////////////////////////

//N.B In queste funzioni il parametro di ingresso user sarebbe superfluo, ma lo passo comunque per aggiungere informazioni degli utenti per l'UI.

int sys_print_user_products(user logged_user, collection user_collection);

int sys_insert_user_product(user logged_user, collection user_collection);

int sys_modify_user_product(user logged_user, collection user_collection);

int sys_delete_user_product(user logged_user, collection user_collection);

int sys_delete_user_products(user logged_user, collection user_collection);

#endif