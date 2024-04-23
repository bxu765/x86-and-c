/**
 * File              : code_generator.c
 * Author            : Alenkruth Krishnan Murali <<firstname>[at]virginia{dot}edu>
 *                   : Daniel George Graham, Professor, UVA.
 *                   : Tom Niemann (https://www.epaperpress.com/lexandyacc/index.html)
 * Date              : 05.04.2024
 * Last Modified Date: 05.04.2024
 * Last Modified By  : Alenkruth Krishnan Murali <<firstname>[at]virginia{dot}edu>
 */
#include <stdio.h>
#include <string.h>
#include "includes.h"
#include "../y.tab.h"

/* global static variable for creating jump labels in loops and conditionals */
static int lbl;

/* function to parse through the AST and generate code */
int ex(nodeType *p, FILE *yyout) {
    /* define and declare variables */
    int return_code = 0;
    int lbl1 = 0;
    int lbl2 = 0;
    // To Do - Create variables for Label creation and management here.
    // To Do - create a variable to return the jump condition here
    // To Do - create a varialble to store the jump condition returned from a ex() call

    /* switch ladder to evaluate the node type and generate code */
    if (!p) return 0; /* not a node */
    switch(p->type) { /* switch on Node type */
    case typeCon:
        /* Type - constant */  
        /* Action - Push the Constant value onto the stack */
        /* Next steps will depend on the operator(s) associated with the constant */
        fprintf(yyout, "\t# push constant onto the stack \n");
        fprintf(yyout, "\tpushq $%d\n\n", p->con.value);
        break;
    case typeId:
        /* Type - identifier */  
        /* Action - Push the identifier's value onto the stack */
        /* The identifiers are stored in a preallocated memory region */
        /* The offset of the identifier with respect 'a' will be used to obtain the value of it */
        /* Next steps will depend on the operator(s) associated with the identifier */

        // Your code here 
        fprintf(yyout, "\tpushq %d(\%rbp)\n\n", 8 * p->id.i);

        break;
    case typeOpr:
        /* Type - operator */  
        /* Action - Depends on the operator. We enter the next switch ladder */
        switch(p->opr.oper) {
        case WHILE:
            /* Operator - While */
            /* Create a loop with labels that is executed 'N' times based on condition */
            /* create and output the label to jump to when condition is true */
            /* Parse the CONDITION on which the while would terminate */
            /* Generate the right code based on the result from parsing the condition */
            /* you might need a switch case here to generate the right jump condition */
            /* parse the code block within the while block */
            /* Jump to the start of the while loop to evaluate the condition and proceed */
            /* label to jump to when the condition fails */

            // Your code to do the steps listed above
            fprintf(yyout, "\n# Implement WHILE handling here \n");
            fprintf(yyout, "\n# Any code withing the while block will not be parsed \n");

            lbl1 = lbl++;
            fprintf(yyout, "\tLABEL%d:\n", lbl1);
            int save_return_code = ex(p->opr.op[0], yyout);
            lbl2 = lbl++;
            switch (save_return_code){
                case 2:
                    fprintf(yyout, "\tjle LABEL%d\n", lbl2);
                    break;
                case 3:
                    fprintf(yyout, "\tjl LABEL%d\n", lbl2);
                    break;
                case 4:
                    fprintf(yyout, "\tjge LABEL%d\n", lbl2);
                    break;
                case 5:
                    fprintf(yyout, "\tjg LABEL%d\n", lbl2);
                    break;
                case 6:
                    fprintf(yyout, "\tjne LABEL%d\n", lbl2);
                    break;
                case 7:
                    fprintf(yyout, "\tje LABEL%d\n", lbl2);
                    break;
            }
            ex(p->opr.op[1], yyout);
            fprintf(yyout, "\tjmp LABEL%d\n", lbl1);
            fprintf(yyout, "\tLABEL%d:\n", lbl2);

            break;

        case IF:
            /* Operator - IF */
            /* Create a code block that is executed based on condition */ 
            /* Parse the CONDITION on which the IF would work on */
            /* Check to see if it is IF... ELSE block or just a IF block */
            /* You can do this by checking the number of operands the node has */
            /* Look at the YACC file to see how IF and IF-ELSEs differ */
            /* This is  used to evaluate IF... ELSE IF.... ELSE ladder */
            /* your implementation will look something like follows */
            /* if ( condition to cehck if it is just an if statement or and if-else ) { implement if-else }
            /* else { implement if } */
            /* When implementing the if and if-else, you will have to generate code
            /* based on the conditon that needs to be checked. This is similar to the while implememntation */
            /* then you parse the code within the if block */
            /* jump to change execution flow to avoid else when if was executed */
            /* create a label to jump to when if condition fails and there is an else to execute */
            /* parse the code block within the else */
            /* label to which the post IF jump jumps to */

            // Your code here
            fprintf(yyout, "\n# implement IF or IF-ELSE handling here \n");
            fprintf(yyout, "\n# Any code within the IF and IF-ELSE block is not parsed \n");

            if(p->opr.nops > 2){
                //This is a if-else
                int save_return_code = ex(p->opr.op[0],yyout);
                lbl1 = lbl++;
                switch (save_return_code){
                    case 2:
                        fprintf(yyout, "\tjle LABEL%d\n", lbl1);
                        break;
                    case 3:
                        fprintf(yyout, "\tjl LABEL%d\n", lbl1);
                        break;
                    case 4:
                        fprintf(yyout, "\tjge LABEL%d\n", lbl1);
                        break;
                    case 5:
                        fprintf(yyout, "\tjg LABEL%d\n", lbl1);
                        break;
                    case 6:
                        fprintf(yyout, "\tjne LABEL%d\n", lbl1);
                        break;
                    case 7:
                        fprintf(yyout, "\tje LABEL%d\n", lbl1);
                        break;
                }
                ex(p->opr.op[1], yyout);
                lbl2 = lbl++;
                fprintf(yyout, "\tjmp LABEL%d\n", lbl2);
                fprintf(yyout, "\tLABEL%d:\n", lbl1);

                ex(p->opr.op[2], yyout);
                fprintf(yyout, "\tLABEL%d:\n", lbl2);
            } else {
                //this is just an if
                int save_return_code = ex(p->opr.op[0],yyout);
                lbl1 = lbl++;
                switch (save_return_code) {
                    case 2:
                        fprintf(yyout, "\tjle LABEL%d\n", lbl1);
                        break;
                    case 3:
                        fprintf(yyout, "\tjl LABEL%d\n", lbl1);
                        break;
                    case 4:
                        fprintf(yyout, "\tjge LABEL%d\n", lbl1);
                        break;
                    case 5:
                        fprintf(yyout, "\tjg LABEL%d\n", lbl1);
                        break;
                    case 6:
                        fprintf(yyout, "\tjne LABEL%d\n", lbl1);
                        break;
                    case 7:
                        fprintf(yyout, "\tje LABEL%d\n", lbl1);
                        break;
                }
                ex(p->opr.op[1], yyout);
                fprintf(yyout, "\tLABEL%d:\n", lbl1);
            }
            break;

        case PRINTCN:
            /* Operator - PRINTCN */
            /* Print the provided character and add a newline */
            /* add code to evaluate the operand for the print */ 
            /* Take a look at the PRINTC implementation */
            /* Understand what it is doing and why it is doing those things */
            /* Think about the changes you would have to make for it to print 2 characters */
            /* PRINTCN is no different from PRINTC */

            // Your code here
            ex(p->opr.op[0], yyout);
            /* no comments inlined for this assembly */
            fprintf(yyout, "\t# print character\n\
\tpopq \%rax\n\
\taddq $48,\%rax\n\
\tpushq \%rax\n\
\tmovq $1,\%rax\n\
\tmovq $1,\%rdi\n\
\tmovq \%rsp,\%rsi\n\
\tmovq $1,\%rdx\n\
\tsyscall\n\
\tpushq $10\n\
\tmovq $1,\%rax\n\
\tmovq $1,\%rdi\n\
\tmovq \%rsp,\%rsi\n\
\tmovq $1,\%rdx\n\
\tsyscall\n\
\t#end print\n\n");
            break;

        case PRINTC:
            /* Operator - PRINTC */
            /* Print the provided character using a linux system call */
            /* the system call only prints a character (8bytes) and prints in ASCII */
            /* evaluate the operand for the print */ 
            ex(p->opr.op[0], yyout);
            /* no comments inlined for this assembly */
            fprintf(yyout, "\t# print character\n\
\tpopq \%rax\n\
\taddq $48,\%rax\n\
\tpushq \%rax\n\
\tmovq $1,\%rax\n\
\tmovq $1,\%rdi\n\
\tmovq \%rsp,\%rsi\n\
\tmovq $1,\%rdx\n\
\tsyscall\n\
\t#end print\n\n");
            break;
        case '=':
            /* Operator - = */
            /* Assign the value from the operation in the RHS to LHS */
            /* parse the operand on the right side of the = */
            /* parse the RHS operand would have pushed the result onto the stack */
            /* pop from stack into the memory address of the identifier on the LHS */
            ex(p->opr.op[1], yyout);
            // Your code here
            fprintf(yyout, "\tpopq %d(\%rbp)\n\n", 8 * p->opr.op[0]->id.i);
            break;

        case UMINUS:
            /* Operator - '-' (Unary Minus)*/
            /* copmute the negation of the value succeeding the operator */
            /* and push result into the stack */
            /* before that, parse the operand and push it into the stack*/             
            ex(p->opr.op[0], yyout);
            /* pop from stack, negate and push into stack */
            /* The instruction to negate a value in a register can be found in the reference website provided */
            fprintf(yyout, "\n# implement negation (unary operation) \n\
\tpopq \%rax\n\
\tnegq \%rax\n\
\tpushq \%rax\n\n");

            break;
        default:
            /* other arithmetic operators and conditional operators */
            /* evaluate the operands associated with the operator and result will be in the stack */
            /* evaluate the operands of the arithmetic operator */
            ex(p->opr.op[0], yyout);
            ex(p->opr.op[1], yyout);
            /* switcing based on the operator */
            switch(p->opr.oper) {
                /* all operations are on signed 64bit data unless specified */  
                /* you can find the x86 instructions in the reference webistres*/  
                case '+': 
                    /* Operator - + */
                    /* Add the operands and push into the stack */ 
                    fprintf(yyout, "\n# implement addition\n\
\tpopq \%rbx\n\
\tpopq \%rax\n\
\taddq \%rax,\%rbx\n\
\tpushq \%rbx\n\n");

                    // your code is here

                    break;
                case '-':
                    /* Operator - - */
                    /* Add the operands and push into the stack */ 
                    fprintf(yyout, "\n # implement subtraction here \n\
\tpopq \%rbx\n\
\tpopq \%rax\n\
\tsubq \%rbx,\%rax\n\
\tpushq \%rax\n\n");

                    // your code here

                    break; 
                case '*':  
                    /* Operator - * */
                    /* Multiply the operands and push into the stack */
                    /* upper 64 bits of the result is neglected */ 
                    fprintf(yyout, "\n # implement multiplication here \n\
\tpopq \%rbx\n\
\tpopq \%rax\n\
\timulq \%rbx,\%rax\n\
\tpushq \%rax\n\n");

                    // your code here

                    break;
                case '/':
                    /* Operator - / */
                    /* divide the operands and push into the stack */
                    /* remiander of the division is neglected */
                    /* Check the felixcloutier's (reference) webiste for details about the division */
                    /* Division is different from the other operations since there are two results */            
                    fprintf(yyout, "\n# implemet division here \n\
\tpopq %rbx\n\
\tpopq %rax\n\
\tpushq %rdx\n\
\tcqo\n\
\tidivq %rbx\n\
\tpopq %rdx\n\
\tpushq %rax\n\n");

                    // your code here

                    break;
                case '>':   
                    /* all conditional operators are simple comparison operations */
                    /* each comparison will update the "EFLAGS" register differently */
                    /* you will use this to write the conditional case inside the IF and WHILE interpreters */
                    /* moreover, other than just implementing a comparison, you will have to return a codition code */
                    /* indicating that you performed a particular type of comparison */
                    /* We implemented it by returning 2 to indicate a greaterthan comparison */
                    /* when we see 2 was returned by the function call to evaluate an operator, we know it was a greater than comparison */
                    /* and we will implement a jle to perform the jump */
                    fprintf(yyout, "\t# implement copmarison operation and return a code for > \n\
\tpopq \%rbx\n\
\tpopq \%rax\n\
\tcmpq \%rbx,\%rax\n\n");

                    // your code here
                    return_code = 2;
                    break;
                case GE:
                    /* implement comparison */
                    fprintf(yyout, "\t# implement copmarison operation and return a code for GE \n\
\tpopq \%rbx\n\
\tpopq \%rax\n\
\tcmpq \%rbx,\%rax\n\n");
                    
                    // your code here 
                    return_code = 3;
                    break;
                case '<':  
                    /* implement comparison */
                    fprintf(yyout, "\t# implement copmarison operation and return a code for < \n\
\tpopq \%rbx\n\
\tpopq \%rax\n\
\tcmpq \%rbx,\%rax\n\n");
                    
                    // your code here 
                    return_code = 4;
                    break;
                case LE:
                    /* implement comparison */
                    fprintf(yyout, "\t# implement copmarison operation and return a code for LE \n\
\tpopq \%rbx\n\
\tpopq \%rax\n\
\tcmpq \%rbx,\%rax\n\n");
                    
                    // your code here 
                    return_code = 5;
                    break;
                case EQ:                      
                    /* implement comparison */
                    fprintf(yyout, "\t# implement copmarison operation and return a code for EQ \n\
\tpopq \%rbx\n\
\tpopq \%rax\n\
\tcmpq \%rbx,\%rax\n\n");
                    
                    // your code here 
                    return_code = 6;
                    break;
                case NE:                     
                    /* implement comparison */
                    fprintf(yyout, "\t# implement copmarison operation and return a code for NE \n\
\tpopq \%rbx\n\
\tpopq \%rax\n\
\tcmpq \%rbx,\%rax\n\n");
                    
                    // your code here 
                    return_code = 7;
                    break;
            }
        }
    }

    /* ideally you would return a variable and not zero when you add support for comparisons */
    return return_code;
}
