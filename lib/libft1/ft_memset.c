/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:32:51 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/31 21:44:25 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	nc;
	size_t			i;

	i = 0;
	nc = c;
	while (i < n)
	{
		((char *) s)[i] = nc;
		i++;
	}
	return (s);
}
