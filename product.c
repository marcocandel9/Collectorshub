#include "product.h"
//La direttiva #include "product.h" dice al preprocessore di inserire il contenuto del file product.h prima della compilazione.

/*
prende in ingresso un puntatore ad una struct product passato per riferimento, lo alloca dinamicamente nell'heap e lo popola
NB come parametro della funzione non passo un doppio puntatore perchè product è già definito in product.h come un puntatore, quindi 
in questo caso scrivendo product* sto passando il puntatore come riferimento (puntatore a puntatore o indirizzo del puntatore)

Restituisce:
    0 Se la creazione del nuovo prodotto va a buon fine
    1 In caso di errore di allocazione del nuovo nodo prodotto
*/
int create_product(product* new_product, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price){
    (*new_product) = (struct product*)malloc(sizeof(struct product));
    if (*new_product == NULL)
        return 1; //errore di allocazione del nuovo nodo prodotto

    //popolo il contenuto informativo di product 
    set_product_name(*new_product,new_name);
    set_product_condition(*new_product,new_condition);
    set_product_type(*new_product,new_type);
    set_product_buyprice(*new_product, new_buy_price);
    return 0; //success
}





/*Prende in ingresso il puntatore al puntatore di una struct product e ne libera il contenuto in memoria dall'heap

    Restituisce:
        0 Se tutto va a buon fine
        1 Se il puntatore passato in ingresso punta a NULL
*/
int delete_product(product* product_todelete){

    //Restituisce 1 se il puntatore al prodotto punta a NULL (prodotto non esistente o non valido)
    if ((*product_todelete)==NULL)
        return 1; 
    
    //libera la memoria nell'heap puntata dal puntatore
    free(*product_todelete);

    //Imposta il puntatore a NULL per rimuovere la condizione di dangling pointer (Puntatore ad un'area di memoria deferenziata e quindi non definita)
    *product_todelete=NULL;
    return 0; 
}




/*  FUNZIONI GETTER
    a.	 int get_product_name(product myproduct, char myproduct_name[MAX_STR_LEN])
    b.	int get_product_type(product myproduct, char myproduct_type[MAX_STR_LEN])
    c.	int get_product_condition(product myproduct, char myproduct_condition[MAX_STR_LEN])
    d.	int get_product_buyprice(product myproduct, float* myproduct_buyprice)
    Prendono in ingresso il puntatore alla struct prodotto e, rispettivamente, le prime 3 degli array di caratteri in cui verrà memorizzato il contenuto informativo del quale si vuole prelevarne il valore, e la quarta un puntatore a float
        Restituiscono:
            a)	1 se il puntatore a struct prodotto passato in ingresso punta a NULL (non inizializzato)
            b)	0 se il valore è stato letto correttamente

*/
int get_product_name(product myproduct, char myproduct_name[MAX_STR_LEN]){
    
    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(myproduct==NULL)
        return 1; 
    
    //accede al campo informativo della struct puntata dal puntatore myproduct e preleva il campo del nome
    strcpy(myproduct_name, myproduct->product_name);
    return 0; //success
}





int get_product_type(product myproduct, char myproduct_type[MAX_STR_LEN]){
    
    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(myproduct==NULL)
        return 1; 
    
    //accede al campo informativo della struct puntata dal puntatore myproduct e preleva il campo del tipo di prodotto
    strcpy(myproduct_type, myproduct->product_type);
    return 0; //success
}





int get_product_condition(product myproduct, char myproduct_condition[MAX_STR_LEN]){
    
    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(myproduct==NULL)
        return 1; 
    
    //accede al campo informativo della struct puntata dal puntatore myproduct e preleva il campo della condizione
    strcpy(myproduct_condition, myproduct->product_condition);
    return 0; //success
}





int get_product_buyprice(product myproduct, float* myproduct_buyprice){
    
    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if(myproduct==NULL)
        return 1;
        
    //accede al campo informativo della struct puntata dal puntatore myproduct e preleva il campo del prezzo d'acquisto
    *myproduct_buyprice = myproduct->product_buyprice;
    return 0; //success
}





/* FUNZIONI SETTER
a.	int set_product_name(product myproduct, char new_name[MAX_STR_LEN]);
b.	int set_product_type(product myproduct, char new_type[MAX_STR_LEN]);
c.	int set_product_condition(product myproduct, char new_condition[MAX_STR_LEN]);
d.	int set_product_buyprice(product myproduct, float new_buyprice);
    Prendono in ingresso il puntatore ad una struct prodotto, settano il nuovo contenuto informativo passato nelle variabili di appoggio richieste in ingresso (array di caratteri per le prime 3 e float per l’ultima).
    Restituiscono:
        a)	1 se il puntatore a struct prodotto passato in ingresso punta a NULL (non inizializzato)
        b)	0 se l’operazione è riuscita

*/
//riceve in ingresso il puntatore passato per copia e il contenuto informativo da aggiornare; ritorna 0 se success, 1 altrimenti
int set_product_name(product myproduct, char new_name[MAX_STR_LEN]){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if((myproduct) == NULL)
        return 1;
    
    //aggiorna il contenuto informativo 
    strcpy(myproduct->product_name, new_name);

    return 0; //success
}





int set_product_type(product myproduct, char new_type[MAX_STR_LEN]){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if((myproduct) == NULL)
        return 1;
    
    //aggiorna il contenuto informativo 
    strcpy(myproduct->product_type, new_type);

    return 0; //success
}





int set_product_condition(product myproduct, char new_condition[MAX_STR_LEN]){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if((myproduct) == NULL)
        return 1;
    
    //aggiorna il contenuto informativo 
    strcpy(myproduct->product_condition, new_condition);
    return 0; //success
}





