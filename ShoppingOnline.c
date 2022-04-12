#include <stdio.h>
//#include <windows.h>
#include <stdlib.h>
#include <string.h>

/*void red(HANDLE hConsole){
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
}*/

int ricaricaSaldo(int ricarica, char *utente){

    FILE *fp;
    char fileUtenti[20] = "utenti.txt";
    fp = fopen(fileUtenti, "a+");

    int check = 0;

    int saldoAttuale = 0;
    char tmpUT[99];
    char typeUT[99];

    while(!feof(fp)){
        fscanf(fp, "%s %d %s\n", tmpUT, &saldoAttuale, typeUT);
        //printf("\n%s %d %s\n", tmpUT, saldoAttuale, typeUT);
        if(strcmp(tmpUT, utente) == 0){
            saldoAttuale = saldoAttuale + ricarica;
            fprintf("%s %d %s", tmpUT, saldoAttuale, typeUT);
            check = 1;
            printf("%d %s", saldoAttuale, tmpUT);
            break;
        }
    }

    return check;
}

int LogIn(char *utente, char *password){
    int UTcheck = 0;
    char tmpUT[99];

    int PWcheck = 0;
    char tmpPW[99];
    
    int check = 0;

    int counter = 1;
    
    FILE *fp;
    char fileUtenti[20] = "utenti.txt";
    char filePassword[20] = "passwords.txt";

    fp = fopen(fileUtenti, "r");
    while (!feof(fp)){
        fscanf(fp, "%s\n", tmpUT);

        if(strcmp(tmpUT, utente) == 0){
            UTcheck = 1;
            break;
        }
    }
    fclose(fp);

    fp = fopen(filePassword, "r");
    while (!feof(fp)){
        fscanf(fp, "%s\n", tmpPW);
        
        if(strcmp(tmpPW, password) == 0){
            PWcheck = 1;
            break;
        }
    }
    fclose(fp);

    if(UTcheck == 1 && PWcheck == 1){
        check = 1;
    }

    //printf("\n%d %d\n", UTcheck, PWcheck);
    return check;
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

        fprintf(fpU, "%s 0 Utente\n", utente);
        fprintf(fpP, "%s\n", password);

        check = 1;

        fclose(fpU);
        fclose(fpP);
    }

    return check;
}

int main(int argc, char *argv[]){

    /*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;*/

    /* Attributi console 
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes; */

    char choose_str[99];

    char utente[99];
    char pass[99];

    int checkL = 0;
    int checkR = 0;
    int check = 0;

    int menuChoice;
    int choice;

    int tmp;

    //red(hConsole);
    printf("\t\tProgetto LASD Aprile 2022\n\t\t     Shopping Online\n\t\t  Dario Morace N86003778\n");
    //reset(hConsole, saved_attributes);

    //blue(hConsole);
    printf("Benvenuto, inserisci Login per autenticarti o Registrazione per registrarti.\n");
    //reset(hConsole, saved_attributes);
    scanf("%s", choose_str);

    while(strcmp(choose_str, "Login") != 0 && strcmp(choose_str, "Registrazione") != 0){
    //red(hConsole);
    printf("Scelta non corretta, riprova.\n");
    //reset(hConsole, saved_attributes);
    scanf("%s", choose_str);
    }

    if(strcmp(choose_str, "Login") == 0){
        
        while(checkL == 0){
            //blue(hConsole);
            printf("Inserisci il tuo nome utente:\n");
            //reset(hConsole, saved_attributes);
            scanf("%s", utente);

            //blue(hConsole);
            printf("Inserisci la tua password:\n");
            //reset(hConsole, saved_attributes);
            scanf("%s", pass);

            checkL = LogIn(utente, pass);

            if(checkL == 1){
                system("clear");
                //green(hConsole);
                printf("Login effettuato con successo!.\n");
                //reset(hConsole, saved_attributes);
            }else{
                //red(hConsole);
                printf("Le credenziali sono incorrette o non presenti. Se non lo hai fatto registrati.\n");
                //reset(hConsole, saved_attributes);
            }
        }
    }
    else if(strcmp(choose_str, "Registrazione") == 0){
        while(checkR == 0){
            //blue(hConsole);
            printf("Inserisci un nome utente:\n");
            //reset(hConsole, saved_attributes);
            scanf("%s", utente);

            //blue(hConsole);
            printf("Inserisci una password:\n");
            //reset(hConsole, saved_attributes);
            scanf("%s", pass);

            checkR = Register(utente, pass);

            if(checkR == 1){
                //green(hConsole);
                printf("Registrazione effettuata con successo!.\n");
                //reset(hConsole, saved_attributes);

                checkL = LogIn(utente, pass);

                if(checkL == 1){
                    //green(hConsole);
                    printf("Login effettuato con successo!.\n");
                    //reset(hConsole, saved_attributes);
                }
            }else{
                //red(hConsole);
                printf("Il nome inserito è già stato preso!. Riprova.\n");
                //reset(hConsole, saved_attributes);
            }
        }
    }

    printf("Benvenuto nello Shop, %s.\n", utente);
    while(menuChoice != 4){

        printf("Menu:\n1]Visiona lo shop.\n2]Visiona carrello.\n3]Gestisci saldo.\n4]Exit\n");
        scanf("%d", &menuChoice);
        switch (menuChoice)
        {
        case 1:
            /* code */

        case 2:
            /* code */

        case 3:
            system("clear");
            printf("Gestione saldo di %s. Digita una scelta.\n", utente);
            while(choice != 4){
                printf("Menu:\n1]Ricarica saldo.\n2]Visiona saldo.\n3]Scarica saldo.\n4]Exit\n");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    printf("Inserisci la quantita' da ricaricare.\n");
                    scanf("%d", &tmp);
                    check = ricaricaSaldo(tmp, utente);

                    if(check == 1){
                        printf("La ricarica di %d è stata effettuata.", tmp);
                        continue;
                    }else{
                        //boh
                        continue;
                    }
                default:
                    printf("Questa scelta non esiste, riprova.\n");
                }
            }
        case 4:
            break;
        default:
            printf("Questa scelta non esiste, riprova.\n");
        }
    }
    //getch();
    return 0;
}