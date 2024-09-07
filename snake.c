#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>
#include <string.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length = 5;
int bend_no = 0;
int len = 0;
char key;
int life = 3;

void record();
void load();
void Delay();
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x, int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();

struct coordinate
{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500], food, body[30];

int main()
{
    Print();
    system("cls");
    load();

    head.x = 25;
    head.y = 20;
    head.direction = RIGHT;
    bend[0] = head;

    Move();
    return 0;
}

void Move()
{
    int a, i;

    do
    {

        Food();
        fflush(stdin);

        len = 0;

        Delay();

        Boarder();

        if (head.direction == RIGHT)

            Right();

        else if (head.direction == LEFT)

            Left();

        else if (head.direction == DOWN)

            Down();

        else if (head.direction == UP)

            Up();

        ExitGame();

    } while (!kbhit());

    a = getch();
    if (a == 27)
    {
        system("cls");
        exit(0);
    }

    key = getch();
    if ((key == RIGHT && head.direction != LEFT && head.direction != RIGHT) || (key == LEFT && head.direction != RIGHT && head.direction != LEFT) || (key == UP && head.direction != DOWN && head.direction != UP) || (key == DOWN && head.direction != UP && head.direction != DOWN))

    {

        bend_no++;

        bend[bend_no] = head;

        head.direction = key;

        if (key == UP)

            head.y--;

        if (key == DOWN)

            head.y++;

        if (key == RIGHT)

            head.x++;

        if (key == LEFT)

            head.x--;

        Move();
    }

    else if (key == 27)

    {

        system("cls");

        exit(0);
    }

    else

    {

        printf("\a");

        Move();
    }
}

void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, b);
}
void load()
{
    int row, col, r, c, q;
    gotoxy(36, 14);
    printf("loading...");
    gotoxy(30, 15);
    for (r = 1; r <= 20; r++)
    {
        printf("%c", 177);
    }
    Sleep(500);
}
void Down()
{
    int i;
    for (i = 0; i <= (head.y - bend[bend_no].y) && len < length; i++)
    {
        GotoXY(head.x, head.y - i);
        {
            if (len == 0)
                printf("v");
            else
                printf("*");
        }
        body[len].x = head.x;
        body[len].y = head.y - i;
        len++;
    }
    Bend();
    if (!kbhit())
        head.y++;
}
void Delay()
{
    Score();
    long double i;
    for (i = 0; i <= (10000000); i++)
        ;
}

