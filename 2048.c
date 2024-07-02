#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

//afiseaza o floare cu petale rosii 
// si trunchi verde
//in partea de stanga sus a ecranului
void flower(WINDOW *window)
{
    init_pair(3, COLOR_RED, COLOR_BLACK);
    wattron(window, COLOR_PAIR(3));
    wattron(window, A_BOLD);
    mvwprintw(window, 3, 5, "/\\");
    mvwprintw(window, 4, 3, "< ** >");
    mvwprintw(window, 5, 5, "\\/");
    wrefresh(window);
    wattroff(window, COLOR_PAIR(3));
    wattroff(window, A_BOLD);

    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    wattron(window, COLOR_PAIR(4));
    wattron(window, A_BOLD);
    mvwprintw(window, 6, 4, "\\|");
    mvwprintw(window, 7, 4, " |/");
    mvwprintw(window, 8, 4, " | ");
    mvwprintw(window, 9, 4, " | ");
    wrefresh(window);
    wattroff(window, COLOR_PAIR(4));
    wattroff(window, A_BOLD);
}

//afisez fereastra in care ai castigat jocul
void win(WINDOW *window)
{
    werase(window);
    box(window, 0, 0);
    mvwprintw(window, 10, 12, "  YOU WIN!!!  ");
    wrefresh(window);
}

//fereastra meniului
int menu(WINDOW *menu_choice)
{

    int x, y, a, b, ch;
    char sir[100][100];
    strcpy(sir[8], " ~New Game~ ");
    strcpy(sir[11], " ~Resume~ ");
    strcpy(sir[14], " ~High scores~ ");
    strcpy(sir[17], " ~Quit~ ");
    werase(menu_choice);
    box(menu_choice, 0, 0);
    flower(menu_choice);
    wrefresh(menu_choice);

    // initializeaza generatorul de numere
    srand(time(0));

    init_pair(1, COLOR_CYAN, COLOR_WHITE);
    wattron(menu_choice, COLOR_PAIR(1));
    wattron(menu_choice, A_BOLD);
    mvwprintw(menu_choice, 4, 15, "  MENU: ");
    wrefresh(menu_choice);
    wattroff(menu_choice, COLOR_PAIR(1));
    wattroff(menu_choice, A_BOLD);

    init_pair(2, COLOR_MAGENTA, COLOR_BLUE);
    wattron(menu_choice, COLOR_PAIR(2));
    mvwprintw(menu_choice, 8, 14, " ~New Game~ ");
    wrefresh(menu_choice);
    mvwprintw(menu_choice, 11, 15, " ~Resume~ ");
    wrefresh(menu_choice);
    mvwprintw(menu_choice, 14, 13, " ~High scores~ ");
    wrefresh(menu_choice);
    mvwprintw(menu_choice, 17, 16, " ~Quit~ ");
    wrefresh(menu_choice);
    wattroff(menu_choice, COLOR_PAIR(2));

    mvwprintw(menu_choice, 8, 26, "  aici");
    wrefresh(menu_choice);

    //alegerea utilizatorului din meniu
    move(8, 14);
    x = 8;
    y = 14;
    ch = getch();
    while (ch == KEY_UP || ch == KEY_DOWN){
        a = x;
        b = y;
        if (ch == KEY_UP)
        {
            if (x == 8)
            {
                x = 17;
                y = 16;
            }
            else
            {
                if (x == 11)
                {
                    y = 14;
                }
                else if (x == 14)
                {
                    y = 15;
                }
                else if (x == 17)
                {
                    y = 13;
                }
                x = x - 3;
                
            }
        }
        else if (ch == KEY_DOWN)
        {
            if (x == 17)
            {
                x = 8;
                y = 14;
            }
            else
            {
                if (x == 8)
                {
                    y = 15;
                }
                else if (x == 11)
                {
                    y = 13;
                }
                else if (x == 14)
                {
                    y = 16;
                }
                x = x + 3;
                
            }
        }
        init_pair(2, COLOR_MAGENTA, COLOR_BLUE);
        wattron(menu_choice, COLOR_PAIR(2));
        mvwprintw(menu_choice, a, b, "%s", sir[a]);
        wattroff(menu_choice, COLOR_PAIR(2));
        mvwprintw(menu_choice, a, b + strlen(sir[a]), "      ");
        wrefresh(menu_choice);
        mvwprintw(menu_choice, x, y + strlen(sir[x]), " aici");
        wrefresh(menu_choice);
        ch = getch();
    }

    if (ch == KEY_ENTER || ch == '\n')
    {
        if (x == 8)
        {
            return 1;
        }
        if (x == 11)
        {
            return 2;
        }
        if (x == 14)
        {
            return 3;
        }
    }
    return 4;
}

