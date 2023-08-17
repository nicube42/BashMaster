/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashmaster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:01:49 by ivautrav          #+#    #+#             */
/*   Updated: 2023/08/17 14:20:15 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASHMASTER_H
# define BASHMASTER_H

# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
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
# define PIPE_ERROR 8

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
	char			*input;
	char			**lexed;
	char			*word;
	int				lexed_size;
	int				lexed_current;
	int				*is_quote;
	int				quote_count;
	int				dquote_count;
	char			**envp;
	char			**splitted_path;
	int				heredoc_pipe[2];
	int				heredoc;
	char			*tmp_filename;
	char			tmp_fd;
	int				last_exit_status;
	int				in_heredoc;
	int				exit_heredoc;
	pid_t			*pids;
	int				n_pids;
	struct s_list	*first;
	struct s_list	*last;
}	t_bash;

typedef struct s_exp
{
	int				i;
	int				l;
	int				k;
	int				m;
	char			*tmp;
}	t_exp;

extern int	g_quit_heredoc;

// prompt.c

char		*prompt_content(t_bash *sh);

// setup.c

void		setup_signals(void);
void		disable_ctrl_c_echo(void);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);
void		child_sigint_handler(int sig);

// lexer+expander

void		replace_substring(char **str, t_exp *exp, t_bash *sh);
void		expand_last_exit_status(t_bash *sh, t_exp *exp);
void		expander(t_bash *sh, char **envp);
void		expander_2(t_bash *sh, t_exp *exp);
char		*create_new_string(char **str, t_exp *exp, t_bash *sh);
int			fill_word(char *input, int i_save, int only_count, t_bash *sh);
char		*allocate_word(int length, t_bash *sh);
int			compute_word_len(char *input, int *i);
int			ft_is_separator(char c);
void		replace_with_empty(t_bash *sh, t_exp *exp);
int			get_substr_length(char *str, int start_idx);
int			get_substr_reallength(char *str, int start_idx);
void		init_lexed_malloc(t_bash *sh);
void		free_lexed(t_bash *sh);
void		clean_exit(char *msg, t_bash *sh);
void		free_envp(t_bash *sh);
void		init_struct(t_bash *sh, char **envp);
int			redirection_to_char(char *input, int i, t_bash *sh, int only_count);
int			pipe_to_char(char *input, int i, t_bash *sh, int only_count);
int			word_to_char(char *input, int i, t_bash *sh, int only_count);
int			quote_to_char(char *input, int i, t_bash *sh, int only_count);
void		lexer_size(char *input, t_bash *sh);
char		**lexer(char *input, t_bash *sh);
int			calculate_redir_to_char(char *input, int i, t_bash *sh);
void		stock_in_struct(t_bash *sh, char *word, int j, int only_count);

// parser

void		parser(t_bash *sh);
int			check_syntax(t_bash *sh);
int			wrong_cmd_error(t_bash *sh);
int			unclosed_quote_error(t_bash *sh);
int			pipe_syntax_error(t_bash *sh);
int			pipe_syntax_error_2(t_bash *sh);
void		correct_redir(t_bash *sh);
t_list		*ft_init_token(t_bash *sh);
void		ft_add_token(t_bash *sh, t_list *to_add);
void		ft_connect_token(t_list *list, t_list *to_add);
void		destroy_tokens(t_bash *sh);
int			ft_is_quote(char c);
int			ft_is_blank(char c);
int			ft_skip_blank(char *line, int i);
void		set_last_of_list(t_bash *sh);
char		**ft_parsing_execve(char **envp, t_bash *sh);
void		count_quote(char *input, t_bash *sh);
int			is_builtin(char *tmp);
int			ft_check_cmd(char *tok, t_bash *sh);

// execution

void		better_dup2(int to_change, int new);
void		better_close(int to_close);
void		better_write(int fd, char *value, size_t size);
void		better_unlink(char *name);
void		pipe_and_execute(t_list *list, t_bash *sh, char *cmd, char **args);
void		child_process(t_list *list, t_bash *sh, char *cmd, char **args);
void		prepare_cmd(t_bash *sh, t_list *list, char **cmd, char ***args);
char		*append_buffer(char *result, char *buffer, size_t bytes_read,
				size_t *total_bytes);
void		close_all_fd(t_bash *sh);
char		*copy_fd_to_str(int fd);
void		execution(t_bash *sh);
void		set_red_exit_fd(t_list *list, int *current_fd_out);
void		set_append_fd(t_list *list, int *current_fd_out);
void		set_red_entry_fd(t_list *list, int *current_fd_in);
void		set_pipe_fd(t_list *list, int *current_fd_in, int *current_fd_out);
void		set_fd(t_bash *sh);
void		set_here_doc_fd(t_list *list, int *current_fd_in, t_bash *sh);
int			heredoc_fd_2(t_list *list, t_bash *sh);
void		handle_child_errors(int pid);
void		close_fds(t_list *list);
void		reset_fds(void);
void		wait_and_handle_status(t_list *list, t_bash *sh, int pid);

// builtins

void		execute_buildin(t_list *list, t_bash *sh);
void		execute_env(t_bash *sh, t_list *list);
void		execute_echo(t_list *list);
void		execute_pwd(t_bash *sh, t_list *list);
int			cd_command(t_bash *bash, t_list *cmd);
void		execute_unset(t_list *list);
void		sort_environ(char **environ);
void		execute_export(t_bash *sh, t_list *list);
int			is_valid_format(char *arg);
void		execute_exit(t_bash *sh, t_list *list);
int			find_key(t_bash *sh, char *key);
void		unset_cmd(t_bash *sh, char *arg);
void		handle_export(t_bash *sh, char **args);
void		handle_unset(t_bash *sh, char **args);

// needed for readline replace line function

extern void	rl_replace_line(const char *str, int i);

#endif