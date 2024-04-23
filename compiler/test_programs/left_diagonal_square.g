# This ToyG program prints a diagonal 
# of dots in a rectangle (square?) of zeros.
i = 0; # no types. i will be treated as a signed integer.
j = 0; # variable names are a single lowercase character.

# a normal C style while loop
while (i < 11){
    j = 0000; # this will be considered as 0
    # j = 012; # this would be illegal raising a syntax error
    while (j < 11) {
        if (i == j) printc -2; # only prints the character 48+(-2) which is '.'
        else if (j == 10) printcn 0; # prints '0' followed by a newline/
        else printc 0;
        j = j + 1;
    }
    i = i + 1;
}
# since the last character would not have a newline printed,
# we manually print a newline character.
printc -38;