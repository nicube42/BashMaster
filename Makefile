NAME = minishell

CC = cc
CFLAGS = #-fsanitize=address #-Wall -Wextra -Werror

SRC = main.c parsing/lexer.c parsing/lexer_utils.c parsing/expander.c parsing/parser.c parsing/token_creator.c parsing/check_syntax.c execution/builtin.c execution/execution.c
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
	mkdir -p obj/parsing
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -Llibft/ -lftprintf

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

