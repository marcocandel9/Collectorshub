//LISTA COLLEZIONI CON LOGICA DI ORDINAMENTO ALFABETICO IN BASE AL NOME DELLA COLLEZIONE. NON ACCETTA DUPLICATI.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "collections.h"





/*
Crea una nuova lista collezioni VUOTA
Prende in ingresso il puntatore alla testa della lista collezioni (puntatore di tipo struct collections) e lo inizializza a NULL
Restituisce 0 
*/
int create_collections_list(collections* collections_list_head){
    *(collections_list_head) = NULL;
    return 0;
}





/*
Inserisce una nuova collezione alla lista collezioni ORDINATA. Implementa l'inserimento anche di una prima collezione a partire da una lista vuota

Prende in ingresso il puntatore alla testa della lista collezioni, l'array di caratteri per il nome della nuova collezione e
l'array di caratteri per il tipo della nuova collezione

Restituisce:
- 1 In caso di errori di allocazione
- 2 In caso di inserimento di un duplicato (NON CONSENTITO)
- 0 Inserisce la nuova collezione con esito positivo
*/
int insert_collection(collections* collections_list_head, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]){

    //Alloco il nuovo nodo della lista collezioni
    collections new_collections_node = (collections*)malloc(sizeof(struct collections)); 
        if(new_collections_node == NULL) return 1; //Restituisce 1 in caso di errori di allocazione

    //Popolo il nuovo nodo della lista collezioni
    int result = create_collection(&(new_collections_node->collection_elem), new_name, new_type);

    //errore di allocazione del nuovo puntatore alla collezione
    if(result == 1){
        free(new_collections_node); //Dealloco il nodo collezione
        return 1; //Errore di allocazione del nuovo nodo collezione, restituisco 1
    } 

    //Altrimenti result = 0, ho allocato il nuovo nodo e la nuova collezione all'interno del nodo, posso inserirlo nella lista collezioni


    //Inserimento in testa (la collezione da inserire è la prima della lista collezioni, la lista delle collezioni è dunque VUOTA)
    if(*collections_list_head == NULL){
        *collections_list_head = new_collections_node; //La testa adesso punterà al nuovo nodo
        new_collections_node->next = NULL;             //Il nuovo nodo sarà anche la coda della lista, punterà a NULL
        return 0; //Success
    }

    //Inserimento intermedio o alpiù in coda, devo scorrere la lista
    //Preparo i puntatori di appoggio per lo scorrimento della lista e un'array di caratteri per il confronto del nome collezione di ogni singolo nodo
    struct collections* r = NULL;                       //Puntatore di appoggio al nodo precedente a quello di osservazione
    struct collections* q = *collections_list_head;     //Puntatore di appoggio al nodo di osservazione
    char collection_name[MAX_STR_LEN];                  //Array di caratteri di appoggio per l'osservazione del nome della collezione di ogni nodo collezione

    //Scorro la lista finchè non raggiungo la coda (r punterà all'ultimo nodo, q a NULL quando ciò accadrà), oppure finchè non trovo un MATCH
    while(q != NULL){
        
        //strcmp restituisce:
        // - un valore negativo se new_name è alfabeticamente inferiore al nome della collezione -> devo interrompere lo scorrimento e inserire il nodo
        // - 0 se new_name == product_name
        // - un valore positivo se new_name è alfabeticamente superiore al nome della collezione -> devo continuare a scorrere la lista
        get_collection_name(q->collection_elem,collection_name);
        int caso = strcmp(new_name,collection_name);

        //In caso di duplicati libera il nuovo noto e restituisce 2 (DUPLICATI NON CONSENTITI)
        if(caso == 0){
            free(new_collections_node);
            return 2; //Duplicato
        }

        //Trovata la corretta posizione di inserimento ordinato, esco dal ciclo while
        if(caso < 0){
            break; 
        }

        //Incremento i puntatori di appoggio
        r = q;
        q = q -> next;
    }
    
    //Inserisco il nuovo nodo nella posizione trovata
    //Caso 1:  (inserimento TESTA) (non mi sono mosso dal primo elemento, r punta a NULL e q punta al primo nodo della lista) (Devo aggiornare la testa)
    if(r == NULL) {
        new_collections_node -> next = *(collections_list_head);
        *(collections_list_head) = new_collections_node; //Aggiorno la testa
    
    } else {     //Caso 2: Inserimento intermedio o alpiù in coda (N.B se inserisco in coda q == NULL)
        r->next = new_collections_node;
        new_collections_node -> next = q;
    }

    return 0; //Success

}

