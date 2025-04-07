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
    SUCCESS,    // нет ошибок
    OPEN_ERROR, // отсутствует закрывающая скобка
    CLOSE_ERROR // для встреченной закрывающей скобки нет подходящей по типу предшествующей скобки
} EXIT_CODE;

static Stack stack;

static const char bracket[] = {"(){}[]"};

EXIT_CODE bracketCheck(const char *str, uint8_t *errBracketType, uint16_t *errSymbolInd)
{
    initStack(&stack);
    uint8_t curOpenBracket;

    for (int i = 0; i < strlen(str); i++)
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
            push(&stack, i);
            curOpenBracket = currBracket;
        }
        else
        {
            // проверяем что найдена закрывающая скобка имеет соответствующую открывающую скобку
            if (isEmpty(&stack) || (currBracket - curOpenBracket) != 1)
            {
                *errBracketType = currBracket;
                *errSymbolInd = i;
                return CLOSE_ERROR;
            }

            pop(&stack);
        }
    }
    if (!isEmpty(&stack))
    {
        return OPEN_ERROR   
    }
    return SUCCESS;
}

int main()
{
    return 0;
}