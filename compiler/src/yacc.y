%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../inc/includes.h"

/* input output handling */
extern FILE *yyin;
extern FILE *yyout;

/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(int i);
nodeType *con(int value);
void freeNode(nodeType *p);
int ex(nodeType *p, FILE *yyout);
int yylex(void);
int epilogue(FILE *yyout);
char buffer[128];
int system(const char *command);

void yyerror(char *s);
int sym[26];                    /* symbol table */

%}

%union {
    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token WHILE IF PRINTC PRINTCN
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list

%%

program:
        function                {epilogue(yyout);
                                fclose(yyout);
                                /* to use for the fork which we will host on portal */
                                // printf("Finished Code Generation. Invoking clang to compile the assembly program.\n");
                                // system("clang out.s -o executable.out -static -O3 -fomit-frame-pointer -Wno-everything");
                                // printf("Clang compilation successful\n");
                                // printf("Removing the generated assembly file\n"); 
                                // system("rm -rvf out.s");
                                // printf("Done!\n");
                                // printf("Run the generated assembly file by using the "./executable.out" command\n");
                                }
        ;

function:
          function stmt         { ex($2, yyout); freeNode($2); }
        | /* NULL */
        ;

stmt:
          ';'                            { $$ = opr(';', 2, NULL, NULL); }
        | expr ';'                       { $$ = $1; }
        | PRINTC expr ';'                { $$ = opr(PRINTC, 1, $2); }
        | PRINTCN expr ';'                { $$ = opr(PRINTCN, 1, $2); }
        | VARIABLE '=' expr ';'          { $$ = opr('=', 2, id($1), $3); }
        | WHILE '(' expr ')' stmt        { $$ = opr(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
        | '{' stmt_list '}'              { $$ = $2; }
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

expr:
          INTEGER               { $$ = con($1); }
        | VARIABLE              { $$ = id($1); }
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
        | expr '+' expr         { $$ = opr('+', 2, $1, $3); }
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); }
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); }
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); }
        | expr '<' expr         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); }
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); }
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); }
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }
        | '(' expr ')'          { $$ = $2; }
        ;

%%

nodeType *con(int value) {
    /* create a node for the constant type */
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
    p->con.value = value;

    return p;
}

nodeType *id(int i) {
    /* create a node for the identifiers */
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    p->id.i = i;

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    /* Create a node for the operators */
    /* oper - operator */
    /* nops - number of operands */
    /* ... - variable number of arguments that will be passed to the va_list we create */

    /* variable list */
    va_list ap;
    /* nodeType was declared in the includes.h header file */
    nodeType *p;
    int i;

    /* allocate node, extending op array */
    if ((p = malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    /* free all the memory that was allocated once code is generated */
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(char *s) {
    /* print when encountering an error */
    fprintf(stderr, "%s \n", s);
    //if (lineno) fprintf(stderr, "in line %d\n", yylineno);
    //else fprintf(stdout, "\n");
}

int epilogue(FILE *yyout){
    /* write the epilogue into the assembly program */
    /* the epilogue will graciously exit the process avoiding a segmentation fault */
    fprintf(yyout, "\n# --------- EPILOGUE -------- \n");
    fprintf(yyout, "#exit the program in a clean manner\nexit:\n");
    fprintf(yyout, "\tmovq $60, %%rax  #; sys_exit syscall number: 60 \n");
    fprintf(yyout, "\txorq %%rdi, %%rdi #; set exit status to 0\n");    
    fprintf(yyout, "\tsyscall");
    fprintf(yyout, "\n# ----------- END EPILOGUE ------------ \n");
    return 0;
}

int main(int argc, char *argv[]) {
    ++argv, --argc;
    if (argc > 0) {
        yyin = fopen(argv[0], "r");
    } else {
        yyin = stdin;
    }

    yyout = fopen("out.s", "w");
    fprintf(yyout, "# ---------- PROLOGUE ----------- \n"); 
    fprintf(yyout, ".section .text\n\t.global main\n");
    fprintf(yyout, "\nmain:\n");
    fprintf(yyout, "\tmovq %%rsp, %%rbp \n");
    fprintf(yyout, "\tlea -208(%%rbp), %%rsp\n");
    fprintf(yyout, "# ---------- END PROLOGUE -----------\n\n");
    yyparse();

    return 0;
}
