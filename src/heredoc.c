/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:33:03 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/29 15:39:53 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*heredoc_name(char *name)
{
	static int	count = 0;

	if (name)
	{
		unlink(name);
		free(name);
	}
	name = ft_strjoin(".heredoc", ft_itoa(count++));
	if (!name)
	{
		perror("[minishell]: heredoc");
		return (NULL);
	}
	return (name);
}

static int	write_heredoc(int fd, char *eof, t_term *term, char **envp)
{
	char	*line_read;
	int		eof_len;

	enable_echo(term);
	eof_len = ft_strlen(eof) - 1;
	line_read = readline("> ");
	while (line_read && ft_strncmp(line_read, eof, \
		ft_max(eof_len, ft_strlen(line_read))))
	{
		if (eof[eof_len] == 'G')
			line_read = replace_env(line_read, envp);
		else
			line_read = ft_strjoin_free(line_read, "\n");
		if (!line_read)
		{
			ft_putstr_fd("[minishell]: heredoc: error: malloc failed\n", 2);
			return (0);
		}
		ft_putstr_fd(line_read, fd);
		free(line_read);
		line_read = readline("> ");
	}
	if (line_read)
		free(line_read);
	return (1);
}

static int	fill_heredoc(char *eof, char *filename, t_term *term, char **envp)
{
	int		fd;

	if (!eof)
	{
		ft_putstr_fd("[minishell]: heredoc: error: no eof\n", 2);
		return (-1);
	}
	fd = open(filename, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
	{
		perror("[minishell]: heredoc");
		return (-1);
	}
	if (!write_heredoc(fd, eof, term, envp))
	{
		disable_echo(term);
		close(fd);
		return (-1);
	}
	disable_echo(term);
	close(fd);
	return (1);
}

static int	create_heredoc(t_cmd *cmd, t_term *term, char **envp)
{
	char	*filename;
	int		i;

	i = 0;
	filename = NULL;
	while (cmd->heredoc && cmd->heredoc[i])
	{
		filename = heredoc_name(filename);
		if (!filename)
			return (0);
		if (fill_heredoc(cmd->heredoc[i], filename, term, envp) == -1)
		{
			free(filename);
			return (0);
		}
		cmd->hdoc = filename;
		i++;
	}
	return (1);
}

int	here_doc_handler(t_cmd *cmd, t_term *term, char **envp)
{
	while (cmd)
	{
		if (!create_heredoc(cmd, term, envp))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
