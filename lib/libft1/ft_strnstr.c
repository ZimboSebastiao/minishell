/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:22:46 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/27 01:06:11 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
	{
		return ((char *)big);
	}
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == *little)
		{
			j = 0;
			while (little[j] != '\0' && i + j < len && big[i + j] == little[j])
				++j;
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		++i;
	}
	return (NULL);
}
