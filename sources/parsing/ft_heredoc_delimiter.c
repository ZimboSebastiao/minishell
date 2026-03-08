/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_delimiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:40:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 00:59:13 by zimbo            ###   ########.fr       */
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

static void	process_delimiter_char(char c, t_quote_state *state, char *result)
{
	if (!state->in_quote && (c == '\'' || c == '"'))
	{
		state->quote_char = c;
		state->in_quote = 1;
	}
	else if (state->in_quote && c == state->quote_char)
		state->in_quote = 0;
	else
		result[state->j++] = c;
}

char	*remove_quotes_from_delimiter(char *delimiter)
{
	char			*result;
	int				i;
	t_quote_state	state;

	result = malloc(ft_strlen(delimiter) + 1);
	if (!result)
		return (NULL);
	i = 0;
	state.in_quote = 0;
	state.quote_char = 0;
	state.j = 0;
	while (delimiter[i])
	{
		process_delimiter_char(delimiter[i], &state, result);
		i++;
	}
	result[state.j] = '\0';
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
