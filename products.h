//per la lista dei prodotti verrà definita una struttura dati lista concatenata con ordinamento in base a nome del prodotto (alfabetico)
//per evitare che l'header file venga incluso più volte aggiungo la direttiva ifndef
#ifndef PRODUCTS_H
#define PRODUCTS_H
#include "product.h"



struct products{
    product product_elem; 
    struct products* next; 
};

typedef struct products* products;  

int insert_product(products* products_list_head, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price);

int remove_product(products* products_list_head, char key_name [MAX_STR_LEN]);

int exist_sorted(products products_list_head, char key_name[MAX_STR_LEN]);

product search_product(products products_list_head, char key_name[MAX_STR_LEN]);

int search_and_modify_product(products* products_list_head, char key_name[MAX_STR_LEN], char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price);

int search_and_print_product(products products_list_head, char key_name[MAX_STR_LEN]);

int print_products(products products_list_head);

int free_products(products* products_list_head);

int save_products(FILE *fptr, products products_list_head);

int load_products(FILE *fptr, products* products_list, char next_line[MAX_STR_LEN]);

#endif