/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:58:58 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 14:26:13 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	set_red_exit_fd(t_list *list, int *current_fd_out)
{
	if (list->id == RED_EXIT_TOKEN && list->value)
	{
		*current_fd_out = open(list->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (*current_fd_out == -1)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		if (list->prev)
			list->prev->fd_out = *current_fd_out;
	}
}

void	set_append_fd(t_list *list, int *current_fd_out)
{
	if (list->id == APPEND_TOKEN && list->value)
	{
		*current_fd_out = open(list->value, O_WRONLY
				| O_CREAT | O_APPEND, 0666);
		if (*current_fd_out == -1)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		if (list->prev)
			list->prev->fd_out = *current_fd_out;
	}
}

void	set_red_entry_fd(t_list *list, int *current_fd_in)
{
	if (list->id == RED_ENTRY_TOKEN && list->value)
	{
		*current_fd_in = open(list->value, O_RDONLY);
		if (*current_fd_in == -1)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		if (list->next)
			list->next->fd_in = *current_fd_in;
	}
}

void	set_pipe_fd(t_list *list, int *current_fd_in, int *current_fd_out)
{
	int	pipe_fd[2];

	(void) current_fd_out;
	if (list->id == PIPE_TOK && list->prev)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (list->prev->id == HERE_DOC_TOKEN)
			list->prev->prev->fd_out = pipe_fd[1];
		else
			list->prev->fd_out = pipe_fd[1];
		if (list->next)
		{
			list->next->fd_in = pipe_fd[0];
			*current_fd_in = pipe_fd[0];
		}
	}
}

void	set_fd(t_bash *sh)
{
	int		current_fd_in;
	int		current_fd_out;
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
		if (!list->prev || (list->prev->id != CMD_TOK
				&& list->prev->id != BUILTIN_TOK))
			set_here_doc_fd(list, &current_fd_in, sh);
		else if (list && list->id == HERE_DOC_TOKEN)
			sh->tmp_fd = heredoc_fd_2(list, sh);
		set_red_exit_fd(list, &current_fd_out);
		set_append_fd(list, &current_fd_out);
		set_red_entry_fd(list, &current_fd_in);
		set_pipe_fd(list, &current_fd_in, &current_fd_out);
		list = list->next;
	}
}
