/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:35:42 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 09:57:45 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static char	*add_path(t_bash *sh, t_list *list)
{
	char	*cmd;
	int		i;

	if (list->value[0] == '/' || (list->value[0] == '.'
			&& (list->value[1] == '/' || (list->value[1] == '.'
					&& list->value[2] == '/'))))
	{
		if (access(list->value, F_OK) == 0)
			return (ft_strdup(list->value));
		else
			return (NULL);
	}
	i = -1;
	if (!sh->splitted_path)
		return (NULL);
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
	if (!*args)
		return ;
	(*args)[0] = list->value;
	i = -1;
	while (list->arguments && list->arguments[++i])
		(*args)[i + 1] = list->arguments[i];
	(*args)[i + 1] = 0;
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
