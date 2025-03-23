#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
//La direttiva #include "product.h" dice al preprocessore di inserire il contenuto del file product.h prima della compilazione.

//prende in ingresso un puntatore ad una struct product passato per riferimento, lo alloca dinamicamente nell'heap e lo popola
//NB come parametro della funzione non passo un doppio puntatore perchè product è già definito in product.h come un puntatore, quindi 
//in questo caso scrivendo product* sto passando il puntatore come riferimento (puntatore a puntatore o indirizzo del puntatore)


int create_product(product* new_product, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price){
    (*new_product) = (struct product*)malloc(sizeof(struct product));
    if (*new_product == NULL)
        return 1; //errore di allocazione del nuovo nodo prodotto

    //popolo il contenuto informativo di product 
    set_product_name(*new_product,new_name);
    set_product_condition(*new_product,new_condition);
    set_product_type(*new_product,new_type);
    set_product_buyprice(*new_product, new_buy_price);
    return 0; //success
}





//Prende in ingresso il puntatore al puntatore di una struct product, ritorna 0 dopo l'eliminazione
int delete_product(product* product_todelete){

    //Restituisce 1 se il puntatore al prodotto punta a NULL (prodotto non esistente o non valido)
    if ((*product_todelete)==NULL)
        return 1; 
    
    //libera la memoria nell'heap puntata dal puntatore
    free(*product_todelete);

    //Imposta il puntatore a NULL per rimuovere la condizione di dangling pointer (Puntatore ad un'area di memoria deferenziata e quindi non definita)
    *product_todelete=NULL;
    return 0; 
}





//Funzioni getter
//Prendono in ingresso il puntatore passato come copia e l'array di caratteri (quindi il puntatore all'array),, restituisce 0 se è success, 1 altrimenti
//La funzione get_product_price ha come parametro formale in ingresso il puntatore a float

int get_product_name(product myproduct, char myproduct_name[MAX_STR_LEN]){
    
    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(myproduct==NULL)
        return 1; 
    
    //accede al campo informativo della struct puntata dal puntatore myproduct e preleva il campo del nome
    strcpy(myproduct_name, myproduct->product_name);
    return 0; //success
}





int get_product_type(product myproduct, char myproduct_type[MAX_STR_LEN]){
    
    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(myproduct==NULL)
        return 1; 
    
    //accede al campo informativo della struct puntata dal puntatore myproduct e preleva il campo del tipo di prodotto
    strcpy(myproduct_type, myproduct->product_type);
    return 0; //success
}





int get_product_condition(product myproduct, char myproduct_condition[MAX_STR_LEN]){
    
    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(myproduct==NULL)
        return 1; 
    
    //accede al campo informativo della struct puntata dal puntatore myproduct e preleva il campo della condizione
    strcpy(myproduct_condition, myproduct->product_condition);
    return 0; //success
}





int get_product_buyprice(product myproduct, float* myproduct_buyprice){
    
    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(myproduct==NULL)
        return 1;
        
    //accede al campo informativo della struct puntata dal puntatore myproduct e preleva il campo del prezzo d'acquisto
    *myproduct_buyprice = myproduct->product_buyprice;
    return 0; //success
}





//funzioni setter

//riceve in ingresso il puntatore passato per copia e il contenuto informativo da aggiornare; ritorna 0 se success, 1 altrimenti
int set_product_name(product myproduct, char new_name[MAX_STR_LEN]){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if((myproduct) == NULL)
        return 1;
    
    //aggiorna il contenuto informativo 
    strcpy(myproduct->product_name, new_name);

    return 0; //success
}





int set_product_type(product myproduct, char new_type[MAX_STR_LEN]){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if((myproduct) == NULL)
        return 1;
    
    //aggiorna il contenuto informativo 
    strcpy(myproduct->product_type, new_type);

    return 0; //success
}





int set_product_condition(product myproduct, char new_condition[MAX_STR_LEN]){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if((myproduct) == NULL)
        return 1;
    
    //aggiorna il contenuto informativo 
    strcpy(myproduct->product_condition, new_condition);
    return 0; //success
}





/*
Funzione che modifica il contenuto informativo del prodotto. Se la stringa passata come parametro è vuota, allora non modifica 
quel contenuto informativo

Prende in ingresso il puntatore passato come riferimento al prodotto, le stringhe del contenuto informativo del prodotto

Restituisce 1 se il puntatore al prodotto è non esistente o non valido
Restituisce 0 se la modifica avviene con esito positivo
*/
int modify_product(product* myproduct, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price){

    // Controlla se il puntatore al prodotto è NULL
    if (*myproduct == NULL)
    return 1;  // Prodotto non esistente o non valido

    // Se new_name non è vuoto, modifica il nome del prodotto
    if (new_name[0] != '\0') 
        strcpy((*myproduct)->product_name, new_name);
    
    // Se new_type non è vuoto, modifica il tipo del prodotto
    if (new_type[0] != '\0') 
        strcpy((*myproduct)->product_type, new_type);
    
    // Se new_condition non è vuoto, modifica la condizione del prodotto
    if (new_condition[0] != '\0') 
        strcpy((*myproduct)->product_condition, new_condition);

    // Se new_buy_price è valido (diverso da un valore sentinella come -1.0f), modifica il prezzo d'acquisto
    if (new_buy_price != -1.0f)  // Supponiamo che -1.0f sia il valore sentinella
        (*myproduct)->product_buyprice = new_buy_price;

    return 0;  // Successo
}





//il float new_buyprice a differenza della funzione getter è passato come copia perchè non deve essere modificato 
int set_product_buyprice(product myproduct, float new_buyprice){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if((myproduct) == NULL)
        return 1;
    
    //Aggiorna il contenuto informativo 
    myproduct->product_buyprice = new_buyprice;

    return 0; //success
}

//ritorna 1 se il puntatore punta NULL, printa altrimenti i contenuti informativi da lui puntati.
int print_product(product myproduct){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if (myproduct == NULL) return 1;
    
    char product_name[MAX_STR_LEN];
    char product_type[MAX_STR_LEN];
    char product_condition[MAX_STR_LEN];
    float product_buyprice;

    get_product_name(myproduct, product_name);
    get_product_type(myproduct, product_type);
    get_product_condition(myproduct, product_condition);
    get_product_buyprice(myproduct, &product_buyprice);

    printf("%s, %s, %s, %f\n", product_name, product_type, product_condition, product_buyprice);
    return 0;
}


