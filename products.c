#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "products.h"


//funzione che crea una nuova lista prodotti a partire dal suo primo elemento
//prende in ingresso un puntatore passato per riferimento (products è stato definito con la typdef come un puntatore)
int create_products_list(products* head){
    
    //imposta i nuovi puntatori a testa a NULL
    *head = NULL;
    return 0;
}





//Inserisce un nuovo prodotto nella lista, prende in ingresso il puntatore passato come riferimento alla lista prodotti e il contenuto informativo del nuovo prodotto, 
//ritorna 1 in caso di errori di allocazione memoria
//ritorna 2 in caso di inserimento di duplicato
//0 altrimenti 
int insert_product(products* products_list_head, char new_name[], char new_type[], char new_condition[], float new_buy_price){
    
    // Creo il nuovo nodo per il nuovo prodotto
    products new_product_node = (products)malloc(sizeof(struct products));
    if(new_product_node == NULL) return 1; // errore di allocazione
    
    // Popolo il nuovo nodo
    int result = create_product(&(new_product_node->product_elem), new_name, new_type, new_condition, new_buy_price);
    if(result == 1) {
        free(new_product_node);
        return 1; // errore nella creazione del prodotto
    }

    // Inserimento ordinato
    // Se la lista è vuota, inserisco in testa
    if(*products_list_head == NULL) {
        new_product_node->next = NULL;
        *products_list_head = new_product_node;
        return 0;
    }

    products r = NULL;
    products q = *products_list_head;
    char product_name[20];

    // Itera fino a trovare il punto di inserimento (ordinamento crescente) (Duplicati NON CONSENTITI)
    while(q != NULL){
        get_product_name(q->product_elem, product_name);
        int caso = strcmp(new_name, product_name);

        // CONTROLLO DUPLICATI: IMPOSTATO SU NON CONSENTITI

        //se le stringhe sono equivalenti, ritorna 2! DUPLICATI NON CONSENTITI //È possibile CONSENTIRE I DUPLICATI RIMUOVENDO LE SEGUENTI 4 LINEE DI CODICE
        if(caso == 0){
            free(new_product_node);
            return 2;
        }

        //CONTROLLO DUPLICATI: IMPOSTATO SU NON CONSENTITI


        if(caso < 0) { // se new_name è "minore" alfabeticamente, interrompi (N.B: r punta ancora a NULL nel caso in cui questa sia la prima iterazione)
             break;
        }
        r = q;
        q = q->next;
    }
    
    // Se non è stato trovato alcun nodo (q==NULL), restituisci un errore
    if(q == NULL) return 1;

    // Caso 1 inserimento: se r è NULL, significa inserimento in testa
    if(r == NULL){
        new_product_node->next = *products_list_head;
        *products_list_head = new_product_node;
    } else {  //Caso 2 inserimento: intermedio o al più in coda (Se è in coda, q == NULL!)
        r->next = new_product_node;
        new_product_node->next = q;
    }
    
    return 0;
}





/*
Prende in ingresso: puntatore testa passato per riferimento, array di caratteri del nome dell'elemento da ricercare ed eliminare
Restituisce 0 in caso di Success
Restituisce 1 se la lista è vuota
Restituisce 2 se non è stato trovato l'elemento
NB Cancella solo sulla base del nome, se disattivo il controllo di evitamento dei duplicati nella funzione insert product non posso selezionare quale dei duplicati eliminare
*/
int remove_product(products* products_list_head, char key_name []){

    //Lista vuota: Restituisce 1
    if(*products_list_head == NULL) return 1;

    //Puntatori di appoggio per scorrere la lista ordinata
    products r = NULL;
    products q = *products_list_head;
    char product_name[20];

    while(q != NULL){
        get_product_name(q->product_elem, product_name);
        int is_not_equal = strcmp(key_name, product_name);
    
        if(is_not_equal == 0){
            break;
        }
        r = q;
        q = q->next;
    }

    // Se non è stato trovato alcun nodo (q==NULL), restituisci 1
    if(q == NULL)
        return 1; 

    //Caso 1 : cancellazione testa, traslo la lista di un nodo in avanti
    if(r==NULL){
        *(products_list_head) = q->next;

        //dealloco il nodo contenete il prodotto che si desidera eliminare

        //Richiamo la funzione delete product per deallocare il prodotto allocato dinamicamente
        delete_product(&(q->product_elem)); //Dealloca la memoria della struttura prodotto
        free(q); //Dealloca la memoria della struttura Products contenente il puntatore a nodo che dopo delete product puntava a NULL

    } else { //Caso 2, cancellazione intermedia o al più in coda (Se è in coda, q == NULL!)
        ( r -> next ) = ( q -> next );
        delete_product(&(q->product_elem)); //Dealloca la memoria della struttura prodotto
        free(q); //Dealloca la memoria della struttura Products contenente il puntatore a nodo che dopo delete product puntava a NULL
    }
    return 0; //Success
}





