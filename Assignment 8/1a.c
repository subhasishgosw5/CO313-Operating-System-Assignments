#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    char *name = argv[0];
    int status;
    int child_counter=0, grand_child_counter=0;
    int child_pid = fork();
    int grand_child_id;
    if (child_pid < 0)
    {
        printf("Fork error\n");
        exit(1);
    }
    if (child_pid == 0)
    {
        printf("Child pid : %d and MyParent Id : %d\n",getpid(),getppid());
        child_counter++;
        grand_child_id = fork();
        if(grand_child_id<0)
        {
            printf("Fork error in grandchild formation");
            exit(1);
        }
        if (grand_child_id == 0)
        {
            // printf("\nGrandChild pid : %d and MyParent Id : %d\n",getpid(),getppid());
            printf("Myself Grand Child printing Roll NO : CSB18031\n\n");
            grand_child_counter++;
            printf("Child Created : %d\n",child_counter);
            printf("GrandChild Created : %d\n",grand_child_counter);
        }
        else
        {
            printf("Parent of Grand Child ppid : %d\n", grand_child_id);
            exit(0);
        }
    }
    else
    {
        printf("My child is %d\n", child_pid);
        exit(0);
    }
}