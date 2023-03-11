/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitlen_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:09:43 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:12:28 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_splitlen(char **splitted)
{
	size_t	len;

	len = 0;
	while (splitted[len])
		len++;
	return (len);
}
