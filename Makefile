NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC 	   = Src/main.c \
			 Src/ft_split_2.c \
	  		 Src/ft_split_2_utils.c \
	  		 Src/ft_split_3.c \
	  		 Src/process_input.c \
	  		 Src/delete_spaces.c \
	  		 Src/minishell_utils.c \
	  		 Src/minishell_helper.c \
	  		 Src/process_input_utils.c \
	  		 Src/signal.c \
	  		 Src/exec.c \
	  		 Src/get_env.c \
	  		 Src/exec_utils.c \
			 Src/exec_utils_helper.c \
			 Src/exec_utils_helper_2.c \
			 Src/exec_utils_helper3.c \
			 Src/exec_heredoc_utils.c \
	  		 Src/handle_pipes.c \
	  		 Src/handle_pipes_utils.c \
			 Src/handle_pipes_helper.c \
	  		 Src/sort.c \
			 Src/exit_status.c \
			 Src/heredoc.c \
			 Src/heredoc_helper.c \
			 Src/append.c \
			 Src/dolar.c \
			 Src/dolar_helper.c \
			 Src/dolar_helper2.c \
			 Src/norm1.c \
			 Src/norm2.c \
			 Src/norm3.c \
			 Src/norm4.c \
			 Src/norm5.c \
			 Src/norm6.c \
			 Src/norm7.c \
			 Src/norm8.c \
			 Src/norm9.c \
			 Src/redirection_output.c \
			 Src/redirection_input.c \
			 Src/remove_quote.c \
	  		 Src/Builtins/chdir.c \
	  		 Src/Builtins/chdir_utils.c \
	  		 Src/Builtins/echo.c \
	  		 Src/Builtins/env.c \
	  		 Src/Builtins/exit.c \
	  		 Src/Builtins/pwd.c \
	  		 Src/Builtins/export2.c \
	  		 Src/Builtins/export.c \
	  		 Src/Builtins/export_helper.c \
	  		 Src/Builtins/Builtins_helper.c \
			 Src/Builtins/Builtins_helper2.c \
			 Src/Builtins/Builtins_helper3.c \
			 Src/Builtins/unset_helper.c \
			 Src/Builtins/unset.c \

OBJ = $(SRC:.c=.o)
INCLUDE = -Iinclude
LIBFT = ./libft/libft.a
LIBS = -lreadline -ltermcap

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ) $(LIBS) $(LIBFT) $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@ $(INCLUDE)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
