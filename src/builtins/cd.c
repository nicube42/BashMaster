/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:52:18 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/14 23:24:00 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static void	update_pwd_in_envp(t_bash *bash, char *new_pwd)
{
	int		i;
	char	*new_entry;

	i = 0;
	while (bash->envp[i])
	{
		if (ft_strncmp(bash->envp[i], "PWD=", 4) == 0)
		{
			free(bash->envp[i]);
			new_entry = ft_strjoin("PWD=", new_pwd);
			if (!new_entry)
				return ;
			bash->envp[i] = ft_strdup(new_entry);
			free (new_entry);
			break ;
		}
		i++;
	}
	bash->last_exit_status = 0;
}

int	cd_command(t_bash *bash, t_list *cmd)
{
	char	old_pwd[4096];
	char	new_pwd[4096];

	if (!cmd->arguments || !cmd->arguments[0])
	{
		ft_putstr_fd("cd: No path provided.\n", 2);
		return (-1);
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
	{
		perror("getcwd error");
		return (-1);
	}
	if (chdir(cmd->arguments[0]) == -1)
	{
		perror("chdir error");
		return (-1);
	}
	if (!getcwd(new_pwd, sizeof(new_pwd)))
	{
		perror("getcwd error");
		return (-1);
	}
	update_pwd_in_envp(bash, new_pwd);
	return (0);
}
