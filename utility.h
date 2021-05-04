// utility.h - Program Utilities //

COORD coord = {0, 0};

void gotoxy(int x, int y)   {
    coord.X = x, coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void frame(int size, int left, int right, int middle = 205)   {
    for(int i = 0; i < size; i++) {
        if(i == 0)  printf("%c", left);
        if(i == size - 1) printf("%c", right);
        else printf("%c", middle);
    }
}

void pallete(int px, int py, int length, int breadth)   {
    gotoxy(px, py);   frame(length, 201, 187);
    for(int i = 0; i < breadth; i++) {
        gotoxy(px, py + i + 1);             printf("%c", 186);
        gotoxy(px + length, py + i + 1);    printf("%c", 186);
    }
    gotoxy(px, py + breadth + 1);  frame(length, 200, 188);
}

void slowmo(int space, int millisec, int x, int y, char *text)  {
    int mover = 0;
    for(char *ptr = text; *ptr != '\0'; ptr++, mover += space)  {
        gotoxy(x + mover, y);
        printf("%c", *ptr);
        Sleep(millisec);
    }
}

void widget(int x, int y, int size, char *word) {
    Sleep(10);  gotoxy(x,   y); frame(size, 201, 187);
    Sleep(10);  gotoxy(x, ++y); printf("%c%s%c", 186, word, 186);
    Sleep(10);  gotoxy(x, ++y); frame(size, 200, 188);
}

void Loader()   {
    system("cls");
    slowmo(3, 30, 60, 18, "LOADING...");
    for(int i = 0; i < 2; i++){
        Sleep(50);  gotoxy(72, 21); printf("|");
        Sleep(50);  gotoxy(74, 21); printf("/");
        Sleep(50);  gotoxy(74, 22); printf("%c", 196);
        Sleep(50);  gotoxy(74, 23); printf("\\");
        Sleep(50);  gotoxy(72, 23); printf("|");
        Sleep(50);  gotoxy(70, 23); printf("/");
        Sleep(50);  gotoxy(70, 22); printf("%c", 196);
        Sleep(50);  gotoxy(70, 21); printf("\\");

        Sleep(50);  gotoxy(72, 21); printf(" ");
        Sleep(50);  gotoxy(74, 21); printf(" ");
        Sleep(50);  gotoxy(74, 22); printf(" ");
        Sleep(50);  gotoxy(74, 23); printf(" ");
        Sleep(50);  gotoxy(72, 23); printf(" ");
        Sleep(50);  gotoxy(70, 23); printf(" ");
        Sleep(50);  gotoxy(70, 22); printf(" ");
        Sleep(50);  gotoxy(70, 21); printf(" ");    }
    system("cls");
}
