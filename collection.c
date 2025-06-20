/*
@Brief
Contenuto informativo del nodo della lista collezioni. È composto da una struct collection, la quale avrà come contenuto 
informativo un array di caratteri (La cui lunghezza massima è definita dalla costante MAX_STR_LEN modificabile in product.c)
Impostato di base a 20 caratteri per il nome della collezione, e un altro array di caratteri di dim[MAX_STR_LEN] che descrive
la tipologia della collezione (es: Console, Videogiochi, Carte collezionabili, francobolli)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "collection.h"


/*
Crea una nuova collezione

Prende in ingresso un puntatore passato per riferimento ad una struct collection, l'array di caratteri del nome della collezione,
l'array di caratteri del  tipo di collezione

Restituisce 1 in caso di errore di allocazione dinamica
Restituisce 0 se tutto va a buon fine
*/
int create_collection(collection* new_collection, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]){
    (*new_collection) = (struct collection*)malloc(sizeof(struct collection));
    if (*new_collection == NULL)
        return 1; //errore di allocazione della nuova struct collection

    ///setter
    set_collection_name(*new_collection,new_name);
    set_collection_type(*new_collection,new_type);
    (*new_collection) -> products_list_head = NULL;

    return 0; //Success
}




/*
Setta un nuovo nome alla collezione

Prende in ingresso un puntatore passato per valore ad una struct collection e il nuovo nome della collezione

Restituisce 1 in caso di puntatore a NULL o non valido
Restituisce 0 se tutto va a buon fine
*/
int  set_collection_name(collection my_collection, char new_name[MAX_STR_LEN]){

    //Controlla se il puntatore alla collezione è NULL, restituisce 1 se lo è (collezione non esistente o non valida)
    if(my_collection == NULL) return 1; 

    //Setta il nome della collezione
    strcpy(my_collection->collection_name,new_name);
    
    //Success
    return 0; 
}





/*
Setta un nuovo tipo alla collezione

Prende in ingresso un puntatore ad una struct collection e il nuovo tipo della collezione

Restituisce 1 in caso di puntatore a NULL o non valido
Restituisce 0 se tutto va a buon fine
*/
int set_collection_type(collection my_collection, char new_type[MAX_STR_LEN]){

    //Controlla se il puntatore alla collezione è NULL, restituisce 1 se lo è (collezione non esistente o non valida)
    if(my_collection == NULL) return 1; 

    //Setta il tipo della collezione
    strcpy(my_collection->collection_type,new_type);
    
    //Success
    return 0; 
}





/*
Aggiunge una lista prodotti alla collezione 

Prende in ingresso il puntatore alla collezione passato per riferimento e il puntatore alla testa della lista prodotti passato per riferimento

Restituisce:
- 1 Se la collezione non è stata ancora creta (PUNTATORE A NULL)
- 0 Se l'inserimento va a buon fine
*/
int insert_products_list(collection* my_collection, products* new_products_list_head){

    // La collezione non è stata ancora creata, restituisci 1
    if((*my_collection) == NULL) return 1;

    // Aggancia la nuova lista prodotti (già creata altrove, anche vuota)
    (*my_collection)->products_list_head = *(new_products_list_head);

    return 0; // Success
}






/*
 Modifica il nome e il tipo della collezione. Se le stringhe passate come parametro di ingresso sono vuote, non modifica quel campo

 Prende in ingresso il puntatore alla collezione passato per riferimento e gli array di caratteri del nuovo nome e del nuovo tipo della collezione

 Restituisce:
 - 1 Se la collezione non è stata ancora creata (PUNTATORE A NULL)
 - 0 Se la modifica va a buon fine
*/
int modify_collection(collection my_collection, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]){
    
    // La collezione non è stata ancora creata o non è valida, restituisci 1
    if(my_collection == NULL) return 1;

    // Se new_name non è vuoto, modifica il nome della collezione
    if(new_name[0] != '\0')
        set_collection_name(my_collection, new_name);

    // Se new_type non è vuoto, modifica il tipo della collezione
    if(new_type[0] != '\0')
        set_collection_type(my_collection, new_type);
    
    return 0; //Success
}





