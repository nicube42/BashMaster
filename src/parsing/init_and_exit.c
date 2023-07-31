/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:17:10 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/31 20:57:10 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	init_lexed_malloc(t_bash *sh)
{
	sh->lexed = malloc(sizeof(char *) * (sh->lexed_size + 1));
	if (!sh->lexed)
		clean_exit("Malloc error", sh);
	sh->is_quote = malloc(sizeof(int) * (sh->lexed_size));
	if (!sh->is_quote)
		clean_exit("Malloc error", sh);
}

void	free_lexed(t_bash *sh)
{
	int	i;

	i = -1;
	while (sh->lexed[++i])
		free (sh->lexed[i]);
	free (sh->lexed);
}

void	clean_exit(char *msg, t_bash *sh)
{
	perror(msg);
	destroy_tokens(sh);
	exit (1);
}

void	init_struct(t_bash *sh, char **envp)
{
	sh->lexed = 0;
	sh->lexed_size = 0;
	sh->lexed_current = 0;
	sh->dquote_count = 0;
	sh->quote_count = 0;
	sh->envp = envp;
	sh->splitted_path = ft_parsing_execve(envp, sh);
	sh->input = 0;
}
