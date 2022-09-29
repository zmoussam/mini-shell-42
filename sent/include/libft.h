/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:58 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/20 08:07:11 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define LIBFT_WSPACES " \t\n\v\f\r"

# include <sys/types.h>
# include <stddef.h>
# include <stdbool.h>

/*
 * A struct that represents a node in a linked list.
 * A NULL pointer is considered as an empty linked list.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef void	(*t_lft_delfn)(void *);
typedef int		(*t_lft_cmpfn)(void *, void *);
typedef void	*(*t_lft_mapfn)(void *);
typedef void	(*t_lft_iterfn)(void *);
typedef bool	(*t_lft_findfn)(void *, void *);

/* Checks for an uppercase letter (A through Z). */
int			ft_isupper(int c);

/* Checks for a lowercase character (a through z). */
int			ft_islower(int c);

/*
 * Checks for an alphabetic character.
 * It is equivalent to `(ft_isupper(c) || ft_islower(c))`.
 */
int			ft_isalpha(int c);

/* Checks for a digit character (0 through 9).*/
int			ft_isdigit(int c);

/*
 * Checks for an alphanumeric character.
 * It is equivalent to `(ft_isalpha(c) || ft_isdigit(c))`.
 */
int			ft_isalnum(int c);

/* Checks for any printable character including space. */
int			ft_isprint(int c);

/*
 * Checks for white-space characters.
 * These are:
 * - space (' ')
 * - form-feed ('\f')
 * - newline ('\n')
 * - carriage return ('\r')
 * - horizontal tab ('\t')
 * - vertical tab ('\v')
 */
int			ft_isspace(int c);

/*
 * Checks whether `c` is a 7-bit unsigned char value
 * that fits into the ASCII character set.
 */
int			ft_isascii(int c);

/* Returns the uppercase equivalent of `c` or `c` itself if there's none. */
int			ft_toupper(int c);

/* Returns the lowercase equivalent of `c` or `c` itself if there's none. */
int			ft_tolower(int c);

/*
 * Computes the absolute value of `n`.
 * The absolute value of INT_MIN is not defined.
 */
int			ft_abs(int n);

/* Returns the smallest int of `a` and `b`. */
int			ft_min(int a, int b);

/* Returns the largest int of `a` and `b`. */
int			ft_max(int a, int b);

/*
 * Converts an int to its string representation.
 * Returns NULL on allocation failure.
 */
char		*ft_itoa(int n);

/*
 * Converts the initial part of the string `str` to an int.
 * The string may begin with an arbitrary amount of white space
 * followed by a single optional '+' or '-' sign.
 * The remainder of the string is converted to an int in the obvious manner,
 * stopping at the first character which is not a valid digit.
 * If an overflow occurs, INT_MAX is returned and errno is set to ERANGE.
 * If an undeflow occurs, INT_MIN is returned and errno is set to ERANGE.
 */
int			ft_atoi(const char *str);

/*
 * Converts the initial part of the string `str` to a long long.
 * The string may begin with an arbitrary amount of white space
 * followed by a single optional '+' or '-' sign.
 * The remainder of the string is converted to a long long
 * in the obvious manner,
 * stopping at the first character which is not a valid digit.
 * If an overflow occurs, LONG_LONG_MAX is returned and errno is set to ERANGE.
 * If an underflow occurs, LONG_LONG_MIN is returned and errno is set to ERANGE.
 */
long long	ft_atoll(const char *str);

/*
 * Fills the first `len` bytes of the memory area pointed to by `b`
 * with the constant byte `c`.
 * Returns `b`.
 */
void		*ft_memset(void *b, int c, size_t len);

/*
 * Allocates memory for an array of `count` elements of `size` bytes each
 * and returns a pointer to the allocated memory.
 * The memory is set to zero.
 * If `count` or  `size` is 0,
 * then ft_calloc() returns either NULL,
 * or a unique pointer value that can later be successfully passed to free()
 * Integer overflow is not handled.
 */
void		*ft_calloc(size_t count, size_t size);

/*
 * Erases the data in the `n` bytes of the memory
 * starting at the location pointed to by `s`,
 * by writing zeros to that area.
 */
void		ft_bzero(void *s, size_t n);

/*
 * Copies `n` bytes from memory area `src` to memory area `dst`.
 * The memory areas must not overlap.
 * Returns `dst`.
 */
void		*ft_memcpy(void *dst, const void *src, size_t n);

/*
 * Copies `n` bytes from memory area `src` to memory area `dst`.
 * The memory areas may overlap.
 * Returns `dst`.
 */
void		*ft_memmove(void *dst, const void *src, size_t n);

/*
 * Scans the initial `n` bytes of the memory area
 * pointed to by `s` for the first instance of `c`.
 * Both `c` and the bytes of the memory area pointed to by `s`
 * are interpreted as unsigned char.
 * Returns a pointer to the matching byte or NULL otherwise.
 */
