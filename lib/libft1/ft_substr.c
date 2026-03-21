/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:49:59 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/30 20:48:52 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*sub;

	if (s == NULL)
		return (NULL);
	k = 0;
	j = 0;
	i = start;
	while (s[k] != '\0')
		k++;
	if (start >= k)
		return (ft_strdup(""));
	k = k - start;
	if (len > k)
		len = k;
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	while (s[i] != '\0' && j < len)
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}
