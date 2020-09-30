#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <utmp.h>


void userlogged()
{
    struct utmp *usersList;
    setutent(); 
    // Description about setutent:
        // The setutent() function resets the input stream to the beginning of the file specified in _PATH_UTMP. Do this before each search for a new entry if you want the entire file to be examined.

    // Files:
        // _PATH_UTMP
        // Specifies the user information file.
    usersList = getutent(); 
    //Description about getutent :
        // The getutent() function reads in the next entry from a user-information file. If the file isn't already open, getutent() opens it. If the function reaches the end of the file, it fails.

    // Returns:
        // A pointer to a utmp structure for the next entry, or NULL if the file couldn't be read or reached the end of file.

    // Files:
        // _PATH_UTMP
        // Specifies the user information file.
    int n_of_users = 0;
    while (usersList != NULL)
    {
        if (usersList->ut_type == USER_PROCESS) //USER_PROCESS checks if it is a user logged process
        {
            printf("User no. %d is %s\n",++n_of_users, usersList->ut_user);
        }
        usersList = getutent();
    }
    printf("\n");
}


int main(int argc, char **argv)
{
    char *name = argv[0];
    int status;
    int exit_code1, exit_code2;
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
            // printf("\nGrandChild pid : %d and MyParent Id : %d\n",getpid(),getppid());
            printf("\nIn GrandChild Process printing the Users Logged here : \n");
            //Will only print user if in Linux system
            userlogged();
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