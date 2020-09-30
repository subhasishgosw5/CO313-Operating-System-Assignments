#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

	int count = 1, child, grandChild, child_count=0, grandchild_count=0;

	child = fork();
	if (child < 0)
	{
		printf( "Fork error\n");

		exit(1);
	}
	if(child == 0){

			grandChild = fork();
			if (grandChild < 0)
			{
				printf( "Fork error\n");

				exit(1);
			}
			else if (grandChild == 0)
			{
				int GC_PPID = getppid(), GC_PID = getpid();
				printf( "\nGrandChild Section :\n\tRoll No is CSB18061\n\tPID = %d. PPID = %d\n",GC_PID, GC_PPID);

				FILE *fp = fopen("GC Data.txt", "w");
				fprintf(fp,"%d %d ", GC_PID , GC_PPID);
				fclose(fp);
			} else {
				printf( "\nChild Section :\n\tPID = %d and PPID = %d\n", getpid(), getppid());

			}

	}
	wait(NULL);

	if (child > 0)
	{
		int GC_PID, GC_PPID;
		FILE *fp = fopen("GC Data.txt", "r");
		fscanf(fp,"%d %d ",&GC_PID,&GC_PPID);
		fclose(fp);
		printf( "\nParent Section :\n\tPID = %d\n\tChild PID = %d & PPID = %d\n\tGrandChild PID = %d PPID = %d\n", getpid(), child, getpid(), GC_PID, GC_PPID);

	}
	if (child == 0)
	{
		count++;
		child_count++;
		if (grandChild == 0)
		{
			count++;
			grandchild_count++;
			printf("\nTotal Processes: %d (Parent = %d, Children = %d, Grandchildren = %d)\n", count,(count-child_count-grandchild_count),child_count,grandchild_count);
		}
	}
	exit(0);
}