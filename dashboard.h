#ifndef DASHBOARD_H_INCLUDED
#define DASHBOARD_H_INCLUDED

/*  DashBoard - NBMP   */

#include "myheaders.h"

/** bt - back to, gt - go to, dd - drop down  */
mystring btHome, gtStats = " (S)TATISTICS ", gtMnage = " (M)ANAGEMENT ", ddUser, gReport[3] = { "RBI Governor", "Year", "Budget" }, year_range, ddU[2] = { " (P)rofile ", " (L)og Out " };
mystring RBIg_name[3] = { "D. Subbarao", "R. Rajan", "Urjit Patel" };

int ddflag = 0, ddlim = 2, outofdash = 0;
int maxbarunit = 1000, barunit = 100, barspace  = 10, barpercent[4] = { 26, 33, 18, 23 };

void Interface(), DashboardNavig(), UserDropDown(), BreakupStats(), BarGraphStats(int), GraphCleaner();

int DashBoard()
{
    system("cls");
    Interface();
    DashboardNavig();
    return 0;
}

void Interface()
{
    pallete(8, 2, 141, 39);
    snprintf(btHome, MAX, " %c %c (H)OME ", 17, 179);
    snprintf(ddUser, MAX, "  (U)SER  %c %c ", 179, 31);
    widget(18 , 6, 13, btHome );
    widget(55 , 6, 15, gtStats);
    widget(90 , 6, 15, gtMnage);
    widget(125, 6, 15, ddUser );
    GraphCleaner();
    BarGraphStats(2021);
}

void UserDropDown()
{
    ddflag = !ddflag;
    if(ddflag)    {
        gotoxy(138, 7); printf("%c", 30);
        gotoxy(125, 8); printf("%c", 204);
        gotoxy(140, 8); printf("%c", 185);
        for(int i = 0; i < ddlim; i++)  {
            gotoxy(125, 9 + 2*i); printf("%c", 186);
            if((2*i + 1)%2 != 0) printf(" %s", ddU[i]);
            gotoxy(140, 9 + 2*i); printf("%c", 186);
            if(i != ddlim - 1)  {
                gotoxy(125, 10 + 2*i); printf("%c", 199);
                for(int j = 0; j < 14; j++) printf("%c", 196);
                gotoxy(140, 10 + 2*i); printf("%c", 182);   }
            else        {
                gotoxy(125, 10 + 2*i); printf("%c", 200);
                for(int j = 0; j < 14; j++) printf("%c", 205);
                gotoxy(140, 10 + 2*i); printf("%c", 188);         }
        }
    }
    else    {
        gotoxy(138, 7); printf("%c", 31);
        gotoxy(125, 8); printf("%c", 200);
        gotoxy(140, 8); printf("%c", 188);
        for(int j = 0; j < 2*ddlim; j++)    {
            gotoxy(125, 9 + j);
            for(int k = 0; k < 16; k++) printf(" ");
        }
    }
}

void BreakupStats()
{
    char ych, year_val[MAX];
    int graphyear, graphflag = 0;
    snprintf(year_range, sizeof(year_range), "%c ( 2011 - 2021 )", 17);
    gotoxy(43, 13);
    while(!graphflag)   {
        for(int i = 0;;)    {
            ych = getch();
            if(ych == '\r') {   year_val[i] = '\0';     break;  }
            else if(ych == '\b')   {  if(i > 0) {printf("\b \b"); year_val[i--] = '\0'; }   }
            else if(ych != ' ' && ych >= '0' && ych <= '9') {
                if(i < 5){
                    year_val[i++] = ych;
                    printf("%c", ych);
                }}}
        graphyear = atoi(year_val);
        if(graphyear >= 2011 && graphyear <= 2021)  {
            gotoxy(55, 13); for(int i = 0; i < 20; i++) printf(" ");
            GraphCleaner();
            BarGraphStats(graphyear);
            graphflag = 1;
        }   else    {
            gotoxy(55, 13); printf("%s", year_range);
            gotoxy(43, 13); printf("         \b\b\b\b\b\b\b\b\b");
        }
    }
}

