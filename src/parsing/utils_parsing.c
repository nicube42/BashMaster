/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:11:19 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/11 11:45:58 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

char	**ft_parsing_execve(char **envp, t_bash *sh)
{
	int		i;
	char	*full_path;
	char	**splitted_path;
	char	*tmp;

	i = 0;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			full_path = envp[i] + 5;
	}
	splitted_path = ft_split(full_path, ':');
	if (!splitted_path)
		clean_exit("Malloc error", sh);
	i = -1;
	while (splitted_path[++i])
	{
		tmp = ft_strjoin(splitted_path[i], "/");
		if (!tmp)
			clean_exit("Malloc error", sh);
		if (splitted_path[i])
			free(splitted_path[i]);
		splitted_path[i] = tmp;
	}
	return (splitted_path);
}

void	count_quote(char *input, t_bash *sh)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_is_quote(input[i]) == 1)
			sh->dquote_count ++;
		if (ft_is_quote(input[i]) == 2)
			sh->quote_count++;
		i++;
	}
}

void	set_last_of_list(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	while (list)
		list = list->next;
	sh->last = list;
}

int	is_builtin(char *tmp)
{
	if (!ft_strncmp(tmp, "echo", 5))
		return (1);
	if (!ft_strncmp(tmp, "cd", 3))
		return (1);
	if (!ft_strncmp(tmp, "pwd", 4))
		return (1);
	if (!ft_strncmp(tmp, "export", 5))
		return (1);
	if (!ft_strncmp(tmp, "unset", 6))
		return (1);
	if (!ft_strncmp(tmp, "env", 4))
		return (1);
	if (!ft_strncmp(tmp, "exit", 5))
		return (1);
	return (0);
}

int	ft_check_cmd(char *tok, t_bash *sh)
{
	int		i;
	char	*cmd;

	i = -1;
	while (sh->splitted_path[++i])
	{
		cmd = ft_strjoin(sh->splitted_path[i], tok);
		if (access(cmd, F_OK) == 0)
		{
			free(cmd);
			return (0);
		}
		free(cmd);
	}
	return (1);
}
