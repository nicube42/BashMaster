/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:45:13 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/31 20:49:00 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

char	*add_path(t_bash *sh, t_list *list)
{
	char	*cmd;
	int		i;

	i = -1;
	while (sh->splitted_path[++i])
	{
		cmd = ft_strjoin(sh->splitted_path[i], list->value);
		if (access(cmd, F_OK) == 0)
			break ;
		free(cmd);
		cmd = 0;
	}
	return (cmd);
}

void	prepare_cmd(t_bash *sh, t_list *list, char **cmd, char ***args)
{
	int	i;

	*cmd = add_path(sh, list);
	i = 0;
	while (list->arguments && list->arguments[i])
		i++;
	*args = (char **)malloc((i + 2) * sizeof(char *));
	(*args)[0] = list->value;
	i = -1;
	while (list->arguments && list->arguments[++i])
		(*args)[i + 1] = list->arguments[i];
	(*args)[i + 1] = 0;
}

void	pipe_and_execute(t_list *list, t_bash *sh, char *cmd, char **args)
{
	if (list->fd_in != -1 && list->fd_in != STDIN_FILENO)
	{
		dup2(list->fd_in, STDIN_FILENO);
		close(list->fd_in);
	}
	if (list->fd_out != STDOUT_FILENO && list->fd_out > 1)
	{
		dup2(list->fd_out, STDOUT_FILENO);
		close(list->fd_out);
	}
	if (list->id == CMD_TOK)
	{
		execve(cmd, args, 0);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		execute_buildin(list, sh);
}

void	execute_cmd(t_list *list, t_bash *sh)
{
	int		i;
	char	**args;
	char	*cmd;
	pid_t	pid;

	if (!list || !list->value)
		return ;
	prepare_cmd(sh, list, &cmd, &args);
	pid = fork();
	if (pid == 0)
	{
		pipe_and_execute(list, sh, cmd, args);
		exit(0);
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		if (list->fd_in != -1 && list->fd_in != STDIN_FILENO)
			close(list->fd_in);
		if (list->fd_out != STDOUT_FILENO && list->fd_out > 1)
			close(list->fd_out);
		waitpid(pid, 0, 0);
	}
	free(args);
	free(cmd);
}

void	execution(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	set_fd(sh);
	while (list)
	{
		if (list->id == CMD_TOK || list->id == BUILTIN_TOK)
			execute_cmd(list, sh);
		list = list->next;
	}
}
