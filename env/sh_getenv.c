/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:39:46 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/24 15:53:53 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "shell.h"
#include "libft.h"
#include <errno.h>

char	*sh_getenv(const char *name)
{
	t_list	*lst;
	t_env	*env;

	if (!name || !*name || ft_strchr(name, '='))
	{
		errno = EINVAL;
		return (NULL);
	}
	lst = g_sh_state.envlst;
	while (lst)
	{
		env = lst->content;
		if (!ft_strcmp(env->name, name))
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}
