/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:56 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/06 21:08:45 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

static char	*ft_token(const char **s, char *sep)
{
	size_t		len;
	char		*token;

	*s += ft_strspn(*s, sep);
	if (**s == '\0')
		return (NULL);
	len = ft_strcspn(*s, sep);
	token = ft_substr(*s, 0, len);
	if (token)
		*s += len;
	return (token);
}

static size_t	ft_tokenc(const char *s, char *sep)
{
	size_t		count;

	count = 0;
	s += ft_strspn(s, sep);
	while (*s)
	{
		count++;
		s += ft_strcspn(s, sep);
		s += ft_strspn(s, sep);
	}
	return (count);
}

char	**ft_split(char const *s, char *sep)
{
	size_t	i;
	size_t	tokenc;
	char	**tokens;

	tokenc = ft_tokenc(s, sep);
	tokens = malloc(sizeof(char *) * (tokenc + 1));
	if (tokens == NULL)
		return (NULL);
	i = 0;
	tokens[i] = ft_token(&s, sep);
	while (tokens[i])
		tokens[++i] = ft_token(&s, sep);
	if (*s == '\0')
		return (tokens);
	ft_free_strarr(tokens);
	return (NULL);
}
