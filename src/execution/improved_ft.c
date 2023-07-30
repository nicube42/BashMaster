/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   improved_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:42:35 by asouchet          #+#    #+#             */
/*   Updated: 2023/07/30 11:40:31 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	improved_dup2(int fildes, int fildes2, t_shell *shell)
{
	int	error;

	error = dup2(fildes, fildes2);
	if (error == -1)
	{
		perror("dup2 error:");
		shell->error->error = error;
	}
	return (error);
}

int	improved_pipe(int fd[2], t_shell *shell)
{
	int	error;

	error = pipe(fd);
	if (error == -1)
	{
		perror("pipe error:");
		shell->error->error = error;
	}
	return (error);
}

pid_t	improved_fork(t_shell *shell)
{
	pid_t	error;

	error = fork();
	if (error == -1)
	{
		perror("fork error:");
		shell->error->error = error;
	}
	return (error);
}

void	_close(int fd)
{
	if (fd != 0 && fd != 1 && fd != 2)
		close(fd);
}

int	is_redir(t_exec *exec)
{
	t_exec	*tmp;

	tmp = exec;
	if (exec == NULL)
		return (0);
	if (tmp->redir == NULL)
		return (0);
	return (1);
}