/*
Funzione che ricerca un elemento nella lista ORDINATA.

Prende in ingresso il puntatore alla testa della lista passato come copia, l'array di caratteri

Restituisce 0 se l'elemento esiste
Restituisce 1 altrimenti
*/

int exist_sorted(products products_list_head, char key_name[]){

    //Lista vuota: ritorno 1
    if(products_list_head == NULL) return 1;

    char product_name[20];
    int found;

    while(products_list_head != NULL){ //l'iterazione termina quando si raggiunge la fine della lista o quando si incontra un prodotto con nome alfabeticamente maggiore di quello ricercato
        get_product_name((products_list_head->product_elem),product_name);
        found = strcmp(key_name,product_name);
        
        if(found == 0) return 0; //Trovato, restituisce 0
        
        // Se il nome cercato è alfabeticamente minore (cioè, strcmp restituisce un valore negativo),
        // significa che il prodotto corrente ha un nome maggiore e quindi il prodotto non esiste nella lista.
        if(found < 0) break;

        products_list_head = products_list_head -> next;
    }

    return 1; // non è stata trovata una corrispondenza
}





/*
Funzione che ricerca un elemento nella lista ORDINATA e ne restituisce un puntatore product del prodotto

Prende in ingresso il puntatore alla testa della lista passato come copia, l'array di caratteri del nome del prodotto ricercato

Restituisce il puntatore product al prodotto se l'elemento è trovato
Restituisce NULL se l'elemento non è stato trovato
*/

product search_product(products products_list_head, char key_name[]){

    char product_name[20];
    int found;

    //Se l'elemento è stato trovato, lo ricerca e lo restituisce
    while(products_list_head != NULL) {
        get_product_name((products_list_head->product_elem),product_name);
        found = strcmp(key_name,product_name);

        if(found == 0) return products_list_head->product_elem; //Se trova la corrispondenza restituisce il puntatore alla struct Product

        products_list_head = products_list_head -> next;
    }

    return NULL; //Restituisce un puntatore a null nel caso negativo

}





/*
Funzione che ricerca un elemento nella lista ORDINATA, ne modifica il contenuto del prodotto nel nodo

Prende in ingresso il puntatore alla testa della lista passato per riferimento, il nome dell'elemento da modificare,
le variabili del contenuto informativo della Struct Prodotto

Restituisce 0 se la modifica va a buon fine
Restituisce 1 se l'elemento non è stato trovato
*/
int modify_product(products* products_list_head, char key_name[], char new_name[], char new_type[], char new_condition[], float new_buy_price){

    //Lista vuota: restituisce 1
    if(*products_list_head == NULL) return 1;

    //Puntatori di appoggio per scorrere la lista
    products r = NULL;
    products q = *products_list_head;
    char product_name[20];
    int found;

    //Ricerca e modifica dell'elemento
    while(q != NULL){
        get_product_name(q->product_elem,product_name);
        found = strcmp(key_name,product_name);

        if(found == 0) break; //Trovato, esci dal ciclo while

        if(found < 0) return 1; //Non è stata trovata una corrispondenza nella lista, ritorna 1 (ELEMENT NOT FOUND)

        r = q;
        q = q -> next;
    }

    //Caso 1: non è stato trovato l'elemento cercato. N.B in questo caso q punta alla coda della lista che è NULL
    if(q == NULL) return 1;

    //Caso 2: è stato trovato l'elemento cercato, modifico il nodo in questione
    strcpy(q->product_elem->product_name , new_name);
    strcpy(q->product_elem->product_type , new_type);
    strcpy(q->product_elem->product_condition , new_condition);
    q->product_elem->product_buyprice = new_buy_price;
    return 0; //Success
}




/*
Funzione che cerca un singolo prodotto e ne printa il contenuto informativo

Prende in ingresso il puntatore alla testa della lista passato per copia e l'array di caratteri del nome del prodotto da ricercare

Restituisce 1 se il prodotto non è stato trovato
Restituisce 0 se il prodotto è stato trovato e ne stampa il contenuto informativo
*/
int search_and_print_product(products products_list_head, char key_name[]){

    product myproduct = search_product(products_list_head, key_name);
    int result = print_product(myproduct);
    if(result == 1) return 1; //myproduct è un puntatore a NULL, il prodotto non è stato trovato, resituisce 1
    return 0; //Success

}




/*
Funzione che stampa l'intera lista dei prodotti.

Prende in ingresso il puntatore alla testa della lista passato come copia 

Restituisce 1 se la lista è vuota
Restituisce 0 se va a buon fine e stampa i contenuti informativi di ciascun prodotto presente in ciascun nodo
*/
int print_products(products products_list_head){
    
    //Controlla se la lista è vuota
    if(products_list_head == NULL) return 1; 

    //Puntatore di appoggio per scorrere la lista
    products q = products_list_head;

    while(q != NULL){
        print_product(q->product_elem);
        printf("\n");
        q = q -> next;
    }

    return 0; //Success
}

