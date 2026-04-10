/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:29:07 by zimbo             #+#    #+#             */
/*   Updated: 2026/04/09 21:29:12 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expand_heredoc_line(char *line, t_shell *shell)
{
	char	*expanded;

	if (!line)
		return (NULL);
	if (ft_strchr(line, '$'))
		expanded = ft_expand_str(line, shell->env_list, shell->exit);
	else
		expanded = ft_strdup(line);
	return (expanded);
}

static int	ft_process_line(char *line, int fd, char *delimiter, t_shell *shell)
{
	char	*expanded_line;

	if (ft_strcmp(line, delimiter) == 0)
		return (1);
	expanded_line = ft_expand_heredoc_line(line, shell);
	if (expanded_line)
	{
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		free(expanded_line);
	}
	return (0);
}

static int	ft_write_heredoc_expand(int fd, char *delimiter, t_shell *shell)
{
	char	*line;
	int		ret;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		ret = ft_process_line(line, fd, delimiter, shell);
		free(line);
		if (ret == 1)
			break ;
	}
	return (0);
}

int	ft_redir_heredoc_with_expand(t_cmd *cmd, char *delimiter, t_shell *shell)
{
	int	fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	ft_write_heredoc_expand(fd, delimiter, shell);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		unlink(".heredoc_tmp");
		return (1);
	}
	unlink(".heredoc_tmp");
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in > 2)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (0);
}
