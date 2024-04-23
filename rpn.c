#include <stdio.h>
#include <ctype.h>
#include <string.h>

void printout(int *list, int size) {
    printf("[ ");
    for(int i = 0; i < size; i++) {
        if (i < size - 1) {
            printf("%d, ", list[i]);
        } else {
            printf("%d ", list[i]);
        }
    }
    puts("]");
}

int main(int argc, const char *argv[]) {
    char buffer[65536];
    int *rpn = (int*)malloc(65536 * sizeof(int));
    int size = 0;
    while (1) {
        char *result = fgets(buffer, 65536, stdin);
        if (result == NULL) {
            printout(rpn, size);
            return 0;
        }
        char * token = strtok(result, " ");
        int toknum = 0;
        while (token != NULL) {
            int num = atoi(token);
            if (num != 0 || token[0] == '0') {
                rpn[size] = num;
                size++;
            } else if(token[0] == '*' || token[0] == '+' || token[0] == '-' || token[0] == '%') {
                int newnum;
                if (size < 2) {
                    printout(rpn, size);
                    return 0;
                }
                if (token[0] == '*') newnum = rpn[size-2] * rpn[size-1];
                if (token[0] == '+') newnum = rpn[size-2] + rpn[size-1];
                if (token[0] == '-') newnum = rpn[size-2] - rpn[size-1];
                if (token[0] == '%') newnum = rpn[size-2] % rpn[size-1];
                rpn[size-2] = newnum;
                size--;
            } else if (token[0] == '\n') {
                printout(rpn, size);
            } else {
                printout(rpn, size);
                return 0;
            }
            token = strtok(NULL, " ");
            printout(rpn, size);
        }
        printout(rpn, size);
    }
    return 0;
}