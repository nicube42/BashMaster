/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:45:22 by asouchet          #+#    #+#             */
/*   Updated: 2023/07/27 14:53:22 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_nb(t_exec *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int	ft_lst_len_exec(t_exec *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int	ft_path_check(char *cmd, t_variable **tmp)
{
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (1);
	while (*tmp && ft_strncmp((*tmp)->name, "PATH", 5))
		*tmp = (*tmp)->next;
	if (*tmp == NULL)
		return (1);
	return (0);
}

char	*ft_get_path(char *cmd, t_shell *shell)
{
	int			j;
	t_variable	*tmp;
	char		**splited_path;

	j = 0;
	tmp = shell->env;
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK | R_OK | F_OK) == 0)
		return (cmd);
	if (ft_path_check(cmd, &tmp))
		return (cmd);
	if (tmp)
		splited_path = ft_split(tmp->value, ':');
	else
		splited_path = NULL;
	while (splited_path[j])
	{
		splited_path[j] = ft_strjoin(splited_path[j], "/");
		splited_path[j] = ft_strjoin(splited_path[j], &cmd[0]);
		if (access(splited_path[j], X_OK | R_OK | F_OK) == 0)
			break ;
		j++;
	}
	return (splited_path[j]);
}

void	inside_last_fork(t_shell *shell, t_exec *exec, t_fd *fd, char *path)
{
	last_dup_case(shell, fd);
	_close(fd->fd[0]);
	_close(fd->tmp[1]);
	_close(fd->fd[1]);
	_close(shell->fd->input);
	_close(shell->fd->output);
	if (!builtin_in_fork(shell, exec->cmd_args[0], exec))
		exit(0);
	path = ft_get_path(exec->cmd_args[0], shell);
	if (!path)
		cmd_not_found(exec->cmd_args[0]);
	if (execve(path, exec->cmd_args, ft_sett(shell->env)) == -1)
		parse_error(exec->cmd_args[0]);
}
