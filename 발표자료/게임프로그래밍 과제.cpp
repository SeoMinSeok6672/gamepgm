#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

void display_rule(void);
void draw_check02(int c, int r);
void reel_series(int r[][3]);
void gotoxy(int x, int y);
int game_progress(int money);
void display_reel(char rc[][3], int r[][3], int index);
void clear_text(void);
void game_control(char reel[][3], int reel_num[][3], int *money);
int return_money(int r[], int betting, int *case_n);
void display_start_screen(void);
void display_jackpot(void);
int get_valid_bet(void);
int get_valid_bet(int current_money);

int attempts = 0;  // 시도 횟수를 기록하는 변수

int main(void)
{
    char reel[6][3] = {"★", "♠", "◆", "♥", "♣", "○"};
    int reel_num[3][3];
    int money = 10000;
    
    srand(time(NULL));
    
    // 시작 화면 출력
    display_start_screen();
    
    printf("  슬롯머신 게임\n\n");
    display_rule();
    
    gotoxy(3, 5);
    printf("릴1 릴2 릴3");
    gotoxy(1, 6);
    draw_check02(3, 3);
    
    for (int i = 0; i < 3; i++) {
        reel_num[0][i] = rand() % 5;
    }
    
    reel_series(reel_num);
    
    do {
        game_control(reel, reel_num, &money);
    } while (money);
    
    gotoxy(3, 20);
    return 0;
}

void display_rule(void)
{
    gotoxy(30, 3); 
    printf("   릴1   릴2  릴3  사례금\n"); 
    gotoxy(30, 4); 
    printf("--------------------------\n");
    gotoxy(30, 5); 
    printf(" 1: ★   ★   ★\t*10\n"); 
    gotoxy(30, 6); 
    printf(" 2: ♠   ♠   ♠\t *7\n"); 
    gotoxy(30, 7); 
    printf(" 3: ◆   ◆   ◆\t *5\n"); 
    gotoxy(30, 8); 
    printf(" 4: ★   ★   기타\t *4\n"); 
    gotoxy(30, 9); 
    printf(" 5: ♠   ♠   기타\t *3\n"); 
    gotoxy(30, 10); 
    printf(" 6: ◆   ◆   기타\t *3\n"); 
    gotoxy(30, 11); 
    printf(" 7: ♥   ♥   기타\t *3\n"); 
    gotoxy(30, 12); 
    printf(" 8: ♣   ♣   기타\t *2\n"); 
    gotoxy(30, 13); 
    printf(" 9: ○   ○   기타\t *1\n"); 
}

