//LISTA COLLEZIONI CON LOGICA DI ORDINAMENTO ALFABETICO IN BASE AL NOME DELLA COLLEZIONE. NON ACCETTA DUPLICATI.

#include "collections.h"





/*
Crea una nuova lista collezioni VUOTA
Prende in ingresso il puntatore alla testa della lista collezioni (puntatore di tipo struct collections) e lo inizializza a NULL
Restituisce 0 
*/
int create_collections_list(collections* collections_list_head){
    *(collections_list_head) = NULL;
    return 0;
}





/*
Inserisce una nuova collezione alla lista collezioni ORDINATA. Implementa l'inserimento anche di una prima collezione a partire da una lista vuota

Prende in ingresso il puntatore alla testa della lista collezioni, l'array di caratteri per il nome della nuova collezione e
l'array di caratteri per il tipo della nuova collezione

Restituisce:
- 1 In caso di errori di allocazione dinamica
- 2 In caso di inserimento di un duplicato (NON CONSENTITO)
- 0 Inserisce la nuova collezione con esito positivo
*/
int insert_collection(collections* collections_list_head, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]){

    //Alloco il nuovo nodo della lista collezioni
    collections new_collections_node = (collections)malloc(sizeof(struct collections)); 
        if(new_collections_node == NULL) return 1; //Restituisce 1 in caso di errori di allocazione

    //Popolo il nuovo nodo della lista collezioni
    int result = create_collection(&(new_collections_node->collection_elem), new_name, new_type);

    //errore di allocazione del nuovo puntatore alla collezione
    if(result == 1){
        free(new_collections_node); //Dealloco il nodo collezione
        return 1; //Errore di allocazione del nuovo nodo collezione, restituisco 1
    } 

    //Altrimenti result = 0, ho allocato il nuovo nodo e la nuova collezione all'interno del nodo, posso inserirlo nella lista collezioni


    //Inserimento in testa (la collezione da inserire è la prima della lista collezioni, la lista delle collezioni è dunque VUOTA)
    if(*collections_list_head == NULL){
        *collections_list_head = new_collections_node; //La testa adesso punterà al nuovo nodo
        new_collections_node->next = NULL;             //Il nuovo nodo sarà anche la coda della lista, punterà a NULL
        return 0; //Success
    }

    //Inserimento intermedio o alpiù in coda, devo scorrere la lista
    //Preparo i puntatori di appoggio per lo scorrimento della lista e un'array di caratteri per il confronto del nome collezione di ogni singolo nodo
    struct collections* r = NULL;                       //Puntatore di appoggio al nodo precedente a quello di osservazione
    struct collections* q = *collections_list_head;     //Puntatore di appoggio al nodo di osservazione
    char collection_name[MAX_STR_LEN];                  //Array di caratteri di appoggio per l'osservazione del nome della collezione di ogni nodo collezione

    //Scorro la lista finchè non raggiungo la coda (r punterà all'ultimo nodo, q a NULL quando ciò accadrà), oppure finchè non trovo un MATCH
    while(q != NULL){
        
        //strcmp restituisce:
        // - un valore negativo se new_name è alfabeticamente inferiore al nome della collezione -> devo interrompere lo scorrimento e inserire il nodo
        // - 0 se new_name == product_name
        // - un valore positivo se new_name è alfabeticamente superiore al nome della collezione -> devo continuare a scorrere la lista
        get_collection_name(q->collection_elem,collection_name);
        int caso = strcmp(new_name,collection_name);

        //In caso di duplicati libera il nuovo noto e restituisce 2 (DUPLICATI NON CONSENTITI)
        if(caso == 0){
            free(new_collections_node);
            return 2; //Duplicato
        }

        //Trovata la corretta posizione di inserimento ordinato, esco dal ciclo while
        if(caso < 0){
            break; 
        }

        //Incremento i puntatori di appoggio
        r = q;
        q = q -> next;
    }
    
    //Inserisco il nuovo nodo nella posizione trovata
    //Caso 1:  (inserimento TESTA) (non mi sono mosso dal primo elemento, r punta a NULL e q punta al primo nodo della lista) (Devo aggiornare la testa)
    if(r == NULL) {
        new_collections_node -> next = (*collections_list_head);
        (*collections_list_head) = new_collections_node; //Aggiorno la testa
    
    } else {     //Caso 2: Inserimento intermedio o alpiù in coda (N.B se inserisco in coda q == NULL)
        r->next = new_collections_node;
        new_collections_node -> next = q;
    }

    return 0; //Success
}





