#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int list_dir(char dir_name[128])
{
    DIR *dir;
    struct dirent *p;

    dir = opendir(dir_name);
    if (dir == NULL)
    {
        err("Cannot open dir!\n");
        return -1;
    }

    while ((p = readdir(dir)) != NULL)
    {
        printf("name: %s\n", p->d_name);
    }
    closedir(dir);

    return 0;
}