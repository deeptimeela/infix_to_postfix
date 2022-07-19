#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
struct Stack
{
    int top_of_stack;
    unsigned max_capacity;
    int* array_stack;
};

struct Stack* createStack( unsigned max_capacity )
{
    struct Stack* stack = (struct Stack*)
           malloc(sizeof(struct Stack));
 
    if (!stack) // if there is no stack existing only 
        return NULL;
 
    stack->top_of_stack = -1; // initially initialize to top_of_stack of stack=-1
    stack->max_capacity = max_capacity; // no of elements it can store
 
    stack->array_stack = (int*) malloc(stack->max_capacity *
                                   sizeof(int));
 
    return stack; // stack is ready now use LIFO 
}
int isEmpty(struct Stack* stack)
{
    return stack->top_of_stack == -1 ; // stack is empty when top_of_stack==-1
}
char peek(struct Stack* stack)
{
    return stack->array_stack[stack->top_of_stack]; //peek is to get the top_of_stackmost element of the stack
}
char remove(struct Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array_stack[stack->top_of_stack--] ; //trying to remove/delete the top_of_stack most element of the stack and then decrement top_of_stack by 1
    return '$';
}
void throw(struct Stack* stack, char op)
{
    stack->array_stack[++stack->top_of_stack] = op; //throw into the stack and increment top_of_stack by one because top_of_stack is shifted now 
}

int check_is_alphabet_number(char ch)
{
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z'); //checking if the element of the stack is actually an opearand to remove it from the stack later
}

int precedence_of_character(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1; //addition and subtraction have same precedence order
 
    case '*':
    case '/':
        return 2; // division and multiplication have same precedence(higher over add and subtraction)
 
    case '^':
        return 3; //exponential has the highest precedence
    }
    return -1;
}

int infixtop_of_stackostfix(char* exp)
{
    int i, k;
 
    
    struct Stack* stack = createStack(strlen(exp)); //creation of a stack of max_capacity of the string length whose postfix we are finding out
    
    if(!stack) //checking the existence of the stack else return -1 exit
        return -1 ;
 
    for (i = 0, k = -1; exp[i]; ++i)
    {
         
        
        if (check_is_alphabet_number(exp[i])) // check if it is an operand or number then remove from the stack
            exp[++k] = exp[i];
         
        
        else if (exp[i] == '(') // if the element is a left opening bracket then throw into the stack  
            throw(stack, exp[i]);
            
        
        else if (exp[i] == ')') // if the element is a closing bracket then keep removeping from the stack until open bracket is got
        
        {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = remove(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1; // expression will become invalid
                
            else
                remove(stack);
        }
        
        else // if we get an opeartor we will check for the precedence of the characters if the precedence of the top_of_stack of stack  is higher than element then remove from tge stack else throw into the stack
        {
            while (!isEmpty(stack) && Prec(exp[i]) <=
            Prec(peek(stack)))
                exp[++k] = remove(stack);
            throw(stack, exp[i]);
        }
 
    }
 
   
    while (!isEmpty(stack)) // remove out all the reamaining elements of the stack
        exp[++k] = remove(stack );
 
    exp[++k] = '\0';
    printf( "%s", exp );
}

int main()
{
    char exp[] = "a*b/(c^d-e)*(f+g-h)/i";
    infixtop_of_stackostfix(exp);
    return 0;
}







 
