/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getenvn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:40:59 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 13:14:55 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "shell.h"
#include "libft.h"
#include <errno.h>

char	*sh_getenvn(const char *name, size_t n)
{
	t_list	*lst;
	t_env	*env;

	if (name)
		n = ft_strnlen(name, n);
	if (!name || !n || ft_memchr(name, '=', n))
	{
		errno = EINVAL;
		return (NULL);
	}
	lst = g_sh_state.envlst;
	while (lst)
	{
		env = lst->content;
		if (!ft_strncmp(env->name, name, n) && env->name[n] == '\0')
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}
