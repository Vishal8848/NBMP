#ifndef MYHEADERS_H_INCLUDED
#define MYHEADERS_H_INCLUDED

/*  System Headers  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

/*  Namespace Utilities  */
using namespace std;

/* Macro Definitions */
#define MAX 100
#define TSIZE 33
#define BUFF_SIZE 1024
#define GAP(val)             \
            printf("\n");       \
            for(int i = 0; i < val; i++)  printf("\t");
#define jumpgap() printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t");
#define box(st, nd) printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", st, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, nd, st, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, nd);

/*  Control Flags   */
int homeflag = 0, loginflag = 0, registerflag = 0, loggedinflag = 0;

/*  Global Variablea   */
int i, j, k, gx, gy;

/* Local Headers   */
#include "utility.h"
#include "dbops.h"
#include "userlogin.h"
#include "userreg.h"
#include "dashboard.h"

#endif // MYHEADERS_H_INCLUDED
