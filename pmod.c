/*********************************************************************
* @file pmod.c
* @brief pmod file
* @author Mac Patterson
* @date 10/28/2026
*********************************************************************/

#include <stdio.h>  
#include <errno.h> 
#include <unistd.h>  
#include <time.h>   

int main(int argc, char* argv[])
{
    errno = 0;
    int new_nice = nice(10);
    if (new_nice == -1 && errno != 0)
    {
        perror("nice");
        return 1;
    }
    printf("Priority reduced. New nice value: %d\n", new_nice);
    struct timespec request;
    struct timespec remaining;
    request.tv_sec = 1;
    request.tv_nsec = 837272638;

    while (nanosleep(&request, &remaining) == -1)
    {
        if (errno == EINTR)
        {
            request = remaining;  // sleep for whatever time is left
        }
        else
        {
            perror("nanosleep");
            return 1;
        }
    }

    printf("Goodbye!\n");

    return 0;
}