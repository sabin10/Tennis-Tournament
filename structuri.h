struct stats_istorie
{
    int nr_meci_win;
    int nr_meci_lost;
};

struct stats_pergame
{
    int serva_win; //ratie de castig a gameului cand serveste, i.e. 77 = 77%
    int returnare_win; //ratie de castig a gameului cand returneaza
};

struct jucator
{
    int loc_atp;
    char nume[20];
    struct stats_istorie;
    struct stats_pergame;
};

//statisticile sunt luate de pe site-ul atp
