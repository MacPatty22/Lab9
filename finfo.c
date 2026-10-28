/*********************************************************************
* @file finfo.c
* @brief finfo
* @author Mac Patterson
* @date 10/28/2026
*********************************************************************/

#include <stdio.h>    
#include <sys/types.h> 
#include <sys/stat.h> 
#include <time.h>     

const char* file_type_string(mode_t mode)
{
    if (S_ISREG(mode))
    {
        return "Regular file";
    }
    else if (S_ISDIR(mode))
    {
        return "Directory";
    }
    else if (S_ISLNK(mode))
    {
        return "Symbolic link";
    }
    else if (S_ISCHR(mode))
    {
        return "Character device";
    }
    else if (S_ISBLK(mode))
    {
        return "Block device";
    }
    else if (S_ISFIFO(mode))
    {
        return "FIFO (named pipe)";
    }
    else if (S_ISSOCK(mode))
    {
        return "Socket";
    }
    return "Unknown";
}

void permission_string(mode_t mode, char perms[10])
{
    perms[0] = (mode & S_IRUSR) ? 'r' : '-';  // owner read
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';  // owner write
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';  // owner execute
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';  // group read
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';  // group write
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';  // group execute
    perms[6] = (mode & S_IROTH) ? 'r' : '-';  // others read
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';  // others write
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';  // others execute
    perms[9] = '\0';
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat info;
    if (lstat(argv[1], &info) == -1)
    {
        perror(argv[1]);
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Type: %s\n", file_type_string(info.st_mode));
    char perms[10];
    permission_string(info.st_mode, perms);
    printf("Permissions: %s (%03o)\n", perms, info.st_mode & 0777);
    printf("Owner user ID: %d\n", (int)info.st_uid);
    printf("Size: %lld bytes\n", (long long)info.st_size);

    struct tm* mod_time = localtime(&info.st_mtime);
    if (mod_time == NULL)
    {
        perror("localtime");
        return 1;
    }

    char time_buf[64];
    if (strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", mod_time) == 0)
    {
        fprintf(stderr, "Error: could not format modification time\n");
        return 1;
    }
    printf("Last modified: %s\n", time_buf);

    return 0;
}