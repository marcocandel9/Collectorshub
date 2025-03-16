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


    char product_name2[] = "ETB trainer box";
    char type2[] = "Pokemon";
    char condition2 [] = "Usata";
    float buyprice2 = 10000;
    insert_product(&(Nuova_lista),product_name2,type2, condition2, buyprice2);

    char product_name3[] = "Autobot";
    char type3[] = "Trasformers";
    char condition3 [] = "Nuovo di zecca";
    float buyprice3 = 100010;
    insert_product(&(Nuova_lista),product_name3,type3, condition3, buyprice3);
    print_products(Nuova_lista);

    printf("breakpoint1\n");
    remove_product(&(Nuova_lista), product_name3);
    print_products(Nuova_lista);

    char prodotto[] = " ";
    printf("breakpoint2\n");
    int result = remove_product(&(Nuova_lista) , prodotto);
    printf("%d \n",result);

    printf("breakpoint3\n");
    print_products(Nuova_lista);
}