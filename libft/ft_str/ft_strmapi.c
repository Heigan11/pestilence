/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:20:32 by chilton           #+#    #+#             */
/*   Updated: 2020/11/09 13:27:52 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	l;
	char	*new_s;

	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	new_s = malloc((l + 1) * sizeof(char));
	if (new_s)
	{
		new_s[l] = '\0';
		while (l--)
		{
			new_s[l] = (*f)(l, s[l]);
		}
	}
	return (new_s);
}