//coloreaza casutele din joc in functie de valoare
void color(WINDOW *window, int lin, int col, int val)
{
    int culoare_pereche = 6;
    switch(val){
        case 2:
        culoare_pereche = 6;
        break;
        case 4:
        culoare_pereche = 7;
        break;
        case 8:
        culoare_pereche = 8;
        break;
        case 16:
        culoare_pereche = 9;
        break;
        case 32:
        culoare_pereche = 10;
        break;
        case 64:
        culoare_pereche = 11;
        break;
        case 128:
        culoare_pereche = 12;
        break;
        case 256:
        culoare_pereche = 13;
        break;
        case 512:
        culoare_pereche = 14;
        break;
        case 1024:
        culoare_pereche = 15;
        break;
        case 2048:
        culoare_pereche = 16;
        break;
        default:
        break;
    }
    wattron(window, COLOR_PAIR(culoare_pereche));
    wattron(window, A_BOLD);
    mvwprintw(window, lin *3 + 6, 
    col * 6 + 6, " %d ", val);
    wrefresh(window);
    wattroff(window, A_BOLD);
    wattroff(window, COLOR_PAIR(culoare_pereche));
}

//initializeaza fereastra de joc nou
void window_new_game(WINDOW *window, int scor)
{
    int i, j;
    
    init_pair(5, COLOR_WHITE, COLOR_RED);
    werase(window);
    box(window, 0, 0);
    wrefresh(window);
    wattron(window, COLOR_PAIR(5));

    for (i = 6; i < 17; i++)
    {
        for (j = 6; j < 29; j++)
        {
            mvwaddch(window, i, j, ACS_CKBOARD);
        }
    }
    //cadranul tablei de joc
    //linia de sus
    mvwhline(window, 5, 5, ACS_HLINE, 24);
    //linia de jos
    mvwhline(window, 17, 5, ACS_HLINE, 24);

    //coloana stanga
    mvwvline(window, 5, 5, ACS_VLINE, 12);
    //coloana dreapta
    mvwvline(window, 5, 29, ACS_VLINE, 12);

    //liniile
    mvwhline(window, 8, 5, ACS_HLINE, 24);
    mvwhline(window, 11, 5, ACS_HLINE, 24);
    mvwhline(window, 14, 5, ACS_HLINE, 24);

    //coloanele
    mvwvline(window, 5, 11, ACS_VLINE, 12);
    mvwvline(window, 5, 17, ACS_VLINE, 12);
    mvwvline(window, 5, 23, ACS_VLINE, 12);

    //coltul stanga sus
    mvwaddch(window, 5, 5, ACS_ULCORNER);
    //coltul dreapta sus
    mvwaddch(window, 5, 29, ACS_URCORNER);
    //coltul stanga jos
    mvwaddch(window, 17, 5, ACS_LLCORNER);
    //coltul dreapta jos
    mvwaddch(window, 17, 29, ACS_LRCORNER);

    wattroff(window, COLOR_PAIR(5));

    wattron(window, COLOR_PAIR(5));
    mvwprintw(window, 2, 24, " SCORE: %d ", scor);
    wattroff(window, COLOR_PAIR(5));
    mvwprintw(window, 1, 2, "COMENZI VALIDE:");
    mvwprintw(window, 3, 2, "￫ ￩ ￬ ￪  Q(menu)");
}