/*
Ottiene il nome della collezione e lo passa all'array di caratteri my_name

Prende in ingresso la collezione e la stringa my_name

Restituisce:
- 1 Se la collezione non è stata ancora creta (PUNTATORE A NULL)
- 0 Se il passaggio va a buon fine
*/
int get_collection_name(collection my_collection, char my_name[MAX_STR_LEN]){
    
    // La collezione non è stata ancora creata o non è valida, restituisci 1
    if((my_collection) == NULL) return 1;

    //Copia il nome della collezione nell'array di caratteri my_name
    strcpy(my_name, my_collection->collection_name);
    
    return 0; //Success
}





/*
Ottiene il tipo della collezione e lo passa all'array di caratteri my_type

Prende in ingresso il puntatore alla collezione (passato per copia) e la stringa my_type

Restituisce:
- 1 Se la collezione non è stata ancora creta (PUNTATORE A NULL)
- 0 Se il passaggio va a buon fine
*/
int get_collection_type(collection my_collection, char my_type[MAX_STR_LEN]){
    
    // La collezione non è stata ancora creata o non è valida, restituisci 1
    if((my_collection) == NULL) return 1;

    //Copia il tipo della collezione nell'array di caratteri my_type
    strcpy(my_type, my_collection->collection_type);
    
    return 0; //Success
}




/*
Restituisce tramite il parametro in ingresso products_list, passato come riferimento, il puntatore
alla testa della lista dei prodotti associati alla collezione my_collection (anch'esso parametro)

Restituisce:
- 1: Collezione vuota
- 0: Restituzione avvenuta con successo. 
*/
int get_products_list(collection my_collection, products* products_list){
    if(my_collection == NULL) return 1; //Collezione invalida o vuota

    *products_list = my_collection->products_list_head;
    return 0;
}





/*
Elimina una collezione liberandone l'area di memoria riservata alla lista dei prodotti associata alla collezione e la struct collection stessa

Prende in ingresso il puntatore alla collezione passato come riferimento

Restituisce:
- 1 Se il puntatore alla collezione è NULL (Collezione non inizializzata o non valida)
- 0 Se tutto va a buon fine
*/
int delete_collection(collection* my_collection){

    //Se il puntatore alla struct collection punta ad 1, restituisce 1 (Collezione non inizializzata o non valida)
    if((*my_collection) == NULL) return 1;

    //Libera la memoria allocata per la lista prodotti associati alla collezione
    free_products(&((*my_collection)->products_list_head));
    free((*my_collection));

    //Imposta il puntatore a NULL per rimuovere la condizione di dangling pointer (Puntatore ad un'area di memoria deferenziata e quindi non definita)
    (*my_collection) = NULL;
    return 0; //Success
}





/*
Stampa su terminale nome e il tipo della collezione

Prende in ingresso il puntatore alla collezione (passato per copia)

Restituisce:
- 1 Se la collezione non è stata ancora creata (PUNTATORE A NULL)
- 0 e ne stampa il contenuto se tutto va a buon fine
*/
int print_collection(collection my_collection){
    
    // La collezione non è stata ancora creata o non è valida, restituisci 1
    if((my_collection) == NULL) return 1;

    char my_collection_name[MAX_STR_LEN];
    char my_collection_type[MAX_STR_LEN];

    //Passa agli array di caratteri nome e tipo il contenuto informativo della collezione (Nome e tipo)
    get_collection_name(my_collection,my_collection_name);
    get_collection_type(my_collection,my_collection_type);

    printf("%s, %s\n", my_collection_name, my_collection_type);
    return 0; //Success
}



//FUNZIONI WRAPPER CHE INCAPSULANO LE FUNZIONI DI PRODUCTS.H 

