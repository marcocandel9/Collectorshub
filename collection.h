#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "products.h"

#ifndef COLLECTION_H
#define COLLECTION_H

struct collection{
    char collection_name[MAX_STR_LEN];  //identificativo nome della collezione
    char collection_type[MAX_STR_LEN];  //identificativo tipo di collezione
    products products_list_head;        //Puntatore alla testa della lista prodotti
};

typedef struct collection* collection;

int create_collection(collection* new_collection, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]);

int set_collection_name(collection* my_collection, char new_name[MAX_STR_LEN]);

int set_collection_type(collection* my_collection, char new_type[MAX_STR_LEN]);

int insert_collection_list(collection* my_collection, products* products_list_head, char new_product_name[MAX_STR_LEN], char new_product_type[MAX_STR_LEN], char new_product_condition[MAX_STR_LEN], float new_product_buy_price);


#endif