/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:16:51 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/28 09:55:50 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	replace_substring(char **str, int start, int end, char *replacement, t_bash *sh)
{
	char	*new_str;
	char	*prefix;
	char	*suffix;
	char	*temp_str;

	prefix = ft_substr(*str, 0, start);
	if (!prefix)
		clean_exit("Malloc error", sh);
	suffix = ft_substr(*str, end, ft_strlen(*str) - end);
	if (!suffix)
		clean_exit("Malloc error", sh);
	temp_str = ft_strjoin(prefix, replacement);
	if (!temp_str)
		clean_exit("Malloc error", sh);
	new_str = ft_strjoin(temp_str, suffix);
	if (!new_str)
		clean_exit("Malloc error", sh);
	free(prefix);
	free(suffix);
	free(temp_str);
	free(*str);
	*str = new_str;
}

void	expander(t_bash *sh, char **envp)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*tmp;

	i = -1;
	j = -1;
	sh->lexed[sh->lexed_size] = 0;
	while (sh->lexed[++i])
	{
		k = -1;
		while (sh->lexed[i][++k])
		{
			if (sh->lexed[i][k] == '$' && sh->is_quote[i] == 0)
			{
				l = k;
				while (!ft_is_blank(sh->lexed[i][l]) && sh->lexed[i][l])
					l++;
				tmp = ft_substr(sh->lexed[i], k + 1, ft_strlen(sh->lexed[i]));
				if (!tmp)
					clean_exit("Malloc error", sh);
				j = -1;
				while (envp[++j])
				{
					if (!ft_strncmp(tmp, envp[j], ft_strlen(tmp))
						&& envp[j][ft_strlen(tmp)] == '=')
					{
						free (tmp);
						tmp = ft_substr(envp[j],
								ft_strlen(tmp) + 1, ft_strlen(envp[j]));
						if (!tmp)
							clean_exit("Malloc error", sh);
						replace_substring(&sh->lexed[i], k, l, tmp, sh);
						break ;
					}
				}
				free (tmp);
			}
		}
	}
}
