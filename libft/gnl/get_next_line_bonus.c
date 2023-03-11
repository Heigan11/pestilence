/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:18:22 by chilton           #+#    #+#             */
/*   Updated: 2021/04/23 17:56:28 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"

static void	push_data(t_file_list *file, char *buf, size_t n)
{
	char	*new_data;
	size_t	new_size;

	new_size = n + file->size;
	if (new_size == 0)
	{
		free(file->data);
		file->data = NULL;
		return ;
	}
	new_data = malloc(sizeof(char) * new_size);
	if (new_data)
	{
		ft_memcpy(new_data, file->data, file->size);
		ft_memcpy(new_data + file->size, buf, n);
		free(file->data);
		file->data = new_data;
		file->size = new_size;
	}
	else
		file->status = -1;
}

static void	pop_line(t_file_list *file, char **line)
{
	size_t	i;
	size_t	new_data_size;

	i = get_eol_index(file->data, file->size);
	*line = malloc(sizeof(char) * (i + 1));
	if (*line)
	{
		ft_memcpy(*line, file->data, i);
		(*line)[i] = '\0';
		if (i == file->size)
			new_data_size = 0;
		else
			new_data_size = file->size - (i + 1);
		file->size = 0;
		push_data(file, file->data + (i + 1), new_data_size);
		if (file->status == -1)
		{
			free(*line);
			line = NULL;
		}
	}
	else
		file->status = -1;
}

static void	read_file(t_file_list *file, int fd)
{
	char	buf[BUFFER_SIZE];
	ssize_t	n;

	n = read(fd, buf, BUFFER_SIZE);
	while (n > 0)
	{
		push_data(file, buf, n);
		if (file->status == -1)
			return ;
		if (get_eol_index(buf, n) != (size_t)n)
			break ;
		n = read(fd, buf, BUFFER_SIZE);
	}
	if (n > 0)
		file->status = 1;
	else
		file->status = (int)n;
}

int	get_next_line(int fd, char **line)
{
	static t_file_list	*files = NULL;
	t_file_list			*cur_file;
	int					cur_status;

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) == -1)
		return (-1);
	*line = NULL;
	cur_file = ft_lstaddget_item(&files, fd);
	if (!cur_file)
		return (-1);
	if (get_eol_index(cur_file->data, cur_file->size) == cur_file->size
		&& cur_file->status != -1)
		read_file(cur_file, fd);
	if (cur_file->status >= 0)
		pop_line(cur_file, line);
	cur_status = cur_file->status;
	if (cur_file->status <= 0)
	{
		if (cur_file->status == -1)
			free(cur_file->data);
		ft_lstdel_item(&files, fd);
	}
	return (cur_status);
}
