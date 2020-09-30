#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utmp.h>
#include <sys/utsname.h>



int main(int argc, char *argv[])
{


    int child, grandChild;
    int stat;

    child = fork();
    if (child < 0)
    {
        printf("Fork error\n");
        exit(1);
    }
    if (child == 0)
    {
        printf("Program Name is %s\n", argv[0]);
        char **args[] = {"./a3_pt2", NULL};
        execv(args[0], args);
    }
    else{

        wait(&stat);
        if (WIFEXITED(stat))
            printf("Child has exited with exit code %d\n", WEXITSTATUS(stat));
        else
            printf("Child has terminated abnormally\n");
        exit(0);

    }



}