#include <stdio.h>
#include <conio.h>
int main(void)
{
	int chr;
	do
	{
		chr=getch();
		if (chr==0 || chr == 0xe0)
	{
			chr=getch();
			printf("확장키 code=%d\n", chr);
		}
		else
			printf("아스키 code=%d\n", chr);
		}while(1);
	return 0;
}
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
		switch(key)
		{
		case 72:
			*y1=*y1-1;
			if (*y1<1) *y1=1; 
			break;
		case 75:
			*x1=*x1-1;
			if (*x1<1) *x1=1;
				break;
		case 77:
			*x1=*x1+1;
			if (*x1>x_b) *x1=x_b;
			break;
		case 80: 
			*y1=*y1+1;
			if (*y1>y_b) *y1=y_b; 
			break;
		default:
			return;
		}
}