/*
Cerca una collezione e ne modifica nome e tipo. Se gli array di caratteri passati in ingresso sono vuoti, allora non modifica quel campo informativo

Restituisce:
- 1 Se la lista collezioni è vuota o non valida (Nessuna collezione da modificare)
- 2 Se non è stata trovata una corrispondenza con il nome della collezione passato in ingresso
- 0 Se tutto va a buon fine

*/
int search_and_modify_collection(collections collections_list_head, char key_name[MAX_STR_LEN], char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]){

    //Puntatore alla testa della lista collezioni uguale a NULL -> Lista vuota , restitusisce 1
    if(collections_list_head==NULL) return 1;

    //Inizializzo le variabili di appoggio utili alla ricerca ordinata nella lista e alla modifica della collezione
    collections q = collections_list_head; //Puntatore di appoggio per lo scorrimento della lista 
    char collection_name[MAX_STR_LEN];
    int found;

    //Ricerco e modifico l'elemento
    while(q != NULL){
        get_collection_name(q->collection_elem,collection_name);

        //strcmp restituisce:
        // - un valore negativo se key_name è alfabeticamente inferiore al nome della collezione-> devo interrompere la ricerca
        // - 0 se key_name == product_name
        // - un valore positivo se key_name è alfabeticamente superiore al nome della collezione -> devo continuare a cercare
        found = strcmp(key_name,collection_name);

        if(found == 0) break; //Name match, interrompo la ricerca

        if(found < 0) return 2; //Non è stata trovata una corrispondenza nella lista, restituisci 2 (COLLEZIONE NOT FOUND)

        q = q -> next;
    }

    //Caso 1: q ha raggiunto la coda della lista e non è stato trovata la collezione cercata. Restituisci 2
    if(q==NULL) return 2;

    //Caso 2: è stata trovata la collezione cercata, modifico il nodo in questione utilizzando la funzione modify_collection di collection_h
    //N.B modify collection, se riceve stringhe vuote in ingresso, non modifica quel contenuto informativo della collezione
    int result = modify_collection((q->collection_elem),new_name, new_type);
    if(result == 1) return 3; //Se modify collection restituisce 0, success, altrimenti restituisce 3 (Errore modifica della collezione) collezione non esistente o non valida

    return 0; //Success
}





/*
Funzione che cerca una collezione sulla base del nome e la rimuove dalla lista
Prende in ingresso il puntatore alla testa della lista collezioni passato come riferimento e l'array di caratteri del nome della collezione da ricercare ed eliminare

Restituisce:
    0 Se tutto va a buon fine
    1 Se la lista collezioni è vuota o non valida
    2 Se non è stata trovata una corrispondenza
    
- 
*/
int remove_collection(collections* collections_list_head, char key_name[MAX_STR_LEN]){

    //Puntatore alla testa della lista collezioni uguale a NULL -> Lista vuota , restitusisce 1
    if(*collections_list_head == NULL) return 1;

    //Puntatori di appoggio per scorrere la lista ordinata
    collections r = NULL;
    collections q = *collections_list_head;
    char collection_name[MAX_STR_LEN];

    while(q != NULL){
        get_collection_name(q->collection_elem,collection_name);

        //strcmp restituisce:
        // - un valore negativo se key_name è alfabeticamente inferiore al nome della collezione-> devo interrompere la ricerca
        // - 0 se key_name == collection_name
        // - un valore positivo se key_name è alfabeticamente superiore al nome della collezione -> devo continuare a cercare
        int is_equal = strcmp(key_name,collection_name);

        if(is_equal==0) break; //Collezione da eliminare trovata interrompo la ricerca

        if(is_equal < 0) return 2; //Collezione non trovata, interrompo la ricerca e restituisco 2

        //Incremento i puntatori
        r = q;
        q = q->next;
    }

    //Se lo scorrimento è giunto fino alla fine della lista, non è stato trovato nessuna collezione corrispondente, restituisco 1
    if(q == NULL) return 1;

    //Caso 1: cancellazione testa, traslo la testa della lista un nodo avanti
    if(r == NULL){
        *collections_list_head = (*collections_list_head) -> next;

        //dealloco il nodo contenente la collezione che desidero eliminare

        //Richiamo la funzione delete collection per deallocare la collezione allocata dinamicamente
        delete_collection(&(q->collection_elem)); //Dealloca la memoria della struct collection
        free(q); //Dealloco la memoria della struttura collections 
    } else {  //Caso 2 cancellazione intermedia o alpiù in coda
         
        (r -> next) = (q -> next);
        delete_collection(&(q->collection_elem)); 
        free(q);
    }

    return 0; //Success
}





