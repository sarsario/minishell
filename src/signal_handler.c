/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:23:56 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/29 15:06:34 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_global_status = 1;
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_setup(struct sigaction *sa)
{
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = sigint_handler;
	if (sigaction(SIGINT, sa, NULL) == -1)
		exit(1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
}

void	reset_sig(struct sigaction *sa)
{
	sa->sa_flags = SA_SIGINFO;
	sa->sa_handler = SIG_DFL;
	if (sigaction(SIGINT, sa, NULL) == -1)
		exit(1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(1);
}

void	disable_echo(t_term *term)
{
	tcgetattr(0, &term->original);
	term->modified = term->original;
	term->modified.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term->modified);
}

void	enable_echo(t_term *term)
{
	tcsetattr(0, TCSANOW, &term->original);
}
