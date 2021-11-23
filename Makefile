#PHONY: all clean fclean re


#LDFLAGS=-L/home/linuxbrew/.linuxbrew/Cellar/readline/lib
#CPPFLAGS=-I/home/linuxbrew/.linuxbrew/Cellar/readline/include
LDFLAGS=-L/Users/yhebbat/.brew/opt/readline/lib
CPPFLAGS=-I/Users/yhebbat/.brew/opt/readline/include
#LDFLAGS=-L/Users/yhebbat/.brew/opt/readline/lib
#CPPFLAGS=-I/Users/yhebbat/.brew/opt/readline/include

#LDFLAGS=-L/home/linuxbrew/.linuxbrew/Cellar/readline/lib
#CPPFLAGS=-I/home/linuxbrew/.linuxbrew/Cellar/readline/include

NAME = minishell

SRC =	./parsing/minishell.c ./parsing/libft0.c ./parsing/ft_split.c ./parsing/toke.c ./parsing/ft_tst.c ./parsing/save_env.c ./parsing/error.c \
		./parsing/free.c ./parsing/fill_cmd_struct.c ./parsing/ft_strjoin.c ./parsing/redirections.c \
		./parsing/libft1.c ./execution/cd.c ./execution/echo.c ./execution/env.c ./execution/execute.c \
		./execution/exit.c ./execution/export.c ./execution/pipes.c ./execution/pwd.c ./execution/unset.c ./execution/redirection_exec.c

#SRC_BONUS =	checker.c get_next_line.c get_next_line_utils.c pile.c \
			operations.c to_check.c utils.c free.c
OBJECT = $(SRC:.c=.o)
#OBJECT_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

$(NAME):
	@gcc -Wall -Werror -Werror $(SRC) -o $(NAME) -lreadline -g $(LDFLAGS) $(CPPFLAGS) -fsanitize=address  
	@echo "✅✅✅"

#bonus:
#	@gcc -Wall -Wextra -Werror $(SRC_BONUS) -o $(NAME_BONUS)
#	@echo "🎁🎁🎁"

clean:
	@rm -f $(OBJECT)
	@echo "🗑️ 🗑️ 🗑️"
fclean: clean
	@rm -f $(NAME)
	@echo "🚮🚮🚮"
re: fclean all
