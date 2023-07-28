/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:44:16 by asouchet          #+#    #+#             */
/*   Updated: 2023/05/29 11:50:31 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(char *cmd)
{
	if (!cmd)
		return ;
	ft_putstr_fd("jean minishell crapaud: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(1);
}

void	parse_error(char *cmd)
{
	if (!cmd)
		return ;
	ft_putstr_fd("jean minishell crapaud: ", 2);
	perror(cmd);
	exit(1);
}

void	minishell_wait(int exec_len)
{
	int	i;

	i = 0;
	while (i < exec_len)
	{
		wait(&g_error_num);
		i++;
	}
}

// static void	wait_child(int last_pid)
// {
// 	int	current_pid;
// 	int	status;

// 	signals();
// 	current_pid = wait(&status);
// 	if (current_pid < 0 && errno != ECHILD)
// 		perror("WAIT ERROR");
// 	if (last_pid == current_pid && g_var.quit_child == NO)
// 	{
// 		if (WIFEXITED(status))
// 			g_var.last_er = WEXITSTATUS(status);
// 		if (WIFSIGNALED(status))
// 			g_var.last_er = WTERMSIG(status) + 128;
// 		if (WIFSTOPPED(status))
// 			g_var.last_er = WSTOPSIG(status);
// 		g_var.quit_child = YES;
// 	}
// }
