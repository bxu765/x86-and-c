i = 0; 
j = 1;
k = 0;
n = 7; #number of digits in the sequence we need

printc i;
printc -16;
printc j;
printc -16;

a = 2; # loop variable
while ( a < n){
    k = i + j;
    printc k;
    i = j;
    j = k;
    printc -16;
    a = a + 1;
}

printc -38;