void		*ft_memchr(const void *s, int c, size_t n);

/*
 * Returns an integer less than, equal to, or greater than zero
 * if the first `n` bytes of `s1` are found, respectively,
 * to be less than, to match, or be greater than the first `n` bytes of `s2`.
 * The memory areas are interpreted as unsigned char.
 * If `n` is zero, the return value is zero.
 */
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/*
 * Returns the number of bytes in the initial `n` bytes of `s`
 * which consist only of bytes from `accept`.
 * The NUL-byte of `accept` is not considered in the matching process.
 */
size_t		ft_memspn(const void *s, const char *accept, size_t n);

/*
 * Returns the number of bytes in the initial `n` bytes of `s`
 * which are not in the string `reject`.
 * The NUL-byte of `accept` is not considered in the matching process.
 */
size_t		ft_memcspn(const void *s, const char *accept, size_t n);

/*
 * Calculates the length of the string `s`,
 * excluding the terminating NUL-byte.
 */
size_t		ft_strlen(const char *s);

/* Same as `ft_strlen()` except that it counts at most `n` characters. */
size_t		ft_strnlen(const char *s, size_t n);

/*
 * Copies up to `size - 1` characters
 * from the NUL-terminated string `src` to `dst`,
 * NUL-terminating the result.
 * Returns the length of `src`.
 */
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

/*
 * Appends the string `src` to the end of `dst`, NUL-terminating the result.
 * Retruns the initial length of `dst` plus the length of `src`.
 * If `size` characters are traversed without finding a NUL-byte,
 * the length of `dst` is considered to be `size`,
 * and the result will not be NUL-terminated.
 */
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);

/*
 * Returns a pointer to the first occurrence of the character `c`
 * in the string `s` or NULL otherwise.
 * The terminating NUL-byte is considered part of the string.
 */
char		*ft_strchr(const char *s, int c);

/*
 * Returns a pointer to the last occurrence of the character `c`
 * in the string `s` or NULL otherwise.
 * The terminating NUL-byte is considered part of the string.
 */
char		*ft_strrchr(const char *s, int c);

/*
 * Returns the number of bytes in the initial segment of `s`
 * which consist only of bytes from `accept`.
 * The NUL-byte is not considered in the matching process.
 */
size_t		ft_strspn(const char *s, const char *accept);

/*
 * Returns the number of bytes in the initial segment of `s`
 * which are not in the string `reject`.
 * The NUL-byte is not considered in the matching process.
 */
size_t		ft_strcspn(const char *s, const char *reject);

/*
 * Compares at most `n` bytes from the two strings `s1` and `s2`.
 * It returns an integer less than, equal to, or greater than zero
 * if `s1` is found, respectively, to be less than, to match,
 * or be greater than s2.
 * If `n` is zero, the return value is zero.
 */
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/*
 * Compares bytes from the two strings `s1` and `s2`.
 * It returns an integer less than, equal to, or greater than zero
 * if `s1` is found, respectively, to be less than, to match,
 * or be greater than s2.
 */
int			ft_strcmp(const char *s1, const char *s2);

/*
 * Locates, in the string referenced by `*str`,
 * the first occurrence of any character in the string `sep`
 * (or the terminating '\0' character) and replaces it with a '\0'.
 * The location of the next character after the delimiter character
 * (or NULL, if the end of the string was reached) is stored in `*str`.
 * The original value of `*str` is returned.
 * If `*str` is initially NULL, NULL is returned.
 */
char		*ft_strsep(char **str, const char *sep);

/*
 * Finds the first occurrence of the string `needle` in the string `haystack`.
 * Return a pointer to the beginning of the located substring,
 * or NULL if the substring is not found.
 */
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

/*
 * Returns a pointer to a new string which is a duplicate of the string `s`,
 * or NULL on allocation failure.
 */
char		*ft_strdup(const char *s1);

/*
 * Returns a pointer to a new string which is a substring of `s`
 * that starts at `start` and has a maximum length of `len`,
 * or NULL on allocation failure.
 * If `start` exceeds the length of `s`
 * then start is considered to be ft_strlen(s).
 */
char		*ft_substr(char const *s, size_t start, size_t len);

/*
 * Returns a pointer to a new string that is the result of concatenating
 * `s1` and `s2`, Or NULL on allocation failure.
 */
char		*ft_strjoin(char const *s1, char const *s2);

/*
 * Removes all leading and trailing occurrences
 * of characters in the string `set` from the string `s`,
 * and returns a pointer to a new string which contains the result,
 * or NULL on allocation failure.
 * The NUL-byte is not considered in the matching process.
 */
char		*ft_strtrim(char const *s, char const *set);

/*
 * Splits `s` into an array of substrings.
 * The substrings are delimited by at least one occurence
 * of one of the characters in the `sep` set.
 * Returns a pointer to the array of substrings, or NULL on allocation failure.
 */
char		**ft_split(char const *s, char *sep);

