NAME = minishell

CC = cc
CFLAGS = -fsanitize=address -Wall -Wextra -Werror

SRC = main.c \
	signals.c \
	\
	lexer+expander/lexer.c \
	lexer+expander/lexer_utils.c \
	lexer+expander/expander.c \
	lexer+expander/init_and_exit.c \
	\
	parser/parser.c \
	parser/parser2.c \
	parser/token_creator.c \
	parser/check_syntax.c \
	parser/utils_parsing.c \
	parser/utils_parsing_2.c \
	\
	execution/execution.c \
	execution/execution_utils.c \
	execution/fd_init.c \
	execution/fd_init2.c \
	execution/better_syscall.c \
	\
	builtins/builtin.c \
	builtins/builtin2.c \
	builtins/ft_cd.c \

DIRS	= .


OBJ_DIR = $(addprefix obj/, $(DIRS))
OBJS = $(addprefix obj/, $(SRC:.c=.o))
SRCS = $(addprefix src/, $(SRC))

LIBFT = libftprintf.a

all: create_dirs $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

create_dirs:
	mkdir -p obj/
	mkdir -p obj/execution
	mkdir -p obj/parser
	mkdir -p obj/builtins
	mkdir -p obj/lexer+expander
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include/readline -Llibft/ -lftprintf

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I ./includes

clean:
	rm -rf obj/
	$(MAKE) -C libft/ clean

fclean:
	rm -rf obj/
	rm -f $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all

fast:
	$(MAKE) -j -C ./libft
	$(MAKE) -j$(nproc)

.PHONY: all create_dirs clean fclean re fast