//miscare de jos in sus ￪
int up(WINDOW *window, int **matr_joc, int *scor, int var)
{
    int i, j;
    int poz;
    int nr_mutari = 0, imbinare = 0;

    for (j = 0; j < 4; j++)
    {
        imbinare = 0;
        for (i = 1; i < 4; i++)
        {
            if (matr_joc[i][j] != 0)
            {
                poz = i-1;
                while (poz >= 0 && matr_joc[poz][j] == 0)
                {
                    poz--;
                }
                if(poz == -1)
                {
                    matr_joc[0][j] = matr_joc[i][j];
                }
                else
                {
                    if (matr_joc[poz][j] == matr_joc[i][j] 
                    && imbinare == 0)
                    {
                        matr_joc[poz][j]*=2;
                        (*scor)+=matr_joc[i][poz];
                        imbinare = 1;
                        poz--;
                    }
                    else
                    {
                        matr_joc[poz+1][j] = matr_joc[i][j];
                        imbinare = 0;
                    }
                }
                if (poz < i-1)
                {
                    matr_joc[i][j] = 0;
                    nr_mutari ++;
                }
            }
        }
    }
    if (nr_mutari == 0 || var == 2)
    {
        return nr_mutari;
    }
    
    window_new_game(window, (*scor));

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (matr_joc[i][j])
            {
                color(window, i, j, matr_joc[i][j]);
            }
        }
    }
    wrefresh(window);
    return nr_mutari;
}

//miscare de sus in jos ￬
int down(WINDOW *window, int **matr_joc, int *scor, int var)
{
    int i, j;
    int poz; 
    int nr_mutari = 0, imbinare = 0;

    for (j = 0; j < 4; j++)
    {
        imbinare = 0;
        for (i = 2; i >= 0; i--)
        {
            if (matr_joc[i][j] != 0)
            {
                poz = i + 1;
                while (poz <= 3 && matr_joc[poz][j] == 0)
                {
                    poz++;
                }
                if (poz == 4)
                {
                    matr_joc[3][j] = matr_joc[i][j];
                }
                else
                {
                    if (matr_joc[poz][j] == matr_joc[i][j]
                    && imbinare == 0)
                    {
                        matr_joc[poz][j]*=2;
                        (*scor)+=matr_joc[i][poz];
                        imbinare = 1;
                        poz++;
                    }
                    else
                    {
                        matr_joc[poz - 1][j] = matr_joc[i][j];
                        imbinare = 0;
                    }
                }
                if (poz > i + 1)
                {
                    matr_joc[i][j] = 0;
                    nr_mutari++;
                }
            }
        }
    }
    if (nr_mutari == 0 || var == 2)
    {
        return nr_mutari;
    }

    window_new_game(window, (*scor));

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (matr_joc[i][j])
            {
                color(window, i, j, matr_joc[i][j]);
            }
        }
    }
    wrefresh(window);
    return nr_mutari;
}

//miscare de la dreapta la stanga ￩
int left(WINDOW *window, int **matr_joc, int *scor, int var)
{
    int i, j;
    int poz; 
    int nr_mutari = 0, imbinare = 0;

    for (i = 0; i < 4; i++)
    {
        imbinare = 0;
        for (j = 1; j < 4; j++)
        {
            if (matr_joc[i][j] != 0)
            {
                poz = j-1;
                while (poz >= 0 && matr_joc[i][poz] == 0)
                {
                    poz--;
                }
                if (poz == -1)
                {
                    matr_joc[i][0] = matr_joc[i][j];
                }
                else
                {
                    if (matr_joc[i][poz] == matr_joc[i][j] 
                    && imbinare == 0)
                    {
                        matr_joc[i][poz]*=2;
                        (*scor)+=matr_joc[i][poz];
                        imbinare = 1;
                        poz--;
                    }
                    else
                    {
                        matr_joc[i][poz+1] = matr_joc[i][j];
                        imbinare = 0;
                    }
                }
                if (poz < j-1)
                {
                    matr_joc[i][j] = 0;
                    nr_mutari++;
                }
            }
        }
    }
    if (nr_mutari == 0 || var == 2)
    {
        return nr_mutari;
    }

    window_new_game(window, (*scor));

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (matr_joc[i][j])
            {
                color(window, i, j, matr_joc[i][j]);
            }
        }
    }
    wrefresh(window);
    return nr_mutari;
}

