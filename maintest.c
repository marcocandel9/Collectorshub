#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "products.h"

int main() {
    char product_name[] = "Xbox360";
    char type[] = "Console";
    char condition [] = "Usata";
    float buyprice = 58.9;



    products Nuova_lista = NULL;
    insert_product(&(Nuova_lista),product_name,type, condition, buyprice);
    print_products(Nuova_lista);

    search_and_print_product(Nuova_lista, product_name);

}