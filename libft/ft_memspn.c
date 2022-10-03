/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:01:37 by syakoubi          #+#    #+#             */
/*   Updated: 2022/01/04 02:05:27 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_memspn(const void *s, const char *accept, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ft_strchr(accept, ((char *)s)[i]))
		i++;
	return (i);
}
