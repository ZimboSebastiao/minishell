/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:12:09 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/12 20:03:31 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_pipe_fds(int pipe_fd[2], int prev_pipe)
{
	if (prev_pipe != -1)
		close(prev_pipe);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

static int	ft_execute_command(t_cmd *cmd, t_shell *sh, int pipe_fd[2], int prev)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_setup_child_signals();
		if (prev != -1)
		{
			dup2(prev, STDIN_FILENO);
			close(prev);
		}
		if (cmd->next)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		ft_child_exec(cmd, sh);
	}
	if (prev != -1)
		close(prev);
	if (cmd->next)
		close(pipe_fd[1]);
	return (pid);
}

static int	ft_wait_for_children(pid_t last_pid, t_shell *sh)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				sh->exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sh->exit = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					write(2, "Quit (core dumped)\n", 20);
			}
		}
		pid = waitpid(-1, &status, 0);
	}
	return (sh->exit);
}

int	ft_executor(t_cmd *list, t_shell *sh)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_pipe;
	pid_t	last_pid;

	prev_pipe = -1;
	cmd = list;
	while (cmd)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (cmd->next && pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
		if (!cmd->next && ft_is_builtin(cmd->args[0]) && prev_pipe == -1)
			return (ft_run_builtin(cmd, sh));
		last_pid = ft_execute_command(cmd, sh, pipe_fd, prev_pipe);
		sh->last_pid = last_pid;
		prev_pipe = pipe_fd[0];
		cmd = cmd->next;
	}
	ft_close_pipe_fds(pipe_fd, prev_pipe);
	return (ft_wait_for_children(last_pid, sh));
}
