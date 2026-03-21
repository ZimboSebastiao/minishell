/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 06:15:02 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/25 05:18:01 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	k = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	while (src[k] != '\0')
		k++;
	if (i >= size)
	{
		return (size + k);
	}
	while (src[j] != '\0' && (j + i) < (size - 1))
	{
		dst[i + j] = src[j];
		++j;
	}
	dst[i + j] = '\0';
	return (k + i);
}
