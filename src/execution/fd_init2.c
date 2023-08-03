/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:42:02 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/03 11:31:22 by ndiamant         ###   ########.fr       */
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
		tmp_file_name = "./here_doc";
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
			better_write(tmp_fd, "\n", 1);
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
		better_unlink(tmp_file_name);
		sh->heredoc = 1;
	}
}

int heredoc_fd_2(t_list *list, t_bash *sh)
{
    int tmp_fd;
    char *tmp_file_name;
    char *line;

    if (list && list->id == HERE_DOC_TOKEN)
    {
        tmp_file_name = "./here_doc";
        tmp_fd = open(tmp_file_name, O_RDWR | O_CREAT, 0600);
        if (tmp_fd == -1)
        {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        while (1)
        {
            line = readline("pipe heredoc> ");
            if (line && ft_strncmp(line, list->value, ft_strlen(list->value)) == 0)
            {
                free(line);
                break;
            }
            better_write(tmp_fd, line, ft_strlen(line));
            better_write(tmp_fd, "\n", 1);
            free(line);
        }
		close(tmp_fd);
		tmp_fd = open(tmp_file_name, O_RDONLY, 0600);
        sh->heredoc = 1;
		sh->tmp_filename = tmp_file_name;
		return (tmp_fd);
    }
}

char	*append_buffer(char *result, char *buffer, size_t bytes_read,
		size_t *total_bytes)
{
	char	*new_result;

	new_result = (char *)malloc(*total_bytes + bytes_read + 1);
	if (!new_result)
		return (NULL);
	if (result)
	{
		ft_memcpy(new_result, result, *total_bytes);
		free(result);
	}
	ft_memcpy(new_result + *total_bytes, buffer, bytes_read);
	*total_bytes += bytes_read;
	return (new_result);
}

char	*copy_fd_to_str(int fd)
{
	char	buffer[4096];
	char	*result;
	ssize_t	bytes_read;
	size_t	total_bytes;

	total_bytes = 0;
	result = NULL;
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		result = append_buffer(result, buffer, bytes_read, &total_bytes);
		if (!result)
			return (NULL);
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	if (bytes_read == -1 || !result)
	{
		free(result);
		return (NULL);
	}
	result[total_bytes] = '\0';
	return (result);
}