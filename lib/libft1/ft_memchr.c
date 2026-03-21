/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 04:30:21 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/31 18:33:34 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	size_t			i;

	i = 0;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == ch)
		{
			return ((unsigned char *)s + i);
		}
		++i;
	}
	return (NULL);
}
