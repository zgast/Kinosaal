#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int Resevierung(int ROW, int COLUMN,int **saal);
int Drucken(int ROW, int COLUMN,int **saal);
int anfang();
void Proof(int ROW, int COLUMN,int green,int blue,int white,int **saal);
int whiteCount(int boolean, int ROW,int COLUMN, int **saal);
int greenCount(int boolean, int ROW,int COLUMN, int **saal);
int blueCount(int boolean, int ROW,int COLUMN, int **saal);

void delay(int number_of_seconds);

void main(int argc, char** argv){

    system("cls");

    int ROW=10,COLUMN=10;

    ROW=atol(argv[1]);
    COLUMN=atol(argv[2]);

    int len=0,give,r,c, white=0,green=0,blue=0;
    int *ptr, **saal;
    int count = 0,i,j;

    len = sizeof(int *) * ROW + sizeof(int) * COLUMN * ROW;
    saal = (int **)malloc(len);

    ptr = (int *)(saal + ROW);

    for(i = 0; i < ROW; i++)
        saal[i] = (ptr + COLUMN * i);

    for(int i=0;i<ROW;i++){
        for(int j=0;j<COLUMN;j++){
            saal[i][j]=0;
        }
    }

    blue = blueCount(0, ROW,COLUMN,saal);
    green = greenCount(0,ROW,COLUMN,saal);
    white = ROW*ROW-(green+blue);


    while(2!=1){
        int e=anfang();
        if(e==1){
            Drucken(ROW,COLUMN,saal);
        }else if(e==2){
            give=Resevierung(ROW,COLUMN,saal);
            r=give%100;
            c=give/100;
            saal[r][c]=1;
        }else if(e==3){
            Proof(ROW,COLUMN,green,blue,white,saal);
        }
        else{
            break;
            for(int i = 0; i < ROW; i++)
                free(ptr[i]);
            free(ptr);
        }
        delay(3);
    }

}


void Proof(int ROW, int COLUMN,int green,int blue,int white,int **saal) {

    int countRow=0,countColumn=0,r=0,c=0,countGreen=0,countBlue=0,countWhite=0;


    while(((r<1)||(r>ROW))||((c<1)||(c>COLUMN))){
        printf("\nBitte Platz eingeben:");
        scanf("%d",&r);
        scanf("%d",&c);
    }

    if(saal[r-1][c-1]==0){
        printf("\nSitzplatzt ist frei.\n");
    }else{
        printf("\nSitzplatzt leider schon reserviert.\n");
    }

    for(int i=0;i<COLUMN;i++){
        if(saal[r-1][i]==0){
            countRow++;
        }
    }
    for(int i=0;i<ROW;i++){
        if(saal[i][c-1]==0){
            countColumn++;
        }
    }
    printf("\nIn der Reihe sind %d Plaetze frei.\nIn der Spalte sind %d Plaetze frei.\n",countRow,countColumn);

    countWhite=whiteCount(1,ROW,COLUMN,saal);
    countGreen=greenCount(1,ROW,COLUMN,saal);
    countBlue=blueCount(1,ROW,COLUMN,saal);

    countWhite=white-countWhite;
    countGreen=green-countGreen;
    countBlue=blue-countBlue;

    printf("\n\nIn der Kategorie weiss sind %d Plaetze frei.\n\nIn der Kategorie blau sind %d Plaetze frei.\n\nIn der Kategorie gruen sind %d Plaetze frei.\n\n",countWhite,countBlue, countGreen);
}
int whiteCount(int boolean, int ROW,int COLUMN, int **saal){
    int countGreen,countBlue,countWhite=0;

    countGreen=greenCount(1,ROW,COLUMN,saal);
    countBlue=blueCount(1,ROW,COLUMN,saal);
    for(int i=0;i<ROW;i++){
        for(int j=0;j<ROW;j++){
            if(saal[i][j]==boolean){
                countWhite++;
            }
        }
    }
    return countWhite-(countGreen+countBlue);
}
int greenCount(int boolean, int ROW,int COLUMN, int **saal){
    int greenCount=0;

    for(int i=0;i<ROW;i++){
        if(saal[i][0]==boolean){
            greenCount++;
        }else if(saal[0][i]==boolean){
            greenCount++;
        }
    }
    for(int i=0;i<ROW;i++){
        if(saal[i][ROW]==boolean){
            greenCount++;
        }else if(saal[0][ROW]==boolean){
            greenCount++;
        }
    }
    if(boolean==0){
        greenCount=greenCount*2-4;
    }
    return greenCount;
}
int blueCount(int boolean, int ROW,int COLUMN, int **saal){
    int blueCount=0;

    for(int i=0;i<ROW-4;i++){
        if(saal[i+2][2]==boolean){
            blueCount++;
        }else if(saal[2][i+2]==boolean){
            blueCount++;
        }
    }
    for(int i=0;i<ROW-4;i++){
        if(saal[i+2][ROW-2]==boolean){
            blueCount++;
        }else if(saal[ROW-2][i+2]==boolean){
            blueCount++;
        }
    }
   if(boolean==0){
       blueCount--;
    }
    return blueCount;
}

int Resevierung(int ROW, int COLUMN,int **saal){
    int r,c,give;

    while((r<=0)||(r>ROW)||(c<=0)||(c>COLUMN)){
        printf("\nBitte Platz eingeben:");
        scanf("%d",&r);
        scanf("%d",&c);
    }

    if(saal[r-1][c-1]==0){
        printf("Sitzplatz wurde reserviert.");
        give=(r-1)*100+c-1;
    }else{
        printf("Sitzplatz leider schon reserviert");
    }

    return give;
}

int Drucken(int ROW, int COLUMN,int **saal){
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COLUMN;j++){
            printf("|%d|", saal[i][j]);
            if(((j%ROW)==ROW-1)) {
                printf("\n");
                for (int i = 0; i < COLUMN; i++) {
                    printf("---");
                }
                printf("\n");
            }

        }
    }
    return 0;
}

int anfang(){
    int e;
    printf("\n\nKINO-SAAL\n1 druecken fuer Ausdruck des Sitzplans.\n2 druecken fuer Reservierung\n3 druecken fuer Testen das der Sitzplatzt frei ist\n\n\nIhre Eingabe:");
    scanf("%d",&e);
    return e;
}



void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;

    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}