/*
Stampa il nome ed il tipo delle collezioni della lista collezioni

Prende in ingresso il puntatore alla testa della lista passato come riferimento

Restituisce:
- 1 In casi di lista collezioni non valida o vuota
- 0 In caso di Successo
*/
int print_collections(collections collections_list_head){

     //Puntatore alla testa della lista collezioni uguale a NULL -> Lista vuota , restitusisce 1
    if(collections_list_head == NULL) return 1;

    //Altrimenti stampa la lista
    while(collections_list_head != NULL){
        print_collection((collections_list_head)->collection_elem);
        collections_list_head = collections_list_head->next;
    }
    return 0; //Success, lista printata
}




/*
Libera completamente la lista delle collezioni

Prende in ingresso li puntatore alla lista delle collezioni passato per riferimento (che viene inizializzato a NULL dopo lo svuotamento)

Restituisce:
- 1 In caso di lista vuota
- 0 In caso di success
*/
int free_collections(collections* collections_list_head){

    //Puntatore alla testa della lista collezioni uguale a NULL -> Lista vuota , restitusisce 1
    if(*collections_list_head == NULL) return 1;

    //Puntatori di appoggio per scorrere la lista
    collections r = NULL;
    collections q = *collections_list_head;

    while(q != NULL){
        r = q;
        q = q -> next;
        delete_collection(&(r->collection_elem));
        free(r);
    }

    //Azzero il puntatore alla lista
    *collections_list_head = NULL;

    return 0; //Success
}





/*
Inserisce la lista dei prodotti alla desiderata collezione della lista collezioni con INSERIMENTO ORDINATO ALFABETICO sulla base del NOME DELLA COLLEZIONE

Prende in ingresso il puntatore alla testa della lista collezioni passato per riferimento, il nome della collezione da ricercare a cui inserire la lista prodotti, e il 
puntatore alla testa della lista prodotti da inserire

Restituisce:
     1 Se la lista delle collezioni è VUOTA
     2 Se non è stata trovata la collezione ricercata
     0 Se tutto va a buon fine
     */
int insert_sorted_products_list(collections* collections_list_head, char key_name[MAX_STR_LEN], products* products_list_head){

    //Puntatore alla testa della lista collezioni uguale a NULL -> Lista vuota, restituisce 1
    if(*collections_list_head == NULL) return 1;

    //Puntatore di appoggio per scorrere la lista collezioni
    collections q = *collections_list_head;
    char collection_name[MAX_STR_LEN];

    //Ricerca ordinata sulla base del nome della collezione (array di caratteri key_name)
    while(q != NULL){
        get_collection_name(q->collection_elem,collection_name);

        //strcmp restituisce:
        // - un valore negativo se key_name è alfabeticamente inferiore al nome della collezione-> devo interrompere la ricerca
        // - 0 se key_name == collection_name
        // - un valore positivo se key_name è alfabeticamente superiore al nome della collezione -> devo continuare a cercare
        int is_equal = strcmp(key_name,collection_name);

        if(is_equal == 0) break; //Corrispondenza trovata, esco dal ciclo while di ricerca ordinata

        if(is_equal < 0) return 2; //Collezione non trovata, restituisci 2
        
        //Incremento il puntatore di appoggio
        q = q->next;
    }

    //se q == NULL, lo scorrimento ha giunto la coda della lista senza trovare una corrispondenza, restituisco 2 (Collezione cercata non trovata nella lista)
    if(q == NULL) return 2;

    insert_products_list(&(q->collection_elem),products_list_head);
    return 0; //Success
}





