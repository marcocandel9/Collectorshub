#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PRODUCT_H
#define PRODUCT_H
#define MAX_STR_LEN 20  //Definisce la dimensione massima degli array di caratteri (20 CARATTERI)
#define MIN_STR_LEN 8 //Definisce la dimensione minima degli array di caratteri (8 CARATTERI)

//definizione struct product, sarà il campo informativo dei nodi della lista products
struct product
{
    char product_name[MAX_STR_LEN]; //nome del prodotto
    char product_type[MAX_STR_LEN]; //tipologia del prodotto es: console, videogioco, francobollo, figurina
    char product_condition[MAX_STR_LEN];    //descrizione delle condizioni del prodotto es: ottime, discrete, usurato, nuovo
    float product_buyprice;   //prezzo di acquisto del prodotto    
};

typedef struct product* product;

int create_product(product* new_product, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price);

int delete_product(product* product_todelete);

int get_product_name(product myproduct, char myproduct_name[MAX_STR_LEN]);

int get_product_type(product myproduct, char myproduct_type[MAX_STR_LEN]);

int get_product_condition(product myproduct, char myproduct_condition[MAX_STR_LEN]);

int get_product_buyprice(product myproduct, float* myproduct_buyprice);

int set_product_name(product myproduct, char new_name[MAX_STR_LEN]);

int set_product_type(product myproduct, char new_type[MAX_STR_LEN]);

int set_product_condition(product myproduct, char new_condition[MAX_STR_LEN]);

int set_product_buyprice(product myproduct, float new_buyprice);

int modify_product(product* myproduct, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price);

int print_product(product myproduct);

int save_product(FILE *fptr, product myproduct);

int read_product(FILE *fptr, char read_product_name[MAX_STR_LEN], char read_product_type[MAX_STR_LEN], char read_product_condition[MAX_STR_LEN], float* read_buyprice);

#endif
