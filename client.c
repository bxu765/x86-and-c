#include <stdio.h>	
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <string.h>
#include <stdlib.h> //atoi 


int main(int argc , char *argv[]){
    /*
        Initalize struct sockaddr_in to contain IP address and port number of server. 
        Remember to read values from argv. (You also need to convert it from 
        a string to an int, so the atoi function is very helpful)
     */

    struct sockaddr_in ip;
    memset(&ip, 0, sizeof(struct sockaddr_in));
    ip.sin_family = AF_INET;
    ip.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &ip.sin_addr);

    //Create Socket  (Remember to check the return value to see if an error occured) 
    int s = socket(AF_INET, SOCK_STREAM, 0);
    
    //Connect to Remote server 
    connect(s, (struct sockaddr*)&ip, sizeof(ip));
    
    //Read message from server (Note: The server sends multiple messages, so you might need a loop)
    char *txt = (char *)malloc(10000);
    ssize_t r = read(s, txt, 10000);
    while (r) {
        fprintf(stdout, "%s", txt);
        r = read(s, txt, 10000);
    }

    //Close socket and free anything you malloced
    close(s);
    free(txt);
    return 0;
}