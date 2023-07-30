/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:44:25 by asouchet          #+#    #+#             */
/*   Updated: 2023/07/30 11:41:08 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	builtin_in_fork(t_shell *shell, char *cmd, t_exec *tmp)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		echo(tmp->cmd_args);
	else if (ft_strcmp(cmd, "env") == 0)
		env(shell);
	else if (ft_strcmp(cmd, "pwd") == 0)
		pwd(shell);
	else
		return (1);
	return (0);
}

int	builtin_out_fork(t_shell *shell, char *cmd, t_exec *tmp)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		cd(shell, tmp->cmd_args);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(shell, tmp->cmd_args);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(shell, tmp->cmd_args);
	else if (ft_strcmp(cmd, "unset") == 0)
		unset(tmp->cmd_args, &(shell->env));
	else
		return (1);
	return (0);
}
