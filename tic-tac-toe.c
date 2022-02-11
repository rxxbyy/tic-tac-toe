/* Tic Tac Toe game in C */
#include <stdio.h>
#include <ctype.h>


typedef struct {
    char slots[10];
} Table;

typedef struct {
    char *username;
    char symbol;
} Player;

void initializeTable(Table *table);
void printTable(Table *table);
void getPlayer(char *prompt, char *usernameVariable, char *symbolVariable);
char getPlayerOpposite(char playerSymbol);
void printPlayer(Player *player);
void play(char *lastPlay, Table *ptrTable);
char checkWinner(Table *ptrTable);
void printWinner(char winnerSymbol, Player *playerOne, Player *playerTwo);
int freeSpace(Table *ptrTable);


int main()
{
    Table table;
    initializeTable(&table);

    char winner;

    char currentUsernameInput[20];
    char currentSymbolInput;

    /* Asking for player's usernames and symbol */
    getPlayer("[FOR PLAYER ONE] Enter your username: ",
        currentUsernameInput, &currentSymbolInput);

    Player playerOne = {currentUsernameInput, currentSymbolInput};

    printf("[FOR PLAYER TWO] Enter your username: ");
    
    char usernameTwo[20];
    scanf("%20s", usernameTwo);

    currentSymbolInput = getPlayerOpposite(playerOne.symbol);

    Player playerTwo = {usernameTwo, currentSymbolInput};

    /* Printing both players */
    printPlayer(&playerOne);
    printPlayer(&playerTwo);

    /* Starting the mainloop */
    char lastPlay = playerTwo.symbol;

    int playing = 1;
    while (playing == 1) {
        printTable(&table);
        play(&lastPlay, &table);
        winner = checkWinner(&table);

        switch (winner) {
            case 'N':
                playing = 1;
                break;
            case 'X':
            case 'O':
                printTable(&table);
                printWinner(winner, &playerOne, &playerTwo);
                playing = 0;
                break;
            case 'T':
                printTable(&table);
                printf("\nGame ends in tie\n");
                playing = 0;
                break;
        }
    }

    return 0;
}

void initializeTable(Table *table)
{
    for (int i = 0; i < 9; i++) {
        table->slots[i] = 'N';
    }
}

void printTable(Table *table)
{
    int i = 0;
    int pattern = 0;

    while (table->slots[i] != '\0') {
        if (table->slots[i] == 'N') printf("| %c|", ' ');
        else printf("| %c|", table->slots[i]);
        pattern++;

        if (pattern == 3) {
            printf("\n---+---+---\n");
            pattern = 0;
        }

        i++;
    }
}

void getPlayer(char *prompt, char *usernameVariable, char *symbolVariable)
{
    printf("%s", prompt);
    scanf("%20s", usernameVariable);

    while (1) {
        printf("Select your symbol\n%2c\n%2c\n-> ", 'X', 'O');
        scanf("\n%c", symbolVariable);
        *symbolVariable = toupper(*symbolVariable);

        if (*symbolVariable != 'X' && *symbolVariable != 'O') {
            puts("\nInvalid selection. Try again\n");
            continue;
        }

        break;
    }
}

char getPlayerOpposite(char playerSymbol)
{
    if (playerSymbol == 'X') return 'O';
    else return 'X';
}

void printPlayer(Player *player)
{
    printf("%s:%2c\n", player->username, player->symbol);
}

void play(char *lastPlay, Table *ptrTable)
{
    int slot;

    printf("Plays \"%c\"\n", getPlayerOpposite(*lastPlay));

    while (1) {
        printf("\nEnter a number of slot [1-9]: ");
        scanf("%1d", &slot);

        if (slot > 0 && slot < 10) {
            if (ptrTable->slots[slot - 1] != 'N') {
                printf("Slot is not free");
            } else {
                ptrTable->slots[slot - 1] = getPlayerOpposite(*lastPlay);
                *lastPlay = getPlayerOpposite(*lastPlay);
                break;
            }
        } else {
            printf("Invalid slot selection");
        }
    }
}

int freeSpace(Table *ptrTable)
{
    for (int i = 0; i < 9; i++) {
        if (ptrTable->slots[i] == 'N') return 1;
    }

    return 0;
}

char checkWinner(Table *ptrTable)
{
    /* Checking for a winner by row */
    if (ptrTable->slots[0] == ptrTable->slots[1] && ptrTable->slots[1] == ptrTable->slots[2] && ptrTable->slots[0] != 'N') 
        return ptrTable->slots[0];
    if (ptrTable->slots[3] == ptrTable->slots[4] && ptrTable->slots[4] == ptrTable->slots[5] && ptrTable->slots[3] != 'N')
        return ptrTable->slots[3];
    if (ptrTable->slots[6] == ptrTable->slots[7] && ptrTable->slots[7] == ptrTable->slots[8] && ptrTable->slots[6] != 'N')
        return ptrTable->slots[6];
    
    /* Checking for a winner by column */
    if (ptrTable->slots[0] == ptrTable->slots[3] && ptrTable->slots[3] == ptrTable->slots[6] && ptrTable->slots[0] != 'N')
        return ptrTable->slots[0];
    if (ptrTable->slots[1] == ptrTable->slots[4] && ptrTable->slots[4] == ptrTable->slots[7] && ptrTable->slots[1] != 'N')
        return ptrTable->slots[1];
    if (ptrTable->slots[2] == ptrTable->slots[5] && ptrTable->slots[5] == ptrTable->slots[8] && ptrTable->slots[2] != 'N')
        return ptrTable->slots[1];
    
    /* Checking for a winner in diagonal */
    if (ptrTable->slots[0] == ptrTable->slots[4] && ptrTable->slots[4] == ptrTable->slots[8] && ptrTable->slots[0] != 'N')
        return ptrTable->slots[0];
    if (ptrTable->slots[6] == ptrTable->slots[4] && ptrTable->slots[4] == ptrTable->slots[2] && ptrTable->slots[6] != 'N')
        return ptrTable->slots[0];

    if (!freeSpace(ptrTable)) return 'T';

    return 'N';
}

void printWinner(char winnerSymbol, Player *playerOne, Player *playerTwo)
{
    if (winnerSymbol == playerOne->symbol) printf("Winner is \"%s\"\n", playerOne->username);
    else printf("Winner is \"%s\"\n", playerTwo->username);
}
