/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:45:13 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/14 18:44:48 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static void	handle_child_execution(t_list *list,
	t_bash *sh, char *cmd, char **args)
{
	child_process(list, sh, cmd, args);
	exit(EXIT_SUCCESS);
}

static void	handle_parent_execution(t_list *list, t_bash *sh, pid_t pid)
{
	pid_t	*new_pids;

	new_pids = (pid_t *)malloc(sizeof(pid_t) * (sh->n_pids + 1));
	if (!new_pids)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (sh->pids)
	{
		ft_memcpy(new_pids, sh->pids, sizeof(pid_t) * sh->n_pids);
		free(sh->pids);
	}
	new_pids[sh->n_pids] = pid;
	sh->pids = new_pids;
	sh->n_pids++;
	g_quit_heredoc = 2;
	handle_child_errors(pid);
	close_fds(list);
	g_quit_heredoc = 0;
}

static void	execute_cmd(t_list *list, t_bash *sh)
{
	char	**args;
	char	*cmd;
	pid_t	pid;

	prepare_cmd(sh, list, &cmd, &args);
	if (!ft_strncmp(list->value, "cd", 3))
		cd_command(sh, list);
	else if (!ft_strncmp(list->value, "exit", 5))
		execute_exit(sh, list);
	else if (!ft_strncmp(list->value, "export", 7) && list->arguments[0])
		handle_export(sh, list->arguments);
	else if (!ft_strncmp(list->value, "unset", 6) && list->arguments[0])
		handle_unset(sh, list->arguments);
	else
	{
		pid = fork();
		if (pid == 0)
			handle_child_execution(list, sh, cmd, args);
		else
			handle_parent_execution(list, sh, pid);
	}
	free(args);
	free(cmd);
	reset_fds();
}

void	execution(t_bash *sh)
{
	t_list	*list;
	int		i;

	list = sh->first;
	sh->pids = NULL;
	sh->n_pids = 0;
	set_fd(sh);
	while (list)
	{
		if ((list->id == CMD_TOK || list->id == BUILTIN_TOK)
			&& sh->exit_heredoc == 0)
			execute_cmd(list, sh);
		list = list->next;
	}
	i = -1;
	while (++i < sh->n_pids)
		wait_and_handle_status(NULL, sh, sh->pids[i]);
	free(sh->pids);
	sh->pids = NULL;
	sh->n_pids = 0;
}
