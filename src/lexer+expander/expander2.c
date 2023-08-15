/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:25:34 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/15 17:34:15 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static void	append_quotes_to_string(char **str, int number_end_quotes)
{
	char	*quotes;
	char	*new_str;
	int		i;

	quotes = (char *)malloc(number_end_quotes + 1);
	i = 0;
	while (i < number_end_quotes)
	{
		quotes[i] = '\'';
		i++;
	}
	quotes[i] = '\0';
	new_str = ft_strjoin(*str, quotes);
	free(*str);
	free(quotes);
	*str = new_str;
}

static int	process_env(t_bash *sh, t_exp *exp, int len_to_end)
{
	int		j;
	int		tmp_size;

	j = -1;
	while (sh->envp[++j])
	{
		if (!ft_strncmp(exp->tmp, sh->envp[j], len_to_end)
			&& sh->envp[j][len_to_end] == '=')
		{
			tmp_size = len_to_end;
			free(exp->tmp);
			exp->tmp = ft_substr(sh->envp[j], tmp_size + 1,
					ft_strlen(sh->envp[j]));
			if (!exp->tmp)
				clean_exit("Malloc error", sh);
			replace_substring(&sh->lexed[exp->i], exp, sh);
			return (1);
		}
	}
	return (0);
}

void	expander_2(t_bash *sh, t_exp *exp)
{
	int		len_to_end;
	int		n_quotes;
	int		ret;

	exp->tmp = ft_substr(sh->lexed[exp->i],
			exp->k + 1, ft_strlen(sh->lexed[exp->i]));
	len_to_end = get_substr_length(sh->lexed[exp->i], exp->k + 1);
	n_quotes = ft_strlen(exp->tmp) - len_to_end;
	if (!exp->tmp)
		clean_exit("Malloc error", sh);
	ret = process_env(sh, exp, len_to_end);
	if (n_quotes && ret == 1)
		append_quotes_to_string(&sh->lexed[exp->i], n_quotes);
}
