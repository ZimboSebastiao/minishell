/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:39 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/31 21:58:55 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	end;
	size_t	i;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	first = 0;
	end = ft_strlen(s1);
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	while (end > first && ft_strchr(set, s1[end -1]))
		end--;
	res = (char *)malloc(end - first + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (first < end)
	{
		res[i] = s1[first];
		i++;
		first++;
	}
	res[i] = '\0';
	return (res);
}