/*
Ricerca una collezione nella lista collezioni sulla base del nome della collezione e ne restituisce il puntatore

    Restituisce:
        1 Se la lista delle collezioni è VUOTA (found collection punterà a NULL)
        2 Se non è stata trovata la collezione ricercata (found collection punterà a NULL)
        0 Se è stata trovata una corrispondenza e restituisce il puntatore a quella collezione
*/
int search_collection(collections collections_list_head, char key_name[MAX_STR_LEN], collection* found_collection){

    //Puntatore alla testa della lista collezioni uguale a NULL -> Lista vuota, restituisce 1
    if(collections_list_head == NULL) return 1;

    //Puntatore di appoggio per scorrere la lista collezioni
    collections q = collections_list_head;
    char collection_name[MAX_STR_LEN];

    //Ricerca ordinata sulla base del nome della collezione (array di caratteri key_name)
    while(q != NULL){
        get_collection_name(q->collection_elem,collection_name);

        //strcmp restituisce:
        // - un valore negativo se key_name è alfabeticamente inferiore al nome della collezione-> devo interrompere la ricerca
        // - 0 se key_name == collection_name
        // - un valore positivo se key_name è alfabeticamente superiore al nome della collezione -> devo continuare a cercare
        int is_equal = strcmp(key_name,collection_name);

        if(is_equal == 0) break; //Corrispondenza trovata, esco dal ciclo while di ricerca ordinata

        if(is_equal < 0) return 2; //Collezione non trovata, restituisci 2
        
        //Incremento il puntatore di appoggio
        q = q->next;
    }

    //se q == NULL, lo scorrimento ha giunto la coda della lista senza trovare una corrispondenza, restituisco 2 (Collezione cercata non trovata nella lista)
    if(q == NULL) return 2;

    *found_collection = q->collection_elem;
    return 0;

}





/*
Ricerca una collezione nella lista collezioni sulla base del nome della collezione.a

    Restituisce:
        1 Se la lista delle collezioni è VUOTA
        2 Se non è stata trovata la collezione ricercata
        0 Se è stata trovata una corrispondenza
*/
int collection_exists(collections collections_list_head, char key_name[MAX_STR_LEN]){

    //Puntatore alla testa della lista collezioni uguale a NULL -> Lista vuota, restituisce 1
    if(collections_list_head == NULL) return 1;

    //Puntatore di appoggio per scorrere la lista collezioni
    collections q = collections_list_head;
    char collection_name[MAX_STR_LEN];

    //Ricerca ordinata sulla base del nome della collezione (array di caratteri key_name)
    while(q != NULL){
        get_collection_name(q->collection_elem,collection_name);

        //strcmp restituisce:
        // - un valore negativo se key_name è alfabeticamente inferiore al nome della collezione-> devo interrompere la ricerca
        // - 0 se key_name == collection_name
        // - un valore positivo se key_name è alfabeticamente superiore al nome della collezione -> devo continuare a cercare
        int is_equal = strcmp(key_name,collection_name);

        if(is_equal == 0) break; //Corrispondenza trovata, esco dal ciclo while di ricerca ordinata

        if(is_equal < 0) return 2; //Collezione non trovata, restituisci 2
        
        //Incremento il puntatore di appoggio
        q = q->next;
    }

    //se q == NULL, lo scorrimento ha giunto la coda della lista senza trovare una corrispondenza, restituisco 2 (Collezione cercata non trovata nella lista)
    if(q == NULL) return 2;

    return 0;

}




/*
Scorre la lista delle collezioni e per ciascun elemento ne salva il contenuto informativo in un file, incapsulando anche le funzioni di salvataggio delle singole collezioni (e quindi dei prodotti)
[ NOTA BENE: NON SI OCCUPA NÈ DI COLLEGARE IL PUNTATORE AL FILE CORRETTO, NÈ DI DEREFERENZIARE IL PUNTATORE, NÈ 
 DI INIZIALIZZARLO IN MODALITÀ APPEND. SPETTA AL CHIAMANTE PRINCIPALE GESTIRLI. ]

    Parametri:
        - fptr: puntatore a file in cui scrivere
        - products_list_head: puntatore alla testa della lista dei prodotti
    Restituisce: 
        - 1: In caso di puntatore a file uguale a null
        - 0: In caso di scrittura avvenuta correttamente (Se la lista è vuota, non scrive semplicemente nulla)

ESEMPIO: 

##Collection
Giochi PS1
Videogiochi
###Product
Silent Hill 2, PAL ITA, Nuovo, 29.99 
###Product
Silent Hill 3, PAL ITA, Nuovo, 29.99 
##Collection
Giochi PS2
Videogiochi
[...]

*/
int save_collections(FILE *fptr, collections collections_list_head){

    if(fptr == NULL) return 1;

    while(collections_list_head != NULL){
        int result = save_collection(fptr, collections_list_head->collection_elem);
        if(result == 1) return 1;
        collections_list_head = collections_list_head->next;
    }

    return 0;


}




