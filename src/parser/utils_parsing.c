/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:11:19 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 16:44:27 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static char	**process_split_path(char **split_path, t_bash *sh)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		if (!tmp)
			clean_exit("Malloc error", sh);
		free(split_path[i]);
		split_path[i] = tmp;
		i++;
	}
	return (split_path);
}

char	**ft_parsing_execve(char **envp, t_bash *sh)
{
	int		i;
	char	*full_path;
	char	**split_path;

	i = 0;
	full_path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			full_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!full_path)
		return (NULL);
	split_path = ft_split(full_path, ':');
	if (!split_path)
		clean_exit("Malloc error", sh);
	return (process_split_path(split_path, sh));
}

void	count_quote(char *input, t_bash *sh)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_is_quote(input[i]) == 1)
			sh->dquote_count++;
		if (ft_is_quote(input[i]) == 2)
			sh->quote_count++;
		i++;
	}
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
	if (!sh->splitted_path)
		return (1);
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
