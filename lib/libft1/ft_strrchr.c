/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:21:23 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/25 03:21:42 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	int				i;

	ch = c;
	i = 0;
	while (s[i])
	{
		++i;
	}
	if (ch == '\0')
		return ((char *)&s[i]);
	while (i > 0)
	{
		--i;
		if (s[i] == ch)
		{
			return ((char *)&s[i]);
		}
	}
	return (NULL);
}
