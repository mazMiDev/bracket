//------------------------------------------------------------------------------------------
// Валидатор скобок
// Мазаев М.И., 2025г.
//------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "stack.h"

typedef enum {
    SUCCESS = 0,    // нет ошибок
    OPEN_ERROR = 1, // отсутствует закрывающая скобка
    CLOSE_ERROR = 2 // для встреченной закрывающей скобки нет подходящей по типу предшествующей скобки
} ValidationCode;

static const char bracket[] = { "(){}[]" };

void printMenu()
{
    printf("Bracket validator\n");
    printf(" <util_name> [STRING|OPTION] [STRING|FILE]\n");
    printf(" When using a utility without flags, the next parameter after its name must be the string to parse.\n");
    printf(" -h\t-  get help on using the utility\n");
    printf(" -s\t-  enter the string as a program startup parameter\n");
    printf(" -f\t-  reading a string to parse from a file\n");
    printf(" -c\t-  input string via console\n");
}

void printResult(ValidationCode valC, uint8_t brType, uint32_t symbolI)
{
    switch (valC) {
        case 0:
            printf("No errors in parentheses were found!\n");
            break;
        case 1:
            printf("No matching closing bracket was found for the opening bracket \"%c\" at position %d.", bracket[brType], symbolI);
            break;
        case 2:
            printf("No matching opening bracket was found for the closeing bracket \"%c\" at position %d.", bracket[brType], symbolI);
            break;
        default:
            break;
    }
}

ValidationCode bracketCheck(const char* str, uint8_t* errBracketType, uint32_t* errSymbolInd)
{
    static Stack openBracketInd;
    initStack(&openBracketInd);

    uint8_t curOpenBracket;

    for (int i = 0; i < strlen(str) - 1; i++) {
        // проверка что встреченный символ скобка
        char* isBracket = strchr(bracket, str[i]);
        if (!isBracket)
            continue;
        // по индексу в строке определяем текущую скобку
        int currBracket = isBracket - bracket;
        // любую открывающую скобку помещаем в стек
        if (currBracket % 2 == 0) {
            push(&openBracketInd, i);
            curOpenBracket = currBracket;
        }
        else {
            // проверяем что найдена закрывающая скобка имеет соответствующую открывающую скобку
            if (isEmpty(&openBracketInd) || (currBracket - curOpenBracket) != 1) {
                *errBracketType = currBracket;
                *errSymbolInd = i;
                return CLOSE_ERROR;
            }
            pop(&openBracketInd);
        }
    }
    // проверяем что не осталось открытых скобок
    if (!isEmpty(&openBracketInd)) {
        *errBracketType = curOpenBracket;
        *errSymbolInd = top(&openBracketInd);
        return OPEN_ERROR;
    }
    return SUCCESS;
}

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        printf("Error: Invalid number of parameters\nTo get help use -h or --help");
        return 1;
    }

    ValidationCode validCode = 0;
    uint8_t brType;
    uint32_t symbolInd;

    if (!strcmp(argv[1], "-h"))
        printHelp();
    else if (!strcmp(argv[1], "-s") && argv[2] != NULL) {
        validCode = bracketCheck(argv[2], &brType, &symbolInd);
    }
    else if (!strcmp(argv[1], "-f") && argv[2] != NULL) {
        FILE* input = fopen(argv[2], "r");
        if (input == NULL) {
            perror("Failed to open input file");
            return 1;
        }

        char str[MAX_SIZE_STACK];
        while (!feof(input) && !validCode) {
            fgets(str, sizeof(str) - 1, input);
            validCode = bracketCheck(str, &brType, &symbolInd);
        }

        fclose(input);
    }
    else if (!strcmp(argv[1], "-c") && argv[2] == NULL) {
        char str[MAX_SIZE_STACK];
        scanf("Enter a string to analyze: %s",str);
    }
    else {
        printf("Error: Invalid parameter\nTo get help use -h or --help");
        return 1;
    }

    printResult(validCode, brType, symbolInd);

    return 0;
}