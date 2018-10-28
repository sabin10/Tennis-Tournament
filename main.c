/*
    PROIECT: TURNEU TENIS
    HANTU COSTIN-SABIN
    CTI, PC, GRUPA 154
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NRJUC 128
#define NRJUC2 64
#define NRJUC3 32
#define NRJUC4 16
#define NRJUC5 8
#define NRJUC6 4
#define NRJUC7 2
#include "structuri.h"
#include "enum.h"
#include "functii.h"


//declarare functii
void citire();
void tragere_sorti();
int meci_sim();
void desfasurare_runda();

int main()
{

    int i;

    FILE *fin, *fout;
    fin = fopen("tenisfile.txt", "r+"); //fisierul din care se iau statisticile
    fout = fopen("rezultate.txt", "w+"); //fisierul in care se va scrie desfasurarea turneului

    if(fin == NULL) //control al erorilor
    {
        fprintf(stderr, "Eroare: fisier intrare!");
        exit(0);
    }

    if(fout == NULL) //control al erorilor
    {
        fprintf(stderr, "Eroare: fisier iesire!");
        exit(1);
    }

    struct jucator *j, *r2, *r3, *op, *sf, *semi, *finala, *winner; /* pointeri la structura jucator pentru fiecare runda in parte;
                                                                        castigatorii din runda precedenta(pointerul precedent) se vor retine
                                                                                in runda urmatoare(pointerul urmator);
                                                                    */


    //alocare dinamica  pentru fiecare pointer la struct in parte in functie de numarul de jucatori din runda respectiva
     j = malloc(NRJUC * sizeof(struct jucator));
    r2 = malloc(NRJUC2 * sizeof(struct jucator));
    r3 = malloc(NRJUC3 * sizeof(struct jucator));
    op = malloc(NRJUC4 * sizeof(struct jucator));
    sf = malloc(NRJUC5 * sizeof(struct jucator));
    semi = malloc(NRJUC6 * sizeof(struct jucator));
    finala = malloc(NRJUC7 * sizeof(struct jucator));
    winner = malloc(sizeof(struct jucator));


    if(j == NULL) //control al erorilor
    {
        printf("Eroare HEAP: struct jucatori j!");
        exit(2);
    }

    if(r2 == NULL) //control al erorilor
    {
        printf("Eroare HEAP: struct jucatori r2!");
        exit(3);
    }

    if(r3 == NULL) //control al erorilor
    {
        printf("Eroare HEAP: struct jucatori r3!");
        exit(4);
    }

    if(op == NULL) //control al erorilor
    {
        printf("Eroare HEAP: struct jucatori op!");
        exit(4);
    }

    if(sf == NULL) //control al erorilor
    {
        printf("Eroare HEAP: struct jucatori sf!");
        exit(5);
    }

    if(semi == NULL) //control al erorilor
    {
        printf("Eroare HEAP: struct jucatori semi!");
        exit(6);
    }

    if(finala == NULL) //control al erorilor
    {
        printf("Eroare HEAP: struct jucatori finala!");
        exit(7);
    }

    if(winner == NULL) //control al erorilor
    {
        printf("Eroare HEAP: struct jucatori winnerul!");
        exit(8);
    }

    citire(j, fin); /* apelarea functiei citire()
                        se vor salva in pointerul j statisticile scrie in fisierul a carui pointer este fin
                    */


    struct jucator *aux; /* acest pointer la struct este folosit ca un ajutor pentru a retine pentru moment anumite adrese din j[i]
                            este folositor pentru functia tragere_sorti()
                        */

    aux=malloc(sizeof(struct jucator)); //alocare dinamica doar pentru un jucator, pentru ca va retine cate unul pe rand
    if(aux == NULL) //control al erorilor
    {
        printf("Eroare HEAP: struct jucatori aux!");
        exit(9);
    }

    tragere_sorti(j, aux);/* apelarea functiei tragere_sorti()
                                amesteca j[i]
                            */
    free(aux); //eliberez memoria de pe HEAP


    desfasurare_runda(j, r2, fout, NRJUC); //desfasurare runda 1
    free(j); //eliberez memoria de pe HEAP

    desfasurare_runda(r2, r3, fout, NRJUC2); //desfasurare runda 2
    free(r2); //eliberez memoria de pe HEAP

    desfasurare_runda(r3, op, fout, NRJUC3); //desfasurare runda 3
    free(r3); //eliberez memoria de pe HEAP

    desfasurare_runda(op, sf, fout, NRJUC4); //desfasurare optimi
    free(op); //eliberez memoria de pe HEAP

    desfasurare_runda(sf, semi, fout, NRJUC5); //desfasurare sferturi
    free(sf); //eliberez memoria de pe HEAP

    desfasurare_runda(semi, finala, fout, NRJUC6); //desfasurare semifinale
    free(semi); //eliberez memoria de pe HEAP

    desfasurare_runda(finala, winner, fout, NRJUC7); //desfasurare finala
    free(finala); //eliberez memoria de pe HEAP
    free(winner); //eliberez memoria de pe HEAP


    return 0;
}
