/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:45:13 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/03 13:35:51 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

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
		if (list->next->id != HERE_DOC_TOKEN)
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

void	child_process(t_list *list, t_bash *sh, char *cmd, char **args)
{
	pipe_and_execute(list, sh, cmd, args);
	exit(0);
}

void	execute_cmd(t_list *list, t_bash *sh)
{
	char	**args;
	char	*cmd;
	pid_t	pid;

	prepare_cmd(sh, list, &cmd, &args);
	pid = fork();
	if (pid == 0)
		child_process(list, sh, cmd, args);
	else if (pid < 0)
		perror("fork");
	else
	{
		if (list->fd_in != -1 && list->fd_in != STDIN_FILENO)
			better_close(list->fd_in);
		if (list->fd_out != STDOUT_FILENO && list->fd_out > 1
			&& list->next->id != HERE_DOC_TOKEN)
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
	int		tmp_fd;
	char	*line;

	list = sh->first;
	set_fd(sh);
	while (list)
	{
		if (list->id == CMD_TOK || list->id == BUILTIN_TOK)
			execute_cmd(list, sh);
		if (list->id == HERE_DOC_TOKEN && list->prev)
		{
			line = copy_fd_to_str(sh->tmp_fd);
			better_close(sh->tmp_fd);
			better_unlink(sh->tmp_filename);
			ft_putstr_fd(line, list->prev->fd_out);
			if (list->prev->fd_out != STDOUT_FILENO && list->prev->fd_out > 1)
				close(list->prev->fd_out);
		}
		list = list->next;
	}
	//ft_print_tokens(sh);
	//printf("%d, %d \n", sh->heredoc_pipe[1], sh->heredoc_pipe[0]);
}
