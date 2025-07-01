# CollectorsHub

**CollectorsHub** è un software companion per collezionisti interamente scritto in C. Permette la creazione del proprio utente tramite chiavi di accesso username - password e la creazione e gestione totale di collezioni personali. A ciascuna collezione sarà possibile aggiungere dei propri prodotti appartenenti alla collezione. 

## Caratteristiche principali

- Gestione multiutente con autenticazione (privilegi utente e admin)
- Possibilità di creare, modificare ed eliminare collezioni personali
- Gestione di prodotti all’interno delle collezioni, con dettagli (nome, descrizione, condizioni, prezzo)
- Interfaccia testuale intuitiva 
- Salvataggio dei dati su file per la persistenza tra sessioni
- Privilegi amministratore per la gestione avanzata degli utenti (cancellazione e promozione ad admin)

### Documentazione tecnica dettagliata

È possibile visualizzare una documentazione tecnica dettagliata dell'intero programma, con tutte le funzionalità dimostrate e spiegate nel dettaglio, al seguente documento di progetto:
[Documento_di_progetto_CandelaMarco_Collectorshub_1.0.docx](https://github.com/user-attachments/files/20854681/Documento_di_progetto_CandelaMarco_Collectorshub_1.0.docx)



## Compilazione (Ambienti Linux)

Per compilare il progetto è sufficiente seguire i seguenti passaggi:
- Clonare la repository github tramite il comando:
```sh
gh repo clone marcocandel9/Collectorshub
```
- eseguire da terminale, nella cartella principale del progetto:
```sh
make
```
(Nella cartella del progetto è presente uno script makefile che permette di compilare velocemente il programma su ambienti Linux).
Nel caso in cui il comando make non è eseguibile, è possibile installare il pacchetto tramite terminale con il seguente comando:
```sh
sudo apt-get install make
```

## Compilazione (Windows o sistemi con compilazione gcc)
In ambienti windows è possibile semplicemente utilizzare il comando per la compilazione:
```sh
gcc -g main.c session.c system_admin.c system.c product.c products.c collection.c collections.c user.c users.c ascii_graphics.c menu.c -o main
```
Il programma è stato testato e reso compatibile sia con ambienti Linux che Windows.

## Utilizzo

Dopo aver compilato il progetto, è sufficiente lanciare il programma dalla cartella principale tramite il comando
```sh
./Collectorshub
```

## Ricompilazione

Se si desidera cancellare l'eseguibile tramite un comando specifico da terminale, è possibile eseguire il seguente comando da terminale
```sh
make clean
```

## File di dati
Il programma salva tutte le informazioni in un file di testo (data.txt) che contiene utenti, collezioni e prodotti in formato leggibile e strutturato.Un esempio di struttura dati (file data.txt):
**NB: il programma si occupa in automatico di creare il file nel caso in cui non esista e di modificarlo durante il salvataggio dei dati, non deve essere modificando manualmente!**
```txt
#USER
NomeUtente
Password
Ruolo
##COLLECTION
NomeCollezione
Categoria
###PRODUCT
NomeProdotto
Descrizione
Condizioni
Prezzo
...
```

## Screenshots (UI DEMO)

**Schermata di login**
![Schermata di Login](https://github.com/user-attachments/assets/b66723d2-79d6-44db-904e-3a47af4d790b)

**Menu utente**
![image](https://github.com/user-attachments/assets/4e8907e7-a682-45f9-b112-53c85288e3a5)

**Panoramica utente** *(Esempio di collezioni e prodotti di un utente)*
![image](https://github.com/user-attachments/assets/fc85a818-5b83-41c9-a99e-f5bc45442713)

**Menu Collezioni**
![image](https://github.com/user-attachments/assets/e5d8e7c2-9600-4dcf-8520-d771c73e8453)

**Menu Prodotti**
![image](https://github.com/user-attachments/assets/122b88ec-4e62-4777-845e-381bae0cedea)

**Menu Admin**
![image](https://github.com/user-attachments/assets/04894ea0-5136-4f42-82dc-23c9df69a9c2)




