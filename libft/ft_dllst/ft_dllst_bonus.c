/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllst_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:26:17 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:51:28 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dllist	*ft_dllstnew(void *data)
{
	t_dllist	*new;

	new = malloc(sizeof(t_dllist));
	if (new)
	{
		new->data = data;
		new->prev = NULL;
		new->next = NULL;
	}
	return (new);
}

void	ft_dllstadd_front(t_dllist **dllst, t_dllist *new)
{
	if (*dllst)
	{
		new->next = *dllst;
		(*dllst)->prev = new;
	}
	*dllst = new;
}

void	ft_dllstclear(t_dllist **dllst, void (*del)(void*))
{
	t_dllist	*tmp;

	while (*dllst)
	{
		tmp = (*dllst)->next;
		del((*dllst)->data);
		free(*dllst);
		*dllst = tmp;
	}
}
