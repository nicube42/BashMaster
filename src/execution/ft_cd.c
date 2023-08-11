/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:52:18 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/11 10:49:37 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

/*int	ft_cd(char **args)
{
    char	*path;

    printf("cc\n");
    if (args[1] == NULL)
        path = getenv("HOME");
    else if (args[2] != NULL)
    {
        ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
        return (1);
    }
    else
        path = args[1];
    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        perror(path);
        return (1);
    }
    return (0);
}*/

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
