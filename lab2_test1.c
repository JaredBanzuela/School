#include "types.h"
#include "user.h"
#include "syscall.h"

int PScheduler(void);

int main(int argc, char *argv[])
{
    PScheduler();

    exit(0);
}    
      
int PScheduler(void){
		 
    // Use this part to test the priority scheduler. Assuming that the priorities range between range between 0 to 31
    // 0 is the highest priority. All processes have a default priority of 10
    // You can use your own priority range/value setup

    int pid, ret_pid, exit_status;
    int i,j,k;
    int start, pstart;
    int end, pend;

    pstart = uptime();
    // printf(1, "Start: %d \n", pstart);
  
    printf(1, "Testing the priority scheduler and setpriority system call:\n");
    printf(1, "Assuming that the priorities range between range between 0 to 31\n");
    printf(1, "0 is the highest priority. All processes have a default priority of 10\n");
    printf(1, " - The parent processes will switch to priority 0\n");
    setprio(0); // Use your own setpriority interface
    for (i = 0; i < 3; i++) {
	pid = fork();
	if (pid > 0) {
            continue;
        } else if ( pid == 0) {
            printf(1, " - Hello! this is child# %d and I will change my priority to %d \n", getpid(), 60 - 20 * i);
            setprio(30 - 10 * i); // Use your own setpriority interface
	    start = uptime();
	    // printf(1, "CStart: %d \n", start);
            for (j = 0; j < 50000; j++) {
                asm("nop");
                for(k = 0; k < 10000; k++) {
                    asm("nop"); 
                }
            }
            printf(1, " - Child #%d with priority %d has finished! \n", getpid(), 30-10*i);		
	    end = uptime();
            // printf(1, "CEnd: %d \n", end);
	    printf(1, "Turnaround? %d0ms \n", end - start);
	    // printf(1, "CBurst: %d \n", getburst());
	    printf(1, "Waiting Time? %d0ms \n", (end - start) - getburst());
            exit(0);
        } else {
            printf(2," \n Error fork() \n");
            exit(-1);
        }
    }

    if(pid > 0) {
        for (i = 0; i < 3; i++) {
            ret_pid = wait(&exit_status);
            printf(1, " - This is the parent: child with PID# %d has finished with status %d \n", ret_pid, exit_status);
        }
        printf(1, " - If processes with highest priority finished first then its correct. \n");
    }
    
    pend = uptime();
    // printf(1, "End: %d \n", pend);
    printf(1, "Parent Turnaround? %d0ms \n", pend - pstart);
    printf(1, "Parent Waiting Time? %d0ms \n", (pend - pstart) - getburst());
			
    return 0;
}

