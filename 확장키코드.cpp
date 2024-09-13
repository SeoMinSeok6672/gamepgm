#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define X_MAX 79 
#define Y_MAX 24 

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b) {
    switch (chr) {
        case 72:  
            if (*y > 0) (*y)--;
            break;
        case 80:  
            if (*y < y_b) (*y)++;
            break;
        case 75: 
            if (*x > 0) (*x)--;
            break;
        case 77: 
            if (*x < x_b) (*x)++;
            break;
    }
}

int main(void) {
    char key;
    int x = 10, y = 5;
    do {
        gotoxy(x, y);
        printf("A");
        key = getch();
        move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
    } while (key != 27);  
    return 0;
}

