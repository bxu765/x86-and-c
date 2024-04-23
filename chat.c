#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
    char *me = getenv("USER");
    char filepath[4096];

    snprintf(filepath, 4096, "/p/%s/mailbox/%s.chat", "cso1", me);
    chmod(filepath, 0666);
    FILE *inbox = fopen(filepath, "r");
    char buffer[4096];
    char *line = fgets(buffer, 4096, inbox);
    truncate(filepath, 0);
    if(line == NULL){
        puts("no messages");
    }else{
        puts(buffer);
    }
    fclose(inbox);

    puts("target?");
    char *target = fgets(buffer, 4096, stdin);
    if(strlen(target) < 3){
        puts("ok bye");
    }
    else{
        target[strlen(target)-1] = '\0';
        snprintf(filepath, 4096, "/p/%s/mailbox/%s.chat", "cso1", target);
        FILE *outbox = fopen(filepath, "a");

        puts("message?");
        char *message = fgets(buffer, 4096, stdin);
        fprintf(outbox, "%s: %s\n", me, message);
        fclose(outbox);
    }

    return 0;
}