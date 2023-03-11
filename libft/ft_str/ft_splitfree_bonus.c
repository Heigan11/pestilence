/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitfree_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:09:57 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:12:32 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_splitfree(char **splitted)
{
	size_t	i;

	if (splitted)
	{
		i = 0;
		while (splitted[i])
		{
			free(splitted[i]);
			i++;
		}
		free(splitted);
	}
}