void ExitGame()
{
    int i;
    for (i = 4; i < length; i++)
    {
        if (body[0].x == body[i].x && body[0].y == body[i].y)
        {
            life--;
            if (life == 0)
                Sleep(2000);
        }
    }
    if (head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30)
    {
        life--;
        if (life >= 0)
        {
            head.x = 25;
            head.y = 20;
            bend_no = 0;
            head.direction = RIGHT;
            Move();
        }
        if (life == 0)
            Sleep(2000);
    }
    if (life == 0)
    {
        system("cls");
        printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
        record();
        exit(0);
    }
}
void Food()
{
    if (head.x == food.x && head.y == food.y)
    {
        length++;
        time_t a;
        a = time(0);
        srand(a);
        food.x = rand() % 70;
        food.y = rand() % 30;

        (food.x <= 10) ? food.x += 11 : 1;
        (food.y <= 10) ? food.y += 11 : 1;
    }
    else if (food.x == 0)
    {
        food.x = rand() % 70;
        (food.x <= 10) ? food.x += 11 : 1;

        food.y = rand() % 30;
        (food.y <= 10) ? food.y += 11 : 1;
    }
}
void Left()
{
    int i;
    for (i = 0; i <= (bend[bend_no].x - head.x) && len < length; i++)
    {
        GotoXY((head.x + i), head.y);
        {
            if (len == 0)
                printf("<");
            else
                printf("*");
        }
        body[len].x = head.x + i;
        body[len].y = head.y;
        len++;
    }
    Bend();
    if (!kbhit())
        head.x--;
}
void Right()
{
    int i;
    for (i = 0; i <= (head.x - bend[bend_no].x) && len < length; i++)
    {
        body[len].x = head.x - i;
        body[len].y = head.y;
        GotoXY(body[len].x, body[len].y);
        {
            if (len == 0)
                printf(">");
            else
                printf("*");
        }
        len++;
    }
    Bend();
    if (!kbhit())
        head.x++;
}
void Bend()
{
    if (!bend_no)
        return;

    int i, j, diff;
    for (i = bend_no; i >= 0 && len < length; i--)
    {
        if (bend[i].x == bend[i - 1].x)
        {
            diff = bend[i].y - bend[i - 1].y;
            if (diff < 0)
                for (j = 1; j <= (-diff); j++)
                {
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y + j;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
            else if (diff > 0)
                for (j = 1; j <= diff; j++)
                {
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y - j;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
        }
        else if (bend[i].y == bend[i - 1].y)
        {
            diff = bend[i].x - bend[i - 1].x;
            if (diff < 0)
                for (j = 1; j <= (-diff) && len < length; j++)
                {
                    body[len].x = bend[i].x + j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
            else if (diff > 0)
                for (j = 1; j <= diff && len < length; j++)
                {
                    body[len].x = bend[i].x - j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if (len == length)
                        break;
                }
        }
    }
}
void Boarder()
{
    system("cls");
    int i;
    GotoXY(food.x, food.y);
    printf("o");
    for (i = 10; i < 71; i++)
    {
        GotoXY(i, 10);
        printf("!");
        GotoXY(i, 30);
        printf("!");
    }
    for (i = 10; i < 31; i++)
    {
        GotoXY(10, i);
        printf("!");
        GotoXY(70, i);
        printf("!");
    }
}
void Print()
{
    printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
    getch();
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
    printf("\n\nPress any key to play game...");
    if (getch() == 27)
        exit(0);
}
void record()
{
    char plname[20], nplname[20], cha, c;
    int i, j, px;
    FILE *info;
    info = fopen("record.txt", "a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]", plname);
    for (j = 0; plname[j] != '\0'; j++)
    {
        nplname[0] = toupper(plname[0]);
        if (plname[j - 1] == ' ')
        {
            nplname[j] = toupper(plname[j]);
            nplname[j - 1] = plname[j - 1];
        }
        else
            nplname[j] = plname[j];
    }
    nplname[j] = '\0';
    fprintf(info, "Player Name :%s\n", nplname);
    time_t mytime;
    mytime = time(NULL);
    fprintf(info, "Played Date:%s", ctime(&mytime));
    fprintf(info, "Score:%d\n", px = Scoreonly());
    for (i = 0; i <= 50; i++)
        fprintf(info, "%c", '_');
    fprintf(info, "\n");
    fclose(info);
    printf("Wanna see past records press 'y'\n");
    cha = getch();
    system("cls");

    if (cha == 'y')
    {
        char fileContent[256];
        info = fopen("record.txt", "r");

        if (info == NULL)
            printf("Error in opening file!!!\n");

        while (fgets(fileContent, sizeof(fileContent), info))
        {
            printf("%s", fileContent);
        }
    }
    fclose(info);
}
int Score()
{
    int score;
    GotoXY(20, 8);
    score = length - 5;
    printf("SCORE : %d", (length - 5));
    score = length - 5;
    GotoXY(50, 8);
    printf("Life : %d", life);
    return score;
}
int Scoreonly()
{
    int score = Score();
    system("cls");
    return score;
}
void Up()
{
    int i;
    for (i = 0; i <= (bend[bend_no].y - head.y) && len < length; i++)
    {
        GotoXY(head.x, head.y + i);
        {
            if (len == 0)
                printf("^");
            else
                printf("*");
        }
        body[len].x = head.x;
        body[len].y = head.y + i;
        len++;
    }
    Bend();
    if (!kbhit())
        head.y--;
}