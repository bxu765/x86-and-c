n = 9; # number of rows
i = 0;
j = 0;
e = 0; # coefficient
r = 0; # row
c = 0; # column

while (r < n) {
    # Calculate the coefficients for the current row
    e = 1;
    c = 0;

    # Print spaces for the current row
    j = 0;
    while (j < (n - r - 1)) {
        printc -16;
        j = j + 1;
    }

    # Print the coefficients for the current row
    while (c <= r) {
        printc e;
        printc -16;

        # Calculate the next coefficient using the combination formula
        e = e * (r - c) / (c + 1);
        c = c + 1;
    }

    printc -38;
    r = r + 1;
}