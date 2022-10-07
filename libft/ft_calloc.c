/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:53 by syakoubi          #+#    #+#             */
/*   Updated: 2021/12/26 11:42:02 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*b;

	b = malloc(count * size);
	if (b)
		return (ft_memset(b, 0, count * size));
	return (b);
}
