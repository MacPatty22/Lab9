/*********************************************************************
* @file info.c
* @brief system calls
* @author Mac Patterson
* @date 10/28/2026
*********************************************************************/

#include <stdio.h> 
#include <time.h>   
#include <unistd.h>   
#include <sys/utsname.h> 
#include <sys/sysinfo.h>  

int main(int argc, char* argv[])
{
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
    {
        perror("clock_gettime");
        return 1;
    }
    long long nanos = (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
    printf("Current time (ns): %lld\n", nanos);

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == -1)
    {
        perror("gethostname");
        return 1;
    }
    hostname[sizeof(hostname) - 1] = '\0';  // guarantee it's null-terminated

    struct utsname info;
    if (uname(&info) == -1)
    {
        perror("uname");
        return 1;
    }

    if (hostname[0] != '\0')
    {
        printf("Network name: %s\n", hostname);
    }
    if (info.sysname[0] != '\0')
    {
        printf("OS name: %s\n", info.sysname);
    }
    if (info.release[0] != '\0')
    {
        printf("OS release: %s\n", info.release);
    }
    if (info.version[0] != '\0')
    {
        printf("OS version: %s\n", info.version);
    }
    if (info.machine[0] != '\0')
    {
        printf("Hardware type: %s\n", info.machine);
    }

    int cpus = get_nprocs();
    printf("Number of CPUs: %d\n", cpus);
    long page_size = getpagesize();
    long long total_mem = (long long)sysconf(_SC_PHYS_PAGES) * page_size;
    long long free_mem = (long long)sysconf(_SC_AVPHYS_PAGES) * page_size;
    printf("Total memory: %lld bytes\n", total_mem);
    printf("Free memory: %lld bytes\n", free_mem);

    return 0;
}