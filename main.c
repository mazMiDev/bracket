//------------------------------------------------------------------------------------------
// Валидатор скобок
// Мазаев М.И., 2025г.
//------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "stack.h"

typedef enum
{
    SUCCESS = 0,    // нет ошибок
    OPEN_ERROR = 1, // отсутствует закрывающая скобка
    CLOSE_ERROR = 2 // для встреченной закрывающей скобки нет подходящей по типу предшествующей скобки
} EXIT_CODE;

static const char bracket[] = {"(){}[]"};

void printMenu()
{
    printf("Bracket validator\n");
    printf(" <util_name> [STRING|OPTION] [STRING|FILE]\n");
    printf(" When using a utility without flags, the next parameter after its name must be the string to parse.\n");
    printf(" -h\t-  get help on using the utility\n");
    printf(" -f\t-  reading a string to parse from a file\n");
    printf(" -c\t-  input string via console\n");
}

EXIT_CODE bracketCheck(const char *str, uint8_t *errBracketType, uint16_t *errSymbolInd)
{
    static Stack openBracketInd;
    initStack(&openBracketInd);
    uint8_t curOpenBracket;

    for (int i = 0; i < strlen(str) - 1; i++)
    {
        // проверка что встреченный символ скобка
        char *isBracket = strchr(bracket, str[i]);
        if (!isBracket)
            continue;

        // по индексу в строке определяем текущую скобку
        int currBracket = isBracket - bracket;

        // любую открывающую скобку помещаем в стек
        if (currBracket % 2 == 0)
        {
            push(&openBracketInd, i);
            curOpenBracket = currBracket;
        }
        else
        {
            // проверяем что найдена закрывающая скобка имеет соответствующую открывающую скобку
            if (isEmpty(&openBracketInd) || (currBracket - curOpenBracket) != 1)
            {
                *errBracketType = currBracket;
                *errSymbolInd = i;
                return CLOSE_ERROR;
            }

            pop(&openBracketInd);
        }
    }
    if (!isEmpty(&openBracketInd))
    {
        return OPEN_ERROR;
    }
    return SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        printf("Error: Invalid number of parameters\nTo get help use -h or --help");
        return 1;
    }

    EXIT_CODE code;

    if (!strcmp(argv[1], "-h"))
        printHelp();
    else if (!strcmp(argv[1], "-f") && argv[2] != NULL)
    {
        FILE *input = fopen(argv[2], "r");
        if (input == NULL)
        {
            perror("Failed to open input file");
            return 1;
        }

        uint8_t errBracketType;
        uint16_t errSymbolInd;
        char str[MAX_SIZE_STACK];
        while (!feof(input))
        {
            fgets(str, sizeof(str) - 1, input);
            code = bracketCheck(str, &errBracketType, &errSymbolInd);
        }

        fclose(input);
        printf("Conversion completed\n");
    }
    else if (!strcmp(argv[1], "-c") && argv[2] == NULL)
    {
        char str[MAX_SIZE_STACK];
        printf("Conversion completed\n");
    }
    else
    {
        printf("Error: Invalid parameter\nTo get help use -h or --help");
        return 1;
    }

    switch (code)
    {
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    default:
        break;
    }

    return 0;
}