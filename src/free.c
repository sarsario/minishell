/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:43:44 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/28 08:38:18 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*free_token(t_token *token)
{
	t_token	*temp;

	while (token && token->prev)
		token = token->prev;
	while (token && token->next)
	{
		temp = token->next;
		free(token->content);
		free(token);
		token = temp;
	}
	if (token)
	{
		free(token->content);
		free(token);
	}
	return (NULL);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		free_2d(tmp->append);
		free_2d(tmp->cmd);
		free_2d(tmp->redir_in);
		free_2d(tmp->redir_out);
		free_2d(tmp->heredoc);
		if (tmp->order)
			free(tmp->order);
		if (tmp->hdoc)
		{
			unlink(tmp->hdoc);
			free(tmp->hdoc);
		}
		tmp = tmp->next;
		free(cmd);
		cmd = tmp;
	}
}
