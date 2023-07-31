/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:42:02 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/31 14:47:58 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	set_here_doc_fd(t_list *list, int *current_fd_in, t_bash *sh)
{
	int		tmp_fd;
	char	*tmp_file_name;

	if (list->id == HERE_DOC_TOKEN && list->value)
	{
		tmp_file_name = "/tmp/here_doc_XXXXXX";
		tmp_fd = open(tmp_file_name, O_RDWR | O_CREAT, 0600);
		if (tmp_fd == -1)
			clean_exit("Open error", sh);
		if (write(tmp_fd, list->value, ft_strlen(list->value)) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		if (close(tmp_fd) == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}
		tmp_fd = open(tmp_file_name, O_RDONLY);
		if (tmp_fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		*current_fd_in = tmp_fd;
		if (list->next)
			list->next->fd_in = tmp_fd;
		if (unlink(tmp_file_name) == -1)
		{
			perror("unlink");
			exit(EXIT_FAILURE);
		}
	}
}