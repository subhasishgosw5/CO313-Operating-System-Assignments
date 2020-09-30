#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


int main()
{
    printf("\nHi! I will be killed by a secondary program!\n");
    int PID = getpid();
    printf("\nMy PID is : %d\n", PID);
    FILE *fp = fopen("to_kill_pid.txt", "w");
    fprintf(fp, "%d ", PID);
    fclose(fp);

    for(;;)
    {
        //Keep the Program Running Until killed from the Secondary Program
    }

    exit(0);
}