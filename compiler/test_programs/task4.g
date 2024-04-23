# copy of the right diagonal square program
i = 0;
j = 0;
while (i < 11){
    j = 0;
    while (j < 11) {
        if (10-i == j) {
            printc 0;
            if (i == 0) printc -38;
        }
        else if (j == 10) printcn -2;
        else printc -2;
        j = j + 1;
    }
    i = i + 1;
}