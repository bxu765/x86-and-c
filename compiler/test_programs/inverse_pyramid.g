i = 0;
j = 0;
r = 10; # rows
s = 0; # spaces
# Print the pyramid
printc 25; # I
printc 30; # n
printc 38; # v 
printc 21; # e 
printc 34; # r 
printc 36; # t 
printc 21; # e
printc 20; # d
printc -16; # Space
printc 32; # P
printc 41; # y
printc 34; # r
printc 17;# a 
printc 29; # m
printc 25; # i
printcn 20; # d

i = r;
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