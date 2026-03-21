/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:15:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:49:37 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

static void	ft_free_heredoc_info(t_heredoc_info *info)
{
	if (info)
	{
		if (info->delimiter)
			free(info->delimiter);
		free(info);
	}
}

int	ft_handle(t_cmd *cmd, char *delimiter_token, t_shell *shell)
{
	t_heredoc_info	*info;
	int				result;

	info = ft_parse_heredoc_delimiter(delimiter_token);
	if (!info)
		return (1);
	if (info->expand)
		result = ft_redir_heredoc_with_expand(cmd, info->delimiter, shell);
	else
		result = ft_redir_heredoc_noexpand(cmd, info->delimiter);
	ft_free_heredoc_info(info);
	return (result);
}