//miscare de la stanga la dreapta ￫
int right(WINDOW *window, int **matr_joc, int *scor, int var)
{
    int i, j;
    int poz;
    int imbinare = 0, nr_mutari = 0;

    for (i = 0; i < 4; i++)
    {
        imbinare = 0;
        for (j = 2; j >= 0; j--)
        {
            if (matr_joc[i][j] != 0)
            {
                poz = j + 1;
                while (poz <= 3 && matr_joc[i][poz] == 0)
                {
                    poz++;
                }
                if (poz == 4)
                {
                    matr_joc[i][3] = matr_joc[i][j];
                }
                else
                {
                    if (matr_joc[i][poz] == matr_joc[i][j] 
                    && imbinare == 0)
                    {
                        matr_joc[i][poz]*=2;
                        (*scor)+=matr_joc[i][poz];
                        imbinare = 1;
                        poz++;
                    }
                    else
                    {
                        matr_joc[i][poz-1] = matr_joc[i][j];
                        imbinare = 0;
                    }
                }
                if (poz > j+ 1)
                {
                    matr_joc[i][j] = 0;
                    nr_mutari++;
                }
            }
        }
    }
    if (nr_mutari == 0 || var == 2)
    {
        return nr_mutari;
    }

    window_new_game(window, (*scor));

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (matr_joc[i][j])
            {
                color(window, i, j, matr_joc[i][j]);
            }
        }
    }
    wrefresh(window);
    return nr_mutari;
}

int verif(int **matr_joc)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 1; j < 4; j++)
        {
            if (matr_joc[i][j] == matr_joc[i][j-1])
            {
                return 0;
            }
            if (matr_joc[j][i] == matr_joc[j-1][i])
            {
                return 0;
            }
        }
    }
    return 1;
}

//returneaza numarul imbinarilor 
//pentru o miscare pe verticala
int vertical_joints(int **matr_joc)
{
    int i, j, poz, imbinare = 0;
    int nr_imbinari = 0;
    int nr_mutari = 0;

    for (j = 0; j < 4; j++)
    {
        imbinare = 0;
        for (i = 2; i >= 0; i--)
        {
            if (matr_joc[i][j] != 0)
            {
                poz = i + 1;
                while (poz <= 3 && matr_joc[poz][j] == 0)
                {
                    poz++;
                }
                if (poz == 4)
                {
                    matr_joc[3][j] = matr_joc[i][j];
                }
                else
                {
                    if (matr_joc[poz][j] == matr_joc[i][j] 
                    && imbinare == 0)
                    {
                        matr_joc[poz][j]*=2;
                        imbinare = 1;
                        nr_imbinari++;
                        poz++;
                    }
                    else
                    {
                        matr_joc[poz - 1][j] = matr_joc[i][j];
                        imbinare = 0;
                    }
                }
                if (poz > i + 1)
                {
                    matr_joc[i][j] = 0;
                    nr_mutari++;
                }
            }
        }
    }

    return nr_imbinari;
}

//returneaza numarul imbinarilor 
//pentru o miscare pe orizontala
int horizontal_joints(int **matr_joc)
{
    int i, j, poz, imbinare = 0;
    int nr_imbinari = 0;
    int nr_mutari = 0;

    for (i = 0; i < 4; i++)
    {
        imbinare = 0;
        for (j = 2; j >= 0; j--)
        {
            if (matr_joc[i][j] != 0)
            {
                poz = j + 1;
                while (poz <= 3 && matr_joc[i][poz] == 0)
                {
                    poz++;
                }
                if (poz == 4)
                {
                    matr_joc[i][3] = matr_joc[i][j];
                }
                else
                {
                    if (matr_joc[i][poz] == matr_joc[i][j] 
                    && imbinare == 0)
                    {
                        matr_joc[i][poz]*=2;
                        imbinare = 1;
                        nr_imbinari++;
                        poz++;
                    }
                    else
                    {
                        matr_joc[i][poz-1] = matr_joc[i][j];
                        imbinare = 0;
                    }
                }
                if (poz > j+ 1)
                {
                    matr_joc[i][j] = 0;
                    nr_mutari++;
                }
            }
        }
    }

    return nr_imbinari;
}

