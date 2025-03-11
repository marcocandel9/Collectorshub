#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "products.h"


//funzione che crea una nuova lista prodotti a partire dal suo primo elemento
//prende in ingresso un puntatore passato per riferimento (products è stato definito con la typdef come un puntatore)
int create_products_list(products* head){
    
    //imposta i nuovi puntatori a testa e next a NULL
    *head = NULL;
    return 0;
}

//Inserisce un nuovo prodotto nella lista, prende in ingresso il puntatore passato come riferimento alla lista prodotti e il contenuto informativo del nuovo prodotto, ritorna 1 in caso di errori, 0 altrimenti (INSERIMENTO DUPLICATI CONTEMPLATO!)
int insert_products_elem(products* products_list, char new_name[], char new_type[], char new_condition[], float new_buy_price){
    
    //creo il nuovo puntatore a nodo per il nuovo prodotto della lista
    products new_product; 
    //alloco spazio nell'heap
    new_product = (struct products*)malloc(sizeof(struct products));
    if(new_product == NULL) return 1; // errore di allocazione
    
    int result = create_product((&(new_product->product_elem)), new_name, new_type,  new_condition,  new_buy_price);
    if(result == 1) return 1; // errore nella creazione del prodotto

    //inserimento ordinato

    //caso base(lista vuota)
    if(*(products_list)==NULL)
        *(products_list)=new_product;
        new_product->next == NULL;
    return 0;


    //preparo i dati per effettuare la comparazione alfabetica del primo carattere del nome
    char firstname[20];
    char secondname[20];
    get_product_name(new_product, firstname);
    get_product_name(((*products_list)->product_elem),secondname);
    struct products* p;
    struct products* q;
    
    //caso 1: inserimento in testa (nome prodotto alfabeticamente minore del primo prodotto)
    if(strcmp(firstname, secondname) < 0) // strcmp() confronta le due stringe
        
        //inserimento testa 
        new_product->next = (*products_list);
        (*products_list) = new_product;

    //caso 2: inserimento in mezzo o alpiù in coda (INSERIMENTO DUPLICATI CONTEMPLATO)
        
}

