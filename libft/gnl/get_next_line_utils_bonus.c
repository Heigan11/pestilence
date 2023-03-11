/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:18:24 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:10:31 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	get_eol_index(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

void	ft_lstdel_item(t_file_list **lst, int fd)
{
	t_file_list	*prev;
	t_file_list	*next;

	if (!*lst)
		return ;
	prev = *lst;
	next = (*lst)->next;
	if ((*lst)->fd == fd)
	{
		free(*lst);
		*lst = next;
		return ;
	}
	while (next)
	{
		if (next->fd == fd)
		{
			prev->next = next->next;
			free(next);
			return ;
		}
		prev = next;
		next = next->next;
	}
}

t_file_list	*ft_lstaddget_item(t_file_list **lst, int fd)
{
	t_file_list	*ptr;

	ptr = *lst;
	while (ptr)
	{
		if (ptr->fd == fd)
			return (ptr);
		ptr = ptr->next;
	}
	ptr = malloc(sizeof(t_file_list));
	if (ptr)
	{
		ptr->fd = fd;
		ptr->data = NULL;
		ptr->size = 0;
		ptr->status = 1;
		ptr->next = *lst;
		*lst = ptr;
	}
	return (ptr);
}
