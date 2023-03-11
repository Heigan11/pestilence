/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:18:17 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:10:51 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_file_list
{
	int					fd;
	char				*data;
	size_t				size;
	int					status;
	struct s_file_list	*next;
}t_file_list;

size_t		get_eol_index(const char *s, size_t n);
void		ft_lstdel_item(t_file_list **lst, int fd);
t_file_list	*ft_lstaddget_item(t_file_list **lst, int fd);
int			get_next_line(int fd, char **line);

#endif
