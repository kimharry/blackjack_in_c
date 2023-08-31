// 1: spade, 2: heart, 3: diamond, 4: clober
// if 'times' is minus: computer's times
// if 'times' if plus: player's times

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define SPADE 1
#define HEART 2
#define DIAMOND 3
#define CLOBER 4

struct card
{
    int num;
    int shape;
} player_card[10] = {}, dealer_card[15] = {}, temp_deck[52], deck[52];

void windowsize(int a, int b);
void blue(void);
void yellow(void);
void red(void);
void white(void);
void shuffle(void);
void print_card(int num, int shape);
void pplay(void);
void dplay(int cards, int psum);
void choose_a(int *psum);

void windowsize(int a, int b)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX font = {};
    font.cbSize = sizeof(font);
    GetCurrentConsoleFontEx(out, 0, &font);
    font.dwFontSize.X = a;
    font.dwFontSize.Y = b;
    SetCurrentConsoleFontEx(out, 0, &font);
}

void blue(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
}

void yellow(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
}

void red(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
}

void white(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void shuffle(void)
{
    int i, j;
    for (i = 0; i < 52; i++)
    {
        temp_deck[i].num = i % 13 + 1;
        temp_deck[i].shape = i % 4 + 1;
    }

    srand(time(NULL));
    for (i = 0; i < 52; i++)
    {
        do
        {
            j = rand() % 52;
        } while (temp_deck[j].num == 0);

        memcpy(&deck[i], &temp_deck[j], sizeof(struct card));
        temp_deck[j].num = 0;
        temp_deck[j].shape = 0;
    }
}

void print_card(int num, int shape)
{
    switch (num)
    {
    case 1:
        printf("(A");
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        printf("(%d", num);
        break;
    case 11:
        printf("(J");
        break;
    case 12:
        printf("(Q");
        break;
    case 13:
        printf("(K");
        break;
    }

    switch (shape)
    {
    case SPADE:
        printf("��) ");
        break;
    case DIAMOND:
        printf("��) ");
        break;
    case HEART:
        printf("��) ");
        break;
    case CLOBER:
        printf("��) ");
        break;
    }
}

void choose_a(int *psum)
{
    char temp;
    printf("\nchoose A value of the card, input y for 1, n for 11\n");
    do
    {
        temp = getchar();
    } while (temp != 'y' && temp != 'n');

    if (temp == 'y')
    {
        printf("You've chosen 1 for card A\n");
        *psum += 1;
    }
    else
    {
        printf("You've chosen 11 for card A\n\n");
        *psum += 11;
    }
}

void pplay(void)
{
    int i, psum = 0;
    char temp;
    system("cls");
    shuffle();

    for (i = 0; i < 5; i++)
    {
        memcpy(&player_card[i], &deck[2 * i], sizeof(struct card));
        memcpy(&dealer_card[i], &deck[2 * i + 1], sizeof(struct card));
    }

    blue();
    printf("computer's cards: ");
    print_card(dealer_card[0].num, dealer_card[0].shape);
    printf("(?\?)\n");

    yellow();
    printf("\nplayer's card: ");
    print_card(player_card[0].num, player_card[0].shape);
    print_card(player_card[1].num, player_card[1].shape);
    printf("\n");

    for (i = 0; i < 2; i++)
    {
        if (player_card[i].num == 1)
        {
            white();
            choose_a(&psum);
        }
        else if (player_card[i].num == 11 || player_card[i].num == 12 || player_card[i].num == 13)
            psum += 10;
        else
            psum += player_card[i].num;
    }
    yellow();
    printf("sum of player's cards: %d\n\n", psum);

    white();
    if (psum == 21)
    {
        red();
        printf("Blackjack! Player win!\n");
        white();
        printf("You made 21 only with 2 cards!\n\n");
        return;
    }
    else if (psum > 21)
    {
        red();
        printf("Computer win!\n");
        white();
        printf("Sum of your cards is over 21\n\n");
        return;
    }

    for (i = 2; i < 5; i++)
    {
        int j;
        printf("y for more cards, n for stop\n");
        do
        {
            fflush(stdin);
            temp = getchar();
        } while (temp != 'y' && temp != 'n');
        system("cls");

        blue();
        printf("computer's cards: ");
        print_card(dealer_card[0].num, dealer_card[0].shape);
        printf("(?\?)\n");

        yellow();
        printf("\nplayer's card: ");

        if (temp == 'n')
        {
            for (j = 0; j <= i - 1; j++)
                print_card(player_card[j].num, player_card[j].shape);
            printf("\n\nsum of player's cards: %d\n\n", psum);
            dplay(i, psum);
            return;
        }

        else if (temp == 'y')
        {
            for (j = 0; j <= i; j++)
                print_card(player_card[j].num, player_card[j].shape);

            if (player_card[i].num == 1)
            {
                white();
                choose_a(&psum);
            }
            else if (player_card[i].num == 10 || player_card[i].num == 11 || player_card[i].num == 12 || player_card[i].num == 13)
                psum += 10;
            else
                psum += player_card[i].num;

            yellow();
            printf("\nsum of player's cards: %d\n\n", psum);
        }

        white();
        if (psum > 21)
        {
            red();
            printf("Computer win!\n");
            white();
            printf("Sum of your cards is over 21\n\n");
            return;
        }
    }

    red();
    printf("Player win!\n");
    white();
    printf("You got 5 cards and sum of your cards is not over 21\n\n");
    return;
}

void dplay(int cards, int psum)
{
    int i = 0, j, dsum = 0;
    system("cls");
    white();
    printf("Computer's turn!\n");
    Sleep(1000);
    system("cls");
    for (i = 0; i < 2; i++)
    {
        if (dealer_card[i].num == 1)
        {
            if (dsum > 10)
                dsum += 1;
            else
                dsum += 11;
        }
        else if (dealer_card[i].num == 10 || dealer_card[i].num == 11 || dealer_card[i].num == 12 || dealer_card[i].num == 13)
            dsum += 10;
        else
            dsum += dealer_card[i].num;
    }
    i = 0;

    if (dsum >= 17)
    {
        blue();
        printf("computer's cards: ");
        print_card(dealer_card[0].num, dealer_card[0].shape);
        print_card(dealer_card[1].num, dealer_card[1].shape);
        printf("\nSum of dealer's cards: %d\n", dsum);

        yellow();
        printf("\nplayer's card: ");
        for (j = 0; j < cards; j++)
            print_card(player_card[j].num, player_card[j].shape);
        printf("\nSum of player's cards: %d\n\n", psum);
        white();
    }

    else
    {

        while (dsum <= 16)
        {
            system("cls");
            dsum = 0;
            blue();
            printf("computer's cards: ");
            for (j = 0; j <= i + 1; j++)
            {
                print_card(dealer_card[j].num, dealer_card[j].shape);
                if (dealer_card[j].num == 1)
                {
                    if (dsum > 10)
                        dsum += 1;
                    else
                        dsum += 11;
                }
                else if (dealer_card[j].num == 10 || dealer_card[j].num == 11 || dealer_card[j].num == 12 || dealer_card[j].num == 13)
                    dsum += 10;
                else
                    dsum += dealer_card[j].num;
            }

            printf("\nSum of dealer's cards: %d\n", dsum);

            yellow();
            printf("\nplayer's card: ");
            for (j = 0; j < cards; j++)
                print_card(player_card[j].num, player_card[j].shape);
            printf("\nSum of player's cards: %d\n\n", psum);

            i++;
            Sleep(2000);
        }
    }

    white();
    if (psum > dsum)
    {
        red();
        printf("Player win!\n");
        white();
        printf("Sum of player's cards are closer to 21 than sum of computer's cards\n\n");
        return;
    }
    else if (psum == dsum)
    {
        red();
        printf("Draw!\n");
        white();
        printf("Both has same sum of cards\n\n");
        return;
    }
    else
    {
        if (dsum > 21)
        {
            red();
            printf("Player win!\n");
            white();
            printf("Sum of computer's cards is over 21\n\n");
            return;
        }
        else
        {
            red();
            printf("Computer win!\n");
            white();
            printf("Sum of computer's cards are closer to 21 than sum of player's cards\n\n");
            return;
        }
    }
}

int main(void)
{
    char again;
    char go_on;
    char rule;
    windowsize(30, 30);

    printf("Welcome to Blackjack!\n");
    printf("Do you know the rule of blackjack? y or n\n");
    do
    {
        fflush(stdin);
        rule = getchar();
    } while (rule != 'y' && rule != 'n');

    if (rule == 'n')
    {
        system("cls");
        printf("Blackjack is a game to make the sum of your cards to be closer to 21 than computer\n");
        printf("Each cards are counted as their numbers and J, Q, and K are counted as 10\n");
        printf("A can be counted one of 1 or 11 as you want\n");
        printf("If sum of cards is over 21, you will lose regardless of computer's sum\n");
        printf("\nPress y to start or n to quit\n");
        do
        {
            fflush(stdin);
            go_on = getchar();
        } while (go_on != 'y' && go_on != 'n');
        if (go_on == 'n')
            return 0;
        else
            goto start;
    }
    else
        goto start;

start:
    pplay();

    printf("Wanna play again? y or n\n");
    do
    {
        fflush(stdin);
        again = getchar();
    } while (again != 'y' && again != 'n');

    if (again == 'y')
    {
        printf("Ok, let's go again!\n");
        Sleep(1500);
        system("cls");
        goto start;
    }
    return 0;
}
