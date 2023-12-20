/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:48:29 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/29 15:38:44 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_global_status = 0;

static int	str_is_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	unclosed(char *str)
{
	int	i;
	int	is_single;
	int	is_double;

	i = 0;
	is_single = 0;
	is_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !is_double)
			is_single = !is_single;
		if (str[i] == '\"' && !is_single)
			is_double = !is_double;
		i++;
	}
	if (is_single || is_double)
	{
		ft_putstr_fd("[minishell]: unclosed quotes\n", 2);
		g_global_status = 1;
		return (1);
	}
	return (0);
}

static t_cmd	*get_cmd(t_token *token, char **envp)
{
	t_cmd	*cmd;

	if (!token)
	{
		ft_putstr_fd("[minishell]: allocation error\n", 2);
		g_global_status = 1;
		return (NULL);
	}
	cmd = parser(token, envp);
	free_token(token);
	if (!cmd || !cmd->order)
	{
		if (cmd)
			free_cmd(cmd);
		ft_putstr_fd("[minishell]: allocation error\n", 2);
		g_global_status = 1;
		return (NULL);
	}
	if (cmd->order[1] == -1)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

static t_cmd	*read_prompt(char **envp)
{
	char	*line_read;
	t_token	*token;

	line_read = readline("[minishell] ");
	if (!line_read)
		exit(1);
	if (str_is_spaces(line_read) || unclosed(line_read))
	{
		free(line_read);
		g_global_status = 0;
		return (NULL);
	}
	add_history(line_read);
	token = tokenizer(line_read);
	free(line_read);
	return (get_cmd(token, envp));
}

int	main(int argc, char **argv, char **envp)
{
	t_term				term;
	struct sigaction	sa;
	t_cmd				*cmds;

	envp = arraydup(envp);
	if (argc != 1 || argv[1])
		return (exit_w_msg("Error: too many arguments\n", 1));
	disable_echo(&term);
	sig_setup(&sa);
	while (1)
	{
		cmds = read_prompt(envp);
		if (cmds)
		{
			add_sigaction(cmds, &sa);
			if (!here_doc_handler(cmds, &term, envp))
				g_global_status = 1;
			else
				g_global_status = exec_cmds(cmds, &envp);
			free_cmd(cmds);
		}
	}
	rl_clear_history();
	enable_echo(&term);
	return (g_global_status);
}
