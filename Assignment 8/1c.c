#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <utmp.h>
#include <errno.h>

int main(int argc, char **argv)
{
    char *name = argv[0];
    
    int status;
    int exit_code1, exit_code2;
    int child_counter=0, grand_child_counter=0;
    int child_pid = fork();
    int grand_child_id;

    char *params[] = {"The name of the Program is :",name, NULL};
    if (child_pid < 0)
    {
        printf("Fork error\n");
        exit(1);
    }
    if (child_pid == 0)
    {
        execv("./test", params);
        printf("Return not expected. Must be an execv error.n\n");
        perror("execv");
        exit_code1 = getpid();
        child_counter++;
        grand_child_id = fork();
        if(grand_child_id<0)
        {
            printf("Fork error in grandchild formation");
            exit(1);
        }
        if (grand_child_id == 0)
        {
            struct utmp *log;    
            printf("I am the grandchild printing the no. of users logging in are :%s\n",log->ut_user);
            exit_code2=getpid();
            grand_child_counter++;
            exit(exit_code2);
        }
        else
        {
            printf("Parent of Grand Child ppid : %d\n", grand_child_id);
            wait(&exit_code2);
            printf("My child's  with PID : %d  exit status is: %d\n",grand_child_id, WEXITSTATUS(exit_code2));
            // exit(exit_code2);
        }
    }
    else
    {
        printf("My child is %d\n", child_pid);
        wait(&exit_code1);
        printf("My child's with PID : %d exit status is: %d\n", child_pid ,WEXITSTATUS(exit_code1));
        // exit(exit_code1);
    }

}