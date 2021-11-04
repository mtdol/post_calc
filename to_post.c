//
// Matthew Dolinka
// 
// Converts an infix arithmetic expression (1+2) to postfix form (12+)
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM     0
#define OP      1
#define Curr    input[0]

// type = "op" | "num"
typedef struct Node {
    int type;
    char val;
    struct Node *l;
    struct Node *r;
} Node;

void clean_str(char*);

void succ(void);
bool accepts(char);
void expect(char);
void error(char*);
static char* expects_err_msg(char, char);

bool is_digit(char);
bool is_member(char, char*);

Node* expr(void);
Node* term(void);
Node* factor(void);

Node* make_num_node(char);
Node* make_op_node(char, Node*, Node*);
void free_node(Node*);
void print_node(Node*); 

char* input;
char* digits = "1234567890";


Node* make_num_node(char n) {
    Node* ptr   = malloc(sizeof(Node));
    ptr->type   = NUM;
    ptr->val    = n;
    ptr->l      = NULL;
    ptr->r      = NULL;
    return ptr;
}

Node* make_op_node(char op, Node *l, Node *r) {
    Node* ptr   = malloc(sizeof(Node));
    ptr->type   = OP;
    ptr->val    = op;
    ptr->l      = l;
    ptr->r      = r;
    return ptr;
}

// prints the node into postfix form
void print_node(Node *n) {
    if (n) {
        switch (n->type) {
            case NUM:
                printf("%c ",n->val);
                break;
            case OP:
                // op case
                print_node(n->l);
                print_node(n->r);
                printf("%c ",n->val);
                break;
        }
    }
}

void free_node(Node *n) {
    if (n) {
        free_node(n->l);
        free_node(n->r);
        free(n);
    }
}

int main(int argc, char* argv[]) {
    Node *n;

    if (argc != 2 || strlen(argv[1]) == 0) {
        puts("no bueno.");
        return -1;
    }
    
    clean_str(argv[1]);
    input = argv[1];

    n = expr();

    if (input[0])
        error("Could not parse whole expr.");

    print_node(n);
    puts("");
     
    free_node(n);

    return 0;
}

void clean_str(char *s) {
    int i = 0, j = 0;
    char *s2 = calloc(strlen(s), sizeof(char));
    while (s[i]) {
        if (s[i] != ' ') {
            s2[j] = s[i];
            j++;
        }
        i++;
    }
    
    strcpy(s, s2);

    free(s2);
}


Node* expr(void) {
    Node *n;
    char c;
    n = term();

    while (Curr == '+' || Curr == '-') {
        c = Curr;
        succ();
        n = make_op_node(c, n, term());
    }

    return n;
}

Node* term(void) {
    Node *n;
    char c;
    n = factor();

    while (Curr == '*' || Curr == '/') {
        c = Curr;
        succ();
        n = make_op_node(c, n, factor());
    }

    return n;
}

Node* factor(void) {
    Node *n;
    char v;
    if (Curr == '(') {
        succ();
        n = expr();
        expect(')');
        return n;
    } else if (is_digit(Curr)) {
        v = Curr;
        succ();
        return make_num_node(v);
    } else {
        error("Could not parse.");
    }
}

void succ(void) {input++;}
bool accepts(char c) {return c == Curr;}
void expect(char c) {
    if (accepts(c)) {
        succ(); 
    } else {
        error(expects_err_msg(c, Curr));
    }
}


bool is_digit(char c) {return is_member(c, digits);}

bool is_member(char c, char *cs) {
    int i = 0;
    while (cs[i]) {
        if (cs[i++] == c) {return true;}
    }
    return false;
}

static char* expects_err_msg(char expected, char got) {
    char *msg;
    char expected_s[] = {expected, 0};
    char got_s[]      = {got, 0};
    msg = calloc(100,sizeof(char));
    strcat(msg, "Expected: ");
    strcat(msg, expected_s);
    strcat(msg, ", Got: ");
    strcat(msg, got_s);

    return msg;
}

void error(char* msg) {puts(msg); exit(-1);}
