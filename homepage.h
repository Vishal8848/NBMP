#ifndef HOMEPAGE_H_INCLUDED
#define HOMEPAGE_H_INCLUDED

/*  HomePage - NBMP   */

#include "myheaders.h"

char title[MAX], slogan[MAX], in1[] = " (L)ogin ", inD[] = " (D)ashboard ", in2[] = " (R)egister ", in3[] = " (E)xit ", __ch;

int Home()  {
    homeflag = 1;
    loginflag = registerflag = 0;
    system("cls");
    snprintf(title, sizeof(title), "%c NATIONAL BUDGET MANAGEMENT PORTAL %c", 4, 4);
    snprintf(slogan, sizeof(slogan), "%c Framing Livelihoods Since Independence ! %c", 4, 4);
    pallete(32, 4, 100, 32);
    gotoxy(36, 7);       frame(92, 201, 187);
    gotoxy(36, 7 + 27);  frame(92, 200, 188);
    for(int i = 0; i < 26; i++) {
        if(i%2 == 0)    gotoxy(36, 8 + i);
        else    gotoxy(36, 34 - i);
        printf("%c", 186);
        for(int j = 0; j < 91; j++) printf(" ");
        printf("%c", 186);
        Sleep(50);
    }
    slowmo(2, 25, 44, 12, title), slowmo(1, 25, 58, 19, slogan);
    if(!loggedinflag)   widget(50, 26, 10, in1);
    else                widget(50, 26, 14, inD);
    widget(75, 26, 13, in2), widget(100, 26, 9, in3);
    return 0;
}

void Navigator()  {
    while(1){
        __ch = getch();
        if(__ch == '\b' || __ch == '\r')    continue;
        if(homeflag){
            switch(__ch)    {
            case 'l': case 'L': case 'd': case 'D':
                    if(!loggedinflag && (__ch == 'l' || __ch == 'L'))   {   UserLogin();    break;  }
                    else if(loggedinflag && (__ch == 'd' || __ch == 'D'))   {  DashBoard();  Home();   break;   }
                case 'r': case 'R': UserRegistration();    break;
                case 'e': case 'E': exit(1);               break;
                default : continue;
            }   continue;
        }
        else if(loginflag){
            switch(LAflag)   {
                case 0:
                    switch(__ch)    {
                        case 'b': case 'B': Home();                break;
                        case 'r': case 'R': UserRegistration();    break;
                        case 'y': case 'Y': UserLogin();           break;
                        default : continue;
                    }   break;
                case 1:
                    switch(__ch)    {
                        case 'b': case 'B': Home();                break;
                        case 'r': case 'R': UserLogin();           break;
                        default : if(!loggedinflag)             continue;
                    }   break;
            }
            if(loggedinflag)    {
                Loader();
                DashBoard();    }
            if(outofdash)   Home();
            continue;
        }
        else if(registerflag){
            switch(RAflag)  {
                case 0:
                    switch(__ch)    {
                        case 'b': case 'B': Home();                break;
                        case 'l': case 'L': UserLogin();           break;
                        default : continue;
                    }   break;
                case 1:
                    switch(__ch)    {
                        case 'b': case 'B': Home();                break;
                        case 'r': case 'R': UserRegistration();    break;
                        case 'l': case 'L': UserLogin();           break;
                        default : continue;
                    }   break;
                default : continue;
            }   continue;
        }
    }
}

#endif // HOMEPAGE_H_INCLUDED
