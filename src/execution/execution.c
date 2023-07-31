/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:45:13 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/31 10:15:16 by ndiamant         ###   ########.fr       */
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

void	execute_cmd(t_list *list, t_bash *sh)
{
	int		i;
	char	**args;
	char	*cmd;
	pid_t	pid;

	if (!list || !list->value)
		return ;
	cmd = add_path(sh, list);
	if (list->fd_in != -1)
		dup2(list->fd_in, STDIN_FILENO);
	if (list->fd_out != -1)
		dup2(list->fd_out, STDOUT_FILENO);
	i = 0;
	while (list->arguments && list->arguments[i])
		i++;
	args = (char **)malloc((i + 2) * sizeof(char *));
	args[0] = list->value;
	i = -1;
	while (list->arguments && list->arguments[++i])
		args[i + 1] = list->arguments[i];
	args[i + 1] = 0;
	pid = fork();
	if (pid == 0)
	{
		if (list->fd_in != -1)
			dup2(list->fd_in, STDIN_FILENO);
		if (list->fd_out != -1)
			dup2(list->fd_out, STDOUT_FILENO);
		execve(cmd, args, 0);
		perror("execve");
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, 0, 0);
	}
	free(args);
	free(cmd);
}


void	execution(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	while (list)
	{
		if (list->id == CMD_TOK)
			execute_cmd(list, sh);
		else if (list->id == PIPE_TOK)
		{

		}
		else if (list->id == BUILTIN_TOK)
		{

		}
		else
		{

		}
		list = list->next;
	}
}