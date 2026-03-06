/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:45:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:50:37 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
		exit(131);
	}
}

void	setup_child_signals(void)
{
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child);
}

void	handle_signal_interactive(int sig)
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

void	setup_interactive_signals(void)
{
	signal(SIGINT, handle_signal_interactive);
	signal(SIGQUIT, SIG_IGN);
}
