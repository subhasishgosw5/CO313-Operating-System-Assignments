#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


void perform_operation(int signal)
{
    printf("\nInterrupt Signal Received: %d\n", signal);
    int PID;
    FILE *fp = fopen("to_kill_pid.txt", "r");
    fscanf(fp, "%d ", &PID);
    fclose(fp);
    printf("\nPID of the process to be killed is %d\n", PID);
    kill(PID, signal);
    printf("\n!!!Process killed Successfully!!!\n");
    exit(0);
}

int main()
{
    printf("Press Ctrl+C to send the signal!\n");

    for(;;)
    {
        void *call=signal(SIGINT, perform_operation);
        if (call == SIG_ERR)
        {
            perror("Signal");
            exit(1);
        }
    }
    exit(0);
}