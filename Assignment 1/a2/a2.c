#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utmp.h>
#include <sys/utsname.h>


void printUsers()
{
    struct utmp *n;
    setutent();
    n = getutent();
    printf("GrandChild Section :\n\tLoggedIn Users are :");
    while (n)
    {
        if (n->ut_type == USER_PROCESS)
        {
            printf("\n\t%s", n->ut_user);
        }
        n = getutent();
    }
    printf("\n");
}

int main()
{

    int child, grandChild;

    child = fork();
    if (child < 0)
    {

        printf("Fork error\n");
        exit(1);
    }

    grandChild = fork();
    if (grandChild < 0)
    {
        printf("Fork error\n");
        exit(1);
    }
    else if (grandChild == 0 && child == 0)
    {
        printUsers();
    }

    wait(NULL);
    exit(0);

}