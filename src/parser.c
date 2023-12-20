/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:00:15 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/29 14:37:31 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_str_heredoc(t_token **token)
{
	char	*s;
	char	*temp;
	int		q;

	q = 0;
	s = ft_strdup("");
	if (!s)
		return (NULL);
	while (*token && !is_new_arg(*token))
	{
		if (is_general_quote(*token))
			*token = str_heredoc_help(*token, &q);
		else
		{
			temp = ft_strdup((*token)->content);
			if (!temp)
				return (NULL);
			s = free_join(s, temp);
			if (!s)
				return (NULL);
			*token = (*token)->next;
		}
	}
	s = heredoc_flag(s, q);
	return (s);
}

int	is_redirection(t_token *token)
{
	if (token->status == GENERAL && \
		(!ft_strncmp(token->content, "<", ft_strlen(token->content)) || \
		!ft_strncmp(token->content, ">", ft_strlen(token->content)) || \
		!ft_strncmp(token->content, "<<", ft_strlen(token->content)) || \
		!ft_strncmp(token->content, ">>", ft_strlen(token->content))))
		return (TRUE);
	else
		return (FALSE);
}

int	is_path_start(t_token *token)
{
	if ((token->status == GENERAL && \
		(token->type == WORDS || token->type == ENV)) || \
		(token->type == SPE_CHAR && \
		(!ft_strncmp(token->content, "\"", ft_strlen(token->content)) \
		|| !ft_strncmp(token->content, "\'", ft_strlen(token->content)))))
		return (TRUE);
	return (FALSE);
}

t_token	*parser_loop(t_token *tmp, t_cmd *cmd, int *i, char **envp)
{
	t_token	*token;
	t_cmd	*next_cmd;

	if (is_path_start(tmp))
		token = parse_path(tmp, cmd, envp);
	else if (is_redirection(tmp))
		token = parse_redirection(tmp, cmd, *i, envp);
	else if (tmp->status == GENERAL && tmp->type == SPE_CHAR && \
		!ft_strncmp(tmp->content, "|", ft_strlen(tmp->content)))
	{
		next_cmd = new_cmd();
		cmd_add_back(&cmd, next_cmd);
		token = tmp->next;
		(*i)++;
	}
	else
		token = tmp->next;
	return (token);
}

t_cmd	*parser(t_token *token, char **envp)
{
	int		nb_cmds;
	int		i;
	t_cmd	*cmd;
	t_token	*tmp;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	nb_cmds = 1;
	tmp = count_pipe(token, &nb_cmds);
	if (nb_cmds == -1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tmp->content, 2);
		ft_putstr_fd("'\n", 2);
		g_global_status = 1;
		cmd->order = add_int(cmd->order, -1);
		return (cmd);
	}
	i = 0;
	tmp = token;
	while (i < nb_cmds && tmp)
		tmp = parser_loop(tmp, cmd, &i, envp);
	return (cmd);
}
