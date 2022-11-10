NAME = libft.a

SRCS = ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c\
ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_atoi.c ft_itoa.c ft_putendl_fd.c\
ft_strlcpy.c ft_tolower.c ft_bzero.c ft_putnbr_fd.c ft_strlen.c ft_strchr_ex.c\
ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c\
ft_memcmp.c ft_strncmp.c ft_isalpha.c ft_split.c ft_memcpy.c ft_strchr.c\
ft_strnstr.c ft_isascii.c ft_striteri.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_strcmp.c ft_putnstr.c\

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c  ft_lstadd_back.c\
 		ft_lstdelone.c ft_lstclear.c ft_lstiter.c\

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${BONUS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -g -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS} bonus
		ar rcs ${NAME} ${OBJS}

bonus : $(OBJSBONUS)
	ar rcs $(NAME) $(OBJS) $(OBJSBONUS)

all:	${NAME} bonus


clean:
		${RM} ${OBJS} ${OBJSBONUS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY = all clean fclean re 