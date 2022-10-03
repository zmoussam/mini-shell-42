/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:39:46 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/20 08:35:03 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "libft.h"
#include <errno.h>
#include <stdbool.h>

static bool	has_name(void *content, void *name)
{
	t_env	*env;

	env = content;
	return (!ft_strcmp(env->name, name));
}

int	sh_unsetenv(const char *name)
{
	t_list	*node;

	if (!name || !*name || ft_strchr(name, '='))
	{
		errno = EINVAL;
		return (-1);
	}
	node = ft_lstfind(g_sh_state.envlst, has_name, (void *)name);
	if (node)
	{
		ft_lstremove(&g_sh_state.envlst, node);
		ft_lstdelone(node, (t_lft_delfn)env_destroy);
	}
	return (0);
}