/*
Legge e carica le collezioni da file e gerarchicamente anche i prodotti, se esistenti, a ciascuna collezione trovata
La funzione utilizza `read_collection` per leggere i dati di ciascuna collezione e `load_products` per caricarne i prodotti associati. 
    Gestisce il passaggio tra tag, uscendo automaticamente in caso di tag superiore (es. `#USER`).

    Parametri:
        - FILE *fptr: puntatore a file già inizializzato e posizionato.
        - collections *collections_list: puntatore alla lista di collezioni (passato per riferimento).
        - char next_line[MAX_STR_LEN]: array di caratteri che conterrà l'eventuale tag successivo (es. `#USER`) non relativo a collezioni o prodotti, per consentire il parsing di livello superiore.

    Valori di ritorno:
        - 1: errore critico (fptr NULL o fallimento ftell/fgets).
        - XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - 3: EOF raggiunto.
        - 4: errore di allocazione memoria durante l'inserimento della collezione o dei prodotti.
        - 5: inserimento duplicato (dato corrotto).
        - 6: Allocazione con effetti inaspettati, problema di allocazione  
        - 7: tag `#USER` incontrato (fine delle collezioni per un dato utente, `next_line` conterrà il tag e il puntatore a file sarà correttamente posizionato).
        - 8: Valore di ritorno di debug: flusso invalido, incontro un tag prodotto prima di aver letto almeno un tag collezione

    Note:
        - In caso di errore in `load_products`, la funzione interrompe l’inserimento e propaga il codice errore.
        - Il valore `next_line` viene aggiornato ogni volta che un tag non atteso viene incontrato
        - La funzione può gestire correttamente più collezioni in sequenza
*/
int load_collections(FILE *fptr, collections* collections_list, char next_line[MAX_STR_LEN]){

    if (fptr == NULL) return 1;

    char coll_name[MAX_STR_LEN];
    char coll_type[MAX_STR_LEN];
    collection new_coll = NULL;

    while (1){ 
        int read_result = read_collection(fptr, coll_name, coll_type, next_line);
        switch(read_result){

            /*caso 1: * fptr == NULL || ftell fallisce  (errore critico)*/
            case 1: return 1;   

            /*caso 2: tag diverso da collezione trovato -> se il tag è utente, esco dalla funzione, se è prodotto, carico i prodotti associati------------------------------*/
            case 2:                                                                                     
                if(strcmp(next_line, "#USER") == 0) return 7;                                           /*tag incontrato == #USER -> esco dalla funzione -------------------*/
                if(new_coll == NULL) return 8;                                                          /*flusso invalido, incontro un tag prodotto prima di aver letto almeno un tag collezione*/
                int prod_load_result = load_products(fptr,&(new_coll->products_list_head),next_line);   /*tag incontrato == ###PRODUCT -> carico i prodotti ----------------*/


                switch(prod_load_result){
                    case 1: return 1;       /* fptr == NULL || ftell fallisce  (errore critico)*/
                    case 2: 
                        if(strcmp(next_line, "##COLLECTION") == 0) continue;    /*tag collezione incontrato dopo aver caricato i prodotti -> carico nuovamente la collezione*/
                        if(strcmp(next_line, "#USER") == 0) return 7;           /*tag utente incontrato dopo aver caricato i prodotti -> esco dalla funzione ---------------*/
                    case 3: return 3;                                           /* Ho raggiunto l'EOF */
                    case 4: return 4;                                           /*  Allocazione memoria fallita  */  
                    case 5: return 5;                                           /*  Inserimento duplicato (impossibile, dati corrotti )*/
                    default: continue;                                          /*  default difensivo, non dovrebbe accadere*/

                }

            /*caso 3: Ho raggiunto l'EOF */
            case 3: return 3;
 
            /*caso 4: *Tag collezione incontrato -> carico la collezione e ne prendo il puntatore nel caso in cui ci siano prodotti da caricarci dentro in seguito ------------------*/
            default:
		{
                int ins_result = insert_collection(collections_list, coll_name, coll_type);
                switch (ins_result){
                    case 1: return 4;     /*  Allocazione memoria fallita  */
                    case 2: return 5;     /*  Inserimento duplicato (impossibile, dati corrotti )*/
                    default: break;
		}
            }

                int search_result = search_collection(*collections_list, coll_name, &(new_coll));
                switch(search_result){
                    case 1: return 6;    /*  Allocazione con effetti inaspettati, problema di allocazione  */
                    case 2: return 6;    /*  Allocazione con effetti inaspettati, problema di allocazione  */
                    default: continue;
                }
        }
    }    
    // Questo punto non dovrebbe mai essere raggiunto
    return -1;
}




