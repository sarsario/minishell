/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 06:55:08 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/30 09:31:27 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_w_msg(char *msg, int status)
{
	g_global_status = status;
	ft_putstr_fd(msg, 2);
	rl_clear_history();
	exit (g_global_status);
}

void	exit_parse(t_token *token, t_cmd *cmd, char *s)
{
	g_global_status = 1;
	if (s)
		free(s);
	free_token(token);
	free_cmd(cmd);
	rl_clear_history();
	ft_putstr_fd("Error: parsing error\n", 2);
	exit(g_global_status);
}

void	exit_lexer(t_token *token, char *line_read, int status)
{
	g_global_status = status;
	free(line_read);
	free_token(token);
	rl_clear_history();
	exit(g_global_status);
}