void show_time(WINDOW *window)
{
    time_t ora;
    struct tm *t;
    time(&ora);
    t = localtime(&ora);
    mvwprintw(window, 19, 5, " ORA %d:%d   DATA %d.%d.%d ", 
    t->tm_hour, t->tm_min, 
    t->tm_mday, t->tm_mon + 1, t->tm_year+1900);
    wrefresh(window);
}

//numara cate casute sunt completate de valori
int marked(int **matr_joc)
{
    int i, j, nr = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (matr_joc[i][j])
            {
                nr++;
            }
        }
    }
    return nr;
}

//verifica daca ai castigat jocul
int verif_2048_win(int **matr_joc)
{
    int i, j, nr = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if(matr_joc[i][j] == 2048)
            {
                nr = 1;
            }
        }
    }
    return nr;
}

void valid_commands(int sus, int jos, int st, int dr,
WINDOW *window)
{
    mvwprintw(window, 1, 2, "COMENZI VALIDE:");
    mvwprintw(window, 3, 2, "￫ ￩ ￬ ￪  Q(menu)");
    wrefresh(window);
    if(!dr)
    {
        mvwprintw(window, 3, 2, " ");
        wrefresh(window);
    }
    if(!st)
    {
        
        mvwprintw(window, 3, 4, " ");
        wrefresh(window);
    }
    if(!sus)
    {
        mvwprintw(window, 3, 8, " ");
        wrefresh(window);
    }
    if(!jos)
    {
        mvwprintw(window, 3, 6, " ");
        wrefresh(window);
    }
    wrefresh(window);

}

