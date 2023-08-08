/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:42:02 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/08 13:50:16 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static int	create_tmp_file(char *tmp_file_name)
{
	int	tmp_fd;

	tmp_fd = open(tmp_file_name, O_RDWR | O_CREAT, 0600);
	if (tmp_fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	return (tmp_fd);
}

static void	write_here_doc(int tmp_fd, t_list *list, char *prompt, t_bash *sh)
{
	char	*line;

	g_global.in_heredoc = 1;
	while (g_global.in_heredoc == 1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_DFL);
		line = readline(prompt);
		if (!line && g_global.in_heredoc == 1)
			continue ;
		if (line[0] == '\0')
			continue ;
		if (line && ft_strncmp(line, list->value, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		if (g_global.in_heredoc == 0)
		{
			free (line);
			break ;
		}
		better_write(tmp_fd, line, ft_strlen(line));
		better_write(tmp_fd, "\n", 1);
		free(line);
	}
	if (g_global.in_heredoc == 0)
		sh->exit_heredoc = 1;
	g_global.in_heredoc = 0;
}

void	set_here_doc_fd(t_list *list, int *current_fd_in, t_bash *sh)
{
	int		tmp_fd;
	char	*tmp_file_name;

	if (list->id != HERE_DOC_TOKEN || !list->value)
		return ;
	tmp_file_name = "./here_doc";
	tmp_fd = create_tmp_file(tmp_file_name);
	write_here_doc(tmp_fd, list, "heredoc> ", sh);
	better_close(tmp_fd);
	tmp_fd = open(tmp_file_name, O_RDONLY);
	if (tmp_fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	*current_fd_in = tmp_fd;
	if (list->next)
		list->next->fd_in = tmp_fd;
	better_unlink(tmp_file_name);
	sh->heredoc = 1;
}

int	heredoc_fd_2(t_list *list, t_bash *sh)
{
	int		tmp_fd;
	char	*tmp_file_name;

	tmp_file_name = "./here_doc";
	tmp_fd = create_tmp_file(tmp_file_name);
	write_here_doc(tmp_fd, list, "pipe heredoc> ", sh);
	close(tmp_fd);
	sh->heredoc = 1;
	sh->tmp_filename = tmp_file_name;
	return (open(tmp_file_name, O_RDONLY, 0600));
}
