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

Restituisce 1 in caso di errori di allocazione
Restituisce 0 se tutto va a buon fine
*/
int create_collection(collection* new_collection, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]){
    (*new_collection) = (struct collection*)malloc(sizeof(struct collection));
    if (*new_collection == NULL)
        return 1; //errore di allocazione del nuovo nodo prodotto

    ///setter
    set_collection_name((*new_collection),new_name);
    set_collection_type((*new_collection),new_type);

    //Inizialmente, la collezione sarà vuota. Verrà popolata da insert_collection_list
    (*new_collection) ->products_list_head = NULL;
}




/*
Setta un nuovo nome alla collezione

Prende in ingresso un puntatore passato per riferimento ad una struct collection e il nuovo nome della collezione

Restituisce 1 in caso di puntatore a NULL o non valido
Restituisce 0 se tutto va a buon fine
*/
int set_collection_name(collection* my_collection, char new_name[MAX_STR_LEN]){

    //Controlla se il puntatore alla collezione è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(*my_collection == NULL) return 1; 

    //Setta il nome della collezione
    strcpy((*my_collection)->collection_name,new_name);
    
    //Success
    return 0; 
}





/*
Setta un nuovo tipo alla collezione

Prende in ingresso un puntatore passato per riferimento ad una struct collection e il nuovo tipo della collezione

Restituisce 1 in caso di puntatore a NULL o non valido
Restituisce 0 se tutto va a buon fine
*/
int set_collection_type(collection* my_collection, char new_type[MAX_STR_LEN]){

    //Controlla se il puntatore alla collezione è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(*my_collection == NULL) return 1; 

    //Setta il nome della collezione
    strcpy((*my_collection)->collection_type,new_type);
    
    //Success
    return 0; 
}





/*
Aggiunge una nuova lista prodotti alla collezione

Prende in ingresso il puntatore alla collezione passato per riferimento e il puntatore alla testa della lista prodotti passato per riferimento

Restituisce 1 se la collezione non è stata ancora creta (PUNTATORE A NULL)
Restituisce 2 per errori nella creazione della nuova lista prodotti a partire dal primo elemento prodotto

*/
int insert_collection_list(collection* my_collection, products* products_list_head, char new_product_name[MAX_STR_LEN], char new_product_type[MAX_STR_LEN], char new_product_condition[MAX_STR_LEN], float new_product_buy_price){
    

}