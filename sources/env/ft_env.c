/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:58:20 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/12 20:36:07 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_env_value(t_env *current, char *value)
{
	if (current->value)
		free(current->value);
	if (value)
		current->value = ft_strdup(value);
	else
		current->value = NULL;
}

void	ft_set_env(char *key, char *value, t_env **env)
{
	t_env	*current;
	t_env	*new;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			ft_update_env_value(current, value);
			return ;
		}
		current = current->next;
	}
	if (value)
		new = ft_new_env_node(ft_strdup(key), ft_strdup(value));
	else
		new = ft_new_env_node(ft_strdup(key), NULL);
	ft_add_env_node(env, new);
}

void	ft_unset_env(char *key, t_env **env)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_count_env_vars(t_env *env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*ft_join_key_value(t_env *env)
{
	char	*joined;
	char	*temp;

	temp = ft_strjoin(env->key, "=");
	joined = ft_strjoin(temp, env->value);
	free(temp);
	return (joined);
}
