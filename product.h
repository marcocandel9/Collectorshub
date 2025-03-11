#include <stdio.h>
#include <stdlib.h>

#ifndef PRODUCT_H
#define PRODUCT_H

//definizione struct product, sarà il campo informativo dei nodi della lista products
struct product
{
    char product_name[20]; //nome del prodotto
    char product_type[20]; //tipologia del prodotto es: console, videogioco, francobollo, figurina
    char product_condition[20];    //descrizione delle condizioni del prodotto es: ottime, discrete, usurato, nuovo
    float product_buyprice;   //prezzo di acquisto del prodotto    
}

typedef struct product* product;

//crea un nuovo prodotto
int create_product(product* new_product, char new_name[], char new_type[], char new_condition[], float new_buy_price);

//elimina un prodotto liberandone l'area di memoria nell'heap
int delete_product(product* product_todelete);

int get_product_name(product myproduct, char myproduct_name[]);

int get_product_type(product myproduct, char myproduct_type[]);

int get_product_condition(product myproduct, char myproduct_condition[]);

int get_product_buyprice(product myproduct, float* myproduct_buyprice);

int set_product_name(product myproduct, char new_name[]);

int set_product_type(product myproduct, char new_type[]);

int set_product_condition(product myproduct, char new_condition[]);

int set_product_buyprice(product myproduct, float new_buyprice);

int print_product(product myproduct);

#endif
