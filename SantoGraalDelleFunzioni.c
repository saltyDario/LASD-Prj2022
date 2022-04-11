
typedef struct Nodo{
    char str[20];
    int roba;
    int dato;
    struct Nodo *next;
}Nodo;

Nodo *newNode(int dato, char* str){
    //funzione che effettua la creazione del nodo con all'interno le variabili
    Nodo *tmp = NULL;
    tmp = (Nodo*)malloc(sizeof(Nodo));
    if(tmp == NULL){
        return NULL;
    }
    else{
        strcpy(tmp -> nameOrg, azienda);
        tmp -> workers = dipendenti;
        tmp -> departments = dipartimenti;
        tmp -> locations = sedi;
        tmp -> next = NULL;
        return tmp;                
    }
}

Nodo *insNodoCoda(Nodo *head, char *str){
    //semplice inserimento in coda che concatena i nodi
    Nodo* tmp = head;
    if(head == NULL){ 
        return newNode(azienda, dipendenti ,dipartimenti, sedi);
    }else{ 
        while(tmp -> next != NULL) tmp = tmp -> next;
            tmp -> next = newNode(azienda, dipendenti ,dipartimenti, sedi);
    }
    return head;
}

Nodo *letturaFile(Nodo *head){
    //legge da file cose
    char roba[99];
    int dati;

    FILE *fp;
    char fname[20] = "file.txt";
    fp = fopen(fname, "r");

	while (!feof(fp)){
        fscanf(fp, "%s %d\n", roba, &dati);
        head = insNodoCoda(head, roba, dati);
    }

    fclose(fp);
    return head;
}

Nodo *letturaFile(Nodo *head, int numero){
    //legge da file i numeri scritti in caratteri
    char parola[99];
    int precedente = 0;
    int tot;
    FILE *fp;
    char fname[20] = "file.txt";
    fp = fopen(fname, "r");

    fscanf(fp, "%s", parola);
    while (!feof(fp)){
        while (strcmp(parola, "stop") != 0)
        {
            head = insNodoCoda(head, tot);
        }
    }
    return head;
}

void printList(Nodo *head){
    //print dei nodi
    Nodo *tmp = head;
    while(tmp != NULL){
        printf(" %s", tmp -> nameOrg);
        printf(" %d %d\n", tmp ->dato, tmp->roba);
        tmp = tmp -> next;
    }
}

Nodo *deleteNode(Nodo *head){
    //funzione che elimina determinati nodi su condizione

    Nodo *tmp = head, *del = NULL;
    Nodo *prec= NULL;
    while(tmp != NULL) {
        if (head->roba > 69420) {
            del = head;
            head = head->next;
            free(del);
            tmp=head;
        }
        else if(tmp->roba >69420){
            del = tmp;
            prec->next = tmp ->next;
            tmp = tmp ->next;
            free(del);
            continue;
        }
        prec = tmp;
        tmp = tmp->next;
    }
        return head;
}

void printOnFile(Nodo *head){
    //scrive cose da una lista su un file
    FILE *fw;
    fw = fopen("risultati.txt", "w");

    while (head != NULL){
       fprintf(fw, "%s %d\n", head->cringe, head ->roba);
       head = head -> next;
    }
    
}

lista *inserisci_Lista(lista *testa) {
    FILE *fp = fopen("testo.txt", "r");
    char stringa[100];
    char author[LEN] = { 0 };
    char genre[LEN]={0};
    float prezzo;
    int copie;
    char bookName[LEN] = { 0 };
    lista *testa = NULL;

    while(fgets(stringa, 100, fp) != NULL) {
        sscanf(stringa, "%[^,], %[^,], %[^,],%f,%d", author, bookName, genre, &prezzo, &copie);
        for (int i = 0; bookName[i] != '\0'; i++) {
            bookName[i] = bookName[i + 1];
            if (bookName[i] == '"')
                bookName[i] = '\0';
        }
        testa = insCoda(testa, author, bookName, genre, prezzo, copie);
    }
    stampaLista(testa);

    fclose(fp);
    return testa;
}

int **alloca_mat(int **mat, int n, int m){
    //crea una matrice passandogli colonne e righe
    int i;

    mat = malloc(n * sizeof(int*));
    for(i = 0; i < n; i++)
        mat[i] = malloc (m *sizeof(int));
    return mat;
}

int **creaMatrice(int grandezza){
    //crea una matrice soltanto da una grandezza (quadrata)
    int **mat;
    
    mat = calloc(grandezza, sizeof(int));
    for(int i = 0; i < grandezza; i++) {
        mat[i] = calloc(grandezza, sizeof(int));
    }
    return mat;
}

int **RiempiMatriceDaFile (int **mat, int *n, int *m) {
    //riempie matrice a partire da un file
    FILE *fp = NULL;
    int i, j;
    fp = fopen("file.txt", "r");
    fscanf(fp, "%d %d", &i, &j);
    *n = i;
    *m = j;

    mat = alloca_mat(mat, i ,j);

    while (!feof(fp)) {
        for (i = 0; i < *n; i++)
            for (j = 0; j < *m; j++)
                fscanf(fp, "%d" , &mat[i][j]);
    }
    fclose(fp);
    return mat;
}

