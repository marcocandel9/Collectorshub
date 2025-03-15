#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "products.h"


//funzione che crea una nuova lista prodotti a partire dal suo primo elemento
//prende in ingresso un puntatore passato per riferimento (products è stato definito con la typdef come un puntatore)
int create_products_list(products* head){
    
    //imposta i nuovi puntatori a testa a NULL
    *head = NULL;
    return 0;
}

//Inserisce un nuovo prodotto nella lista, prende in ingresso il puntatore passato come riferimento alla lista prodotti e il contenuto informativo del nuovo prodotto, ritorna 1 in caso di errori, 0 altrimenti (INSERIMENTO DUPLICATI CONTEMPLATO!)
int insert_product(products* products_list_head, char new_name[], char new_type[], char new_condition[], float new_buy_price){
    
    // Creo il nuovo nodo per il nuovo prodotto
    products new_product_node = (products)malloc(sizeof(struct products));
    if(new_product_node == NULL) return 1; // errore di allocazione
    
    // Popolo il nuovo nodo
    int result = create_product(&(new_product_node->product_elem), new_name, new_type, new_condition, new_buy_price);
    if(result == 1) {
        free(new_product_node);
        return 1; // errore nella creazione del prodotto
    }

    // Inserimento ordinato
    // Se la lista è vuota, inserisco in testa
    if(*products_list_head == NULL) {
        new_product_node->next = NULL;
        *products_list_head = new_product_node;
        return 0;
    }

    products r = NULL;
    products q = *products_list_head;
    char product_name[20];

    // Itera fino a trovare il punto di inserimento (ordinamento crescente) (Duplicati contemplati)
    while(q != NULL){
        get_product_name(q->product_elem, product_name);
        int caso = strcmp(new_name, product_name);
        if(caso < 0) { // se new_name è "minore" alfabeticamente, interrompi (N.B: r punta ancora a NULL nel caso in cui questa sia la prima iterazione)
             break;
        }
        r = q;
        q = q->next;
    }
    
    // Caso 1 inserimento: se r è NULL, significa inserimento in testa
    if(r == NULL){
        new_product_node->next = *products_list_head;
        *products_list_head = new_product_node;
    } else {  //Caso 2 inserimento: intermedio o al più in coda (Se è in coda, q == NULL!)
        r->next = new_product_node;
        new_product_node->next = q;
    }
    
    return 0;
}

