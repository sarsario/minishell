/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:33:47 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/30 08:40:04 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define FALSE 0
# define TRUE 1

// GLOBAL
extern int	g_global_status;

// TYPE
# define WORDS 1
# define WHITE_SPACE 2
# define ENV 3
# define SPE_CHAR 4

// STATUS
# define GENERAL 1
# define QUOTES 2
# define DQUOTES 3

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	char			*content;
	int				status;
	int				type;
}					t_token;

typedef struct s_cmd
{
	struct s_cmd		*next;
	struct sigaction	*sa;
	int					*order;
	char				**cmd;
	char				**heredoc;
	char				**append;
	char				**redir_in;
	char				**redir_out;
	char				*hdoc;
}						t_cmd;

typedef struct s_child
{
	t_cmd	*cmd;
	char	***envp;
	int		**pipefd;
	int		nb_cmd;
}			t_child;

typedef struct s_term
{
	struct termios	original;
	struct termios	modified;
}					t_term;

char	*free_join(char *s1, char *s2);
int		exit_w_msg(char *msg, int status);
void	exit_lexer(t_token *token, char *line_read, int status);
void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);
int		is_op_space(char c, int (*ints)[3]);
int		is_spe_char(t_token *token);
int		is_redirection(t_token *token);
int		is_path_start(t_token *token);
t_token	*next_token(t_token *token, char line_read);
void	set_token_type(t_token *token);
int		dollar(char *line_read, int i);
void	ft_quote(char line_read, int (*ints)[3], t_token *token);
void	ft_status(t_token *token, int quote, int dquote);
t_token	*init_token(void);
t_token	*free_token(t_token *token);
void	token_add_back(t_token **head, t_token *token);
t_token	*tokenizer(char *line_read);
void	free_cmd(t_cmd *cmd);
void	exit_parse(t_token *token, t_cmd *cmd, char *s);
void	ft_status(t_token *token, int quote, int dquote);
t_token	*count_pipe(t_token *token, int *nb_cmd);
char	*ft_realloc(char *str, int size);
void	free_2d(char **str);
char	**ft_realloc_2d(char **str, int size);
int		ft_strlen_2d(char **str);
char	*get_env_value(char *env, char **envp);
char	*partial_str(t_token *token, char **envp, char *s);
char	*get_str(t_token **token, char **envp);
char	*heredoc_flag(char *s, int q);
char	*get_str_heredoc(t_token **token);
t_token	*parse_path(t_token *token, t_cmd *cmd, char **envp);
t_token	*parse_redirection(t_token *token, t_cmd *cmd, int i, char **envp);
t_token	*parse_heredoc(t_token *token, t_cmd *cmd, int i);
t_cmd	*parser(t_token *token, char **envp);
int		is_new_arg(t_token *token);
int		is_general_quote(t_token *token);
t_token	*str_heredoc_help(t_token *token, int *q);
char	**add_str(char **arr, char *str);
char	**arraydup(char **arg);

//-------------------cmd_list.c------------------
t_cmd	*new_cmd(void);
t_cmd	*cmd_last(t_cmd *cmd);
void	cmd_add_back(t_cmd **cmd, t_cmd *new);
int		*realloc_int(int *arr, int size);
int		*add_int(int *arr, int n);
void	add_sigaction(t_cmd *cmds, struct sigaction *sa);

//------------------signal.c------------------
void	sigint_handler(int sig, siginfo_t *info, void *ucontext);
void	sig_setup(struct sigaction *sa);
void	reset_sig(struct sigaction *sa);
void	disable_echo(t_term *term);
void	enable_echo(t_term *term);

//------------------exec.c------------------
void	free_2d_int(int **str, int size);
int		count_cmds(t_cmd *cmd);
int		**init_pipes(int nb_cmd);
void	close_pipes(int **pipefd, int nb);
int		fork_exec(t_cmd *cmd, char ***envp, int **pipefd, int nb_cmd);
int		exec_cmds(t_cmd *cmd, char ***envp);
int		first_child(t_child *data, int i);
char	*get_path(char **envp, char *name);
int		direct_path(t_child *data);
char	*get_direct_path(t_child *data);
int		last_child(t_child *data, int i);
int		middle_child(t_child *data, int i);
int		exec_single(t_child *data);

//------------------fd_handler.c------------------
int		fd_in_handler(t_child *data);
int		fd_out_handler(t_child *data, char **r_out, char **r_app);

//------------------heredoc.c------------------
int		here_doc_handler(t_cmd *cmd, t_term *term, char **envp);
char	*ft_strjoin_free(char *s_to_free, char *s2);
char	*replace_env(char *str, char **envp);
int		ft_max(int x, int y);

//------------------exec_builtin.c------------------
int		is_builtin(char **strs);
int		exec_builtin(t_child *data);

//----------------buitin----------------------------
int		ft_cd(char **path, char ***envp);
int		ft_echo(char **args);
int		ft_env(char **cmd, char ***envp);
int		ft_export(char **args, char ***envp, int x_arg, int x_env);
int		ft_exit(char **arg);
int		ft_pwd(void);
int		ft_unset(char **args, char ***envp);

#endif