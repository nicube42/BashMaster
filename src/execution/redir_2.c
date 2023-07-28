/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:49:54 by asouchet          #+#    #+#             */
/*   Updated: 2023/05/30 09:48:15 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_redir_exec(t_shell *shell, t_exec *exec)
{
	t_redir	*tmp;

	tmp = exec->redir;
	parse_redir(shell, tmp);
	if (shell->error->error != 0)
		return ;
	parse_opening(shell, tmp);
	if (shell->error->error != 0)
		return ;
}

char	*join_env(char *name, char *value)
{
	char	*ret;
	char	*tmp;

	if (!strcmp(name, ""))
		return (ft_strdup(""));
	tmp = ft_strjoin(name, "=");
	ret = ft_strjoin(tmp, value);
	free(tmp);
	return (ret);
}

void	sh_level_update(t_variable *env)
{
	t_variable	*tmp;
	int			atoi_tmp;

	tmp = env;
	while (tmp)
	{
		if (!strcmp(tmp->name, "SHLVL"))
		{
			atoi_tmp = ft_atoi(tmp->value) + 1;
			free(tmp->value);
			tmp->value = ft_itoa(atoi_tmp);
			return ;
		}
		tmp = tmp->next;
	}
}
