r = 10; # size of square
c = 0;
i = 0; 
j = 0;

# Print the top row
while (i < r) {
    printc -16;
    printc -6;
    i = i + 1;
}
printc -38;

# Print the middle rows
i = 2;
while (i <= r - 1) {
    printc -16;
    printc -6;
    j = 2;
    while (j <= r - 1) {
        printc -16;
        printc -16;
        j = j + 1;
    }
    printc -16;
    printcn -6;
    i = i + 1;
}

# Print the bottom row
if (r > 1) {
    i = 1;
    printc -16;
    while (i <= r) {
        printc -6;
        printc -16;
        i = i + 1;
    }
}
printc -38;