/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:13:51 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 15:44:08 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static void	handle_here_doc_token(t_list *list, t_bash *sh, int temp_fd)
{
	ssize_t	bytes_read;
	char	buffer[1024];
	char	*line;

	if (list->fd_in > 2)
	{
		bytes_read = read(list->fd_in, buffer, sizeof(buffer));
		while (bytes_read > 0)
		{
			write(temp_fd, buffer, bytes_read);
			bytes_read = read(list->fd_in, buffer, sizeof(buffer));
		}
	}
	line = copy_fd_to_str(sh->tmp_fd);
	better_close(sh->tmp_fd);
	better_unlink(sh->tmp_filename);
	ft_putstr_fd(line, temp_fd);
	better_close(temp_fd);
	temp_fd = open("tempfile", O_RDWR | O_CREAT, 0666);
	better_dup2(temp_fd, STDIN_FILENO);
	better_close(list->fd_in);
	list->fd_in = temp_fd;
}

static void	redirect_fd(t_list *list)
{
	if (list->fd_in != -1 && list->fd_in != STDIN_FILENO)
		better_dup2(list->fd_in, STDIN_FILENO);
	if (list->fd_out != STDOUT_FILENO && list->fd_out > 1)
		better_dup2(list->fd_out, STDOUT_FILENO);
}

void	pipe_and_execute(t_list *list, t_bash *sh, char *cmd, char **args)
{
	int		temp_fd;

	if (list->next && list->next->id == HERE_DOC_TOKEN)
	{
		temp_fd = open("tempfile", O_RDWR | O_CREAT, 0666);
		handle_here_doc_token(list, sh, temp_fd);
	}
	redirect_fd(list);
	close_all_fd(sh);
	if (list->next && list->next->id == HERE_DOC_TOKEN)
		unlink("tempfile");
	if (list->id == CMD_TOK)
	{
		execve(cmd, args, sh->envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		execute_buildin(list, sh);
}

void	child_process(t_list *list, t_bash *sh, char *cmd, char **args)
{
	g_quit_heredoc = 2;
	signal(SIGINT, child_sigint_handler);
	signal(SIGQUIT, SIG_DFL);
	setup_signals();
	pipe_and_execute(list, sh, cmd, args);
	g_quit_heredoc = 0;
}
