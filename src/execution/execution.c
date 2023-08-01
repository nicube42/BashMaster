/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:45:13 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/01 16:12:36 by ndiamant         ###   ########.fr       */
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
		better_dup2(list->fd_in, STDIN_FILENO);
		better_close(list->fd_in);
	}
	if (list->fd_out != STDOUT_FILENO && list->fd_out > 1)
	{
		better_dup2(list->fd_out, STDOUT_FILENO);
		better_close(list->fd_out);
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
	int		heredoc_fd;

	heredoc_fd = -1;
	prepare_cmd(sh, list, &cmd, &args);
	if (list->next)
		if (list->next->id == HERE_DOC_TOKEN)
			set_here_doc_fd(list->next, &heredoc_fd, sh);
	pid = fork();
	if (pid == 0)
	{
		if (heredoc_fd != -1)
		{
			better_dup2(heredoc_fd, STDIN_FILENO);
			better_close(heredoc_fd);
		}
		pipe_and_execute(list, sh, cmd, args);
		exit(0);
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		if (list->fd_in != -1 && list->fd_in != STDIN_FILENO)
			better_close(list->fd_in);
		if (list->fd_out != STDOUT_FILENO && list->fd_out > 1)
			better_close(list->fd_out);
		waitpid(pid, 0, 0);
	}
	free(args);
	free(cmd);
	better_dup2(STDIN_FILENO, 0);
    better_dup2(STDOUT_FILENO, 1);
    better_dup2(STDERR_FILENO, 2);
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
