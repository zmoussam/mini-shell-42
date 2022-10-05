/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_strarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:26:44 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/01 00:33:02 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

char	**lst_to_strarr(t_list *lst)
{
	size_t	size;
	size_t	i;
	char	**strarr;

	size = ft_lstsize(lst);
	strarr = malloc((size + 1) * sizeof(char *));
	if (strarr)
	{
		i = 0;
		while (lst)
		{
			strarr[i] = ft_strdup(lst->content);
			if (!strarr[i])
			{
				ft_free_strarr(strarr);
				return (NULL);
			}
			i++;
			lst = lst->next;
		}
		strarr[i] = NULL;
	}
	return (strarr);
}
