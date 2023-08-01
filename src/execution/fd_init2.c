/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:42:02 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/01 14:58:05 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	set_here_doc_fd(t_list *list, int *current_fd_in, t_bash *sh)
{
	int		tmp_fd;
	char	*tmp_file_name;
	char	*line;

	if (list->id == HERE_DOC_TOKEN && list->value)
	{
		tmp_file_name = "/tmp/here_doc_XXXXXX";
		tmp_fd = open(tmp_file_name, O_RDWR | O_CREAT, 0600);
		if (tmp_fd == -1)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		while (1)
		{
			line = readline("heredoc> ");
			if (line && ft_strncmp(line, list->value,
					ft_strlen(list->value)) == 0)
			{
				free(line);
				break ;
			}
			better_write(tmp_fd, line, ft_strlen(line));
			free(line);
		}
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
		//better_unlink(tmp_file_name);
		sh->heredoc = 1;
	}
}
