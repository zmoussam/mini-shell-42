/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 20:54:40 by syakoubi          #+#    #+#             */
/*   Updated: 2022/10/02 17:25:57 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stddef.h>

void	ft_free_strarr(char **strarr)
{
	size_t	i;

	if (strarr)
	{
		i = 0;
		while (strarr[i])
			free(strarr[i++]);
		free(strarr);
	}
}
