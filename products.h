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

int remove_product(products* products_list_head, char key_name []);

int exist_sorted(products products_list_head, char key_name[]);

product search_product(products products_list_head, char key_name[]);

int modify_product(products* products_list_head, char key_name[], char new_name[], char new_type[], char new_condition[], float new_buy_price);

int search_and_print_product(products products_list_head, char key_name[]);

int print_products(products products_list_head);




#endif