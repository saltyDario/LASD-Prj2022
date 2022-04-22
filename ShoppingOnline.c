#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elemento{
    char nome[99];
    char taglie[99];
    int prezzo;
    struct Elemento *next;
}Elemento;

typedef struct Utente{
    char nome[99];
    int saldo;
    char tipo_ut[99];
}Utente;

typedef struct Attesa{
    char nome[99];
    char prodotto[99];
    char taglia[2];
    struct Attesa *next;
}Attesa;

void red(HANDLE hConsole){
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}

void green(HANDLE hConsole){
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}

void blue(HANDLE hConsole){
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}

void reset(HANDLE hConsole, WORD saved_attributes){
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

Attesa *waitListNode(char *nomeUt, char *tagliaSc, char *prodottoSc){
    
    Attesa *tmp = NULL;
    tmp = (Attesa*)malloc(sizeof(Attesa));
    if(tmp == NULL){
        return NULL;
    }
    else{
        strcpy(tmp -> nome, nomeUt);
        strcpy(tmp -> prodotto, prodottoSc);
        strcpy(tmp -> taglia, tagliaSc);
        tmp -> next = NULL;
        return tmp;                
    }
}

Attesa *insNodoCodaAttesa(Attesa *head, char *nome, char *selectedSize, int counter, Elemento *testa){
    //semplice inserimento in coda che concatena i nodi
    Attesa* tmp = head;
    Elemento* temp = testa;

    for(int i = 1; i < counter; i++){
        temp = temp -> next;
    }

    if(head == NULL){ 
        return waitListNode(nome, selectedSize, temp->nome);
    }else{ 
        while(tmp -> next != NULL) tmp = tmp -> next;
            tmp -> next = waitListNode(nome, selectedSize, temp->nome);
    }
    return head;
}

Elemento *AddCarrello(int counter, char *selectedSize, Elemento *head, Elemento *headCart, Utente *utente){
    
    Elemento *tmp = head;
    Elemento *new = NULL;
    char sceltaCoda[2];
    char *ret;

    for(int i = 1; i < counter; i++){
        tmp = tmp -> next;
    }

    ret = strstr(tmp->taglie, selectedSize);
    if(ret != NULL){
        if(headCart == NULL){
            Elemento *headCart = (Elemento*)malloc(sizeof(Elemento));
            memcpy(headCart, tmp, sizeof(headCart));
            headCart ->next = NULL;
            return headCart;
        }else{
            new = (Elemento*)malloc(sizeof(Elemento));
            memcpy(new, tmp, sizeof(new));
            new -> next = headCart;
            return headCart;
        }
    }else{
        printf("La taglia scelta non e' disponibile, vuoi metterti in coda per averla?\n");
        printf("Digita Y o N.\n");
        while(strcmp(sceltaCoda, "Y") != 0 && strcmp(sceltaCoda, "N") != 0){
            scanf("%s", sceltaCoda);
            printf("Digita Y o N.\n");
        }

        if(strcmp(sceltaCoda, "Y") == 0){
            return NULL;
        }
        /*else if(strcmp(sceltaCoda, "N") != 0){
            return NULL;
        }*/

    }

}

void printList(Elemento *head){
    //print dei nodi
    int counter = 1;
    char ch[99];
    Elemento *tmp = head;

    while(tmp != NULL){
        printf("%d]%s", counter, tmp ->nome);
        printf(" %d %s\n", tmp ->prezzo, tmp->taglie);
        counter++;
        tmp = tmp -> next;
    }
}

void printCart(Elemento *head){
    //print dei nodi
    Elemento *tmp = head;

    while(tmp != NULL){
        printf("%s\n", tmp ->nome);
        tmp = tmp -> next;
    }
}

Elemento *newNode(char *nome, int prezzo, char *taglie){
    //funzione che effettua la creazione del nodo con all'interno le variabili
    Elemento *tmp = NULL;
    tmp = (Elemento*)malloc(sizeof(Elemento));
    if(tmp == NULL){
        return NULL;
    }
    else{
        strcpy(tmp -> nome, nome);
        tmp -> prezzo = prezzo;
        tmp -> next = NULL;
        strcpy(tmp -> taglie, taglie);
        return tmp;                
    }
}

Elemento *insNodoCoda(Elemento *head, char *nome, int prezzo, char *taglie){
    //semplice inserimento in coda che concatena i nodi
    Elemento* tmp = head;
    if(head == NULL){ 
        return newNode(nome, prezzo, taglie);
    }else{ 
        while(tmp -> next != NULL) tmp = tmp -> next;
            tmp -> next = newNode(nome, prezzo, taglie);
    }
    return head;
}

Elemento *letturaFile(Elemento *head){
    //legge da file cose
    char nome[99];
    int prezzo;
    char taglie[99];

    FILE *fp;
    char fname[20] = "capi.txt";
    fp = fopen(fname, "r");

	while (!feof(fp)){
        fscanf(fp, "%s %d %s\n", nome, &prezzo, taglie);
        head = insNodoCoda(head, nome, prezzo, taglie);
    }

    fclose(fp);
    return head;
}

Elemento *scaricaProdotti(Elemento *head){
    head = letturaFile(head);
    return head;
}

void resetSaldo(Utente *utente){

    utente->saldo = 0;

    FILE *fp;
    char fileUtenti[20] = "utenti.txt";
    fp = fopen(fileUtenti, "r+");
    
    int saldoAttuale = 0;
    char tmpUT[99];
    char typeUT[99];

    int pos = 0;

    /*while(!feof(fp)){
        fscanf(fp, "%s %s %d\n", tmpUT, typeUT,  &saldoAttuale);
        //printf("\n%s %d %s\n", tmpUT, saldoAttuale, typeUT);
        if(strcmp(tmpUT, utente->nome) == 0){

            fseek(fp, pos, SEEK_SET);
            fprintf(fp, "%s %s %d", tmpUT, typeUT, utente->saldo);
            break;
        }
    }*/
}

int ricaricaSaldo(int ricarica, Utente *utente){

    FILE *fp;
    char fileUtenti[20] = "utenti.txt";
    fp = fopen(fileUtenti, "r+");

    //FILE *fp2;
    //char fileNew[20] = "utenti.txt";
    //fp2 = fopen(fileNew, "w");

    int check = 0;
    int pos = 0;

    int saldoAttuale = 0;
    char tmpUT[99];
    char typeUT[99];

    while(!feof(fp)){
        fscanf(fp, "%s %s %d\n", tmpUT, typeUT, &saldoAttuale);
        //printf("\n%s %d %s\n", tmpUT, saldoAttuale, typeUT);
        if(strcmp(tmpUT, utente->nome) == 0){
            saldoAttuale = utente->saldo + ricarica;
            utente->saldo = saldoAttuale;

            fseek(fp, pos, SEEK_SET);
            fprintf(fp, "%s %s %d\n", tmpUT, typeUT, saldoAttuale);
            
            check = 1;
            //printf("\n%d %s\n", saldoAttuale, tmpUT);
            break;
        }
    }

    return check;
}

Utente *LogIn(char *utente, char *password){
    int UTcheck = 0;
    char tmpUT[99];
    int cash = 0;
    char typeUt[99];

    int PWcheck = 0;
    char tmpPW[99];

    //char c;

    int counter = 1;
    
    Utente *tmp = NULL;

    FILE *fp;
    char fileUtenti[20] = "utenti.txt";
    char filePassword[20] = "passwords.txt";

    fp = fopen(fileUtenti, "r");
    while (!feof(fp)){
        fscanf(fp, "%s %s %d\n", tmpUT, typeUt, &cash);

        //printf("\n%s %s\n", utente, password);

        /*do {
            c = fgetc(fp);
        }while (c != '\n');*/

        if(strcmp(tmpUT, utente) == 0){
            UTcheck = 1;
            break;
        }else{
            counter = counter + 1;
        }
    }
    //printf("%d\n", counter);
    fclose(fp);

    fp = fopen(filePassword, "r");

    for(int i = 0; i < counter; i++){
        fscanf(fp, "%s\n", tmpPW);
    }    
    
    if(strcmp(tmpPW, password) == 0){
        PWcheck = 1;
    }

    fclose(fp);

    if(UTcheck == 1 && PWcheck == 1){

        tmp = (Utente*)malloc(sizeof(Utente));
        if(tmp == NULL){
            return NULL;
        }else{
            strcpy(tmp -> nome, utente);
            tmp -> saldo = cash;
            strcpy(tmp -> tipo_ut, typeUt);             
        }
    }

    //printf("\n%d %d\n", UTcheck, PWcheck);
    return tmp;
}

int Register(char *utente, char *password){
    int UTduplicate = 0;
    int check = 0;
    char tmpUT[] = "init";

    FILE *fpU;
    FILE *fpP;

    char fileUtenti[20] = "utenti.txt";
    char filePassword[20] = "passwords.txt";

    fpU = fopen(fileUtenti, "r");
    while (!feof(fpU)){
        fscanf(fpU, "%s\n", tmpUT);

        if(strcmp(tmpUT, utente) == 0){
            UTduplicate = 1;
            break;
        }
    }
    fclose(fpU);

    if(UTduplicate == 0){
        fpU = fopen(fileUtenti, "a");
        fpP = fopen(filePassword, "a");

        fprintf(fpU, "%s Utente 0\n", utente);
        fprintf(fpP, "%s\n", password);

        check = 1;

        fclose(fpU);
        fclose(fpP);
    }

    return check;
}

int main(int argc, char *argv[]){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //Attributi console
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes; 

    int choose;

    Utente *ut_log = NULL;
    Elemento *head = NULL;
    Elemento *headCart = NULL;

    Attesa *nodeAttesa = NULL;

    char utente[99];
    char pass[99];

    int checkL = 0;
    int checkR = 0;
    int check = 0;

    int menuChoice = 0;
    int choice;

    int chooseCart = -1;
    char selectedSize[3];

    int tmp;

    green(hConsole);
    printf("\t\tProgetto LASD Aprile 2022\n\t\t     Shopping Online\n\t\t  Dario Morace N86003778\n");
    reset(hConsole, saved_attributes);

    blue(hConsole);
    printf("Benvenuto, effettua il Login o la Registrazione per autenticarti.\n");
    printf("Menu:\n1]Login\n2]Registrazione\n3]Exit\n");
    reset(hConsole, saved_attributes);
    scanf("%d", &choose);

    while(choose != 1 && choose != 2 && choose != 3){  
    system("cls");    
    red(hConsole);
    printf("Scelta non corretta, riprova.\n");
    reset(hConsole, saved_attributes);
    blue(hConsole);
    printf("Menu:\n1]Login\n2]Registrazione\n3]Exit\n");
    reset(hConsole, saved_attributes);
    scanf("%d", &choose);
    }

    if(choose == 1){
        
        while(ut_log->nome == NULL){
            blue(hConsole);
            printf("Inserisci il tuo nome utente:\n");
            reset(hConsole, saved_attributes);
            scanf("%s", utente);

            blue(hConsole);
            printf("Inserisci la tua password:\n");
            reset(hConsole, saved_attributes);
            scanf("%s", pass);

            ut_log = LogIn(utente, pass);

            if(ut_log ->nome != NULL){
                system("cls");
                green(hConsole);
                printf("Login effettuato con successo!.\n");
                reset(hConsole, saved_attributes);

            }else{
                red(hConsole);
                printf("Le credenziali sono incorrette o non presenti. Se non lo hai fatto registrati.\n");
                reset(hConsole, saved_attributes);
            }
        }
    }
    else if(choose == 2){
        while(checkR == 0){
            blue(hConsole);
            printf("Inserisci un nome utente:\n");
            reset(hConsole, saved_attributes);
            scanf("%s", utente);

            blue(hConsole);
            printf("Inserisci una password:\n");
            reset(hConsole, saved_attributes);
            scanf("%s", pass);

            checkR = Register(utente, pass);

            if(checkR == 1){
                green(hConsole);
                printf("Registrazione effettuata con successo!.\n");
                reset(hConsole, saved_attributes);

                ut_log = LogIn(utente, pass);

                if(checkL == 1){
                    green(hConsole);
                    printf("Login effettuato con successo!.\n");
                    reset(hConsole, saved_attributes);
                }
            }else{
                red(hConsole);
                printf("Il nome inserito e' gia' stato preso!. Riprova.\n");
                reset(hConsole, saved_attributes);
            }
        }
    }
    else if(choose == 3){
        system("cls");
        blue(hConsole);
        printf("Alla prossima!.\n");
        reset(hConsole, saved_attributes);
        exit(1);
    }

    printf("Benvenuto nello Shop, %s.\n", utente);
    while(menuChoice != 4){

        blue(hConsole);
        printf("Menu:\n1]Visiona lo shop.\n2]Visiona carrello.\n3]Gestisci saldo.\n4]Exit\n");
        reset(hConsole, saved_attributes);
        scanf("%d", &menuChoice);
        switch (menuChoice)
        {
        case 1:
            system("cls");

            int pagina = 1;

            blue(hConsole);
            printf("Benvenuto nello store, ecco i prodotti disponibili.\n");
            head = scaricaProdotti(head);
            while(chooseCart != 0){
                printList(head);

                printf("Digita un numero per aggiungere un prodotto al carrello.(0 per uscire)\n");
                reset(hConsole, saved_attributes);
                scanf("%d", &chooseCart);

                if(chooseCart == 0){
                    continue;
                }

                printf("Digita una taglia per il prodotto selezionato (S - M - L - XL)\n");
                scanf("%s", selectedSize);

                headCart = AddCarrello(chooseCart, selectedSize, head, headCart, ut_log);
                if(headCart == NULL){
                    nodeAttesa = insNodoCodaAttesa(nodeAttesa, ut_log->nome, selectedSize, chooseCart, head);
                }
            }

            continue;
        case 2:
            if(headCart == NULL){
                printf("Il tuo carrello e' vuoto al momento.\n");
            }else{
                printCart(headCart);
                printf("Vuoi procedere con l'acquisto?.\n");
            }

            continue;
        case 3:
            system("cls");
            printf("Gestione saldo di %s. Digita una scelta.\n", ut_log -> nome);
            while(choice != 4){
                blue(hConsole);
                printf("Menu:\n1]Ricarica saldo.\n2]Visiona saldo.\n3]Scarica saldo.\n4]Go back\n");
                reset(hConsole, saved_attributes);
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    printf("Inserisci la quantita' da ricaricare.\n");
                    scanf("%d", &tmp);
                    check = ricaricaSaldo(tmp, ut_log);

                    if(check == 1){
                        system("cls");
                        green(hConsole);
                        printf("La ricarica di %d e' stata effettuata.\n", tmp);
                        printf("Nuovo saldo disponibile: %d\n", ut_log->saldo);
                        reset(hConsole, saved_attributes);
                        continue;
                    }else{
                        //boh
                        continue;
                    }
                case 2:
                    system("cls");
                    printf("%s hai a disposizione %d.\n", ut_log->nome, ut_log->saldo);
                    continue;
                case 3:
                    system("cls");
                    resetSaldo(ut_log);
                    printf("Il saldo a disposizione e' stato svuotato.\n");
                    continue;
                case 4:
                    menuChoice = 0;
                    system("cls");
                    continue;
                default:
                    printf("Questa scelta non esiste, riprova.\n");
                }
            }
            continue;
        case 4:
            system("cls");
            blue(hConsole);
            printf("Alla prossima!.\n");
            reset(hConsole, saved_attributes);
            exit(1);
        default:
            printf("Questa scelta non esiste, riprova.\n");
        }
    }
    
    
    getch();
    return 0;
}