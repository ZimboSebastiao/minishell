/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 23:39:16 by zimbo             #+#    #+#             */
/*   Updated: 2026/02/16 04:15:10 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

int	ft_is_operator(char	c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*ft_new_token(t_token_type type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_add_token(t_token **list, t_token *new)
{
	t_token	*tmp;

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

t_token	*ft_read_operator(char **line)
{
	if (**line == '|')
	{
		(*line)++;
		return (ft_new_token(TOKEN_PIPE, NULL));
	}
	else if (**line == '<')
	{
		if (*(*line + 1) == '<')
		{
			(*line) += 2;
			return (ft_new_token(TOKEN_HEREDOC, NULL));
		}
		(*line)++;
		return (ft_new_token(TOKEN_REDIR_IN, NULL));
	}
	else if (**line == '>')
	{
		if (*(*line + 1) == '>')
		{
			(*line) += 2;
			return (ft_new_token(TOKEN_APPEND, NULL));
		}
		(*line)++;
		return (ft_new_token(TOKEN_REDIR_OUT, NULL));
	}
	return (NULL);
}

t_token	*ft_read_word(char **line)
{
	char	*start;
	int		len;
	char	*word;

	start = *line;
	len = 0;

	while ((*line)[len] && (*line)[len] != ' ' && (*line)[len] != '\t' && !ft_is_operator((*line)[len]))
	{
		len++;
	}
	word = ft_strndup(start, len);
	if (!word)
		return (NULL);

	(*line) += len;
	return (ft_new_token(TOKEN_WORD, word));
}

t_token	*ft_lexer(char *input)
{
	t_token	*list;
	t_token	*new_token;

	list = NULL;
	while (*input)
	{
		ft_skip_spaces(&input);
		if (!*input)
			break;
		if (ft_is_operator(*input))
			new_token = ft_read_operator(&input);
		else
			new_token = ft_read_word(&input);
		ft_add_token(&list, new_token);
	}
	return (list);
}
