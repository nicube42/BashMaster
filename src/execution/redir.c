/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:47:37 by asouchet          #+#    #+#             */
/*   Updated: 2023/06/08 16:48:08 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	land_here_doc(t_shell *shell, char *heredoc)
{
	improved_pipe(shell->fd->fd, shell);
	ft_putstr_fd(heredoc, shell->fd->fd[1]);
	shell->fd->input = shell->fd->fd[0];
	_close(shell->fd->fd[1]);
}

void	redir_new_file(char *file, t_shell *shell, int cases)
{
	int	fd;

	if (shell->fd->output != 1)
	{
		_close(shell->fd->output);
		shell->fd->output = 1;
	}
	if (cases == 0)
		fd = open(file, O_TRUNC | O_RDWR | O_CREAT, 0644);
	else
		fd = open(file, O_APPEND | O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": trouble on creating file\n", 2);
		shell->error->error = 1;
	}
	shell->fd->output = fd;
}

void	redir_file(char *file, t_shell *shell)
{
	int	fd;

	if (shell->fd->input != 0)
	{
		_close(shell->fd->input);
		shell->fd->input = 0;
	}
	fd = open(file, O_RDWR, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->error->error = 1;
	}
	shell->fd->input = fd;
}

void	parse_redir(t_shell *shell, t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->cases == 0 || tmp->cases == 1)
			redir_new_file(tmp->file, shell, tmp->cases);
		if (shell->error->error != 0)
			break ;
		tmp = tmp->next;
	}
}

void	parse_opening(t_shell *shell, t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->cases == 2)
			redir_file(tmp->file, shell);
		if (shell->error->error != 0)
			break ;
		if (tmp->cases == 3)
			land_here_doc(shell, tmp->here_doc);
		if (shell->error->error != 0)
			break ;
		tmp = tmp->next;
	}
}