void stampaMat(int **mat, int n, int m){
    //printa la matrice partendo da colonne righe
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int **updateMat(lista *testa, int **mat, int n, int m){
    //sovrascrive una matrice da una lista
    lista* tmp = testa;
    while(tmp != NULL){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if(tmp ->valore == mat[i][j]){
                    tmp = tmp -> next;
                }else{
                    mat[i][j] = 0;
                }
            }
            
        }
    }
    return mat;
}

lista *freeLista (lista *testa){
    //free della lista
    lista *del = NULL;
    if(testa == NULL)
        return NULL;
    else{
        while(testa  != NULL){
            del = testa;
            testa = testa ->next;
            free(del);
        }
    }
    return testa;
}

lista *delDispari(lista *testa){
    //elimina varie tipologie di dati a partire da una lista
    lista *tmp = testa, *del = NULL;
    lista *prec= NULL;
    while(tmp != NULL) {
        if (testa->valore % 2 != 0) {
            del = testa;
            testa = testa->next;
            free(del);
            tmp = testa;
        }
        else if(tmp->valore % 2 != 0){
            del = tmp;
            prec->next = tmp ->next;
            tmp = tmp ->next;
            free(del);
            continue;
        }
        prec = tmp;
        tmp = tmp->next;
    }
    return testa;
}

void copiaFile(){
    //copia da un file ad un altro
    FILE *fp = NULL;
    FILE *appoggio = NULL;

    char stringa[50];
    int n;
    int i;

    fp = fopen("file.txt", "r");
    appoggio = fopen("appoggio.txt", "w");
    while (!feof(fp)){
        fgets(stringa, 50, fp);
        n = strlen(stringa);
        for (i = 0; i < n; i++){
            if (stringa[i] == '#'){
                stringa[i] = '\0';
            }
            
        }
        fprintf(appoggio, "%s", stringa);
    }
    fclose(fp);
    fclose(appoggio);
}

void bubbleSort(Nums* head){
    //bubble sort di una lista
    int swapped;
    Nums *ptr1;
    Nums *lptr = NULL;
  
    if (head == NULL)
        return;
  
    do
    {
        swapped = 0;
        ptr1 = head;
  
        while (ptr1->next != lptr)
        {
            if (ptr1 -> number > ptr1 -> next -> number)
            { 
                swap(ptr1, ptr1 -> next);
                swapped = 1;
            }
            ptr1 = ptr1 -> next;
        }
        lptr = ptr1;
    }while (swapped);
}
void swap(Nums *a, Nums *b){
    int temp = a -> number;
    a -> number = b -> number;
    b -> number = temp;
}

Nums* concatenaListe(Nums* headA, Nums* headB){
    //concatenamento di una lista
    int n, *rito;
    rito = headA;

    while(headA -> next != NULL){
        headA = headA -> next;
    }
    headA -> next = headB;
    return rito;
}

Nodo* invertiLista(Nodo* headA, Nodo* headB){
    //inversione di una lista
    while(headA != NULL){
        headB = insCaratteriTesta(headB, headA -> carattere);
        headA = headA -> next;
    }
    return headB;
}

///////////////////////////////////////////////Stack\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct stack{
	int *dati;
	int stack_pointer; 
}stack;

void reset_stack (stack *stack){
	stack->stack_pointer = -1;
}

void alloca_vett(stack *stack,int dimensione){
	stack->dati=(int*)malloc(dimensione*sizeof(int));
}
																			
void push_stack (stack *stack,int numero){
	stack->stack_pointer++;
	stack->dati[stack->stack_pointer]=numero;
}

void print_stack (stack *stack){
	int dimensione = stack->stack_pointer;
	stack->stack_pointer = 0;
	while(stack->stack_pointer<=dimensione){
		printf("%d ",stack->dati[stack->stack_pointer]);
		stack->stack_pointer++;
	}
}

Nodo* ricercaPop(Nodo *stackHead, int num){
    //ricerca di un numero con stack con lista
    Nodo *tmp = stackHead;

    while(stackHead != NULL){
        if(stackHead -> numero == num){
            flag = 1;
            return stackHead;
        }else{
            tmp = stackHead;
            stackHead = stackHead -> next;
            free(tmp);
        }
    }
    return stackHead;
}

///////////////////////////////////////////////Ricorsione\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Nodo* ricercaDato(Nodo* head, int trovato){
    //ricera di un dato maniera ricorsiva
    if(head -> next == NULL){
        return head;
    }else if(head -> dato == trovato){
        return head;
        }else{
        return(ricercaDato(head = head -> next, trovato));
    }
}

int inserimento(int *p, int n){
    //inserimento in un vettore ricorsivamente
    if(n < 0){
        return 0;
    }else{
        printf("Inserisci un numero:");
        scanf("%d", &p[n]);
        return(inserimento(p,n - 1));
    }
}

void stampaCaratteri(Nodo* head){
    //stampa di una lista ricorsivamente
    if(head != NULL){
        printf("Dato: %d\n", head -> dato);
        return(stampaCaratteri(head = head -> next));
    }
}


