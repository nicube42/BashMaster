/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:02:03 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/08 11:27:24 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

void	disable_ctrl_c_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	child_sigint_handler(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

void	sigint_handler(int sig)
{
	(void) sig;
	if (g_global.in_heredoc == 1)
		g_global.in_heredoc = 0;
	if (g_global.in_cmd)
	{
		g_global.in_cmd = 0;
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (g_global.in_heredoc == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int sig)
{
	(void) sig;
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
