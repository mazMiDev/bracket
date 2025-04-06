#include <stdbool.h>

#define MAX_SIZE_STACK 100

typedef struct
{
    char data[MAX_SIZE_STACK];
    int top;
} Stack;

inline void initStack(Stack *stack);

inline bool isEmpty(Stack *stack);

inline bool isFully(Stack *stack);

inline void push(Stack *stack, char val);

inline char top(Stack *stack);

inline void pop(Stack *stack);