int new_game(WINDOW *window, int **matr_joc, int var, int scor)
{
    int i, j, ch;
    int rand_nr, rand_nr2;
    int lin, col, lin2, col2;
    int casute_marcate = 0, nr_mutari = 0;
    int nr_mutari_up = 0, nr_mutari_down = 0;
    int nr_mutari_left = 0, nr_mutari_right = 0;
    int nr_celule_imbinate_o = 0, nr_celule_imbinate_v = 0;
    int **copie_matr;

    copie_matr = (int **) malloc(5 * sizeof(int *));

    for (i = 0; i <= 4; i++)
    {
        copie_matr[i] = (int *) malloc(5 * sizeof(int));
    }
    
    wrefresh(window);
    if (var == 1)
    {
        window_new_game(window, 0);
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                matr_joc[i][j] = 0;
            }
        }
        wrefresh(window);

        rand_nr = (rand() % 3) + 2;
        if (rand_nr == 3)
        {
            rand_nr = 2;
        }
        lin = (rand() % 4) + 1;
        col = (rand() % 4) + 1;
        matr_joc[lin - 1][col - 1] = rand_nr;

        rand_nr2 = (rand() % 3) + 2;
        if (rand_nr2 == 3)
        {
            rand_nr2 = 2;
        }
        lin2 = lin;
        col2 = col;
        while (lin2 == lin && col2 == col)
        {
            lin2 = (rand() % 4) + 1;
            col2 = (rand() % 4) + 1;
        }
        matr_joc[lin2 - 1][col2 - 1] = rand_nr2;

        color(window, lin - 1, col - 1, rand_nr);

        color(window, lin2 - 1, col2 - 1, rand_nr2);

        casute_marcate = 2;
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }
        nr_mutari_up = up(window, copie_matr, &scor, 2);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }
        nr_mutari_down = down(window, copie_matr, &scor, 2);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }
        nr_mutari_right = right(window, copie_matr, &scor, 2);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }

        nr_mutari_left = left(window, copie_matr, &scor, 2);
        valid_commands(nr_mutari_up, nr_mutari_down,
                        nr_mutari_left, nr_mutari_right, window);
    }

    show_time(window);
    wrefresh(window);

    timeout(5000);
    ch = getch();
    while (ch != 'q' && ch != 'Q')
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }
        nr_mutari_up = up(window, copie_matr, &scor, 2);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }
        nr_mutari_down = down(window, copie_matr, &scor, 2);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }
        nr_mutari_right = right(window, copie_matr, &scor, 2);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }

        nr_mutari_left = left(window, copie_matr, &scor, 2);

        if (ch == ERR)
        {
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    copie_matr[i][j] = matr_joc[i][j];
                }
            }
            nr_celule_imbinate_o = 
            horizontal_joints(copie_matr);

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    copie_matr[i][j] = matr_joc[i][j];
                }
            }
            nr_celule_imbinate_v =
            vertical_joints(copie_matr);

            rand_nr2 = (rand() % 2) + 1;
            if (nr_celule_imbinate_o > 
            nr_celule_imbinate_v)
            {
                switch(rand_nr2)
                {
                    case 1:
                    ch = KEY_LEFT;
                    break;
                    case 2:
                    ch = KEY_RIGHT;
                    break;
                    default:
                    break;
                }
            }
            else if (nr_celule_imbinate_o <= 
            nr_celule_imbinate_v 
            && nr_celule_imbinate_v > 0)
            {
                switch(rand_nr2)
                {
                    case 1:
                    ch = KEY_UP;
                    break;
                    case 2:
                    ch = KEY_DOWN;
                    break;
                    default:
                    break;
                }
            }

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    copie_matr[i][j] = matr_joc[i][j];
                }
            }
            if (nr_celule_imbinate_o == 0
            && nr_celule_imbinate_v == 0)
            {
                if (nr_mutari_up)
                {
                    ch = KEY_UP;
                }
                if (nr_mutari_down)
                {
                    ch = KEY_DOWN;
                }
                if (nr_mutari_right)
                {
                    ch = KEY_RIGHT;
                }
                if (nr_mutari_left)
                {
                    ch = KEY_LEFT;
                }
            }
        }
        if (ch == KEY_UP || ch == KEY_DOWN || 
            ch == KEY_RIGHT || ch == KEY_LEFT)
        {
            if (ch == KEY_UP)
            {
                nr_mutari = up(window, matr_joc, &scor, 1);
                show_time(window);
                wrefresh(window);
            }
            else if (ch == KEY_DOWN)
            {
                nr_mutari = down(window, matr_joc, &scor, 1);
                show_time(window);
                wrefresh(window);
            }
            else if (ch == KEY_RIGHT)
            {
                nr_mutari = right(window, matr_joc, &scor, 1);
                show_time(window);
                wrefresh(window);
            }
            else
            {
                nr_mutari = left(window, matr_joc, &scor, 1);
                show_time(window);
                wrefresh(window);
            }
            if (verif_2048_win(matr_joc))
            {
                win(window);
                break;
            }
            casute_marcate = marked(matr_joc);
            if (casute_marcate < 16 && nr_mutari != 0)
            {
                rand_nr = (rand() % 3) + 2;
                if (rand_nr == 3)
                {
                    rand_nr = 2;
                }
                do
                {
                    lin = (rand() % 4) + 1;
                    col = (rand() % 4) + 1;
                }while (matr_joc[lin - 1][col - 1]);

                matr_joc[lin - 1][col - 1] = rand_nr;
                color(window, lin - 1, col - 1, rand_nr);
                casute_marcate++;
            }
            if (casute_marcate == 16 && verif(matr_joc))
            {
                timeout(-1);
                return scor * (-1);
            }
        }
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }
        nr_mutari_up = up(window, copie_matr, &scor, 2);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }
        nr_mutari_down = down(window, copie_matr, &scor, 2);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }
        nr_mutari_right = right(window, copie_matr, &scor, 2);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                copie_matr[i][j] = matr_joc[i][j];
            }
        }

        nr_mutari_left = left(window, copie_matr, &scor, 2);
        valid_commands(nr_mutari_up, nr_mutari_down,
                        nr_mutari_left, nr_mutari_right, window);
        wrefresh(window);
        ch = getch();
    }
    timeout(-1);
    if(ch == 'q' || ch == 'Q')
    {
        return scor;
    }
}

//fereastra pentru joc pierdut
void game_ov(WINDOW *window)
{
    werase(window);
    box(window, 0, 0);
    mvwprintw(window, 10, 12, "  GAME OVER!!!  ");
    wrefresh(window);
}

