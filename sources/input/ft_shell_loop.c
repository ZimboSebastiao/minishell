/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:52:07 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 02:55:07 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->value);
		free(tmp);
	}
}

static void	ft_process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = ft_lexer(line);
	if (!tokens)
		return ;
	cmds = ft_parser(tokens);
	if (cmds)
	{
		shell->cmds = cmds;
		ft_expand_variables(cmds, shell->env_list, shell->exit);
		shell->exit = ft_executor(cmds, shell);
		ft_free_cmds(cmds);
	}
	ft_free_tokens(tokens);
}

void	ft_shell_loop(t_env *env)
{
	char	*line;
	t_shell	shell;

	shell.env_list = env;
	shell.exit = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ft_process_line(line, &shell);
		free(line);
	}
}
