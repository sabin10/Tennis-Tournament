
void citire(struct jucator *j, FILE *fptr)
{
    int i;
    for(i=0 ; i<NRJUC; i++)
    {
        fscanf(fptr, "%d", &j[i].loc_atp);
        fscanf(fptr, "%s", j[i].nume);
        fscanf(fptr, "%d", &j[i].nr_meci_win);
        fscanf(fptr, "%d", &j[i].nr_meci_lost);
        fscanf(fptr, "%d", &j[i].serva_win);
        fscanf(fptr, "%d", &j[i].returnare_win);
    }
    /* fiecare 6 linii vor corespunde unui j[i]
        iar fiecare din cele 6 linii vor corespunde unui membru al struct jucator

    */
}


void tragere_sorti(struct jucator *j, struct jucator *aux)
{

    int x, i;
    srand(time(NULL));
    while((x=rand() % NRJUC) != (NRJUC-1)) //se extrage un numar de 0 la 127, iar loopul va merge pana cand se va extrage numarul 126
    {

        // se salveaza temporal in aux datele extrase random
        aux[0].loc_atp = j[x].loc_atp;
        strcpy(aux[0].nume, j[x].nume);
        aux[0].nr_meci_win = j[x].nr_meci_win;
        aux[0].nr_meci_lost = j[x].nr_meci_lost;
        aux[0].serva_win = j[x].serva_win;
        aux[0].returnare_win = j[x].returnare_win;

        // se vor muta de la j[i] la j[i-1] toate datele care sunt mai mari ca x
        for(i=(x+1) ; i<NRJUC ; i++)
        {
            j[i-1].loc_atp = j[i].loc_atp;
            strcpy(j[i-1].nume, j[i].nume);
            j[i-1].nr_meci_win = j[i].nr_meci_win;
            j[i-1].nr_meci_lost = j[i].nr_meci_lost;
            j[i-1].serva_win = j[i].serva_win;
            j[i-1].returnare_win = j[i].returnare_win;
        }
        // aduc datele salvate temporal in aux pe ultima pozitie a vectorului j
        j[NRJUC-1].loc_atp = aux[0].loc_atp;
        strcpy(j[NRJUC-1].nume, aux[0].nume);
        j[NRJUC-1].nr_meci_win = aux[0].nr_meci_win;
        j[NRJUC-1].nr_meci_lost = aux[0].nr_meci_lost;
        j[NRJUC-1].serva_win = aux[0].serva_win;
        j[NRJUC-1].returnare_win = aux[0].returnare_win;
    }
}