//resume
int window_resume(WINDOW *window, int **matr_joc, int scor)
{
    int i, j, val;
    if (scor == -1)
    {
        werase(window);
        box(window, 0, 0);
        mvwprintw(window, 10, 5, "  NU AI JUCAT NICIUN JOC!!!  ");
        wrefresh(window);
        return -1;
    }

    window_new_game(window, scor);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (matr_joc[i][j])
            {
                color(window, i, j, matr_joc[i][j]);
            }
        }
    }
    wrefresh(window);
    val = new_game(window, matr_joc, 2, scor);
    return val;
}

//fereastra high score
void show_score(WINDOW *window, int scor)
{
    werase(window);
    box(window, 0, 0);
    wattron(window, COLOR_PAIR(11));
    wattron(window, A_BOLD);
    mvwprintw(window, 7, 12, "  HIGH SCORE: ");
    wrefresh(window);
    wattroff(window, COLOR_PAIR(11));
    wattroff(window, A_BOLD);

     //linia de sus
    mvwhline(window, 10, 3, ACS_HLINE, 33);
    //linia de jos
    mvwhline(window, 14, 3, ACS_HLINE, 33);

    //coloana stanga
    mvwvline(window, 10, 3, ACS_VLINE, 4);
    //coloana dreapta
    mvwvline(window, 10, 36, ACS_VLINE, 4);

    //coltul stanga sus
    mvwaddch(window, 10, 3, ACS_ULCORNER);
    //coltul dreapta sus
    mvwaddch(window, 10, 36, ACS_URCORNER);
    //coltul stanga jos
    mvwaddch(window, 14, 3, ACS_LLCORNER);
    //coltul dreapta jos
    mvwaddch(window, 14, 36, ACS_LRCORNER);

    mvwprintw(window, 12, 4, "SCORUL MAXIM OBTINUT ESTE: %d", scor);
}

