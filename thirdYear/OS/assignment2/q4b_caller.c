#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main() {
    printf("#####################CALLER#################################\n");
    char * uniqueNamedFifo = "uniqueNamedFifo";
    if (mkfifo(uniqueNamedFifo, 0777) == -1) {
            perror("Fifo file could not be created\n");
            return 1;
    }
    int fn = open(uniqueNamedFifo, O_WRONLY);
    char* str;
    int len;
    while (1) {
        printf("Send data: ");
        fgets(str, 100, stdin);
        str[strlen(str) - 1] = '\0';
        len = strlen(str) + 1;
        if (write(fn, &len, sizeof(int)) == -1) {
            printf("Can't write string length\n");
            return 0;
        }
        if (write(fn, str, sizeof(char) * len) == -1) {
            printf("Can;t write data to fifo\n");
            return 0;
        }
        if (strcmp(str, "TERMINATE") == 0) {
            break;
        }
        printf("Message sent\n");
    }
    printf("CONVERSATION ENDED\n");
    close(fn);
    return 0;
};
