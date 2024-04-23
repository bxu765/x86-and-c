%{
// This section contains C style includes and declarations
#include <stdlib.h>
#include <string.h>
#include "../inc/includes.h"
#include "y.tab.h"
void yyerror(char *);
int yylineno;
%}

%%

[a-z]       { 
                yylval.sIndex = *yytext - 'a';
                return VARIABLE;
            }

[0]*           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[1-9][0-9]* {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[-()<>=+*/;{}.] {
                return *yytext;
            }

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"printc"        return PRINTC;
"printcn"        return PRINTCN;

\n              {yylineno++;};
#(.*)        ;       /* ignore comments */
[ \t]+          ;       /* ignore whitespace */

.              {
                char numStr[10];
                snprintf(numStr, sizeof(numStr), "%d", yylineno);
                yyerror(strcat("Unknown character in line ", numStr));
               }
%%
int yywrap(void) {
    return 1;
}
