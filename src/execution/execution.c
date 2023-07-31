/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:45:13 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/31 12:06:44 by ndiamant         ###   ########.fr       */
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
		{
			dup2(list->fd_in, STDIN_FILENO);
			close(list->fd_in); // Close original fd_in
		}
		if (list->fd_out > 1) // Skip 0 and 1, which are standard input and output
		{
			dup2(list->fd_out, STDOUT_FILENO);
			close(list->fd_out); // Close original fd_out
		}
		execve(cmd, args, 0);
		perror("execve");
		exit(EXIT_FAILURE); // Exit if execve fails
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

static void	handle_redirection(t_list *list, int *current_fd_in,
	int *current_fd_out)
{
	int	flags;

	if (list->id == RED_ENTRY_TOKEN && list->value)
		*current_fd_in = open(list->value, O_RDONLY);
	if ((list->id == RED_EXIT_TOKEN || list->id == APPEND_TOKEN) && list->next
		&& list->next->value)
	{
		flags = (list->id == RED_EXIT_TOKEN) ? O_WRONLY | O_CREAT | O_TRUNC
			: O_WRONLY | O_CREAT | O_APPEND;
		*current_fd_out = open(list->next->value, flags, 0666);
	}
}

void	set_fd(t_bash *sh)
{
	int	current_fd_in;
	int	current_fd_out;
	t_list	*list;

	list = sh->first;
	current_fd_in = 0;
	current_fd_out = 1;
	while (list)
	{
		if (list->id == CMD_TOK || list->id == BUILTIN_TOK)
		{
			list->fd_in = current_fd_in;
			list->fd_out = current_fd_out;
		}
		if (list->id == RED_EXIT_TOKEN && list->value)
		{
			current_fd_out = open(list->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (list->prev)
				list->prev->fd_out = current_fd_out;
		}
		if (list->id == APPEND_TOKEN && list->value) // Handling the append token
		{
			current_fd_out = open(list->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (list->prev)
				list->prev->fd_out = current_fd_out;
		}
		list = list->next;
	}
	ft_print_tokens(sh);
}

void	execution(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	set_fd(sh);
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
