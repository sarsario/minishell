/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:02:54 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/11 16:08:00 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->next = 0;
	token->content = 0;
	token->prev = 0;
	token->status = 0;
	token->type = 0;
	return (token);
}

void	token_add_back(t_token **head, t_token *token)
{
	t_token	*temp;

	if (!*head)
	{
		*head = token;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = token;
	token->prev = temp;
}
