/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 23:39:16 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 00:47:40 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	current;

	current = **line;
	if (current == '|')
	{
		(*line)++;
		return (ft_new_token(TOKEN_PIPE, NULL));
	}
	else if (current == '<' || current == '>')
		return (handle_redirection(line, current));
	return (NULL);
}

t_token	*ft_read_word(char **line)
{
	char	*start;
	int		len;
	char	*word;

	start = *line;
	len = 0;
	while ((*line)[len] && (*line)[len] != ' '
		&& (*line)[len] != '\t' && !ft_is_operator((*line)[len]))
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
			break ;
		if (ft_is_operator(*input))
			new_token = ft_read_operator(&input);
		else
			new_token = ft_read_word(&input);
		ft_add_token(&list, new_token);
	}
	return (list);
}
