NAME = minishell

# Compile
CC = clang
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
LIBFLAG = -lreadline
INC = -I$(INC_DIR)
HEADER = $(INC_DIR)/minishell.h

# Location
SRC_DIR = src
INC_DIR = inc

# Source files
MAIN = main.c 
WRITE = write.c write_perror.c ft_putstr_fd.c
AST = tree.c redirection_exception.c add_litteral.c add_operator.c \
	set_ds_for_redirection_exception.c
BUILTINS = cd.c echo.c env.c export.c pwd.c unset.c exit.c is_builtin.c \
	is_export.c
EXEC = exec.c redirection_exec.c pipeline_exec.c litteral_exec.c files_open.c \
	access_command.c wait_n_close.c delimeter_exec.c dup.c \
	delimeter_write_n_read.c wait_delimiter_fork.c	
FT_LST = ft_lstadd_back.c ft_lstadd_front.c ft_lstdel.c ft_lst_delone.c \
		 ft_lstlast.c ft_lstnew.c ft_lst_find.c
FT_STR = ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_strncmp.c ft_nb_str.c ft_split.c ft_substr.c \
		ft_itoa.c ft_atoi.c ft_is_alpha.c
FT_BTREE = del_btree.c new_btree.c
LEXER = lexer.c regroup_token.c is_operator.c is_redirection.c is_pipe.c \
		is_isspace.c is_delimeter.c reverse_order_pipe_lexer.c \
		token_man_set.c delete_isspaces_token.c is_quote.c
PARSING = parsing.c pars_operator.c pars_quotes.c pars_whats_follows_operator.c \
		pars_special_case.c
ERRORS = error.c free.c free_str.c close_redirections.c
VAR = recup_env.c treat_var.c operations_var.c set_env.c modify_existed_var.c
INIT = init.c init_pipe.c init_first.c init_delimiter.c
SIGNAL = signal.c
SRC = $(addprefix src/, $(MAIN)) \
	  $(addprefix src/ast/, $(AST)) \
	  $(addprefix src/ft_lst/, $(FT_LST)) \
	  $(addprefix src/ft_str/, $(FT_STR)) \
	  $(addprefix src/ft_btree/, $(FT_BTREE)) \
	  $(addprefix src/lexer/, $(LEXER)) \
	  $(addprefix src/parsing/, $(PARSING)) \
	  $(addprefix src/var/, $(VAR)) \
	  $(addprefix src/write/, $(WRITE)) \
	  $(addprefix src/errors/, $(ERRORS)) \
	  $(addprefix src/exec/, $(EXEC)) \
	  $(addprefix src/init/, $(INIT)) \
	  $(addprefix src/signal/, $(SIGNAL)) \
	  $(addprefix src/builtins/, $(BUILTINS))

# Object files
OBJ = $(SRC:.c=.o)

# Patern rule 
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c ${HEADER}
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ) $(LIBFLAG)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
