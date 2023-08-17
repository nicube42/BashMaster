RED = \033[0;31m
NOCOLOR = \033[0m
GREEN = \033[0;32m
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

SRC = main.c \
	signals.c \
	prompt.c \
	\
	lexer+expander/lexer.c \
	lexer+expander/lexer_utils.c \
	lexer+expander/expander.c \
	lexer+expander/expander2.c \
	lexer+expander/init_and_exit.c \
	\
	parser/parser.c \
	parser/parser2.c \
	parser/token_creator.c \
	parser/check_syntax.c \
	parser/check_syntax2.c \
	parser/utils_parsing.c \
	parser/utils_parsing_2.c \
	\
	execution/execution.c \
	execution/execution_utils.c \
	execution/fd_init.c \
	execution/fd_init2.c \
	execution/better_syscall.c \
	execution/child.c \
	execution/parent_control.c \
	\
	builtins/builtin.c \
	builtins/cd.c \
	builtins/exit.c \
	builtins/export+unset.c \
	builtins/export_with_args.c \
	builtins/unset_with_args.c \

DIRS	= .


OBJ_DIR = $(addprefix obj/, $(DIRS))
OBJS = $(addprefix obj/, $(SRC:.c=.o))
SRCS = $(addprefix src/, $(SRC))

LIBFT = libftprintf.a

all: create_dirs $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

create_dirs:
	@mkdir -p obj/
	@mkdir -p obj/execution
	@mkdir -p obj/parser
	@mkdir -p obj/builtins
	@mkdir -p obj/lexer+expander
	@mkdir -p $(OBJ_DIR)

all: logo $(NAME)

logo :
	@tput setaf 2; cat ascii_art/42minishell; tput setaf default

#m1
#-L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include/readline
#42mac
#-L /Users/ndiamant/.brew/opt/readline/lib -I /Users/ndiamant/.brew/opt/readline/include/readline
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -g -o $(NAME) -lreadline -L /Users/ndiamant/.brew/opt/readline/lib -I /Users/ndiamant/.brew/opt/readline/include/readline -Llibft/ -lftprintf
	@echo "Assembling $(NAME)"
	@echo "${GREEN}✓${NOCOLOR}"
	@echo "$(GREEN)Compilation is done$(NOCOLOR)"

obj/%.o: src/%.c
	@echo "Compiling $^: "
	@$(CC) $(CFLAGS) -g -c -o $@ $< -I ./includes
	@echo "${GREEN}✓${NOCOLOR}"

clean:
	@echo "${RED}Cleaning objects: ${NOCOLOR}"
	@rm -rf obj/
	@$(MAKE) -C libft/ clean
	@echo "${GREEN}✓${NOCOLOR}"

fclean:
	@echo "${RED}Cleaning all: ${NOCOLOR}"
	@rm -rf obj/
	@rm -f $(NAME)
	@$(MAKE) -C libft/ fclean
	@echo "${GREEN}✓${NOCOLOR}"

re: fclean all

fast:
	@$(MAKE) -j -C ./libft
	@$(MAKE) -j$(nproc)

norme: 
	norminette src/ libft/ ./includes

.PHONY: all create_dirs clean fclean re fast norme
