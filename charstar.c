#include <stdio.h>

/*
size_t mystrlen(const char *s) {
    size_t counter = 0;
    while(*s != '\0'){
        counter++;
        s++;
    }
    return counter;
}
*/

size_t mystrlen(const char *s) {
    char *c = s;
    while(*c != '\0') c++;
    return c-s;
}

char *simple_split(char *s, char delim) {
    if(s == NULL) return NULL;
    while(*s != '\0'){
        if(*s == delim) {
            *s = '\0';
            return s + 1;
        }
        s++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    const char *s = "even elephants exfoliate";
size_t slen = mystrlen2(s);
puts(s + (slen/2));
}