# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 19:25:54 by zmoussam          #+#    #+#              #
#    Updated: 2022/09/27 19:28:09 by zmoussam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
flags = -readline -Wall -Wextra -Werror

all: $(NAME)

clean:

fclean: clean

re: