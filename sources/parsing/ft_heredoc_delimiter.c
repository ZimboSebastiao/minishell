/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_delimiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:40:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:35:38 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static char	*remove_quotes_from_delimiter(char *delimiter)
{
	char	*result;
	int		i;
	int		j;
	int		in_quote;
	char	quote_char;

	result = malloc(ft_strlen(delimiter) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	quote_char = 0;
	while (delimiter[i])
	{
		if (!in_quote && (delimiter[i] == '\'' || delimiter[i] == '"'))
		{
			quote_char = delimiter[i];
			in_quote = 1;
		}
		else if (in_quote && delimiter[i] == quote_char)
			in_quote = 0;
		else
			result[j++] = delimiter[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

t_heredoc_info	*parse_heredoc_delimiter(char *delimiter_token)
{
	t_heredoc_info	*info;

	info = malloc(sizeof(t_heredoc_info));
	if (!info)
		return (NULL);
	if (has_quotes(delimiter_token))
	{
		info->expand = 0;
		info->delimiter = remove_quotes_from_delimiter(delimiter_token);
	}
	else
	{
		info->expand = 1;
		info->delimiter = ft_strdup(delimiter_token);
	}
	return (info);
}