/*
Permette l'inserimento di un prodotto ad una collezione passata come parametro. Richiede come parametri in ingresso inoltre i contenuti informativi del prodotto. 
Effettua il controllo sui duplicati nella lista dei prodotti associata a user_collection. 
Restituisce: 
- 1: In caso di collezione non inizializzata(punta a null)
- 2: in caso di prodotto già esistente nella lista
- 3: Errore di allocazione dinamica
- 0: L'inserimento è andato a buoan fine
*/
int insert_collection_product(collection user_collection, char product_name[MAX_STR_LEN], char product_type[MAX_STR_LEN], char product_condition[MAX_STR_LEN], float product_buyprice){
    if(user_collection == NULL) return 1; //Collezione non inizializzata

    int exists = exist_sorted(user_collection->products_list_head, product_name);
    if(exists == 0) return 2; //Prodotto già esistente nella lista, non consente duplicati

    int result = insert_product(&(user_collection->products_list_head),product_name,product_type,product_condition,product_buyprice);
    if(result == 1) return 3; //Fatal error: errore di allocazione dinamica
    return 0; //altrimenti tutto è andato a buon fine.
}



/*
Permette la modifica di un prodotto ad una collezione passata come parametro. Richiede come parametri in ingresso inoltre i contenuti informativi del prodotto. 
Effettua il controllo sui duplicati nella lista dei prodotti associata a user_collection. 
Restituisce: 
- 1: In caso di collezione non inizializzata(== a null)
- 2: Prodotto non esistente nella lista
- 3: Lista inconsistente
- 4: Elemento non valido (stringhe o float non conformi all'aggiunta del prodotto)
- 0: La modifica è andata a buoan fine
*/
int modify_collection_product(collection user_collection, char key_product_name[MAX_STR_LEN], char new_product_name[MAX_STR_LEN], char new_product_type[MAX_STR_LEN], char new_product_condition[MAX_STR_LEN], float new_product_buyprice){
    if(user_collection == NULL) return 1; //Collezione non inizializzata

    int exists = exist_sorted(user_collection->products_list_head, key_product_name);
    if(exists != 0) return 2; //Prodotto non esistente nella lista

    int result = search_and_modify_product(&(user_collection->products_list_head),key_product_name,new_product_name,new_product_type,new_product_condition,new_product_buyprice);
    switch(result){
        case 1:
            return 3; //ERRORE 3: LISTA INCONSISTENTE: lista prodotti vuota (non dovrebbe accadere!)
        case 2:
            return 3; //ERRORE 3: LISTA INCONSISTENTE: lista prodotti vuota (non dovrebbe accadere!)
        case 3:
            return 4; //ERRORE 4: Elemento non valido
        default:
            return 0; //modifica avvenuta correttamente
    }
}



/*
Permette l'eliminazione di un prodotto da una collezione. Richiede in ingresso la collezione da cui si vuole eliminare il prodotto e il nome del prodotto da eliminare

Restituisce:
- 1: In caso di collezione non inizializzata(== a null)
- 2: Prodotto non esistente nella lista
- 3: Lista inconsistente
- 0: L'eliminazione e' andata a buon fine
*/
int delete_collection_product(collection user_collection, char key_product_name[MAX_STR_LEN]){
    
    if(user_collection == NULL) return 1; //Collezione non inizializzata

    int exists = exist_sorted(user_collection->products_list_head, key_product_name);
    if(exists != 0) return 2; //Prodotto non esistente nella lista

    int result = remove_product(&(user_collection->products_list_head),key_product_name);

    if(result == 1 || result == 2) return 3; //Errore critico: lista inconsistente (non dovrebbe accadere, controllo difensivo)

    return 0; //Successo
}



/*
Permette l'eliminazione di tutti i prodotti di una collezione. Richiede in ingresso la collezione da cui si vuole eliminare i prodotti

Restituisce:
- 1: In caso di collezione non inizializzata(== a null)
- 0: L'eliminazione e' andata a buon fine
*/
int delete_collection_products(collection user_collection){

    if(user_collection == NULL) return 1; //Collezione non inizializzata

    free_products(&(user_collection->products_list_head));
    return 0;
}


