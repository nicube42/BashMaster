/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashmaster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:01:49 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/20 01:31:15 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASHMASTER_H
# define BASHMASTER_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

typedef struct s_command
{

}	t_command;

typedef struct s_bash
{
	char	**lexed;
	int		lexed_size;
	int		lexed_current;
}	t_bash;

char	**lexer(char *input, t_bash	*sh);
void	lexer_size(char *input, t_bash *sh);

int		ft_is_blank(char c);
int		ft_skip_blank(char *line, int i);
int		redirection_to_char(char *input, int i, t_bash *sh, int only_count);
int		pipe_to_char(char *input, int i, t_bash *sh, int only_count);
int		word_to_char(char *input, int i, t_bash *sh, int only_count);

void	expander(t_bash *sh, char **envp);

#endif