/* Frees an array of strings.*/
void		ft_free_strarr(char **strarr);

/*
 * Returns a pointer to a new string populated with the results of calling `f`
 * on every character in `s`, or NULL on allocation failure.
 * `f` receives the index of the processed character
 * and the character itself.
 */
char		*ft_strmapi(char const *s, char (*f)(size_t, char));

/*
 * Calls `f` on each character in `s`.
 * `f` receives the index of the processed character
 * and a pointer to it.
 */
void		ft_striteri(char *s, void (*f)(size_t, char*));

/* Converts all lowercase characters to their uppercase counterpart. */
void		ft_strtoupper(char *s);

/* Converts all uppercase characters to their lowercase counterpart. */
void		ft_strtolower(char *s);

/*
 * Outputs the character `c` to the file descriptor `fd`.
 * Returns the number of bytes written or -1 on failure.
 */
ssize_t		ft_putchar_fd(char c, int fd);

/*
 * Outputs the string `s` to the file descriptor `fd`.
 * Returns the number of bytes written or -1 on failure.
 */
ssize_t		ft_putstr_fd(const char *s, int fd);

/*
 * Outputs at most `n` characters from the string `s`
 * to the file descriptor `fd`.
 * Returns the number of bytes written or -1 on failure.
 */
ssize_t		ft_putnstr_fd(const char *s, size_t n, int fd);

/*
 * Outputs the string `s` to the file descriptor `fd`,  followed by a newline.
 * Returns the number of bytes written or -1 on failure.
 */
ssize_t		ft_putendl_fd(const char *s, int fd);

/*
 * Outputs the string representation of an int to the file descriptor `fd`.
 * Returns the number of bytes written or -1 on failure.
 */
ssize_t		ft_putnbr_fd(int n, int fd);

/*
 * Creates a new `t_list` node, and returns a pointer to it
 * that can be freed using `free`.
 * The `next` member is set to NULL.
 * Returns NULL on allocation failure.
 */
t_list		*ft_lstnew(void *content);

/*
 * Adds the node `new` at the beginning of the linked list `*lst`.
 * If the linked list is empty, `*lst` is set to `new`.
 */
void		ft_lstadd_front(t_list **lst, t_list *new);

/*
 * Adds the node `new` at the end of the linked list `*lst`.
 * If the linked list is empty, `*lst` is set to `new`.
 */
void		ft_lstadd_back(t_list **lst, t_list *new);

/* Counts the number of nodes in the linked list and returns it. */
int			ft_lstsize(t_list *lst);

/* Returns the last node of the linked list. */
t_list		*ft_lstlast(t_list *lst);

/*
 * Finds the node for which `f` returns true.
 * `f` receives the current node's content and `arg`.
 * Returns NULL if no such node is found.
 */
t_list		*ft_lstfind(t_list *lst, t_lft_findfn f, void *arg);

/* Frees the node’s content using `del` then frees `lst` using `free()`. */
void		ft_lstdelone(t_list *lst, t_lft_delfn del);

/* Removes the provided node from the list `*lst` but does not free it. */
void		ft_lstremove(t_list **lst, t_list *to_remove);

/*
 * Frees the linked list's nodes and their contents using `ft_lstdelone()`
 * and sets `*lst` to NULL.
 */
void		ft_lstclear(t_list **lst, t_lft_delfn del);

/*
 * Calls `f` for each node in the linked list.
 * `f` receives a pointer to the content of the currently processed node.
 */
void		ft_lstiter(t_list *lst, t_lft_iterfn f);

/*
 * Creates a new linked list populated with
 * the results of calling `f` on each node's content.
 * `f` receives a pointer to the content of the currently processed node,
 * and returns a pointer to the new content.
 * Returns NULL on allocation failure.
 */
t_list		*ft_lstmap(t_list *lst, t_lft_mapfn f, t_lft_delfn del);

/*
 * Inserts a new node in the sorted linked list,
 * and keeps the sorted order using the comparison function `cmp`.
 */
void		ft_lstinsert_sorted(t_list **lst, t_list *new, t_lft_cmpfn cmp);
/*
 * Returns a line read from the file descriptor `fd`.
 * Returns NULL if there are no more characters to read,
 * or if an error occured.
 */
char		*get_next_line(int fd);

/*
 * This function mimics the real `printf` but is limited:
 * - Supports these specifiers: 'cspdiuxX%'
 * - Supports these flags: '-0#+ '
 * - Supports the minimum width
 * - Supports the precision
 */
int			ft_printf(const char *format, ...);

/*
 * Returns the value of the environment variable `name`
 * as a NUL-terminated string which should not be modified by the application.
 * If the variable `name` is not in the current environment, NULL is returned.
 * If `name` is a NULL pointer, points to an empty string,
 * or points to a string containing an '=' character, NULL is returned
 * and errno is set to EINVAL.
 */
char		*ft_getenv(const char *name);

#endif /* LIBFT_H */
