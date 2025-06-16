#include "products.h"



/*
Inserisce un nuovo prodotto nella lista. Implementa anche l'inserimento del primo elemento di una lista precedentemente vuota. 
Prende in ingresso il puntatore passato come riferimento alla lista prodotti e il contenuto informativo del nuovo prodotto

Restituisce:
- 1 in caso di errori di allocazione memoria
- 2 in caso di inserimento di duplicato (DUPLICATI NON CONSENTITI)
- 0 Se inserisce il prodotto con esito positivo 
*/
int insert_product(products* products_list_head, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price){
    
    // Creo il nuovo nodo per il nuovo prodotto
    products new_products_node = (products)malloc(sizeof(struct products));
    if(new_products_node == NULL) return 1; // errore di allocazione
    
    // Popolo il nuovo nodo
    int result = create_product(&(new_products_node->product_elem), new_name, new_type, new_condition, new_buy_price);
    if(result == 1) {
        free(new_products_node);
        return 1; // errore nella creazione del prodotto
    }

    // Inserimento ordinato
    // Se la lista è vuota, inserisco in testa
    if(*products_list_head == NULL) {
        new_products_node->next = NULL;
        *products_list_head = new_products_node;
        return 0;
    }

    products r = NULL;
    products q = *products_list_head;
    char product_name[MAX_STR_LEN];

    // Itera fino a trovare il punto di inserimento (ordinamento crescente) (Duplicati NON CONSENTITI)
    while(q != NULL){
        get_product_name(q->product_elem, product_name);

        //strcmp restituisce:
        // - un valore negativo se new_name è alfabeticamente inferiore al nome del prodotto -> devo interrompere lo scorrimento e inserire il nodo
        // - 0 se new_name == product_name
        // - un valore positivo se new_name è alfabeticamente superiore al nome del prodotto -> devo continuare a scorrere la lista
        int caso = strcmp(new_name, product_name);


        // CONTROLLO DUPLICATI: IMPOSTATO SU NON CONSENTITI

        //se le stringhe sono equivalenti, ritorna 2! DUPLICATI NON CONSENTITI //È possibile CONSENTIRE I DUPLICATI RIMUOVENDO LE SEGUENTI 4 LINEE DI CODICE
        if(caso == 0){
            free(new_products_node);
            return 2;
        }

        //CONTROLLO DUPLICATI: IMPOSTATO SU NON CONSENTITI


        if(caso < 0) { // se new_name è "minore" alfabeticamente, interrompi lo scorrimento (N.B: r punta ancora a NULL nel caso in cui questa sia la prima iterazione)
             break;
        }
        r = q;
        q = q->next;
    }
    

    // Caso 1 inserimento: se r è NULL, significa inserimento in testa
    if(r == NULL){
        new_products_node->next = *products_list_head;
        *products_list_head = new_products_node;
    } else {  //Caso 2 inserimento: intermedio o al più in coda (Se è in coda, q == NULL!)
        r->next = new_products_node;
        new_products_node->next = q;
    }
    
    return 0;
}





/*
Effettua una ricerca ORDINATA alfabeticamente del prodotto sulla base del suo nome e lo rimuove dalla lista

Prende in ingresso: puntatore alla testa della lista passato per riferimento, array di caratteri del nome dell'elemento da ricercare ed eliminare

Restituisce:
- 0 in caso di Success
- 1 Se la lista prodotti è vuota o non valida
- 2 Se non è stato trovato l'elemento prodotto con il nome desiderato

NB Cancella solo sulla base del nome, se disattivo il controllo di evitamento dei duplicati nella funzione insert product non posso selezionare quale dei duplicati eliminare
*/
int remove_product(products* products_list_head, char key_name [MAX_STR_LEN]){

    //Lista vuota: Restituisce 1
    if(*products_list_head == NULL) return 1;

    //Puntatori di appoggio per scorrere la lista ordinata
    products r = NULL;
    products q = *products_list_head;
    char product_name[MAX_STR_LEN];

    while(q != NULL){
        get_product_name(q->product_elem, product_name);

        //strcmp restituisce:
        // - un valore negativo se key_name è alfabeticamente inferiore al nome del prodotto -> devo interrompere la ricerca
        // - 0 se key_name == product_name
        // - un valore positivo se key_name è alfabeticamente superiore al nome del prodotto -> devo continuare a cercare
        int is_equal = strcmp(key_name, product_name);
    
        if(is_equal == 0){
            break;
        }

        if(is_equal < 0) return 2; //Prodotto non trovato, interrompo la ricerca e restituisco 2

        //Incremento i puntatori    
        r = q;
        q = q->next;
    }

    // Se lo scorrimento è giunto fino alla fine della lista, non ho trovato nessun prodotto corrispondente, restituisco 1
    if(q == NULL) return 2;

    //Caso 1 : cancellazione testa, traslo la lista un nodo in avanti
    if(r==NULL){
        *(products_list_head) = (*products_list_head) -> next;

        //dealloco il nodo contenete il prodotto che si desidera eliminare

        //Richiamo la funzione delete product per deallocare il prodotto allocato dinamicamente
        delete_product(&(q->product_elem)); //Dealloca la memoria della struttura prodotto
        free(q); //Dealloca la memoria della struttura Products 

    } else { //Caso 2, cancellazione intermedia o al più in coda (Se è in coda, q == NULL!)
        ( r -> next ) = ( q -> next );
        delete_product(&(q->product_elem)); //Dealloca la memoria della struttura prodotto
        free(q); //Dealloca la memoria della struttura Products 
    }
    return 0; //Success
}





