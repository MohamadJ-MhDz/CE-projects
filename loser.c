#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clui.h"
#include <stdbool.h>
#include <time.h>

char all[10000];
struct login // before the first use of `l`.
{
    char firstName[50];
    char lastName[50];
    char userName[50];
    char password[50];
};
void starter();
void registration();
void login();
int check_pass(char c[]);
bool game();
bool loser_game();
void startGame();
int main()
{
    change_color(10);
    printf("Welcome to the LOSER!\n\n");
    reset_color();

    starter();
}
void starter()
{
    int option;

    change_color(12);
    printf("Press 1 to Sign-up\nPress 2 to Log-in\nPress 3 to Exit\n\n");
    reset_color();
    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 1:
        registration();
        break;
    case 2:
        login();
        break;
    case 3:
        system("cls");
        exit(0);
    }
    starter();
}
void registration(void)
{
    system("CLS");
    char firstname[30], lastName[30], password[30];
    struct login l;
    FILE *log;

    log = fopen("login.bin", "ab+");
    system("cls");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }
    change_color_rgb(150, 10, 15);
    printf("\nWelcome to the LOSER \nwe need you to enter your credentials for your account.\n");
    reset_color();
    printf("\nEnter your First Name:\n");
    scanf("%s", &l.firstName);
    getchar();

    printf("\nEnter your last Name:\n");
    scanf("%s", &l.lastName);
    getchar();

    for (int i = 0; i < 3; ++i)
    {
        printf(".");
        flush();
        delay(600);
    }
    change_color(7);
    printf("\nThank you.\nNow please set a username and password as credentials for system login.\nEnsure the username is not longer than 30 characters long.\nEnsure your password is at least 8 characters long and contains lowercase, uppercase, numerical and special character values.\n");
    reset_color();
    change_color(11);
    printf("\nEnter Username:\n");
    scanf("%s", &l.userName);
    do
    {
        printf("\nEnter Password:\n");
        scanf("%s", &l.password);
        printf("\n pass : %s \n", &l.password);
        if (check_pass(l.password) == 0)
            printf("Weak password\nType a new pass\n");
    } while (check_pass(l.password) == 0);
    fwrite(&l, sizeof(l), 1, log);
    reset_color();
    printf("\nConfirming details...\n...\nWelcome, %s!\n\n", l.firstName);
    printf("\nRegistration Successful!\n");
    delay(3500);
    getchar();
    system("CLS");
    fclose(log);
}

void login(void)
{
    system("CLS");
    char username[50], password[50];

    struct login l;

    FILE *log = fopen("login.bin", "rb");
    if (log == NULL)
    {
        printf("Error in opening the file!");
        starter();
    }

    printf("\nPlease Enter your login credentials below to enter your account\n\n");
    printf("Username:\n");
    scanf("%s", username);
    printf("\nPassword:\n");
    scanf("%s", password);
    int flag = 0;
    system("CLs");
    change_color(2);

    while (fread(&l, sizeof(l), 1, log))
    {
        printf("user : %s\npass : %s\n", l.userName, l.password);
        if (strcmp(username, l.userName) == 0 && strcmp(password, l.password) == 0)
        {
            system("CLs");
            printf("\nHi %s!\nyour Login was Successful \nyou are now in your account!\n", l.firstName);
            flag = 1;
            fclose(log);
            startGame();
        }
    }
    if (flag == 0)
        printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
    fclose(log);
    reset_color();
}
// return 1 yani password motabar ast
int check_pass(char c[])
{
    // check size of pass
    int sz = 0;
    while (c[sz] != '\0')
        sz++;
    if (sz < 8)
        return 0;
    // check small char, captal char,number char, special char
    int small = 0, captal = 0, number = 0, special = 0;
    for (int i = 0; i < sz; i++)
    {
        if (c[i] >= 'a' && c[i] <= 'z')
        {
            small = 1;
            continue;
        }
        if (c[i] >= 'A' && c[i] <= 'Z')
        {
            captal = 1;
            continue;
        }
        if (c[i] >= '0' && c[i] <= '9')
        {
            number = 1;
            continue;
        }
        // age ye char na harf bashe na adad pas khase
        special = 1;
    }
    if (small == 0 || captal == 0 || number == 0 || special == 0)
        return 0;
    return 1;
}

void startGame()
{
    int option;
    printf("Press 1 to play");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        loser_game();
        break;
    default:
        break;
    }
}

bool game(char c[])
{
    char loser[10] = {'l', 'o', 's', 'e', 'r'};
    int cnt_wrong = 0, cnt_true = 0;
    int size = 0;
    bool flag[30], flag2[30];
    for (int i = 0; i < 30; i++)
    {
        flag[i] = 0;
        flag2[i] = 0;
    }
    while (c[size] != '\0')
        size++;
    bool x = 0;
    while (cnt_wrong < 5 && cnt_true < size)
    {
        change_color(7);
        for (int i = 0; i < cnt_wrong; i++)
            printf("%c", loser[i]);
        for (int i = cnt_wrong; i < 5; i++)
            printf(" _ ");
        printf("\n... Your chances : %d\n", 5 - cnt_wrong);
        for (int i = 0; i < size; i++)
        {
            if (flag2[i])
                printf("%c", c[i]);
            else
                printf("_");
        }
        reset_color();
        printf("\n");
        change_color(7);
        printf("\n... Enter a character : \n");
        reset_color();
        char input;
        if (!x)
        {
            x = 1;
            getchar();
        }
        //        getchar();
        scanf("%c", &input);
        //       printf("input : %c\n", input);
        getchar();
        if (input < 'a')
            input += 32;
        if (input > 'z' || input < 'a')
        {
            change_color(5);
            printf("\n..... Invalid input .....\n");
            reset_color();
            continue;
        }
        if (flag[input - 'a'])
        {
            change_color(6);
            printf("\n..... This char is already Entered .....\n");
            reset_color();
            continue;
        }
        flag[input - 'a'] = 1;
        int k = 0;
        for (int i = 0; i < size; i++)
        {
            if (input == c[i] || input == c[i] + 32)
            {
                flag2[i] = 1;
                k++;
            }
        }
        if (k == 0)
            cnt_wrong++;
        cnt_true += k;
    }
    change_color(6);
    printf("\n..... The hidden word is : %s .....\n", c);
    reset_color();
    if (cnt_true == size)
    {
        printf("\n");
        change_background_color(3);
        printf("......you Won......");
        reset_color();
        printf("\n");
        return 1;
    }
    printf("\n");
    change_background_color(5);
    printf(".....you Lost.....");
    reset_color();
    printf("\n");
    return 0;
}
bool loser_game()
{
    char words[50][50] = {"Google", "Telegram", "OneDrive", "Youtube", "Chrome", "Gmail", "Facebook", "Spotify", "PayPal", "Twitch", "Uber", "whatsapp"};
    change_color(7);
    printf("\n..... Welcome to loser_game .....\n");
    reset_color();
    delay(3500);
    // chose random word from words[][]
    srand(time(NULL));
    int ind = rand() % 12;
    return game(words[ind]);
}