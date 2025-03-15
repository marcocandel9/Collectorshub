//per la lista dei prodotti verrà definita una struttura dati lista doppiamente concatenata con ordinamento in base a nome del prodotto (alfabetico)
//per evitare che l'header file venga incluso più volte aggiungo la direttiva ifndef
#ifndef PRODUCTS_H
#define PRODUCTS_H
#include "product.h"



struct products{
    product product_elem; 
    struct products* next; 
};

typedef struct products* products;  

int create_products_list(products* head);

int insert_product(products* products_list_head, char new_name[], char new_type[], char new_condition[], float new_buy_price);

int delete_product(products* products_list_head, char key_name []);










#endif