/*
modifica il contenuto informativo del prodotto. Se la stringa passata come parametro è vuota o, nel caso del float prezzo di acquisto, riceve un valore considerato come “sentinella” cioè -1.0f, allora non modifica quel contenuto informativo
Prende in ingresso il puntatore passato come riferimento al prodotto, le stringhe del contenuto informativo del prodotto
    Restituisce:
        a)	1 se il puntatore a struct prodotto passato in ingresso punta a NULL (non inizializzato)
        b)	0 se la modifica avviene con esito positivo

*/
int modify_product(product* myproduct, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN], char new_condition[MAX_STR_LEN], float new_buy_price){

    // Controlla se il puntatore al prodotto è NULL
    if (*myproduct == NULL)
    return 1;  // Prodotto non esistente o non valido

    // Se new_name non è vuoto, modifica il nome del prodotto
    if (new_name[0] != '\0') 
        strcpy((*myproduct)->product_name, new_name);
    
    // Se new_type non è vuoto, modifica il tipo del prodotto
    if (new_type[0] != '\0') 
        strcpy((*myproduct)->product_type, new_type);
    
    // Se new_condition non è vuoto, modifica la condizione del prodotto
    if (new_condition[0] != '\0') 
        strcpy((*myproduct)->product_condition, new_condition);

    // Se new_buy_price è valido (diverso da un valore sentinella come -1.0f), modifica il prezzo d'acquisto
    if (new_buy_price != -1.0f)  // Supponiamo che -1.0f sia il valore sentinella
        (*myproduct)->product_buyprice = new_buy_price;

    return 0;  // Successo
}





//il float new_buyprice a differenza della funzione getter è passato come copia perchè non deve essere modificato 
int set_product_buyprice(product myproduct, float new_buyprice){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if((myproduct) == NULL)
        return 1;
    
    //Aggiorna il contenuto informativo 
    myproduct->product_buyprice = new_buyprice;

    return 0; //success
}

/*
Prende in ingresso il puntatore a struct prodotto, restituisce 1 se il puntatore al prodotto punta a NULL (prodotto non inizializzato), 
0 altrimenti (tutto va a buon fine) e stampa a schermo il contenuto informativo della struct prodotto 
(Nome, tipologia, condizioni, prezzo di acquisto).
*/
int print_product(product myproduct){

    //Controlla se il puntatore al prodotto è NULL, restituisce 1 se lo è (prodotto non esistente o non valido)
    if (myproduct == NULL) return 1;
    
    char product_name[MAX_STR_LEN];
    char product_type[MAX_STR_LEN];
    char product_condition[MAX_STR_LEN];
    float product_buyprice;

    get_product_name(myproduct, product_name);
    get_product_type(myproduct, product_type);
    get_product_condition(myproduct, product_condition);
    get_product_buyprice(myproduct, &product_buyprice);

    printf("%s, %s, %s, %.2f\n", product_name, product_type, product_condition, product_buyprice);
    return 0;
}



/*
Salva su file i campi informativi di un prodotto.
[ NOTA BENE: NON SI OCCUPA NÈ DI COLLEGARE IL PUNTATORE AL FILE CORRETTO, NÈ DI DEREFERENZIARE IL PUNTATORE, NÈ 
 DI INIZIALIZZARLO IN MODALITÀ APPEND. SPETTA AL CHIAMANTE PRINCIPALE GESTIRLI. ]
 Prevede una indentazione doppia per la scrittura delle informazioni dei prodotti
Parametri: 
    - fptr: puntatore a file passato in ingresso 
    - myproduct: puntatore a struct product
    - indentation_level: numero di tabulazioni da inserire prima di ogni campo del prodotto (massimo supportato: max_indentation = 5) (minimo == 0, non accetta numeri negativi)
Restituisce: 
    - 2: errore, inserimento di un livello di indentazione non supportato (MAGGIORE DI MAX_INDENTATION == 5 O MINORE DI 0 (NEGATIVO))
    - 1: errore, il puntatore a file o product è uguale a NULL
    - 0: se il file è stato scritto correttamente

ESEMPIO: (product_indentation_level = 1)
    {
    Nome prodotto
    Tipologia prodotto
    Condizioni prodotto
    Prezzo di acquisto prodotto
    }
*/
int save_product(FILE *fptr, product myproduct, int product_indentation_level){

    if(myproduct == NULL || fptr == NULL) return 1;

    //questa variabile indicherà il livello massimo di indentanzioni supportate dalla funzione. È possibile modificarlo per aumentare il numero max
    // di indentanzioni
    int const max_indentation = 5; 

    if(product_indentation_level > max_indentation || product_indentation_level < 0) return 2;
    char indentations_string[MAX_STR_LEN] = "";
    
    //Se voglio un livello di indentazione diverso da 0, devo aggiungere il numero corretto di tab
    if(product_indentation_level != 0){
        for(int i = 0; i < product_indentation_level; i++){
            strcat(indentations_string, "\t");
            }
    }

    char product_name[MAX_STR_LEN];
    char product_type[MAX_STR_LEN];
    char product_condition[MAX_STR_LEN];
    float product_buyprice;

    get_product_name(myproduct, product_name);
    get_product_type(myproduct, product_type);
    get_product_condition(myproduct, product_condition);
    get_product_buyprice(myproduct, &product_buyprice);
    
    fprintf(fptr, "%s{\n",indentations_string);
    fprintf(fptr, "%s%s\n",indentations_string,product_name);
    fprintf(fptr, "%s%s\n",indentations_string,product_type);
    fprintf(fptr, "%s%s\n",indentations_string,product_condition);
    fprintf(fptr, "%s%.2f\n",indentations_string,product_buyprice);
    fprintf(fptr, "%s}\n",indentations_string);


    return 0;
}