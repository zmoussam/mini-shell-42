DEBUG=0
BUFFER_SIZE=4096
CC := cc
INCLUDES := -I ../include
CFLAGS := $(INCLUDES) -Wall -Wextra -Werror -MMD$(shell [ "$(DEBUG)" = "1" ] && echo " -g")
NAME := libft.a
SRCS := ft_isupper.c\
ft_islower.c\
ft_isalpha.c\
ft_isdigit.c\
ft_isalnum.c\
ft_isprint.c\
ft_isspace.c\
ft_isascii.c\
ft_toupper.c\
ft_tolower.c\
ft_abs.c\
ft_min.c\
ft_max.c\
ft_itoa.c\
ft_atoi.c\
ft_atoll.c\
ft_memset.c\
ft_calloc.c\
ft_bzero.c\
ft_memcpy.c\
ft_memmove.c\
ft_memchr.c\
ft_memcmp.c\
ft_memspn.c\
ft_memcspn.c\
ft_strlen.c\
ft_strnlen.c\
ft_strlcpy.c\
ft_strlcat.c\
ft_strchr.c\
ft_strrchr.c\
ft_strspn.c\
ft_strcspn.c\
ft_strsep.c\
ft_strncmp.c\
ft_strcmp.c\
ft_strnstr.c\
ft_strdup.c\
ft_substr.c\
ft_strjoin.c\
ft_strtrim.c\
ft_split.c\
ft_free_strarr.c\
ft_strmapi.c\
ft_striteri.c\
ft_strtoupper.c\
ft_strtolower.c\
ft_putchar_fd.c\
ft_putstr_fd.c\
ft_putnstr_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_lstnew.c\
ft_lstadd_front.c\
ft_lstadd_back.c\
ft_lstsize.c\
ft_lstlast.c\
ft_lstfind.c\
ft_lstdelone.c\
ft_lstremove.c\
ft_lstclear.c\
ft_lstiter.c\
ft_lstmap.c\
ft_lstinsert_sorted.c\
ft_getenv.c\
ft_printf/ft_printf.c\
ft_printf/parsers.c\
ft_printf/common.c\
ft_printf/get_handler.c\
ft_printf/handle_char.c\
ft_printf/handle_decimal.c\
ft_printf/handle_hex.c\
ft_printf/handle_percent.c\
ft_printf/handle_pointer.c\
ft_printf/handle_string.c\
ft_printf/handle_unsigned.c\
gnl/gnl.c\
gnl/file.c\
gnl/file_list.c\


OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

.PHONY: all re clean fclean

all: $(NAME)

clean:
	rm -f $(OBJS) $(DEPS)
fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJS)
	ar cr $(NAME) $(OBJS)

gnl/%.o: gnl/%.c
	$(CC) $(CFLAGS) -c -D BUFFER_SIZE=$(BUFFER_SIZE) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(DEPS)