int meci_sim(int j1_serva_win, int j1_returnare_win, int j2_serva_win, int j2_returnare_win, FILE *fout)
{
    /*
        meciul se termina atunci cand unul dintre jucatori a castigat 2 seturi, i.e. s1=2 sau s2=2
    */

    // x1= numar gameuri j1 set1     x2= numar gameuri j2 set1
    // y1= numar gameuri j1 set2     y2= numar gameuri j2 set2
    // z1= numar gameuri j1 set3     z2= numar gameuri j2 set3
    // s1= numar seturi j1           s2= numar seturi j2
    int x1 = 0, x2 = 0, y1=0, y2=0, z1=0, z2=0, s1 = 0, s2 = 0;
    int c1, c2, i;
    srand(time(NULL));

    /*
    se va extrage random un numar intre 0 si (rata de win la servire jucator1 + rata de win la primire jucator2 - 1) " in caz ca jucator1 serveste "
    daca numarul extras < rata de win la servire jucator1 => jucator1 a castigat gameul
    daca numarul extras > rata de win la servire jucator1 => jucator2 a castigat gameul
    gameul urmator, jucator2 serveste iar procesul se va repeta, insa luand in considerare (rata de win la servire jucator2, rata de win la primire jucator1)
    */

    //se joaca primul set pana cand x1=6 sau x2=6
    for(i=0 ; i<12 ; i++)
    {
        c1 = rand() % (j1_serva_win + j2_returnare_win);
        if (c1 < j1_serva_win)
        {
            x1++;
            if(x1 == 6) break;
        }
        else if(c1 >= j1_serva_win)
        {
            x2++;
            if(x2 == 6) break;
        }
        c2 = rand() % (j2_serva_win + j1_returnare_win);
        if(c2 < j2_serva_win)
        {
            x2++;
            if(x2 == 6) break;
        }
        else if(c2 >= j2_serva_win)
        {
            x1++;
            if(x1 == 6) break;

        }
    }
    if (x1 == 6) s1 ++;
    if (x2 == 6) s2 ++;
    fprintf(fout, "set1:%d-%d ", x1, x2);

    //se joaca al-2lea set pana cand y1=6 sau y2=6
    for(i=0 ; i<12 ; i++)
    {
        c1 = rand() % (j1_serva_win + j2_returnare_win);
        if (c1 < j1_serva_win)
        {
            y1++;
            if(y1 == 6) break;
        }
        else if(c1 >= j1_serva_win)
        {
            y2++;
            if(y2 == 6) break;
        }
        c2 = rand() % (j2_serva_win + j1_returnare_win);
        if(c2 < j2_serva_win)
        {
            y2++;
            if(y2 == 6) break;
        }
        else if(c2 >= j2_serva_win)
        {
            y1 ++;
            if(y1 == 6) break;

        }
    }

    if (y1 == 6) s1 ++;
    if (s1 == 2)
    {
        fprintf(fout, "set2:%d-%d ", y1, y2);
        return (s1-s2);
    }
    if (y2 == 6) s2 ++;
    if (s2 == 2)
    {
        fprintf(fout, "set2:%d-%d ", y1, y2);
        return (s1-s2);
    }

    //se joaca al-3lea set pana cand z1=6 sau z2=6-> doar daca nu s-a castigat meciul deja
    for(i=0 ; i<12 ; i++)
    {
        c1 = rand() % (j1_serva_win + j2_returnare_win);
        if (c1 < j1_serva_win)
        {
            z1++;
            if(z1 == 6) break;
        }
        else if(c1 >= j1_serva_win)
        {
            z2++;
            if(z2 == 6) break;
        }
        c2 = rand() % (j2_serva_win + j1_returnare_win);
        if(c2 < j2_serva_win)
        {
            z2++;
            if(z2 == 6) break;
        }
        else if(c2 >= j2_serva_win)
        {
            z1++;
            if(z1 == 6) break;

        }
    }

    if (z1 == 6) s1 ++;
    if (s1 == 2)
    {
        fprintf(fout, "set2:%d-%d ", y1, y2);
        fprintf(fout, "set3:%d-%d ", z1, z2);
        return (s1-s2);
    }
    if (z2 == 6) s2 ++;
    if (s2 == 2)
    {
        fprintf(fout, "set2:%d-%d ", y1, y2);
        fprintf(fout, "set3:%d-%d ", z1, z2);
        return (s1-s2);
    }



    return (s1-s2);

}


void forfunctie(struct jucator *j, struct jucator *r2, FILE *fout, int nr_jucatori)
{
    int i, x;
    for(i=0 ; i<=((nr_jucatori/2)-1); i++)
    {
        fprintf(fout, "%s-%s:\t", j[i].nume, j[nr_jucatori-1-i].nume);
        x = meci_sim(j[i].serva_win, j[i].returnare_win, j[nr_jucatori-1-i].serva_win, j[nr_jucatori-1-i].returnare_win, fout);
        /* apelare functia meci_sim() care returneaza (numar seturi jucator1 - numar seturi jucator2)
        daca meci_sim() returneaza 2 => scorul a fost 2-0;
        daca meci_sim() returneaza 1 => scorul a fost 2-1;
        daca meci_sim() returneaza -2 => scorul a fost 0-2;
        daca meci_sim() returneaza -1 => scorul a fost 1-2;

        */
        if( x == 2 ) //j1 win
        {
            fprintf(fout, "->Scor meci:2-0\n");
            r2[i].loc_atp = j[i].loc_atp;
            strcpy(r2[i].nume, j[i].nume);
            r2[i].serva_win = j[i].serva_win;
            r2[i].returnare_win = j[i].returnare_win;
        }
        else if( x == 1 ) //j1 win
        {
            fprintf(fout, "->Scor meci:2-1\n");
            r2[i].loc_atp = j[i].loc_atp;
            strcpy(r2[i].nume, j[i].nume);
            r2[i].serva_win = j[i].serva_win;
            r2[i].returnare_win = j[i].returnare_win;
        }
        else if( x == -2 ) //j2 win
        {
            fprintf(fout, "->Scor meci:0-2\n");
            r2[i].loc_atp = j[nr_jucatori-1-i].loc_atp;
            strcpy(r2[i].nume, j[nr_jucatori-1-i].nume);
            r2[i].serva_win = j[nr_jucatori-1-i].serva_win;
            r2[i].returnare_win = j[nr_jucatori-1-i].returnare_win;
        }
        else if( x == -1 ) //j2 win
        {
            fprintf(fout, "->Scor meci:1-2\n");
            r2[i].loc_atp = j[nr_jucatori-1-i].loc_atp;
            strcpy(r2[i].nume, j[nr_jucatori-1-i].nume);
            r2[i].serva_win = j[nr_jucatori-1-i].serva_win;
            r2[i].returnare_win = j[nr_jucatori-1-i].returnare_win;
        }

        if( nr_jucatori == 2 && (x == 2 || x == 1)) fprintf(fout, "Castigatorul turneului este %s\n", r2[i].nume);
        if( nr_jucatori == 2 && (x == -2 || x == -1)) fprintf(fout, "Castigatorul turneului este %s\n", r2[i].nume);
    }
}

