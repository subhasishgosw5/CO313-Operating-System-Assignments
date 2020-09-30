#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


void perform_operation(int signal)
{
    printf("\nInterrupt Signal Received!\n\nCreating Fork...\n\n");

    int child = fork();
    if (child < 0)
    {
        printf("Fork error\n");
        exit(1);
    }
    if (child == 0)
    {
        printf("Child Section:\n\tPID is %d and PPID is %d\n", getpid(), getppid());

    }
    else
    {
        wait(NULL);
        printf("Parent Section:\n\tPID is %d and PPID is %d\n", getpid(), getppid());
    }
    exit(0);
}

int main()
{
    printf("\nPress Ctrl+C to send Interrupt Signal!\n");

    for(;;)
    {
        void *call=signal(SIGINT, perform_operation);
        if ( call == SIG_ERR)
        {
            perror("Signal");
            exit(1);
        }
    }
    exit(0);
}