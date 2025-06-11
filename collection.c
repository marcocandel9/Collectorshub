/*
@Brief
Contenuto informativo del nodo della lista collezioni. È composto da una struct collection, la quale avrà come contenuto 
informativo un array di caratteri (La cui lunghezza massima è definita dalla costante MAX_STR_LEN modificabile in product.c)
Impostato di base a 20 caratteri per il nome della collezione, e un altro array di caratteri di dim[MAX_STR_LEN] che descrive
la tipologia della collezione (es: Console, Videogiochi, Carte collezionabili, francobolli)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "collection.h"


/*
Crea una nuova collezione

Prende in ingresso un puntatore passato per riferimento ad una struct collection, l'array di caratteri del nome della collezione,
l'array di caratteri del  tipo di collezione

Restituisce 1 in caso di errore di allocazione dinamica
Restituisce 0 se tutto va a buon fine
*/
int create_collection(collection* new_collection, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]){
    (*new_collection) = (struct collection*)malloc(sizeof(struct collection));
    if (*new_collection == NULL)
        return 1; //errore di allocazione della nuova struct collection

    ///setter
    set_collection_name(*new_collection,new_name);
    set_collection_type(*new_collection,new_type);
    (*new_collection) -> products_list_head = NULL;

    return 0; //Success
}




/*
Setta un nuovo nome alla collezione

Prende in ingresso un puntatore passato per valore ad una struct collection e il nuovo nome della collezione

Restituisce 1 in caso di puntatore a NULL o non valido
Restituisce 0 se tutto va a buon fine
*/
int  set_collection_name(collection my_collection, char new_name[MAX_STR_LEN]){

    //Controlla se il puntatore alla collezione è NULL, restituisce 1 se lo è (collezione non esistente o non valida)
    if(my_collection == NULL) return 1; 

    //Setta il nome della collezione
    strcpy(my_collection->collection_name,new_name);
    
    //Success
    return 0; 
}





/*
Setta un nuovo tipo alla collezione

Prende in ingresso un puntatore ad una struct collection e il nuovo tipo della collezione

Restituisce 1 in caso di puntatore a NULL o non valido
Restituisce 0 se tutto va a buon fine
*/
int set_collection_type(collection my_collection, char new_type[MAX_STR_LEN]){

    //Controlla se il puntatore alla collezione è NULL, restituisce 1 se lo è (collezione non esistente o non valida)
    if(my_collection == NULL) return 1; 

    //Setta il tipo della collezione
    strcpy(my_collection->collection_type,new_type);
    
    //Success
    return 0; 
}





/*
Aggiunge una lista prodotti alla collezione 

Prende in ingresso il puntatore alla collezione passato per riferimento e il puntatore alla testa della lista prodotti passato per riferimento

Restituisce:
- 1 Se la collezione non è stata ancora creta (PUNTATORE A NULL)
- 0 Se l'inserimento va a buon fine
*/
int insert_products_list(collection* my_collection, products* new_products_list_head){

    // La collezione non è stata ancora creata, restituisci 1
    if((*my_collection) == NULL) return 1;

    // Aggancia la nuova lista prodotti (già creata altrove, anche vuota)
    (*my_collection)->products_list_head = *(new_products_list_head);

    return 0; // Success
}






/*
 Modifica il nome e il tipo della collezione. Se le stringhe passate come parametro di ingresso sono vuote, non modifica quel campo

 Prende in ingresso il puntatore alla collezione passato per riferimento e gli array di caratteri del nuovo nome e del nuovo tipo della collezione

 Restituisce:
 - 1 Se la collezione non è stata ancora creata (PUNTATORE A NULL)
 - 0 Se la modifica va a buon fine
*/
int modify_collection(collection my_collection, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]){
    
    // La collezione non è stata ancora creata o non è valida, restituisci 1
    if(my_collection == NULL) return 1;

    // Se new_name non è vuoto, modifica il nome della collezione
    if(new_name[0] != '\0')
        set_collection_name(my_collection, new_name);

    // Se new_type non è vuoto, modifica il tipo della collezione
    if(new_type[0] != '\0')
        set_collection_type(my_collection, new_type);
    
    return 0; //Success
}





/*
Ottiene il nome della collezione e lo passa all'array di caratteri my_name

Prende in ingresso la collezione e la stringa my_name

Restituisce:
- 1 Se la collezione non è stata ancora creta (PUNTATORE A NULL)
- 0 Se il passaggio va a buon fine
*/
int get_collection_name(collection my_collection, char my_name[MAX_STR_LEN]){
    
    // La collezione non è stata ancora creata o non è valida, restituisci 1
    if((my_collection) == NULL) return 1;

    //Copia il nome della collezione nell'array di caratteri my_name
    strcpy(my_name, my_collection->collection_name);
    
    return 0; //Success
}





/*
Ottiene il tipo della collezione e lo passa all'array di caratteri my_type

Prende in ingresso il puntatore alla collezione (passato per copia) e la stringa my_type

Restituisce:
- 1 Se la collezione non è stata ancora creta (PUNTATORE A NULL)
- 0 Se il passaggio va a buon fine
*/
int get_collection_type(collection my_collection, char my_type[MAX_STR_LEN]){
    
    // La collezione non è stata ancora creata o non è valida, restituisci 1
    if((my_collection) == NULL) return 1;

    //Copia il tipo della collezione nell'array di caratteri my_type
    strcpy(my_type, my_collection->collection_type);
    
    return 0; //Success
}





/*
Elimina una collezione liberandone l'area di memoria riservata alla lista dei prodotti associata alla collezione e la struct collection stessa

Prende in ingresso il puntatore alla collezione passato come riferimento

Restituisce:
- 1 Se il puntatore alla collezione è NULL (Collezione non inizializzata o non valida)
- 0 Se tutto va a buon fine
*/
int delete_collection(collection* my_collection){

    //Se il puntatore alla struct collection punta ad 1, restituisce 1 (Collezione non inizializzata o non valida)
    if((*my_collection) == NULL) return 1;

    //Libera la memoria allocata per la lista prodotti associati alla collezione
    free_products(&((*my_collection)->products_list_head));
    free((*my_collection));

    //Imposta il puntatore a NULL per rimuovere la condizione di dangling pointer (Puntatore ad un'area di memoria deferenziata e quindi non definita)
    (*my_collection) = NULL;
    return 0; //Success
}





/*
Stampa su terminale nome e il tipo della collezione

Prende in ingresso il puntatore alla collezione (passato per copia)

Restituisce:
- 1 Se la collezione non è stata ancora creata (PUNTATORE A NULL)
- 0 e ne stampa il contenuto se tutto va a buon fine
*/
int print_collection(collection my_collection){
    
    // La collezione non è stata ancora creata o non è valida, restituisci 1
    if((my_collection) == NULL) return 1;

    char my_collection_name[MAX_STR_LEN];
    char my_collection_type[MAX_STR_LEN];

    //Passa agli array di caratteri nome e tipo il contenuto informativo della collezione (Nome e tipo)
    get_collection_name(my_collection,my_collection_name);
    get_collection_type(my_collection,my_collection_type);

    printf("%s, %s\n", my_collection_name, my_collection_type);
    return 0; //Success
}