void desfasurare_runda(struct jucator *j, struct jucator *r2, FILE *fout, int nr_jucatori)
{
    /* dupa apelarea functiei tragere_sorti in main, acum jucatorii vor fi amestecati
        in fiecare runda vor juca primii trasi cu ultimii trasi
            ex: j[0] joaca cu j[127];
                j[1] joaca cu j[126] etc;
        participantii in runda curenta sunt apelati din primul argument al functiei,
            iar castigatorii vor fi salvati in al2lea argument la functiei

        *fout reprezinta pointer la fisierul unde se va scrie desfasurarea
        nr_jucatori = numarul de jucatori din runda curenta


    */
    int x, i;

    if (nr_jucatori == NRJUC)
    {
         fprintf(fout, "RUNDA %d - ", runda1); // s-a folosit enum
         fprintf(fout, "PRELIMINARII TURUL 3\n");
    }

    if (nr_jucatori == NRJUC2)
    {
         fprintf(fout, "RUNDA %d - ", runda2);
         fprintf(fout, "PRELIMINARII TURUL 2\n");
    }

    if (nr_jucatori == NRJUC3)
    {
         fprintf(fout, "RUNDA %d - ", 3);
         fprintf(fout, "PRELIMINARII TURUL 1\n");
    }

    if (nr_jucatori == NRJUC4)
    {
         fprintf(fout, "RUNDA %d - ", 4);
         fprintf(fout, "OPTIMI\n");
    }

    if (nr_jucatori == NRJUC5)
    {
         fprintf(fout, "RUNDA %d - ", 5);
         fprintf(fout, "SFERTURI\n");
    }

    if (nr_jucatori == NRJUC6)
    {
         fprintf(fout, "RUNDA %d - ", 6);
         fprintf(fout, "SEMIFINALE\n");
    }

    if (nr_jucatori == NRJUC7)
    {
         fprintf(fout, "RUNDA %d - ", 7);
         fprintf(fout, "FINALA\n");
    }

    forfunctie(j, r2, fout, nr_jucatori);

/*

    for(i=0 ; i<=((nr_jucatori/2)-1); i++)
    {
        fprintf(fout, "%s-%s:\t", j[i].nume, j[nr_jucatori-1-i].nume);
        x = meci_sim(j[i].serva_win, j[i].returnare_win, j[nr_jucatori-1-i].serva_win, j[nr_jucatori-1-i].returnare_win, fout);

        if( x == 2 ) //j1 win
        {
            fprintf(fout, "->Scor meci:2-0\n");
            r2[i].loc_atp = j[i].loc_atp;
            strcpy(r2[i].nume, j[i].nume);
            r2[i].serva_win = j[i].serva_win;
            r2[i].returnare_win = j[i].returnare_win;
        }
        else if( x == 1 ) //j1 win
        {
            fprintf(fout, "->Scor meci:2-1\n");
            r2[i].loc_atp = j[i].loc_atp;
            strcpy(r2[i].nume, j[i].nume);
            r2[i].serva_win = j[i].serva_win;
            r2[i].returnare_win = j[i].returnare_win;
        }
        else if( x == -2 ) //j2 win
        {
            fprintf(fout, "->Scor meci:0-2\n");
            r2[i].loc_atp = j[nr_jucatori-1-i].loc_atp;
            strcpy(r2[i].nume, j[nr_jucatori-1-i].nume);
            r2[i].serva_win = j[nr_jucatori-1-i].serva_win;
            r2[i].returnare_win = j[nr_jucatori-1-i].returnare_win;
        }
        else if( x == -1 ) //j2 win
        {
            fprintf(fout, "->Scor meci:1-2\n");
            r2[i].loc_atp = j[nr_jucatori-1-i].loc_atp;
            strcpy(r2[i].nume, j[nr_jucatori-1-i].nume);
            r2[i].serva_win = j[nr_jucatori-1-i].serva_win;
            r2[i].returnare_win = j[nr_jucatori-1-i].returnare_win;
        }

        if( nr_jucatori == 2 && (x == 2 || x == 1)) fprintf(fout, "Castigatorul turneului este %s\n", r2[i].nume);
        if( nr_jucatori == 2 && (x == -2 || x == -1)) fprintf(fout, "Castigatorul turneului este %s\n", r2[i].nume);
    }
    */

    fprintf(fout, "----------\n");
}

