/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_delimiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:40:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/10 16:55:25 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_has_quotes(char *str)
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

static void	ft_process_delimiter_char(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote && (c == '\'' || c == '"'))
	{
		*quote_char = c;
		*in_quote = 1;
	}
	else if (*in_quote && c == *quote_char)
		*in_quote = 0;
}

char	*ft_remove_quotes_from_delimiter(char *delimiter)
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
		ft_process_delimiter_char(delimiter[i], &in_quote, &quote_char);
		if (!(delimiter[i] == '\'' || delimiter[i] == '"')
			|| (in_quote && delimiter[i] != quote_char))
			result[j++] = delimiter[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

t_heredoc_info	*ft_parse_heredoc_delimiter(char *delimiter_token)
{
	t_heredoc_info	*info;

	info = malloc(sizeof(t_heredoc_info));
	if (!info)
		return (NULL);
	if (ft_has_quotes(delimiter_token))
	{
		info->expand = 0;
		info->delimiter = ft_remove_quotes_from_delimiter(delimiter_token);
	}
	else
	{
		info->expand = 1;
		info->delimiter = ft_strdup(delimiter_token);
	}
	if (!info->delimiter)
	{
		free(info);
		return (NULL);
	}
	return (info);
}
