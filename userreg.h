#ifndef USERREG_H_INCLUDED
#define USERREG_H_INCLUDED

/*  New User : Registration Page - NBMP   */

typedef char mystring[MAX];

mystring attributes[7] = {"First Name : ", "Last Name : ", "Mobile : ", "Email ID : ", "User Name : ", "Password : ", "Confirm Password : "};
mystring getattri[7] = {"<enter first name>", "<enter last name>", "<98XXX XXXXX>", "<example@gmail.com>", "<example1234>", "<enter password>", "<retype password>"};
mystring attributerror[7] = {"Give a Nice Name !", "Field Empty !!", "Invalid Number !", "Is this an Address ?", "Not Fat Enough !", "Make it Tough !", "Ouch ! Failed to Confirm"};

typedef struct {
    char fname[16], lname[16];
    char mobile[12], email[26], valid[4];
    char username[21], password[21];
    char confpasswd[21], showpasswd[21];
}Register;

int count, sflag, showflag, vflag, errflag[7] = {0}, statusflag, RAflag, status(int, Register);
int counter[7] = {18, 17, 13, 19, 13, 16, 17}, sizer[7]   = {15, 15, 11, 25, 20, 20, 20};

int UserRegistration()
{
    registerflag = 1;
    homeflag = loginflag = statusflag = RAflag = 0;
    char ch, check;
    Register test;
    system("cls");
    pallete(48, 3, 55, 30);
    gx = 54, gy = 10;
    for(int i = 0; i < 7; i++)  {
        gotoxy(gx, gy + i*3);
        printf("%20s", attributes[i]);
        errflag[i] = 0;
    }
    gotoxy(gx + 10, gy - 3);
    printf("* USER CREDENTIALS *");
    for(int flag = 0; flag < 7; flag++) {
        mystring common;
        gotoxy(gx + 52, gy + flag*3);
        if(errflag[flag])   printf("%c %s", 17, attributerror[flag]);
        gotoxy(gx + 20, gy + flag*3);
        for(count = 0; count < MAX; )   {
            if(count == 0)  {   printf("%s", getattri[flag]); sflag = 1;}
            ch = getch();
            if(sflag == 1)  {
                for(count = counter[flag]; count != 0; count--) printf("\b");
                for(count = 0; count < counter[flag]; count++) printf(" " );
                for(count = counter[flag]; count != 0; count--) printf("\b");
                sflag = 0;
            }
            if(ch == '\r') {   common[count] = '\0'; break; }
            else if(ch == '\b') {   if(count > 0)   {  printf("\b \b"); common[count--] = '\0';  }   }
            else if(ch != ' '){
                if(count < sizer[flag]) {
                    if((flag <= 1 && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) || (flag == 2 && (ch >= '0' && ch <= '9'))){
                        printf("%c", ch);
                        common[count++] = ch;
                    }
                    else if(flag >= 3)  {
                        if(flag == 6)   printf("*");
                        else printf("%c", ch);
                        if(flag == 5)  {
                            Sleep(100);
                            printf("\b*");
                        }
                        common[count++] = ch;
        }}}}
        switch(flag)    {
            case 0 :    strcpy(test.fname     , common); break;
            case 1 :    strcpy(test.lname     , common); break;
            case 2 :    strcpy(test.mobile    , common); break;
            case 3 :    strcpy(test.email     , common); break;
            case 4 :    strcpy(test.username  , common); break;
            case 5 :    strcpy(test.password  , common); break;
            case 6 :    strcpy(test.confpasswd, common); break;
        }
        statusflag = status(flag, test);
        if(statusflag)  {
            if(flag == 6){
                strcpy(test.valid, "YES");
                strcpy(test.showpasswd, test.password);
            }
            gotoxy(gx + 52, gy + flag*3);   // Cancel Error
            for(i = 0; i < 30; i++)    printf(" ");
        }
        else    {
            gotoxy(gx + 20, gy + flag*3);   // Refill Space
            for(i = 0; i < 25; i++)    printf(" ");
            errflag[flag] = 1, --flag;
            continue;
        }
        if(flag == 6 && strcmp(test.valid, "YES") == 0)  {
            gotoxy(gx, gy + flag*3);
            printf("%20s", "Show Password : ");
            checkpass:
            for(i = 0; i < strlen(test.showpasswd); i++)    {
                if(showflag == 1)   printf("%c", test.showpasswd[i]);
                else if(showflag == 0) printf("*");
            }
            if(showflag == 1)   {
                showflag = 0;   Sleep(1000);
                for(i = strlen(test.password); i != 0; i--) printf("\b");
                for(i = 0; i < strlen(test.password); i++ ) printf(" " );
                for(i = strlen(test.password); i != 0; i--) printf("\b");
                goto checkpass;
            }
            printf(" (y/n)");
            getcheck:   check = getch();
            if(check == 'y' || check == 'Y')    {
                showflag = 1;
                for(i = strlen(test.password) + 6; i != 0; i--) printf("\b");
                for(i = 0; i < strlen(test.password) + 6; i++ ) printf(" " );
                for(i = strlen(test.password) + 6; i != 0; i--) printf("\b");
                goto checkpass;
            }
            else if(check == 'N' || check == 'n')   break;
            else goto getcheck;
        }
    } // " REGISTER "
    gotoxy(gx + 14, gy + 23);   frame(11, 201, 187);
    gotoxy(gx + 14, gy + 24);   printf("%c REGISTER %c", 185, 204);
    gotoxy(gx + 14, gy + 25);   frame(11, 200, 188);
    gotoxy(gx +  8, gy + 21);
    RAflag = Implicit.UsernameAuthentication(test.username);
    switch(RAflag)
    {
        case 0:
            printf("* Registration %s *", Implicit.UserRegistration(test.fname, test.lname, test.mobile, test.email, test.username, test.password));
            gotoxy(gx +  6, gy + 27);
            printf("... (B)ack \t (L)ogin...");
            break;
        case 1:
            printf("* Username Already Exists *");
            gotoxy(gx +  3, gy + 27);
            printf("... (B)ack \t (R)etry\t (L)ogin ...");
            break;
    }
    return RAflag;
}

int status(int flagval, Register test){
    switch(flagval) {
            case 0 :    return (strlen(test.fname)  >  2);
            case 1 :    return (strlen(test.lname)  >  0);
            case 2 :    return (strlen(test.mobile) >  9);
            case 3 :    return (strlen(test.email)  > 10);
            case 4 :    return (strlen(test.username) > 5);
            case 5 :    return (strlen(test.password) > 8);
            case 6 :    return (strcmp(test.password, test.confpasswd) == 0);
            default:    return 0;
    }
    return 0;
}

#endif // USERREG_H_INCLUDED
