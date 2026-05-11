/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:31:28 by zimbo             #+#    #+#             */
/*   Updated: 2026/05/11 16:16:36 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_write_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (1);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static int	ft_fork_heredoc(char *delimiter)
{
	int		fd;
	pid_t	pid;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		ft_write_heredoc(fd, delimiter);
		close(fd);
		exit(0);
	}
	close(fd);
	return (pid);
}

static int	ft_wait_heredoc(pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		unlink(".heredoc_tmp");
		g_signal = SIGINT;
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(".heredoc_tmp");
		return (-1);
	}
	return (0);
}

static int	ft_create_heredoc_file(char *delimiter)
{
	pid_t	pid;
	int		fd;

	pid = ft_fork_heredoc(delimiter);
	if (pid < 0)
		return (-1);
	if (ft_wait_heredoc(pid) != 0)
		return (-1);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
		return (-1);
	unlink(".heredoc_tmp");
	return (fd);
}

int	ft_redir_heredoc(t_cmd *cmd, char *delimiter)
{
	int	fd;

	fd = ft_create_heredoc_file(delimiter);
	if (fd < 0)
		return (1);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (0);
}