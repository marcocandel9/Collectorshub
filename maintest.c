#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "collections.h"

int main() {

    //Creo una nuova lista prodotti e aggiungo un nuovo prodotto
    products Nuova_lista;
    create_products_list(&(Nuova_lista));

    char product_name1[MAX_STR_LEN] = "Xbox360";
    char type1[MAX_STR_LEN] = "Console";
    char condition1 [MAX_STR_LEN] = "Usata";
    float buyprice1 = 58.9;

    insert_product(&(Nuova_lista),product_name1,type1, condition1, buyprice1);


    char product_name2[MAX_STR_LEN] = "ETB trainer box";
    char type2[MAX_STR_LEN] = "Pokemon";
    char condition2 [MAX_STR_LEN] = "Usata";
    float buyprice2 = 10000;
    insert_product(&(Nuova_lista),product_name2,type2, condition2, buyprice2);

    //Stampo la lista dei prodotti( ne conterrà due )
    print_products(Nuova_lista);

    printf("Controllo rimozione prodotti\n");
    //Rimuovo dei prodotti dalla lista
    remove_product(&(Nuova_lista), product_name1);

    printf(" Adesso la lista sarà composta da un solo prodotto:\n");
    print_products(Nuova_lista);

    printf(" Controllo cosa succede quando rimuovo tutti i prodotti dalla lista e la printo:\n");
    remove_product(&(Nuova_lista), product_name2);
    
    //dovrebbe stampare 1 cioè lista vuota
    printf("%d\n",print_products(Nuova_lista));

    char product_name3[MAX_STR_LEN] = "TEST PRODOTTO 3";
    char type3[MAX_STR_LEN] = "TEST";
    char condition3 [MAX_STR_LEN] = "TEST";
    float buyprice3 = 0;
    insert_product(&(Nuova_lista),product_name3,type3, condition3, buyprice3);
    print_products(Nuova_lista);

    printf("\n\ncontrollo della ricerca e modifica di un prodotto\n\n");

    char product_name3_modified[MAX_STR_LEN] = "TEST PRODOTTO 3_mod";
    char type3_modified[MAX_STR_LEN] = ""; // questo campo non deve essere modificato
    char condition3_modified [MAX_STR_LEN] = "";
    float buyprice3_modified = -1.0f; //Questo campo non può essere modificato

    search_and_modify_product(&(Nuova_lista),product_name3,product_name3_modified,type3_modified,condition3_modified, buyprice3_modified);

    print_products(Nuova_lista);

    
    //TEST COLLEZIONI

    char my_collection1_name[MAX_STR_LEN] = "Collezione di marco";
    char my_collection1_type[MAX_STR_LEN] = "Carte Collezionabili";
    char my_collection1modified_name[MAX_STR_LEN] = "Coll. 1 di Marco";
    char empty[MAX_STR_LEN] = "";
  
    collections collezioni = NULL;

    insert_collection(&(collezioni), my_collection1_name, my_collection1_type);
    remove_collection(&(collezioni),my_collection1_name);
    print_collections(collezioni);
    printf("breakpoint stampa lista con una sola collezione\n");

    char my_collection2_name[MAX_STR_LEN] = "Carte pokemon";
    char my_collection2_type[MAX_STR_LEN] = "Carte collezionabili";
    insert_collection(&(collezioni), my_collection2_name, my_collection2_type);
    print_collections(collezioni);

    search_and_modify_collection(&(collezioni), my_collection2_name,my_collection1modified_name, empty);
    printf("breakpoint 2: search and modify\n");
    print_collections(collezioni);


    printf("breakpoint 3: aggiunta seconda collezione\n");
    insert_collection(&(collezioni),my_collection1_name,my_collection2_type);



    print_collections(collezioni);

    insert_sorted_products_list(&collezioni, my_collection1_name, &Nuova_lista);
    printf("\n La precedente collezione contiene i seguenti prodotti: \n");
    print_products(Nuova_lista);

    
    
    printf("\n Libero tutte le collezioni e stampo niente: \n");
    free_collections(&(collezioni));
    print_collections(collezioni);
}