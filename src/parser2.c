/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:53:56 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/30 09:32:53 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char *env, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_strncmp(env, "$?", ft_strlen(env)))
		return (ft_itoa(g_global_status));
	env++;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, ft_strlen(env)) == 0)
		{
			tmp = ft_strdup(envp[i] + ft_strlen(env) + 1);
			if (!tmp)
				return (NULL);
			return (tmp);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*partial_str(t_token *token, char **envp, char *s)
{
	char	*tmp;

	if (token->status != QUOTES && token->type == ENV)
		tmp = get_env_value(token->content, envp);
	else
		tmp = ft_strdup(token->content);
	if (!tmp)
	{
		if (s)
			free(s);
		return (NULL);
	}
	return (tmp);
}

int	is_general_quote(t_token *token)
{
	if (token->status == GENERAL && token->type == SPE_CHAR && \
		(!ft_strncmp(token->content, "\"", ft_strlen(token->content)) \
		|| !ft_strncmp(token->content, "\'", ft_strlen(token->content))))
		return (TRUE);
	return (FALSE);
}

char	*get_str(t_token **token, char **envp)
{
	char	*s;
	char	*tmp;

	s = ft_strdup("");
	if (!s)
		return (NULL);
	while (*token && !is_new_arg(*token))
	{
		if (is_general_quote(*token))
			*token = (*token)->next;
		else
		{
			tmp = partial_str(*token, envp, s);
			if (!tmp)
				return (NULL);
			s = free_join(s, tmp);
			if (!s)
				return (NULL);
			*token = (*token)->next;
		}
	}
	return (s);
}

t_token	*parse_path(t_token *token, t_cmd *cmd, char **envp)
{
	char	*cmd_arg;
	t_token	*first;
	t_cmd	*last;
	char	**tmp;

	first = token;
	cmd_arg = get_str(&token, envp);
	if (!cmd_arg)
		exit_parse(first, cmd, cmd_arg);
	last = cmd_last(cmd);
	tmp = add_str(last->cmd, cmd_arg);
	if (!tmp)
		exit_parse(first, cmd, cmd_arg);
	last->cmd = tmp;
	last->order = add_int(last->order, 0);
	if (!last->order)
		exit_parse(first, cmd, cmd_arg);
	return (token);
}
