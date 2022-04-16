/*
Grammar: 
E  -> i E'
E' -> + i E' | eps
*/

#include<stdio.h>
#include<string.h>
#include<curses.h>

void E();
void E_();
void match(char t);

char l;

int main()
{
    l = getchar();
    // E is a start symbol.
    E();

    // if lookahead = $, it represents the end of the string
    // Here l is lookahead.
    if (l == '$')
        printf("Parsing Successful");
}

// Definition of E, as per the given production
void E()
{
    if (l == 'i') {
        match('i');
        E_();
    }
}

// Definition of E' as per the given production
void E_()  
{
    if (l == '+') {
        match('+');
        match('i');
        E_();
    }//The second condition of E'
    else if (l == 'e')
    {
        match('e');
    }
    return ;
}

// Match function
void match(char t)
{
    if (l == t) {
        l = getchar();
    }
    else
        printf("Error");
}
