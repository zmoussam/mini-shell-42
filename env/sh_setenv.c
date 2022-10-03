/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:41:38 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/20 08:35:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "libft.h"
#include <errno.h>
#include <stdbool.h>

static int	add_env(const char *name, const char *value)
{
	t_env	*env;
	t_list	*new;

	env = env_init(name, value);
	new = ft_lstnew(env);
	if (!env || !new)
	{
		env_destroy(env);
		ft_lstdelone(new, NULL);
		return (-1);
	}
	ft_lstinsert_sorted(&g_sh_state.envlst, new, (t_lft_cmpfn)env_cmp);
	return (0);
}

static bool	has_name(void *content, void *name)
{
	t_env	*env;

	env = content;
	return (!ft_strcmp(env->name, name));
}

int	sh_setenv(const char *name, const char *value)
{
	t_list	*node;

	if (!name || !*name || ft_strchr(name, '='))
	{
		errno = EINVAL;
		return (-1);
	}
	node = ft_lstfind(g_sh_state.envlst, has_name, (void *)name);
	if (node)
		return (env_update(node->content, value));
	return (add_env(name, value));
}
