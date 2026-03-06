/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:52:07 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:21:22 by zimbo            ###   ########.fr       */
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

static void	process_line(char *line, t_shell *shell)
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
		ft_expand_variables(cmds, shell->env_list, shell->exit_status);
		shell->exit_status = executor(cmds, shell);
		ft_free_cmds(cmds);
	}
	ft_free_tokens(tokens);
}

void	ft_shell_loop(t_env *env)
{
	char	*line;
	t_shell	shell;

	shell.env_list = env;
	shell.exit_status = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		process_line(line, &shell);
		free(line);
	}
}
