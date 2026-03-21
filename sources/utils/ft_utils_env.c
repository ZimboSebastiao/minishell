/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:02:05 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:05:02 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_add_env_node(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_parse_env_var(char *env_var, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		*key = ft_strndup(env_var, equal_sign - env_var);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(env_var);
		*value = ft_strdup("");
	}
}

t_env	*ft_init_env(char **envp)
{
	t_env	*env;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		ft_parse_env_var(envp[i], &key, &value);
		ft_add_env_node(&env, ft_new_env_node(key, value));
		i++;
	}
	return (env);
}

char	*ft_get_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
