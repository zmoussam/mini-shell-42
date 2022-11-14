# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 11:32:30 by mel-hous          #+#    #+#              #
#    Updated: 2022/11/14 13:20:26 by mel-hous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -I$(HOME)/.brew/opt/readline/include  -Wall -Wextra -Werror -MMD -g
LDFLAGS := -L$(HOME)/.brew/opt/readline/lib  -lreadline 
NAME := minishell
SRC =	env1/create_env.c\
		env1/env_find.c\
		env1/env_ld.c\
	    lexer/change_mode.c\
		lexer/ft_exp.c\
		lexer/ft_expand_var.c\
		lexer/ft_expand_wldc.c\
		lexer/get_next_token.c\
		lexer/get_token.c\
		lexer/initialisation.c\
		lexer/is_match.c\
		lexer/lex_search.c\
		lexer/quote_def.c\
		lexer/wc_ld_create.c\
		utils/utils.c\
		utils/cmd_list.c\
		utils/remove_q.c\
		utils/put_line.c\
		utils/wc_ld.c\
		utils/ft_clear_av.c\
		parsing/av_creat.c\
		parsing/check_pipe.c\
		parsing/cmd_components.c\
		parsing/collect_cmd.c\
		parsing/collect_rdr.c\
		parsing/ft_pipe_line.c\
		parsing/node_creat.c\
		parsing/node_del.c\
		parsing/parse_input.c\
		parsing/parser_start.c\
		parsing/rdr_addback.c\
		parsing/print_error.c\
		execution/execution_utils.c\
		execution/execution_utils2.c\
		execution/execution.c\
		execution/builtins/cd/cd.c\
		execution/builtins/cd/cd_utils.c\
		execution/builtins/echo.c\
		execution/builtins/env.c\
		execution/builtins/exit.c\
		execution/builtins/export/export.c\
		execution/builtins/export/export_utils.c\
		execution/builtins/export/export_parsing.c\
		execution/builtins/pwd.c\
		execution/builtins/unset.c\
		redirection/redirection.c\
		redirection/heredoc.c\
		redirection/rdr_input.c\
		redirection/rdr_output.c\
		main.c\

OBJ := $(SRC:.c=.o)
DEP := $(SRC:.c=.d)

.PHONY: all re clean fclean bonus

all: $(NAME)

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJ) $(DEP)

fclean:
	$(MAKE) -C libft fclean
	rm -rf $(NAME) $(OBJ) $(DEP)

re: fclean all

libft.a:
	$(MAKE) -C libft

$(NAME): libft.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) libft/libft.a $(LDFLAGS)

-include $(DEP)