DEBUG := 0
CC := cc
INCLUDES := -I include -I$(HOME)/.homebrew/opt/readline/include
CFLAGS := $(INCLUDES) -Wall -Wextra -Werror -MMD $(shell [ "$(DEBUG)" = "1" ] && echo " -g")
LDFLAGS := -L$(HOME)/.homebrew/opt/readline/lib -lreadline
NAME := minishell
SRC := env/env_cmp.c\
env/env_destroy.c\
env/env_init.c\
env/env_update.c\
env/sh_getenv.c\
env/sh_getenvn.c\
env/sh_getenvp.c\
env/sh_setenv.c\
env/sh_unsetenv.c\
lexer/lexer_advance.c\
lexer/lexer_eat.c\
lexer/lexer_eat_string.c\
lexer/lexer_init.c\
lexer/lexer_next.c\
lexer/lexer_peek.c\
lexer/lexer_perror.c\
lexer/lexer_skip_spaces.c\
lexer/token_init.c\
main.c\
parser/expand_glob.c\
parser/expand_params.c\
parser/node_destroy.c\
parser/node_init.c\
parser/node_tree_destroy.c\
parser/parse.c\
parser/parse_cmd.c\
parser/parse_cmd_elem.c\
parser/parse_line.c\
parser/parse_pipe.c\
parser/parse_pipeline.c\
parser/parse_rdr.c\
parser/print_syntax_error.c\
parser/rdr_destroy.c\
parser/rdr_init.c\
utils/encode_quotes.c\
utils/glob_match_enc.c\
utils/is_glob_enc.c\
utils/lst_to_strarr.c\
utils/remove_quotes.c\
utils/remove_quotes_enc.c\
utils/switch_quote_mode.c\
utils/switch_quote_mode_enc.c\
builtins/echo.c\
builtins/env/create_env.c\
builtins/env/env_find.c\
builtins/env/env.c\
builtins/cd.c\


OBJ := $(SRC:.c=.o)
DEP := $(SRC:.c=.d)

.PHONY: all re clean fclean bonus

all: $(NAME)

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJ) $(DEP)

fclean:
	$(MAKE) -C libft fclean
	rm -f libft.a
	rm -rf $(NAME) $(OBJ) $(DEP)

re: fclean all

libft.a:
	$(MAKE) -C libft
	mv libft/libft.a .

$(NAME): libft.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) libft.a $(LDFLAGS)

-include $(DEP)
