NAME =	minishell
SRC = 	sources/minishell.c sources/builtin/cd.c sources/builtin/echo_cmd.c sources/builtin/exit.c \
		sources/builtin/export_utils.c sources/builtin/export.c sources/builtin/pwd.c sources/builtin/unset.c \
		sources/env/env1.c sources/env/get_env.c sources/exec/builtin.c sources/exec/exec.c \
		sources/exec/extra.c sources/parsing/env.c sources/parsing/fix_token.c sources/parsing/token.c \
		sources/parsing/type.c sources/parsing/utils.c sources/tools/parse.c sources/tools/pipe.c \
		sources/tools/pipe2.c sources/tools/sig.c 
		       
CC = 	gcc

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ./libft/libft.a ${SRC}
	${CC} ${CFLAGS} ${SRC} -Ilibft ./libft/libft.a -lreadline  -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -o $@

./libft/libft.a:
	@make -C ./libft

clean:
	@make clean -C ./libft

fclean: clean
	@make fclean -C ./libft
	rm -rf ${NAME}

re: fclean all