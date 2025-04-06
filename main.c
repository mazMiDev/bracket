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
    SUCCESS,          // нет ошибок
    OPEN_ERROR,       // ошибка в отсутствие закрывающей скобки
    OPEN_CLOSE_ERROR, // встречена не соответствующая закрывающая скобка
    CLOSE_ERROR,      // ошибка в отсутствие закрывающей скобки
} EXIT_CODE;

static Stack stack;

static const char bracket[] = {"(){}[]"};

EXIT_CODE bracketCheck(const char *str, uint8_t *errBracketType, uint32_t* errSymbolInd)
{
    initStack(&stack);
    uint8_t curOpenBracket;

    for (int i = 0; i < strlen(str); i++)
    {
        char *isBracket = strchr(bracket, str[i]);
        if (!isBracket)
            continue;

        int currBracket = isBracket - bracket;

        if (currBracket % 2 == 0)
        {
            push(&stack, i);
            curOpenBracket = currBracket;
        }
        else
        {
            if ((currBracket - curOpenBracket) != 1)
            {
                *errBracketType = curOpenBracket;
                *errSymbolInd = top(&stack);
                return OPEN_CLOSE_ERROR;
            }
        }
    }
    if (isEmpty(&stack))
    {
        errBracketType
    }
    return SUCCESS;
}

int main()
{
    return 0;
}