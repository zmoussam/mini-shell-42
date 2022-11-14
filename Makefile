# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 11:32:30 by mel-hous          #+#    #+#              #
#    Updated: 2022/11/14 14:58:34 by mel-hous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -I$(HOME)/.brew/opt/readline/include  -Wall -Wextra -Werror -MMD 
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
		libft/ft_isdigit.c libft/ft_memset.c\
		libft/ft_strjoin.c libft/ft_strtrim.c\
		libft/ft_isprint.c\
		libft/ft_putchar_fd.c libft/ft_strlcat.c\
		libft/ft_substr.c libft/ft_atoi.c\
		libft/ft_itoa.c libft/ft_putendl_fd.c\
		libft/ft_strlcpy.c libft/ft_tolower.c\
		libft/ft_bzero.c libft/ft_putnbr_fd.c\
		libft/ft_strlen.c libft/ft_strchr_ex.c\
		libft/ft_toupper.c libft/ft_calloc.c\
		libft/ft_memchr.c libft/ft_putstr_fd.c\
		libft/ft_strmapi.c libft/ft_isalnum.c\
		libft/ft_memcmp.c libft/ft_strncmp.c\
		libft/ft_isalpha.c libft/ft_split.c\
		libft/ft_memcpy.c libft/ft_strchr.c\
		libft/str_tolower.c\
		libft/ft_strnstr.c libft/ft_isascii.c\
		libft/ft_striteri.c libft/ft_memmove.c\
		libft/ft_strdup.c libft/ft_strrchr.c\
		libft/ft_strcmp.c libft/ft_putnstr.c\

OBJ := $(SRC:.c=.o)
DEP := $(SRC:.c=.d)

.PHONY: all re clean fclean bonus

all: $(NAME)

clean:
	rm -rf $(OBJ) $(DEP)

fclean:
	rm -rf $(NAME) $(OBJ) $(DEP)

re: fclean all

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

-include $(DEP)