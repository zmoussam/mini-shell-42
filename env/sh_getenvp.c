/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getenvp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:17:02 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/24 15:04:38 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

static char	*envtostr(t_env *env)
{
	char	*tmp;
	char	*s;

	tmp = ft_strjoin(env->name, "=");
	s = NULL;
	if (tmp)
		s = ft_strjoin(tmp, env->value);
	free(tmp);
	return (s);
}

static size_t	count_exported(t_list *envlst)
{
	size_t	count;
	t_env	*env;

	count = 0;
	while (envlst)
	{
		env = envlst->content;
		if (env->value)
			count++;
		envlst = envlst->next;
	}
	return (count);
}

static char	**fill_envp(char **envp, t_list *envlst)
{
	t_env	*env;
	size_t	i;

	i = 0;
	while (envlst)
	{
		env = envlst->content;
		if (env->value)
		{
			envp[i] = envtostr(env);
			if (!envp[i])
				return (NULL);
			i++;
		}
		envlst = envlst->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**sh_getenvp(void)
{
	t_list	*lst;
	char	**envp;

	lst = g_sh_state.envlst;
	envp = malloc((count_exported(lst) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	if (fill_envp(envp, lst))
		return (envp);
	ft_free_strarr(envp);
	return (NULL);
}
