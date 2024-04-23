i = 0;
j = 0;
n = 0; # number to be printed
s = 0; # inital spaces needed

# Outer loop for rows
while (i <= 9) {
    # Print spaces
    s = 9 - i;
    j = 0;
    while (j < s) {
        printc -16;
        j = j + 1;
    }

    # Print the first half of the row
    n = 1;
    j = 0;
    while (j < i) {
        printc n;
        n =  n + 1;
        j = j + 1;
    }

    # Print the second half of the row
    n = n - 2;
    j = 1;
    while (j < i) {
        printc n;
        n = n - 1;
        j = j + 1;
    }

    printc -38;
    i = i + 1;
}