/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:53:26 by asouchet          #+#    #+#             */
/*   Updated: 2023/07/30 11:40:56 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	dup_case(t_shell *shell, t_fd *fd)
{
	if (shell->fd->input != 0)
		improved_dup2(shell->fd->input, STDIN_FILENO, shell);
	else
		improved_dup2(fd->tmp[0], STDIN_FILENO, shell);
	if (shell->error->error)
		exit(1);
	if (shell->fd->output != 1)
		improved_dup2(shell->fd->output, STDOUT_FILENO, shell);
	else
		improved_dup2(fd->fd[1], STDOUT_FILENO, shell);
	if (shell->error->error)
		exit(1);
}

void	last_dup_case(t_shell *shell, t_fd *fd)
{
	if (shell->fd->input != 0)
		improved_dup2(shell->fd->input, STDIN_FILENO, shell);
	else
		improved_dup2(fd->tmp[0], STDIN_FILENO, shell);
	if (shell->error->error)
		exit(1);
	improved_dup2(shell->fd->output, STDOUT_FILENO, shell);
	if (shell->error->error)
		exit(1);
}
