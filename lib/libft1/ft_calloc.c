/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:06:47 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/28 20:03:19 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*ptr;
	size_t	bytes;

	i = 0;
	ptr = NULL;
	bytes = nmemb * size;
	if (nmemb != 0 && (bytes / nmemb != size))
		return (NULL);
	ptr = malloc(bytes);
	if (ptr == NULL)
		return (NULL);
	while (i < bytes)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
