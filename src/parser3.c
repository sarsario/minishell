/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:27:23 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/30 09:36:39 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*parse_redir_out(t_token *token, t_cmd *cmd, int i, char **envp)
{
	char	*file;
	t_token	*first;
	t_cmd	*last;
	char	**tmp;

	if (i)
		i++;
	first = token;
	while (token->status == GENERAL && token->type == WHITE_SPACE)
		token = token->next;
	file = get_str(&token, envp);
	if (!file)
		exit_parse(first, cmd, file);
	last = cmd_last(cmd);
	tmp = add_str(last->redir_out, file);
	if (!(tmp))
		exit_parse(first, cmd, file);
	last->redir_out = tmp;
	last->order = add_int(last->order, 4);
	if (!(last->order))
		exit_parse(first, cmd, file);
	return (token);
}

static t_token	*parse_redir_in(t_token *token, t_cmd *cmd, int i, char **envp)
{
	char	*file;
	t_token	*first;
	t_cmd	*last;
	char	**tmp;

	if (i)
		i++;
	first = token;
	while (token->status == GENERAL && token->type == WHITE_SPACE)
		token = token->next;
	file = get_str(&token, envp);
	if (!file)
		exit_parse(first, cmd, file);
	last = cmd_last(cmd);
	tmp = add_str(last->redir_in, file);
	if (!(tmp))
		exit_parse(first, cmd, file);
	last->redir_in = tmp;
	last->order = add_int(last->order, 3);
	if (!(last->order))
		exit_parse(first, cmd, file);
	return (token);
}

static t_token	*parse_append(t_token *token, t_cmd *cmd, int i, char **envp)
{
	char	*file;
	t_token	*first;
	t_cmd	*last;
	char	**tmp;

	if (i)
		i++;
	first = token;
	while (token->status == GENERAL && token->type == WHITE_SPACE)
		token = token->next;
	file = get_str(&token, envp);
	if (!file)
		exit_parse(first, cmd, file);
	last = cmd_last(cmd);
	tmp = add_str(last->append, file);
	if (!(tmp))
		exit_parse(first, cmd, file);
	last->append = tmp;
	last->order = add_int(last->order, 2);
	if (!(last->order))
		exit_parse(first, cmd, file);
	return (token);
}

t_token	*parse_heredoc(t_token *token, t_cmd *cmd, int i)
{
	char	*eof;
	t_token	*first;
	t_cmd	*last;
	char	**tmp;

	if (i)
		i++;
	first = token;
	while (token->status == GENERAL && token->type == WHITE_SPACE)
		token = token->next;
	eof = get_str_heredoc(&token);
	if (!eof)
		exit_parse(first, cmd, eof);
	last = cmd_last(cmd);
	tmp = add_str(last->heredoc, eof);
	if (!(tmp))
		exit_parse(first, cmd, eof);
	last->heredoc = tmp;
	last->order = add_int(last->order, 1);
	if (!(last->order))
		exit_parse(first, cmd, eof);
	return (token);
}

t_token	*parse_redirection(t_token *token, t_cmd *cmd, int i, char **envp)
{
	if (!ft_strncmp(token->content, ">", ft_strlen(token->content)))
		token = parse_redir_out(token->next, cmd, i, envp);
	else if (!ft_strncmp(token->content, "<", ft_strlen(token->content)))
		token = parse_redir_in(token->next, cmd, i, envp);
	else if (!ft_strncmp(token->content, ">>", ft_strlen(token->content)))
		token = parse_append(token->next, cmd, i, envp);
	else if (!ft_strncmp(token->content, "<<", ft_strlen(token->content)))
		token = parse_heredoc(token->next, cmd, i);
	return (token);
}
