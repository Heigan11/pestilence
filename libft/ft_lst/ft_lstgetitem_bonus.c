/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetitem_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:34:50 by chilton           #+#    #+#             */
/*   Updated: 2021/04/23 16:34:53 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstgetitem(t_list *lst, void *data_ref, int (*cmp)())
{
	while (lst)
	{
		if (cmp(lst->content, data_ref) == 0)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}
