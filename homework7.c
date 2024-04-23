/*************************************************
 * CS 2130 Homework 7
 * Spring 2023 - Writing C
 *
 * Computing ID: jqt7xn
 ************************************************/

// ===============================================
// Write your functions here:
#include <stdbool.h>
#include<stdio.h>
#include<string.h>

// TODO: Write functions here
void titlecase(char *s){
    char *c = s;
    bool is_after_space = false;
    while(*c != '\0'){
        if(*c > 0x60 && *c < 0x7B && is_after_space)
            *c = *c - 0x20;
        is_after_space = (*c == 0x20);
        c++;
    }
}

void fibarray(unsigned short *dest, unsigned num){
    if(num > 0) dest[0] = 1;
    if(num > 1){
        dest[1] = 1;
        for(int i = 2; i < num; i++){
            dest[i] = dest[i-1] + dest[i-2];
        }
    }
}

long recpow(long x, unsigned char e){
    if(e == 0) return 1;
    if(e == 1) return x;
    return x * recpow(x, e-1);
}

unsigned long nextprime(unsigned long x){
    unsigned long y = x + 1;
    if(y < 2) y = 2;
    while(true){
        bool prime = true;
        for(int z = 2; z < y; z++){
            if(y%z == 0) prime = false;
        }
        if(prime) return y;
        y++;
    }
    return -1;
}

void pull0(int *arr, unsigned length){
    int zeros = 0;
    int nonzeros[length];
    int counter = 0;
    for(int i = 0; i < length; i++){
        if(arr[i] == 0){
            zeros++;
        }else{
            nonzeros[counter] = arr[i];
            counter++;
        }
    }    
    for(int j = 0; j < zeros; j++) arr[j] = 0;
    for(int k = 0; k < counter; k++) arr[k+zeros] = nonzeros[k];
}

int nondup(int *arr, unsigned length){
    for(int i = 0; i < length; i++){
        bool has_dup = false;
        for(int j = 0; j < length; j++){
            if(i != j && arr[i] == arr[j]){
                has_dup = true;
            }
        }
        if(!has_dup) return arr[i];
    }
    return -1;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Update the followng main function to test your
// code.  You should test normal input values as
// well as edge cases.  Do NOT rely only on the
// Gradescope submission site, as submissions are
// limited.
// Note: You must leave this comment block to ensure
// proper grading of your submission.


int main() {
    int x[] = {28, 12, 8, 0, 0, 28, 8};
    printf("%d\n", nondup(x, 7));
    printf("%d\n", nondup(x + 2, 5));
}
