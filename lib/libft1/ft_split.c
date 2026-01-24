/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:49:53 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/31 22:50:56 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	free_all(char **arr, int i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

static char	*alloc_word(char const **s, char c)
{
	int		len;
	int		j;
	char	*word;

	len = 0;
	j = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (j < len)
	{
		word[j] = (*s)[j];
		j++;
	}
	word[j] = '\0';
	*s += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !(res))
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		res[i] = alloc_word(&s, c);
		if (!res[i])
			return (free_all(res, i), NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
