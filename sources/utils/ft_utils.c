/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:54:12 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/12 21:17:48 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_array(t_env *env)
{
	char	**array;
	t_env	*tmp;
	int		count;
	int		i;

	count = ft_count_env_vars(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			array[i] = ft_join_key_value(tmp);
			i++;
		}
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

void	ft_add_redir(t_redir **list, t_redir *new)
{
	t_redir	*tmp;

	if (!new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_redir_type	ft_token_to_redir(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND)
		return (redir_append);
	if (type == TOKEN_HEREDOC)
		return (redir_heredoc);
	return (REDIR_IN);
}

void	ft_skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

int	ft_is_word_char(char c, int *in_quotes, char *quote_char)
{
	if (!*in_quotes && (c == '\'' || c == '"'))
	{
		*quote_char = c;
		*in_quotes = 1;
		return (1);
	}
	if (*in_quotes && c == *quote_char)
	{
		*in_quotes = 0;
		return (1);
	}
	if (!*in_quotes && (c == ' ' || c == '\t' || ft_is_operator(c)))
		return (0);
	return (1);
}