void draw_check02(int c, int r)
{
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[12]; 
    for (i = 1; i < 12; i++) {
        b[i] = 0xa0 + i;
    }
    printf("%c%c", a, b[3]);
    for (i = 0; i < c - 1; i++) {
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[8]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for (i = 0; i < r - 1; i++) {
        printf("%c%c", a, b[2]);
        for (j = 0; j < c; j++) {
            printf("  ");
            printf("%c%c", a, b[2]);
        }
        printf("\n");
        printf("%c%c", a, b[7]);
        for (j = 0; j < c - 1; j++) {
            printf("%c%c", a, b[1]);
            printf("%c%c", a, b[11]);
        }
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[9]);
        printf("\n");
    }
    printf("%c%c", a, b[2]);
    for (j = 0; j < c; j++) {
        printf("  ");
        printf("%c%c", a, b[2]);
    }
    printf("\n");
    printf("%c%c", a, b[6]);
    for (i = 0; i < c - 1; i++) {
        printf("%c%c", a, b[1]);
        printf("%c%c", a, b[10]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

void reel_series(int r[][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            r[j][i] = (r[0][i] + j) % 6;
}

void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int game_progress(int money)
{
    int bet;

    // 유효한 배팅 금액을 입력받기
    bet = get_valid_bet(money);  // money 값을 전달

    if (bet == 0) {
        exit(0);  // 배팅 금액이 0이면 게임 종료
    }

    // 배팅 금액과 남은 금액을 함께 하단에 출력
    gotoxy(1, 24);
    printf("배팅 금액: %d원 | 남은 금액: %d원", bet, money);

    return bet;
}



int get_valid_bet(int current_money)
{
    char input[100];
    int bet;

    while (1) {
        // 하단에 현재 남은 금액과 배팅 금액 입력 요청을 출력
        gotoxy(1, 22);
        printf("현재 남은 금액: %d원 | 배팅 금액을 입력하세요: ", current_money);

        // 입력받기
        fgets(input, sizeof(input), stdin);

        // 입력값이 숫자인지 확인
        if (sscanf(input, "%d", &bet) == 1 && bet >= 0) {
            // 배팅 금액이 현재 돈보다 크지 않도록 처리
            if (bet > current_money) {
                gotoxy(1, 23);
                printf("현재 금액보다 큰 배팅은 할 수 없습니다. 다시 입력해주세요.");
            } else {
                // 오류 메시지 삭제
                gotoxy(1, 23);
                printf("                                                      ");  // 오류 메시지 지우기
                return bet;  // 유효한 금액 입력
            }
        } else {
            gotoxy(1, 23);
            printf("잘못된 숫자를 입력하셨습니다. 다시 입력해주세요: ");
        }
    }
}


void display_reel(char rc[][3], int r[][3], int index)
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = index; j < 3; j++) {
            gotoxy(3 + j * 4, 7 + i * 2);
            printf("%s", rc[r[i][j]]);
        }
}

void clear_text(void)
{
    int i, j;
    for (i = 17; i < 20; i++) {
        gotoxy(1, i);
        for (j = 0; j < 42; j++)
            printf(" ");
    }
}

void game_control(char reel[][3], int reel_num[][3], int *money)
{
    int i, j, bet, case_num = 0, thank, num[3];
    double pst;
    clock_t start, end;

    display_reel(reel, reel_num, 0);
    bet = game_progress(*money);

    for (i = 0; i < 3; i++) {
        start = clock();
        do {
            for (j = i; j < 3; j++)
                reel_num[0][j] = reel_num[1][j];
            reel_series(reel_num);
            display_reel(reel, reel_num, i);
            end = clock();
            pst = (double)(end - start) / CLK_TCK;
        } while (!kbhit() || (pst < 1));
        num[i] = reel_num[1][i];
    }
    getch();
    thank = return_money(num, bet, &case_num);
    if (thank == 0)
        *money -= bet;
    else
        *money += thank;

    // 잭팟 체크
    if (num[0] == num[1] && num[1] == num[2]) {
        display_jackpot();
    }

    // 시도 횟수 증가
    attempts++;

    // 10회 시도마다 경고 메시지 출력
    if (attempts % 10 == 0) {
        gotoxy(1, 21);
        printf("과도한 게임은 건강과 가족의 행복을 해칠 수 있습니다. 적절한 휴식과 함께 책임질 수 있는 게임을 하십시오!");
    }
}

int return_money(int r[], int betting, int *case_n)
{
    if (r[0] == r[1] && r[1] == r[2]) {
        if (r[0] == 0) {
            *case_n = 1;
            return (betting * 10);
        }
        else if (r[0] == 1) {
            *case_n = 2;
            return (betting * 7);
        }
        else if (r[0] == 2) {
            *case_n = 3;
            return (betting * 5);
        }
    }
    else if (r[0] == r[1]) {
        if (r[0] == 0) {
            *case_n = 4;
            return (betting * 4);
        }
        else if (r[0] == 1) {
            *case_n = 5;
            return (betting * 3);
        }
        else if (r[0] == 2) {
            *case_n = 6;
            return (betting * 3);
        }
        else if (r[0] == 3) {
            *case_n = 7;
            return (betting * 3);
        }
    }
    else if (r[1] == r[2]) {
        if (r[1] == 4) {
            *case_n = 8;
            return (betting * 2);
        }
        else if (r[1] == 5) {
            *case_n = 9;
            return (betting * 1);
        }
    }
    return 0;
}

void display_start_screen(void)
{
    printf("====================================\n");
    printf("          슬롯머신 게임             \n");
    printf("====================================\n");
    printf("게임을 시작하려면 아무 키나 누르세요\n");
    getch();  // 키 입력 대기
}

void display_jackpot(void)
{
    gotoxy(1, 20);
    printf("***** JACKPOT!!! *****");
}

