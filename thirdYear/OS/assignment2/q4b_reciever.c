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
    printf("#####################RECEIVER#################################\n");
    char * uniqueNamedFifo = "uniqueNamedFifo";
    int fn = open(uniqueNamedFifo, O_RDONLY);
    char* str;
    int len;
    while (1) {
        if (read(fn, &len, sizeof(int)) == -1) {
            return 0;
        }
        if (read(fn, str, sizeof(char) * len) == -1) {
            return 0;
        }
        if (strcmp(str, "TERMINATE") == 0)
        break;
        printf("Message recieved : %s\n", str);
    }
    printf("CONVERSATION ENDED\n");
    close(fn);
    remove(uniqueNamedFifo);//Removing FIFO file
    return 0;
};