/*    
Salva su file una collezione della struttura dati, incapsulando anche il salvataggio della lista prodotti sottostante. 
[N.B: è compito del chiamante impostare il puntatore a file in modalità append e di chiuderlo dopo l'utilizzo. Se la lista prodotti
della collezione è vuota, non scriverà nulla tra le relative parentesi graffe]

Parametri: 
    - fptr: puntatore al file in cui scrivere i dati
    - my_collection: collezione di cui si vogliono salvare i dati

Restituisce: 
    - 1: puntatore a file == NULL o collezione == NULL
    - 0: salvataggio avvenuto con successo
*/
int save_collection(FILE *fptr, collection my_collection){

    if(fptr == NULL || my_collection == NULL) return 1;

    char collection_name[MAX_STR_LEN];
    char collection_type[MAX_STR_LEN];
    get_collection_name(my_collection,collection_name);
    get_collection_type(my_collection,collection_type);

    fprintf(fptr,"##COLLECTION\n");
    fprintf(fptr,"%s\n",collection_name);
    fprintf(fptr,"%s\n",collection_type);
    int result = save_products(fptr, my_collection->products_list_head);
    if(result == 1) return 1;

    return 0;
}



/*
Permette LA LETTURA dei campi informativi di una collezione da file. Al caricamento si occuperà invece la funzione load_collections di products.h. 
La funzione, durante il parsing del file, controlla che la prima stringa letta dal puntatore al file, passato come parametro,
sia la stringa di tag collezione (##COLLEZIONE). Se così non fosse, restituisce un errore e ripristina la posizione del puntatore prima
della chiamata alla funzione stessa. La funzione si aspetta dunque che il puntatore al file sia già posizionato al tag del collezione 
da caricare, inoltre è ruolo del chiamante deallocare il puntatore al file stesso. 
Dopo il successo, il cursore è posizionato sulla riga successiva all’ultima letta, quindi pronto per un eventuale nuovo tag (o EOF)

Parametri: 
    - fptr: puntatore a file (si presume sia già inizializzato e che punti alla posizione del file corretta da leggere del collezione(CIOÈ SUBITO PRIMA DEL TAG))
    - collection_name: array dei caratteri che conterrà il nome della collezione letta
    - collection_type: array dei caratteri che conterrà la tipologia della collezione
    - next_line: se la lettura fallisce (in caso di lettura di una newline con tag diverso da collezione) allora questo array di caratteri conterrà il nuovo tag per il confronto delle funzioni superiori
    
Valori di ritorno: 
    - 1: Puntatore al file == NULL (errore critico) , ftell fallisce (errore critico)
    - 2: Puntatore a file punta ad un'area del file che non corrisponde ad una collezione (LA PRIMA STRINGA CHE LEGGE NON È IL TAG COLLEZIONE 
    - 3: Ho raggiunto l'EOF
    - 0: Lettura avvenuta con successo. Adesso il puntatore a file punterà all'inizio della linea successiva a quella della collezione letto pronto per un eventuale nuovo tag (o EOF)
*/
int read_collection(FILE *fptr, char collection_name[MAX_STR_LEN], char collection_type[MAX_STR_LEN], char next_line[MAX_STR_LEN]){

    /*controlli iniziali ----------*/
    if(fptr == NULL) return 1;

    long init_pos = ftell(fptr);
    if(init_pos == -1L) return 1;

    /*tag----------------------------------*/
    char buf[MAX_STR_LEN];
    if(fgets(buf,MAX_STR_LEN,fptr) == NULL) return 3; //EOF
    buf[strcspn(buf, "\n")] = '\0';

    if(strcmp(buf,"##COLLECTION") != 0){
        strcpy(next_line,buf);          /* Prelevo il tag successivo */
        fseek(fptr,init_pos,SEEK_SET);
        return 2;                           
    }                                   /*tag diverso da collezione*/
 
    /*leggo i dati------------------------------*/
    if  (fgets(collection_name,MAX_STR_LEN,fptr) == NULL ||
        fgets(collection_type,MAX_STR_LEN,fptr) == NULL )
        return 1;                           /*errore critico di lettura del buffer*/
    
    /*rimuovo i caratteri di newline-------------*/
    collection_name[strcspn(collection_name,"\n")] = '\0';
    collection_type[strcspn(collection_type,"\n")] = '\0';

    return 0;
}


