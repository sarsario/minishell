/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:32:23 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/29 15:09:15 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->sa = NULL;
	cmd->order = NULL;
	cmd->cmd = NULL;
	cmd->heredoc = NULL;
	cmd->append = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->hdoc = NULL;
	return (cmd);
}

t_cmd	*cmd_last(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*temp;

	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_token	*str_heredoc_help(t_token *token, int *q)
{
	token = token->next;
	if (!*q)
		*q = !*q;
	return (token);
}

void	add_sigaction(t_cmd *cmds, struct sigaction *sa)
{
	t_cmd	*temp;

	temp = cmds;
	while (temp)
	{
		temp->sa = sa;
		temp = temp->next;
	}
}