/*
Funzione che ricerca un elemento nella lista ORDINATA.

Prende in ingresso il puntatore alla testa della lista passato come copia, l'array di caratteri

Restituisce:
    0 se l'elemento esiste
    1 Se la lista passata è vuota
    2 Se non è stata trovata alcuna corrispondenza
*/
int exist_sorted(products products_list_head, char key_name[MAX_STR_LEN]){

    //Lista vuota: ritorno 1
    if(products_list_head == NULL) return 1;

    char product_name[MAX_STR_LEN];
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

    return 2; // non è stata trovata una corrispondenza
}





/*
Funzione che ricerca un elemento nella lista ORDINATA e ne restituisce un puntatore product del prodotto

Prende in ingresso il puntatore alla testa della lista passato come copia, l'array di caratteri del nome del prodotto ricercato

Restituisce il puntatore product al prodotto se l'elemento è trovato
Restituisce NULL se l'elemento non è stato trovato
*/

product search_product(products products_list_head, char key_name[MAX_STR_LEN]){

    char product_name[MAX_STR_LEN];
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
//N.B modify product, se riceve in ingresso  stringhe vuote o un valore di float pari a quello sentinella (-1.0f), non modifica quel contenuto del prodotto

Prende in ingresso il puntatore alla testa della lista passato per riferimento, il nome dell'elemento da modificare,
le variabili del contenuto informativo della Struct Prodotto

Restituisce:
- 1 Se la lista prodotti è vuota o non valida (Nessun prodotto da modificare)
- 2 Se non è stata trovata una corrispondenza con il nome del prodotto passato in ingresso
- 3 se l'elemento non è valido (errore nella modifica del prodotto)
- 0 Se tutto va a buon fine
*/
int search_and_modify_product(products* products_list_head, char key_name[MAX_STR_LEN], char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price){

    //Lista vuota: restituisce 1
    if(*products_list_head == NULL) return 1;

    //Puntatore di appoggio per scorrere la lista
    products q = *products_list_head;
    char product_name[MAX_STR_LEN];
    int found;

    //Ricerca e modifica dell'elemento
    while(q != NULL){
        get_product_name(q->product_elem,product_name);

        //strcmp restituisce:
        // - un valore negativo se key_name è alfabeticamente inferiore al nome del prodotto -> devo interrompere la ricerca
        // - 0 se key_name == product_name
        // - un valore positivo se key_name è alfabeticamente superiore al nome del prodotto -> devo continuare a cercare
        found = strcmp(key_name,product_name);

        if(found == 0) break; //Trovato, esci dal ciclo while

        if(found < 0) return 2; //Non è stata trovata una corrispondenza nella lista, Restituisci 2 (PRODUCT NOT FOUND)

        q = q -> next;
    }

    //Caso 1: non è stato trovato l'elemento cercato. N.B in questo caso q punta alla coda della lista che è NULL
    if(q == NULL) return 2;

    //Caso 2: è stato trovato l'elemento cercato, modifico il nodo in questione utilizzando la funzione modify_product di product.h
    //N.B modify product, se riceve in ingresso  stringhe vuote o un valore di float pari a quello sentinella (-1.0f), non modifica quel contenuto del prodotto
    int result = modify_product(&(q->product_elem), new_name, new_type, new_condition, new_buy_price);
    if (result == 1) return 3; //Se modify product restituisce 0, success, altrimenti restituisce 3 (Errore modifica del prodotto) prodotto non esistente o non valido
    
    return 0; //Success
}





/*
Funzione che cerca un singolo prodotto e ne printa il contenuto informativo

Prende in ingresso il puntatore alla testa della lista passato per copia e l'array di caratteri del nome del prodotto da ricercare

Restituisce:
- 1 se il prodotto non è stato trovato
- 0 se il prodotto è stato trovato e ne stampa il contenuto informativo
*/
int search_and_print_product(products products_list_head, char key_name[MAX_STR_LEN]){

    product myproduct = search_product(products_list_head, key_name);
    int result = print_product(myproduct);
    if(result == 1) return 1; //myproduct è un puntatore a NULL, il prodotto non è stato trovato, resituisce 1
    return 0; //Success

}





/*
Funzione che stampa l'intera lista dei prodotti.

Prende in ingresso il puntatore alla testa della lista passato come copia 

Restituisce:
- 1 se la lista è vuota
- 0 se va a buon fine e stampa il contenuto informativo di ciascun prodotto presente in ciascun nodo
*/
int print_products(products products_list_head){
    
    //Puntatore alla testa della lista == NULL -> Lista vuota, restituisce 1
    if(products_list_head == NULL) return 1; 

    //Puntatore di appoggio per scorrere la lista
    products q = products_list_head;

    while(q != NULL){
        print_product(q->product_elem);
        q = q -> next;
    }

    return 0; //Success
}





/*
Funzione che libera totalmente la lista prodotti

Prende in ingresso il puntatore alla testa della lista passato per riferimento (che viene inizializzato a NULL dopo lo svuotamento)

Restituisce:
- 1 Se la lista prodotti è vuota 
- 0 Se la liberazione della lista va a buon fine
*/
int free_products(products* products_list_head){

    //Puntatore alla testa della lista == NULL -> Lista vuota, restituisce 1
    if(*products_list_head == NULL) return 1;

    //Puntatore di appoggio per scorrere la lista
    products r = NULL;
    products q = *products_list_head;

    //Ciclo while che elimina (dealloca) ogni elemento struct prodotto di ciascun nodo della lista prodotti. 
    while(q != NULL){
        r = q;
        q = q -> next;
        delete_product(&(r->product_elem));  //Dealloca lo struct prodotto del nodo in questione
        free(r);                             //Dealloca lo struct products (l'intero nodo)
    } 

    *products_list_head = NULL; //azzero la testa della lista

    return 0; //Success

}



/*
Scorre la lista dei prodotti e per ciascun elemento ne salva il contenuto informativo in un file. 
[ NOTA BENE: NON SI OCCUPA NÈ DI COLLEGARE IL PUNTATORE AL FILE CORRETTO, NÈ DI DEREFERENZIARE IL PUNTATORE, NÈ 
 DI INIZIALIZZARLO IN MODALITÀ APPEND. SPETTA AL CHIAMANTE PRINCIPALE GESTIRLI. ]

    Parametri:
        - fptr: puntatore a file in cui scrivere
        - products_list_head: puntatore alla testa della lista dei prodotti
        - indentation_level: numero di tabulazioni da inserire prima di ogni campo del prodotto (massimo supportato: max_indentation = 5)
    Restituisce: 
        - 2: product_indentation_level ha un valore invalido (negativo o maggiore di quanto definito in save_product(default: 5))
        - 1: In caso di puntatore a file uguale a null
        - 0: In caso di scrittura avvenuta correttamente (anche la lista è vuota, non scrive semplicemente nulla)

ESEMPIO: (product_indentation_level = 1)
    {
    Nome prodotto
    Tipologia prodotto
    Condizioni prodotto
    Prezzo di acquisto prodotto
    }
    {
    Nome prodotto
    Tipologia prodotto
    Condizioni prodotto
    Prezzo di acquisto prodotto
    }
*/
int save_products(FILE *fptr, products products_list_head, int product_indentation_level){

    if(fptr == NULL) return 1;


    while(products_list_head != NULL){
        int result = save_product(fptr, products_list_head->product_elem, product_indentation_level);
        if(result == 1) return 1;
        if(result == 2) return 2;
        products_list_head = products_list_head -> next;
    }

    return 0;
}