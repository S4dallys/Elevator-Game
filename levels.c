#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define ROW 21
#define COL 51

int isInRange(int row, int col)
{
    if (row >= 0 && row <= ROW-1) 
        if (col >= 0 && col <= COL-1)
            return 1;
    
    return 0;
}

int isValidMove(char ground[][COL], int x, int y, char key)
{
    switch(key)
    {
        case 'w':
            if (ground[x-1][y] != 'x')
            {
                return 1;
            }
            break;
        case 'a':
            if (ground[x][y-1] != 'x')
            {
                return 1;
            }
            break;
        case 's':
            if (ground[x+1][y] != 'x')
            {
                return 1;
            }
            break;
        case 'd':
            if (ground[x][y+1] != 'x')
            {
                return 1;
            }
            break;
    }
    return 0;
}

void printGame(char ground[][COL]) 
{
    int i;
    for (i=0; i<ROW; i++)
    {
        printf("%s\n", ground[i]);
    }
}

int main() {

    char key = 0;
    char ground[ROW][COL] = {
    " xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxx", 
	"  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  xxxxxxxxxxx", 
	"x  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  xxxxxxxxxxxx", 
	"xx  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  xxxxxxxxxxxxx", 
	"xxx  xxxxxxxxxxxxxxxxxxxxxxxxxxxxx  xxxxxxxxxxxxxx", 
	"xxxx  xxxxxxxxxxxxxxxxxxxxxxxxxxx  xxxxxxxxxxxxxxx", 
	"xxxxx  xxxxxxxxxxxxxxxxxxxxxxxxx  xxxxxxxxxxxxxxxx", 
	"xxxxxx  xxxxxxxxxxxxxxxxxxxxxxx  xxxxxxxxxxxxxxxxx", 
	"xxxxxxx  xxxxxxxxxxxxxxxxxxxxx  xxxxxxxxxxxxxxxxxx", 
	"xxxxxxxx  xxxxxxxxxxxxxxxxxxx  xxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxx  xxxxxxxxxxxxxxxxx  xxxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxxx  xxxxxxxxxxxxxxx  xxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxx  xxxxxxxxxxxxx  xxxxxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxx  xxxxxxxxxxx  xxxxxxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxx  xxxxxxxxx  xxxxxxxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxx  xxxxxxx  xxxxxxxxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxx  xxxxx  xxxxxxxxxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx  xxx  xxxxxxxxxxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxxx  x  xxxxxxxxxxxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxxxx   xxxxxxxxxxxxxxxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"};
    int col = 0;
    int row = 0;

    while(key != 'x')
    {
        system("cls");
        ground[row][col] = 'o';
        printGame(ground);
        key = getch();

        if (key == 'a' && isInRange(row, col - 1) && isValidMove(ground, row, col, key))
        {
            ground[row][col] = ' ';
            col--;
        } 
        else if (key == 'd' && isInRange(row, col + 1) && isValidMove(ground, row, col, key))
        {
            ground[row][col] = ' ';
            col++;
        }
        else if (key == 'w' && isInRange(row - 1, col) && isValidMove(ground, row, col, key))
        {
            ground[row][col] = ' ';
            row--;
        }
        else if (key == 's' && isInRange(row + 1, col) && isValidMove(ground, row, col, key))
        {
            ground[row][col] = ' ';
            row++;
        }
    }



    return 0;
}