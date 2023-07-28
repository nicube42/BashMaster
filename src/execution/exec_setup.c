/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:51:59 by asouchet          #+#    #+#             */
/*   Updated: 2023/06/08 08:45:33 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	declare_var(t_shell *shell, t_fd *fd, t_file *file, t_error *error)
{
	file->input = 0;
	file->output = 1;
	file->fd[1] = 1;
	file->fd[0] = 0;
	error->error = 0;
	error->global = 0;
	fd->fd[0] = 0;
	fd->fd[1] = 1;
	fd->tmp[0] = 0;
	fd->tmp[1] = 1;
	shell->error = error;
	shell->fd = file;
}

void	one_cmd(t_shell *shell, t_exec *tmp, t_fd *fd)
{
	if (is_redir(tmp))
		t_redir_exec(shell, tmp);
	if (shell->error->error != 0)
		return ;
	if (tmp->cmd_args)
		last_cmd_in_file(shell, tmp, fd);
}

void	middle_execution(t_shell *shell, t_exec *tmp, t_fd *fd)
{
	int	exec_len;
	int	i;

	i = 0;
	exec_len = ft_lst_len_exec(tmp);
	while (i < exec_len - 1)
	{
		if (shell->error->error != 0)
			return ;
		if (is_redir(tmp))
			t_redir_exec(shell, tmp);
		if (shell->error->error != 0)
			return ;
		if (tmp->cmd_args)
			multiple_cmd(shell, tmp, fd);
		shell->error->error = 0;
		tmp = tmp->next;
		i++;
	}
	if (is_redir(tmp))
		t_redir_exec(shell, tmp);
	if (shell->error->error != 0)
		return ;
	last_cmd_in_file(shell, tmp, fd);
}

int	ft_env_len(t_variable *lst)
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

char	**ft_sett(t_variable *env)
{
	t_variable	*tmp;
	char		**ret;
	int			i;

	i = 0;
	tmp = env;
	ret = malloc(sizeof(char *) * (ft_env_len(tmp) + 1));
	if (!ret)
		exit(1);
	while (ret[i] && tmp)
	{
		ret[i] = join_env(tmp->name, tmp->value);
		i++;
		tmp = tmp->next;
	}
	ret[i] = "\0";
	return (ret);
}
