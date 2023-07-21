/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashmaster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:01:49 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/21 10:53:10 by ndiamant         ###   ########.fr       */
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

typedef struct s_list
{
	char			*value;
	char			**arguments;
	int				id;
	int				fd_in;
	int				fd_out;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_bash
{
	char			**lexed;
	int				lexed_size;
	int				lexed_current;
	struct s_list	*first;
}	t_bash;

char	**lexer(char *input, t_bash	*sh);
void	lexer_size(char *input, t_bash *sh);

int		ft_is_blank(char c);
int		ft_skip_blank(char *line, int i);
int		redirection_to_char(char *input, int i, t_bash *sh, int only_count);
int		pipe_to_char(char *input, int i, t_bash *sh, int only_count);
int		word_to_char(char *input, int i, t_bash *sh, int only_count);

void	expander(t_bash *sh, char **envp);

void	parser(t_bash *sh);

t_list	*ft_init_token(void);
void	ft_add_token(t_bash *sh, t_list *to_add);
void	ft_connect_token(t_list *list, t_list *to_add);
void	ft_print_tokens(t_bash *sh);

#endif