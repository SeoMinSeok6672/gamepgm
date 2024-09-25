#include <stdio.h>
#include <string.h>

typedef struct {
    int order;
    char shape[4];  
    char number[3]; 
} trump;

void make_card(trump m_card[]) {
    int i, j;
    char shape[4][4] = {"¢¼", "¡ß", "¢¾", "¢À"};  
    
    for (i = 0; i < 4; i++) {
        for (j = i * 13; j < i * 13 + 13; j++) {
            m_card[j].order = i;
            strcpy(m_card[j].shape, shape[i]);  
            
            int card_number = j % 13 + 1;
            switch (card_number) {
                case 1:
                    strcpy(m_card[j].number, "A");  
                    break;
                case 11:
                    strcpy(m_card[j].number, "J");  
                    break;
                case 12:
                    strcpy(m_card[j].number, "Q");  
                    break;
                case 13:
                    strcpy(m_card[j].number, "K");  
                    break;
                default:
                    sprintf(m_card[j].number, "%d", card_number);  
                    break;
            }
        }
    }
}

void display_card(trump m_card[]) {
    int i, count = 0;
    for (i = 0; i < 52; i++) {
        printf("%s", m_card[i].shape);

        if (strcmp(m_card[i].number, "A") == 0 || 
            strcmp(m_card[i].number, "J") == 0 || 
            strcmp(m_card[i].number, "Q") == 0 || 
            strcmp(m_card[i].number, "K") == 0) {
            printf("%-2s", m_card[i].number);  
        } else {
            printf("%-2s", m_card[i].number);  
        }

        count++;
        if ((i % 13) == 12) { 
            printf("\n");
            count = 0;
        }
    }
}
int main() {
    trump m_card[52];
    make_card(m_card);  

    display_card(m_card); 

    return 0;
}


