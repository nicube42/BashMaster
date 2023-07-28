/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:23:10 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/06/09 09:56:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_inside_mid_fork(t_shell *shell, t_exec *exec, t_fd *fd, char *path)
{
	dup_case(shell, fd);
	_close(fd->tmp[1]);
	_close(fd->tmp[0]);
	_close(fd->fd[0]);
	_close(fd->fd[1]);
	if (!builtin_in_fork(shell, exec->cmd_args[0], exec))
		exit(0);
	path = ft_get_path(exec->cmd_args[0], shell);
	if (!path)
		cmd_not_found(exec->cmd_args[0]);
	if (execve(path, exec->cmd_args, ft_sett(shell->env)) == -1)
		parse_error(exec->cmd_args[0]);
}

void	minishell_fork(t_shell *shell, t_exec *exec, t_fd *fd)
{
	char	*path;
	int		pid;

	path = NULL;
	if (!builtin_out_fork(shell, exec->cmd_args[0], exec))
		return ;
	pid = improved_fork(shell);
	if (shell->error->error != 0)
		return ;
	if (pid == 0)
		ft_inside_mid_fork(shell, exec, fd, path);
	_close(fd->tmp[0]);
	_close(fd->tmp[1]);
	_close(shell->fd->input);
	shell->fd->input = 0;
	_close(shell->fd->output);
	shell->fd->output = 1;
}

void	multiple_cmd(t_shell *shell, t_exec *exec, t_fd *fd)
{
	if (exec->cmd_args == NULL)
		return ;
	if (fd->fd[1] != 1)
		fd->tmp[1] = fd->fd[1];
	if (fd->fd[0] != 0)
		fd->tmp[0] = fd->fd[0];
	improved_pipe(fd->fd, shell);
	minishell_fork(shell, exec, fd);
}

void	last_cmd_in_file(t_shell *shell, t_exec *exec, t_fd *fd)
{
	char	*path;
	int		pid;

	if (exec->cmd_args == NULL)
		return ;
	if (!builtin_out_fork(shell, exec->cmd_args[0], exec))
		return ;
	if (fd->fd[1] != 1)
		fd->tmp[1] = fd->fd[1];
	if (fd->fd[0] != 0)
		fd->tmp[0] = fd->fd[0];
	improved_pipe(fd->fd, shell);
	path = NULL;
	pid = improved_fork(shell);
	if (pid == 0)
		inside_last_fork(shell, exec, fd, path);
	_close(fd->tmp[0]);
	_close(fd->tmp[1]);
	_close(shell->fd->input);
	shell->fd->input = 0;
	_close(shell->fd->output);
	shell->fd->output = 1;
}

// Execute une commande
void	execution(t_shell *shell)
{
	t_exec	*tmp;
	t_fd	fd;
	t_file	file;
	t_error	error;
	int		cmd_count;

	tmp = shell->exec;
	declare_var(shell, &fd, &file, &error);
	cmd_count = cmd_nb(tmp);
	if (cmd_count == 1)
		one_cmd(shell, tmp, &fd);
	else
		middle_execution(shell, tmp, &fd);
	minishell_wait(cmd_count);
}
