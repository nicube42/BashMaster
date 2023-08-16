/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:29:21 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 15:18:22 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	handle_child_errors(int pid)
{
	if (pid < 0)
		perror("fork");
}

void	close_fds(t_list *list)
{
	if (list->fd_in > 2)
		better_close(list->fd_in);
	if (list->fd_out > 2)
		better_close(list->fd_out);
}

void	reset_fds(void)
{
	better_dup2(STDIN_FILENO, 0);
	better_dup2(STDOUT_FILENO, 1);
	better_dup2(STDERR_FILENO, 2);
}

void	wait_and_handle_status(t_list *list, t_bash *sh, int pid)
{
	int	status;

	(void) list;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		sh->last_exit_status = 128 + sh->last_exit_status;
		kill(pid, SIGKILL);
	}
	else if (WIFEXITED(status))
		sh->last_exit_status = WEXITSTATUS(status);
}
