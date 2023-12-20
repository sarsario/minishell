/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:24:54 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/27 11:37:58 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_free(char *s_to_free, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s_to_free && !s2)
		return (NULL);
	if (!s_to_free)
		return (ft_strdup(s2));
	if (!s2)
		return (s_to_free);
	new_str = ft_calloc(ft_strlen(s_to_free) + ft_strlen(s2) + 1, sizeof(char));
	if (!new_str)
		return (free(s_to_free), NULL);
	i = 0;
	j = 0;
	while (s_to_free[i])
		new_str[j++] = s_to_free[i++];
	free(s_to_free);
	i = 0;
	while (s2[i])
		new_str[j++] = s2[i++];
	return (new_str);
}

static int	found_env(char *str, int *start_env, int *end_env)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
			{
				*start_env = i;
				*end_env = i + 1;
				return (1);
			}
			else if (str[i + 1] && \
				(ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			{
				*start_env = i++;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				*end_env = i - 1;
				return (1);
			}
		}
	}
	return (0);
}

static char	*get_env_var(char *str, int start_env, int end_env, char **envp)
{
	char	*env_var;
	char	*tmp;

	env_var = ft_substr(str, start_env, end_env - start_env + 1);
	if (!env_var)
		return (NULL);
	tmp = get_env_value(env_var, envp);
	free(env_var);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*replace_env_var(char *str, char *env_var, int start_env, \
	int end_env)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = ft_calloc(ft_strlen(str) + ft_strlen(env_var) + 1, sizeof(char));
	if (!new_str)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (i < start_env)
		new_str[j++] = str[i++];
	i = 0;
	while (env_var[i])
		new_str[j++] = env_var[i++];
	i = end_env + 1;
	while (str[i])
		new_str[j++] = str[i++];
	free(str);
	return (new_str);
}

char	*replace_env(char *str, char **envp)
{
	int		start_env;
	int		end_env;
	char	*env_var;

	if (!str)
		return (NULL);
	str = ft_strjoin_free(str, "\n");
	if (!str)
		return (NULL);
	start_env = 0;
	end_env = 0;
	while (found_env(str, &start_env, &end_env))
	{
		env_var = get_env_var(str, start_env, end_env, envp);
		if (!env_var)
			return (free(str), NULL);
		str = replace_env_var(str, env_var, start_env, end_env);
		if (!str)
			return (NULL);
		free(env_var);
	}
	return (str);
}
