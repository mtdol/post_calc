//
// Matthew Dolinka
//
// interprets a postfix arithmetic string like "12+" to "3"
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef float (*fptr)(float,float);

float run_calc(char*);
void push(float*, float, int*);
float pop(float*, int*);
bool is_member(char, char*);
bool is_op(char);
bool is_digit(char);
fptr to_op(char);

char ops[]      = "+-*/";
char digits[]   = "0123456789";
bool failure    = false;

int main(int argc, char* argv[]) {
    float res;

    if (argc != 2 || strlen(argv[1]) == 0) {
        puts("no bueno.");
        return -1;
    }

    res = run_calc(argv[1]);
    if (failure) {
        puts("Could not parse input string.");
        //printf("%f\n", res);
        return -1;
    } else {
        printf("%f\n", res);
        return 0;
    }
}

float run_calc(char* cs) {
    int si, i, si_max, elemi;
    float *stack, res;
    char c, *elem;
#define Push(v) push(stack, (v), &si)
#define Pop()   pop(stack, &si)
    
    
    // the stack will be at most the size of cs
    si_max  = strlen(cs);
    stack   = malloc(si_max*sizeof(float));
    si      = 0;
    i       = 0;
    res     = 0;
    c       = 0;
    // where we store the number we are parsing
    elem    = calloc(si_max, sizeof(char));
    elemi   = 0;
    
    while (i < si_max) {
        c = cs[i];
        if (is_op(c) && si >= 2) {
            res = to_op(c)(Pop(), Pop());
            Push(res);
        } else if (is_digit(c)) {
            elem[elemi++] = c;
        } else if (c == ' ') {
            if (elemi != 0) {
                Push(atoi(elem));
                // clean `elem`
                memset(elem, 0, elemi);
                elemi = 0;
            }
        } else {
            // we don't know what `c` is so abort
            failure = true;
            break;
        }

        i++;
    }
    
    if (elemi != 0) {Push(atoi(elem));}
    res = Pop();
    free(stack);
    free(elem);
    if (si != 0) {
        failure = true;
    }
    
    return res;
}

void push(float* s, float v, int* si) {s[++(*si)] = v;}
float pop(float* s, int* si) {return s[(*si)--];}

bool is_member(char c, char *cs) {
    int i = 0;
    while (cs[i]) {
        if (cs[i++] == c) {return true;}
    }
    return false;
}

bool is_op(char c) {return is_member(c, ops);}
bool is_digit(char c) {return is_member(c, digits);}

float fadd(float x, float y) {return x + y;}
float fsub(float x, float y) {return x - y;}
float fmul(float x, float y) {return x * y;}
float fdiv(float x, float y) {return x / y;}

fptr to_op(char c) {
    switch(c) {
        case '+':
            return fadd;
            break;
        case '-':
            return fsub;
            break;
        case '*':
            return fmul;
            break;
        case '/':
            return fdiv;
            break;
    }
}
