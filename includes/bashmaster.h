/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashmaster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:01:49 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/25 19:26:45 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASHMASTER_H
# define BASHMASTER_H

# include <stdio.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

# define GREEN	"\033[0;32m"
# define RED	"\033[0;31m"
# define RESET	"\033[0m"

# define CMD_TOK 1
# define PIPE_TOK 2
# define RED_ENTRY_TOKEN 3
# define HERE_DOC_TOKEN 4
# define RED_EXIT_TOKEN 5
# define APPEND_TOKEN 6
# define BUILTIN_TOK 7

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
	int				*is_quote;
	int				quote_count;
	int				dquote_count;
	char			**envp;
	char			**splitted_path;
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

int		quote_to_char(char *input, int i, t_bash *sh, int only_count);
int		ft_is_quote(char c);

int		check_syntax(t_bash *sh);
int		pipe_syntax_error(t_bash *sh);
int		pipe_syntax_error_2(t_bash *sh);
int		unclosed_quote_error(t_bash *sh);
int		wrong_cmd_error(t_bash *sh);
int		ft_check_cmd(char *tok, t_bash *sh);

int		is_builtin(char *tmp);

void	execute(t_bash *sh);

void	execute_pwd(t_bash *sh);
void	execute_buildin(t_list *list, t_bash *sh);
void	execute_echo(t_list *list);
void	execute_env(t_bash *sh);

#endif