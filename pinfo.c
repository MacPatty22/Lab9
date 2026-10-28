/*********************************************************************
* @file pinfo.c
* @brief pfinfo file
* @author Mac Patterson
* @date 10/28/2026
*********************************************************************/

#define _GNU_SOURCE

#include <stdio.h>  
#include <stdlib.h> 
#include <errno.h>  
#include <unistd.h>
#include <sched.h>
#include <sys/resource.h>  
#include <sys/types.h>     

const char* policy_to_string(int policy)
{
    switch (policy)
    {
        case SCHED_OTHER:
            return "SCHED_OTHER (default time-sharing)";
        case SCHED_FIFO:
            return "SCHED_FIFO (real-time, first-in first-out)";
        case SCHED_RR:
            return "SCHED_RR (real-time, round-robin)";
        case SCHED_BATCH:
            return "SCHED_BATCH (batch processing)";
        case SCHED_IDLE:
            return "SCHED_IDLE (very low priority background)";
        default:
            return "UNKNOWN";
    }
}

int main(int argc, char* argv[])
{
    pid_t pid;

    if (argc == 1)
    {
        pid = getpid();
    }
    else if (argc == 2)
    {
        char* endptr;
        errno = 0;
        long value = strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || endptr == argv[1] || value <= 0)
        {
            fprintf(stderr, "Error: '%s' is not a valid process ID\n", argv[1]);
            return 1;
        }
        pid = (pid_t)value;
    }
    else
    {
        fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
        return 1;
    }

    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0)
    {
        if (errno == ESRCH)
        {
            fprintf(stderr, "Error: process %d does not exist\n", pid);
        }
        else
        {
            perror("getpriority");
        }
        return 1;
    }
    
    int policy = sched_getscheduler(pid);
    if (policy == -1)
    {
        if (errno == ESRCH)
        {
            fprintf(stderr, "Error: process %d does not exist\n", pid);
        }
        else
        {
            perror("sched_getscheduler");
        }
        return 1;
    }

    printf("Process ID: %d\n", pid);
    printf("Priority (nice value): %d\n", priority);
    printf("Scheduling policy: %s\n", policy_to_string(policy));

    return 0;
}