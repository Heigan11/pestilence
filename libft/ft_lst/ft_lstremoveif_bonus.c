/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:43:39 by chilton           #+#    #+#             */
/*   Updated: 2021/01/26 19:20:49 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremoveif(t_list **lst, void *data_ref, int (*cmp)(),
void (*del)(void *))
{
	t_list	*prev;
	t_list	*next;

	if (*lst)
	{
		prev = *lst;
		next = (*lst)->next;
		if (!cmp((*lst)->content, data_ref))
		{
			ft_lstdelone(*lst, del);
			*lst = next;
			return ;
		}
		while (next)
		{
			if (!cmp(next->content, data_ref))
			{
				prev->next = next->next;
				ft_lstdelone(next, del);
				return ;
			}
			prev = next;
			next = next->next;
		}
	}
}
