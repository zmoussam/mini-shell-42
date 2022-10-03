/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:26:24 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/20 08:07:58 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, t_lft_findfn f, void *arg)
{
	while (lst)
	{
		if (f(lst->content, arg))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
