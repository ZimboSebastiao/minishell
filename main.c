/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:07:06 by zimbo             #+#    #+#             */
/*   Updated: 2026/02/16 04:28:38 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_signal(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, SIG_IGN);

	// env = ft_init_env(envp);
	ft_shell_loop(env);
	// ft_free_env(env);

	return (EXIT_SUCCESS);
}