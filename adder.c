#include <stdio.h>
#include <string.h>

int main(int args, char *argv[]) {
    char type;
    if(args < 2){
        printf("What types of values do you want to add: ");
        scanf("%c", &type);
    }else{
        if(strcmp(argv[1], "-s") == 0) type = 'S';
        else if(strcmp(argv[1], "-i") == 0) type = 'I';
        else if(strcmp(argv[1], "-f") == 0) type = 'F';
        else{
            printf("Invalid flag supplied");
            return 0;
        }
    }
    if(type == 'S'){
        char string1[21];
        char string2[11];
        printf("Enter First String: ");
        scanf("%10s", string1);
        printf("Enter Second String: ");
        scanf("%10s", string2);
        strcat(string1,string2);
        printf("%s\n", string1);
    }else if(type == 'I'){
        int value1 = 0;
        int value2 = 0;
        printf("Enter your first value: ");
        scanf("%d", &value1);
        printf("Enter your second value: ");
        scanf("%d", &value2);
        printf("%d\n", value1+value2);
    }else if(type == 'F'){
        float value1 = 0;
        float value2 = 0;
        printf("Enter your first value: ");
        scanf("%f", &value1);
        printf("Enter your second value: ");
        scanf("%f", &value2);
        printf("%f\n", value1+value2);
    }
}