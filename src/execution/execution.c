/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:45:13 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/09 15:04:36 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	pipe_and_execute(t_list *list, t_bash *sh, char *cmd, char **args)
{
	int		temp_fd;
	char	buffer[1024];
	char	*line;
	ssize_t	bytes_read;

	if (list->next && list->next->id == HERE_DOC_TOKEN)
	{
		temp_fd = open("tempfile", O_RDWR | O_CREAT, 0666);
		if (list->fd_in != 0)
		{
			while ((bytes_read = read(list->fd_in, buffer, sizeof(buffer))) > 0)
				write(temp_fd, buffer, bytes_read);
		}
		line = copy_fd_to_str(sh->tmp_fd);
		better_close(sh->tmp_fd);
		better_unlink(sh->tmp_filename);
		ft_putstr_fd(line, temp_fd);
		lseek(temp_fd, 0, SEEK_SET);
		better_dup2(temp_fd, STDIN_FILENO);
		better_close(list->fd_in);
		list->fd_in = temp_fd;
	}
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
	if (list->next && list->next->id == HERE_DOC_TOKEN)
		unlink("tempfile");
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
	g_global.in_cmd = 1;
	signal(SIGINT, child_sigint_handler);
	signal(SIGQUIT, SIG_DFL);
	setup_signals();
	pipe_and_execute(list, sh, cmd, args);
	g_global.in_cmd = 0;
}

static void	handle_child_errors(int pid)
{
	if (pid < 0)
		perror("fork");
}

static void	close_fds(t_list *list)
{
	if (list->fd_in != -1 && list->fd_in != STDIN_FILENO)
		better_close(list->fd_in);
	if (list->fd_out != STDOUT_FILENO && list->fd_out > 1)
		better_close(list->fd_out);
}

static void	reset_fds(void)
{
	better_dup2(STDIN_FILENO, 0);
	better_dup2(STDOUT_FILENO, 1);
	better_dup2(STDERR_FILENO, 2);
}

static void	wait_and_handle_status(t_list *list, t_bash *sh, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		kill(pid, SIGKILL);
	}
	else if (WIFEXITED(status))
		sh->last_exit_status = WEXITSTATUS(status);
}

void execute_cmd(t_list *list, t_bash *sh)
{
	char	**args;
	char	*cmd;
	pid_t	pid;

	prepare_cmd(sh, list, &cmd, &args);
	if (!ft_strncmp(list->value, "cd", 3))
		cd_command(sh, list);
	else if (!ft_strncmp(list->value, "exit", 5))
		execute_exit(sh, list);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			child_process(list, sh, cmd, args);
		}
		else
		{
			g_global.in_cmd = 1;
			handle_child_errors(pid);
			close_fds(list);
			wait_and_handle_status(list, sh, pid);
			g_global.in_cmd = 0;
		}
	}
	free(args);
	free(cmd);
	reset_fds();
}

void	execution(t_bash *sh)
{
	t_list	*list;
	t_list	*prev;
	int		tmp_fd;
	char	*line;
	int		fd[2];

	list = sh->first;
	set_fd(sh);
	while (list)
	{
		if ((list->id == CMD_TOK || list->id == BUILTIN_TOK)
			&& sh->exit_heredoc == 0)
			execute_cmd(list, sh);
		list = list->next;
	}
	//ft_print_tokens(sh);
}
