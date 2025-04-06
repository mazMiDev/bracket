#include "stack.h"

inline void initStack(Stack *stack)
{
    stack->top = -1;
}

inline bool isEmpty(Stack *stack)
{
    return stack->top == -1;
}

inline bool isFully(Stack *stack)
{
    return stack->top == MAX_SIZE_STACK - 1;
}

inline void push(Stack *stack, char val)
{
    if (isFully(stack))
    {
        stack->top++;
        stack->data[stack->top] = val;
    }
}

inline char top(Stack *stack)
{
    if (!isEmpty())
        return stack->data[stack->top];
    return 0;
}

inline void pop(Stack *stack)
{
    if (isEmpty(stack))
        stack->top--;
}