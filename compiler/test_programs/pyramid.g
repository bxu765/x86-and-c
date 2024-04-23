i = 0;
j = 0;
r = 10; # rows
s = 0; # spaces
# Print the pyramid
printc 32; # P
printc 41; # y
printc 34; # r
printc 17;# a 
printc 29; # m
printc 25; # i
printcn 20; # d

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