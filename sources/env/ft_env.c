/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 02:04:35 by zimbo             #+#    #+#             */
/*   Updated: 2026/02/25 23:03:32 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_env	ft_new_env_node(char *key, char *value)
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

static void	ft_add_env_node(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void	ft_parse_env_var(char *env_var, char **key, char **value)
{
	char *equal_sign;

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

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			free(tmp->key)
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
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

void	ft_set_env(char *key, char *value, t_env **env)
{
	t_env	*current;
	t_env	*new;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			free(key);
			return ;
		}
		current = current->next;
	}
	new = ft_new_env_node(ft_strdup(key), ft_strdup(value));
	ft_add_env_node(env, new);
}

void ft_unset_env(char *key, t_env **env)
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

char **ft_env_to_array(t_env *env)
{
	char	**array;
	char	*joined;
	t_env	*tmp;
	int		count;
	int		i;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		joined = ft_strjoin(env->key, "=");
		array[i] = ft_strjoin(joined, env->value);
		free(joined);
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}