/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zalberti <zalberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:52:19 by zalberti          #+#    #+#             */
/*   Updated: 2025/07/31 22:47:02 by zalberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		i;
	char	*s;
	int		temp;

	temp = n;
	i = (n <= 0);
	while (temp && (i++ >= 0))
		temp /= 10;
	s = malloc(i + 1);
	if (!s)
		return (NULL);
	s[i] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
		s[0] = '-';
	while (i-- && n)
	{
		if (n < 0)
			s[i] = -(n % 10) + '0';
		else
			s[i] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}