void BarGraphStats(int year = 2020)
{
    float *barval = Implicit.BreakupfromDB(year);
    int minbar = 999, setbar[4] = {0};
    gotoxy(90, 20);
    if(year < 2013)      printf("%s", RBIg_name[0]);
    else if(year < 2016) printf("%s", RBIg_name[1]);
    else                 printf("%s", RBIg_name[2]);
    gotoxy(94, 24); printf("%d", year);
    gotoxy(90, 28); printf("%4.4f Cr.", barval[4]);
    for(int i = 0; i < 5; minbar = 999, i++)  {
        int getbar = (int)barval[i];
        for(int j = 1; j <= 20; j++)    if(abs(j*(barunit/2) - getbar) < minbar)    minbar = abs(j*(barunit/2) - getbar);
        for(int k = 1000; k > barunit; k -= 50) if(k == getbar + minbar || k == getbar - minbar) setbar[i] = k;
        //printf("-- %d (%d) [%d]-- ", getbar, minbar, setbar[i]);
    }
    for(int i = 0; i < 4; i++)  {
        gotoxy(30 + i*15, 37);  printf("%c", 207);
        for(int j = 0; j < (setbar[i]/(barunit/2)); Sleep(30), j++) {
            gotoxy(30 + i*15, 36 - j);
            if(j == (setbar[i]/(barunit/2)) - 1)    printf("%c%c%c%c%c", 218, 196, 196, 196, 191);
            else printf("%c   %c", 179, 179);
        }
        gotoxy(34 + i*15, 37);  printf("%c", 207);
        gotoxy(29 + i*15, 36 - (setbar[i]/(barunit/2)));    printf("%4.3f", barval[i]);
    }
}

void GraphCleaner()
{
    gotoxy(41, 12); frame(11, 218, 191, 196);
    gotoxy(25, 13); printf("Search (Y)ear : %c          %c", 179, 179);
    gotoxy(41, 14); frame(11, 192, 217, 196);
    gotoxy(16, 15); printf("Cr. Rs");
    pallete(24, 15, 62, 21);
    for(int i = 0; i < 10; i++) {
        gotoxy(18, 17 + 2*i);   printf("%4d", maxbarunit - (i*barunit));
        gotoxy(25, 17 + 2*i);   printf("\b%c", 199);
        for(int j = 0; j < 61; j++) printf("%c", 196);  printf("%c", 182);
        gotoxy(25, 16 + 2*i);   for(int j = 0; j < 61; j++) printf(" ");
    }
    gotoxy(25, 36);   for(int j = 0; j < 61; j++) printf(" ");
    gotoxy(25, 38); printf("   Healthcare       States        Defence       Education");
    gotoxy(25, 39); for(int i = 0; i < 4; i++)  printf("     (%2d%%)     ", barpercent[i]);
    for(int i = 0, j = 19; i < 3; i++, j+=4)    {
        gotoxy(88, j-1); printf("%s", gReport[i]);
        gotoxy(88, j  ); frame(15, 218, 191, 196);
        gotoxy(88, j+1); printf("%c              %c", 179, 179);
        gotoxy(88, j+2); frame(15, 192, 217, 196);
    }
}

void DashboardNavig()
{
    char dch;
    while(1)    {
        gotoxy(1,1);
        outofdash = 0;
        switch(dch = getch())
        {
            case 'H': case 'h':   outofdash = 1;                    break;
            case 'S': case 's':   printf("This is Stats");          break;
            case 'M': case 'm':   printf("This is Manage");         break;
            case 'U': case 'u':   UserDropDown();                   break;
            case 'Y': case 'y':   BreakupStats();                   break;
        }   if(outofdash) break;   }
}

#endif // DASHBOARD_H_INCLUDED
