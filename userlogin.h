#ifndef USERLOGIN_H_INCLUDED
#define USERLOGIN_H_INCLUDED

/*  Existing User : Login Page - NBMP   */

int upflag, pflag, LAflag;
char user[2][20] = { " Username : "," Password : " }, U0P1[2][20], _ch;

int UserLogin()
{
    loginflag = 1;
    homeflag = registerflag = loggedinflag = LAflag = 0;
    system("cls");
    pallete(56, 6, 38, 15);
    gx = 63, gy = 10;
    gotoxy(gx, gy);
    printf("   * USER CREDENTIALS *");
    for(i = 0; i < 2; i++)
    {
        gotoxy(gx - 5, gy + (i*3 + 3));
        printf("  %s", user[i]);
    }
    for(upflag = pflag = 0; upflag < 2; upflag++)
    {
        if(upflag == 1) pflag = 1;
        if(!pflag){
            gotoxy(gx - 4, gy + 3);
            printf("%c", 16);
        }
        else    {
            gotoxy(gx - 3, gy + 3);
            printf("\b ");
            gotoxy(gx - 4, gy + 6);
            printf("%c", 16);
        }
        gotoxy(gx + 9, gy + (upflag*3) + 3);
        for(i = 0;;)
        {
            _ch = getch();
            if(_ch == '\r') {  U0P1[upflag][i] = '\0';  break; }
            if(_ch == '\b')    {  if(i > 0){  U0P1[upflag][i--] = '\0';    printf("\b \b"); }   }
            else if(_ch != ' ') {
                if(i < 20)  {
                    printf("%c", _ch);
                    U0P1[upflag][i++] = _ch;
                    if(upflag)  {
                        Sleep(100);
                        printf("\b*");
                    }
                }
            }
        }
    }
    gotoxy(gx - 3, gy + 6); printf("\b ");  // " LOGIN "
    gotoxy(gx + 7, gy + 11);   frame(8, 201, 187);
    gotoxy(gx + 7, gy + 12);   printf("%c LOGIN %c", 185, 204);
    gotoxy(gx + 7, gy + 13);   frame(8, 200, 188);
    gotoxy(gx, gy + 9);
    LAflag = Implicit.PasswordAuthentication(U0P1[0], U0P1[1]);
    switch(LAflag)
    {
        case 0:
            printf("  * Incorrect Username *");
            gotoxy(gx - 10, gy + 15);
            printf("... (B)ack \t (R)egister \t Retr(y) ...");
            break;
        case 1:
            printf("\b\b\b* Invalid Username or Password *");
            gotoxy(gx - 5, gy + 15);
            printf("... (B)ack \t \t (R)etry ...");
            break;
        case 2:
            printf("   * Login Successful *");
            gotoxy(gx - 3, gy + 15);
            printf("Moving to DashBoard in 5 ...");;
            for(i = 4; i > 0; Sleep(1000), i--)  printf("\b\b\b\b\b%d ...", i);
            loggedinflag = 1;
            break;
        default:
            printf(" * System Fault *");
            gotoxy(gx - 5, gy + 15);
            printf("... (B)ack \t \t (R)etry ...");
            break;
    }
    return LAflag;
}

#endif // USERLOGIN_H_INCLUDED