int main()
{
    int val_meniu, val_game, ok, ch;
    int **matr_joc;
    int primul_joc = 0;
    int scor_maxim = 0;
    int i;
    int val = 5;

    //initializeaza fereastra
    //aloca memorie
    initscr();

    //pentru stoparea pastrarii liniei
    raw();

    //pentru folosirea tastelor
    keypad(stdscr, TRUE);

    //nu permite afisarea caracterelor
    //introduse de utilizator la tastatura
    noecho();

    //ascunde cursorul
    curs_set(0);

    //initializeaza suportul pentru culori
    start_color();
    init_pair(100, COLOR_WHITE, COLOR_BLACK);

    //crearea unei ferestre pentru ecranul jocului
    WINDOW *window = newwin(20, 40, 1, 1);
    refresh();
    //ecranul meniului
    WINDOW *menu_choice = newwin(20, 40, 1, 1);
    refresh();
    //ecranul high scores
    WINDOW *highScor = newwin(20, 40, 1, 1);
    refresh();
    //jocul antorior pt resume
    WINDOW *game_resume = newwin(20, 40, 1, 1);
    //game over
    WINDOW *game_over = newwin(20, 40, 1, 1);
    //adaug contur ecranului
    box(window, 0, 0);
    box(menu_choice, 0, 0);
    box(highScor, 0, 0);
    box(game_resume, 0, 0);
    box(game_over, 0, 0);
    //actualizam caracteristicile de fundal
    wbkgd(window, COLOR_PAIR(100));
    wbkgd(menu_choice, COLOR_PAIR(100));
    wbkgd(highScor, COLOR_PAIR(100));
    wbkgd(game_resume, COLOR_PAIR(100));
    wbkgd(game_over, COLOR_PAIR(100));

    matr_joc = (int **) malloc(5 * sizeof(int *));

    for (i = 0; i <= 4; i++)
    {
        matr_joc[i] = (int *) malloc(5 * sizeof(int));
    }

    //culori pentru patratele din joc de valori diferite
    i = 1;
    init_pair(val + i, COLOR_WHITE, COLOR_BLUE);
    i++;
    init_pair(val + i, COLOR_WHITE, COLOR_MAGENTA);
    i++;
    init_pair(val + i, COLOR_WHITE, COLOR_RED);
    i++;
    init_pair(val + i, COLOR_WHITE, COLOR_YELLOW);
    i++;
    init_pair(val + i, COLOR_WHITE, COLOR_GREEN);
    i++;
    init_pair(val + i, COLOR_WHITE, COLOR_CYAN);
    i++;
    init_pair(val + i, COLOR_WHITE, 70);
    i++;
    init_pair(val + i, COLOR_WHITE, 20);
    i++;
    init_pair(val + i, COLOR_WHITE, 105);
    i++;
    init_pair(val + i, COLOR_WHITE, 30);
    i++;
    init_pair(val + i, COLOR_WHITE, 42);
    i++;

    ok = 1;
    val_meniu = menu(menu_choice);
    //afisez continutul ecranului
    wrefresh(menu_choice);

    while (ok)
    {
        ok = 0;
        if (val_meniu == 1)
        {
            val_game = new_game(window, matr_joc, 1, 0);
            wrefresh(window);
            primul_joc = 1;
            if (val_game >= 0)
            {
                ok = 1;
                val_meniu = menu(menu_choice);
                wrefresh(menu_choice);
                if (verif_2048_win(matr_joc))
                {
                    if (val_game > scor_maxim)
                    {
                        scor_maxim = val_game;
                    }
                }
            }
            if (val_game < 0)
            {
                val_game = val_game * (-1);
                game_ov(game_over);
                wrefresh(game_over);
                ch = getch();
                while (ch != 'q' && ch != 'Q')
                {
                    ch = getch();
                }
                ok = 1;
                val_meniu = menu(menu_choice);
                wrefresh(menu_choice);
                if (val_game > scor_maxim)
                {
                    scor_maxim = val_game;
                }
                val_game = val_game * (-1);
            }
            
        }
        else if (val_meniu == 2)
        {
            if (primul_joc == 0)
            {
                window_resume(game_resume, matr_joc, -1);
                wrefresh(game_resume);
                ch = getch();
                while (ch != 'q' && ch != 'Q')
                {
                    ch = getch();
                }
                ok = 1;
                val_meniu = menu(menu_choice);
                wrefresh(menu_choice);
            }
            else
            {
                if (val_game < 0)
                {
                    val_game = val_game * (-1);
                    game_ov(game_over);
                    wrefresh(game_over);
                    ch = getch();
                    while (ch != 'q' && ch != 'Q')
                    {
                        ch = getch();
                    }
                    ok = 1;
                    val_meniu = menu(menu_choice);
                    wrefresh(menu_choice);
                    if (val_game > scor_maxim)
                    {
                        scor_maxim = val_game;
                    }
                    val_game = val_game * (-1);
                }
                else
                {
                    val_game = window_resume(game_resume,
                                         matr_joc, val_game);
                    if (val_game >= 0)
                    {
                        wrefresh(game_resume);
                        ok = 1;
                        val_meniu = menu(menu_choice);
                        wrefresh(menu_choice);
                        if (verif_2048_win(matr_joc))
                        {
                            if (val_game > scor_maxim)
                            {
                                scor_maxim = val_game;
                            }
                        }
                    }
                    else if (val_game < 0)
                    {
                        val_game = val_game * (-1);
                        game_ov(game_over);
                        wrefresh(game_over);
                        ch = getch();
                        while (ch != 'q' && ch != 'Q')
                        {
                            ch = getch();
                        }
                        ok = 1;
                        val_meniu = menu(menu_choice);
                        wrefresh(menu_choice);
                        if (val_game > scor_maxim)
                        {
                            scor_maxim = val_game;
                        }
                        val_game = val_game * (-1);
                    }
                }
            }  
        }
        else if (val_meniu == 3)
        {
            show_score(highScor, scor_maxim);
            wrefresh(highScor);
            ch = getch();
            while (ch != 'q' && ch != 'Q')
            {
                ch = getch();
            }
            if (ch == 'q' || ch == 'Q')
            {
                ok = 1;
                val_meniu = menu(menu_choice);
                wrefresh(menu_choice);
            }
        }
        else
        {
            attroff(COLOR_PAIR(100));
            //dealoca memorie si incheie ncurses
            delwin(window);
            delwin(menu_choice);
            delwin(highScor);
            endwin();
            return 0;
        }
    }

    attroff(COLOR_PAIR(100));
    getch();
    //dealoca memorie si incheie ncurses
    delwin(window);
    delwin(menu_choice);
    delwin(highScor);
    endwin();
    return 0;
}
