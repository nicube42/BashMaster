/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 03:55:50 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 16:57:54 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static int	create_redirection_token(t_bash *sh, t_list *to_add, int i)
{
	to_add = NULL;
	to_add = ft_init_token(sh);
	to_add->value = ft_strdup(sh->lexed[i]);
	if (!to_add->value)
		clean_exit("Malloc error", sh);
	to_add->fd_in = 0;
	to_add->fd_out = 0;
	to_add->arguments = 0;
	if (sh->lexed[i][0] == '<')
	{
		if (sh->lexed[i][1] == '<')
			to_add->id = HERE_DOC_TOKEN;
		else
			to_add->id = RED_ENTRY_TOKEN;
	}
	else
	{
		if (sh->lexed[i][1] == '>')
			to_add->id = APPEND_TOKEN;
		else
			to_add->id = RED_EXIT_TOKEN;
	}
	ft_add_token(sh, to_add);
	i++;
	return (i);
}

static int	create_pipe_token(t_bash *sh, t_list *to_add, int i)
{
	to_add = ft_init_token(sh);
	to_add->value = ft_strdup(sh->lexed[i]);
	if (!to_add->value)
		clean_exit("Malloc error", sh);
	to_add->fd_in = 0;
	to_add->fd_out = 0;
	to_add->arguments = 0;
	to_add->id = PIPE_TOK;
	ft_add_token(sh, to_add);
	i++;
	return (i);
}

static int	create_cmd_token_2(t_bash *sh, int i, t_list *to_add)
{
	int	j;

	j = 0;
	while (i < sh->lexed_size && sh->lexed[i][0] != '<'
		&& sh->lexed[i][0] != '>' && sh->lexed[i][0] != '|'
			&& sh->lexed[i] && ft_strncmp(sh->lexed[i], "$?", 2))
	{
		to_add->arguments[j] = ft_strdup(sh->lexed[i]);
		if (!to_add->arguments[j])
			clean_exit("Malloc error", sh);
		i++;
		j++;
	}
	to_add->arguments[j] = 0;
	return (i);
}

static int	create_cmd_token(t_bash *sh, t_list *to_add, int i)
{
	int	j;

	j = i + 1;
	to_add = ft_init_token(sh);
	to_add->value = ft_strdup(sh->lexed[i]);
	if (!to_add->value)
		clean_exit("Malloc error", sh);
	to_add->fd_in = 0;
	to_add->fd_out = 0;
	while (j < sh->lexed_size && sh->lexed[j][0] != '<'
		&& sh->lexed[j][0] != '>' && sh->lexed[j][0] != '|'
			&& ft_strncmp(sh->lexed[j], "$?", 2))
		j++;
	i++;
	to_add->arguments = malloc (sizeof(char *) * (j + 1));
	if (!to_add->arguments)
		clean_exit("Malloc error", sh);
	i = create_cmd_token_2(sh, i, to_add);
	to_add->id = CMD_TOK;
	if (is_builtin(to_add->value))
		to_add->id = BUILTIN_TOK;
	ft_add_token(sh, to_add);
	return (i);
}

void	parser(t_bash *sh)
{
	int		i;
	t_list	*to_add;

	i = 0;
	to_add = NULL;
	sh->first = 0;
	while (sh->lexed[i])
	{
		if (sh->lexed[i][0] == '<' || sh->lexed[i][0] == '>')
			i = create_redirection_token(sh, to_add, i);
		else if (sh->lexed[i][0] == '|')
			i = create_pipe_token(sh, to_add, i);
		else
			i = create_cmd_token(sh, to_add, i);
	}
	correct_redir(sh);
}
