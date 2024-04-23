i = 0;
j = 0;
r = 10; # rows
s = 0; # spaces
# Print the Diamond
printc 20; #d
printc 25; #I
printc 17; #a 
printc 29; #m
printc 31; #o
printc 30; #n
printcn 20; # D


i = 8;
while (i <= r) {
    # Print spaces
    s = r - i;
    j = 0;
    while (j < s) {
        printc -16;
        j = j + 1;
    }

    # Print asterisks
    j = 0;
    while (j < (2 * i - 1)) {
        printc -6;
        j = j + 1;
    }

    printc -38;
    i = i + 1;
}

i = r - 1;
while (i >= 1) {
    # Print spaces
    s = r - i;
    j = 1;
    while (j <= s) {
        printc -16;
        j = j + 1;
    }

    # Print asterisks
    j = 1;
    while (j <= (2 * i - 1)) {
            printc -6;
            j = j + 1;
    }

    printc -38;
    i = i - 1;
}