/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 03:20:11 by zimbo             #+#    #+#             */
/*   Updated: 2026/02/16 04:24:51 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_redir_type	ft_token_to_redir(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_IN);
}

t_cmd	*ft_parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current_cmd;
	t_token	*current;
	int		arg_count;
	char	**args;
	int		i;

	cmds = NULL;
	current = tokens;
	while (current)
	{
		current_cmd = ft_new_cmd();
		if (!current_cmd)
			return (NULL);
		arg_count =0;
		t_token *temp = current;
		while (temp && temp->type != TOKEN_PIPE)
		{
			if (temp->type == TOKEN_WORD)
				arg_count++;
			temp = temp->next;
		}
		args = malloc(sizeof(char *) * (arg_count + 1));
		if (!args)
			return (NULL);
		i = 0;
		while (current && current->type != TOKEN_PIPE)
		{
			if (current->type == TOKEN_WORD)
			{
				args[i] = ft_strdup(current->value);
				i++;
			}
			else if (current->type >= TOKEN_REDIR_IN)
			{
				if (current->next && current->next->type == TOKEN_WORD)
				{
					t_redir *redir = ft_new_redir(
						ft_token_to_redir(current->type),
						ft_strdup(current->next->value)
					);
					ft_add_redir(&current_cmd->redirs, redir);
					current = current->next;
				}
			}
			current = current->next;
		}
		args[i] = NULL;
		current_cmd->args = args;
		ft_add_cmd(&cmds, current_cmd);
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
	return (cmds);
}

void	ft_free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
			{
				free(tmp->args[i]);
				i++;
			}
			free(tmp->args);
		}
		if (tmp->redirs)
			ft_free_redirs(tmp->redirs);
		free(tmp);
	}
}

void	ft_free_redirs(t_redir *redirs)
{
	t_redir	*tmp;
	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}