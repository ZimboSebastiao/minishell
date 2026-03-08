/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:36:43 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 00:47:30 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_redirection(char **line, char current)
{
	if (current == '<')
	{
		if (*(*line + 1) == '<')
		{
			(*line) += 2;
			return (ft_new_token(TOKEN_HEREDOC, NULL));
		}
		(*line)++;
		return (ft_new_token(TOKEN_REDIR_IN, NULL));
	}
	else if (current == '>')
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

int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->redirs = NULL;
	new->next = NULL;
	return (new);
}

void	ft_add_cmd(t_cmd **list, t_cmd *new)
{
	t_cmd	*tmp;

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

t_redir	*ft_new_redir(t_redir_type type, char *file)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = file;
	new->next = NULL;
	return (new);
}
