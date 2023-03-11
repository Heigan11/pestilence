/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:00:11 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:14:21 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	next_word(char const **s, char c)
{
	size_t	l;

	while (**s && **s == c)
	{
		(*s)++;
	}
	l = 0;
	while ((*s)[l] && (*s)[l] != c)
	{
		l++;
	}
	return (l);
}

static size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = next_word(&s, c);
		if (*s)
			i++;
		s += len;
	}
	return (i);
}

static char	*new_word(char const **str, char c)
{
	size_t	len;
	char	*word;

	len = next_word(str, c);
	word = malloc((len + 1) * sizeof(char));
	if (word)
		ft_strlcpy(word, *str, len + 1);
	*str += len;
	return (word);
}

static void	cleanup(char **words, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	n_words;
	size_t	i;

	if (!s)
		return (NULL);
	n_words = word_count(s, c);
	words = malloc((n_words + 1) * sizeof(char *));
	if (words)
	{
		i = 0;
		words[n_words] = NULL;
		while (i < n_words)
		{
			words[i] = new_word(&s, c);
			if (!words[i])
			{
				cleanup(words, i);
				return (NULL);
			}
			i++;
		}
	}
	return (words);
}
