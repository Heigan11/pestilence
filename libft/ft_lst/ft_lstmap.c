/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:09:26 by chilton           #+#    #+#             */
/*   Updated: 2020/11/09 20:01:51 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*new_list;

	new_list = NULL;
	while (lst)
	{
		ptr = ft_lstnew(f(lst->content));
		if (ptr)
		{
			ft_lstadd_back(&new_list, ptr);
		}
		else
		{
			ft_lstclear(&new_list, del);
		}
		lst = lst->next;
	}
	return (new_list);
}
