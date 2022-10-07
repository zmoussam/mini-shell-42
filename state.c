/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 00:29:24 by syakoubi          #+#    #+#             */
/*   Updated: 2022/10/03 22:33:48 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "env.h"
#include <stdio.h>
#include <stdlib.h>

t_sh_state	g_sh_state;

static int	add_entry(char *entry)
{
	char	*name;
	char	*value;
	t_env	*env;
	t_list	*new;

	name = ft_strsep(&entry, "=");
	value = entry;
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

static int	create_envlst(char **envp)
{
	while (*envp)
	{
		if (add_entry(*envp))
			return (-1);
		envp++;
	}
	return (0);
}

static int	increment_shlvl(void)
{
	char	*shlvl;

	shlvl = sh_getenv("SHLVL");
	if (shlvl)
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		if (!shlvl || sh_setenv("SHLVL", shlvl))
		{
			free(shlvl);
			return (-1);
		}
		free(shlvl);
	}
	else if (sh_setenv("SHLVL", "1"))
		return (-1);
	return (0);
}

int	sh_state_init(int argc, char **argv, char **envp)
{
	(void)argc;
	g_sh_state.exit_status = 0;
	g_sh_state.envlst = NULL;
	if (create_envlst(envp) || increment_shlvl() || sh_setenv("SHELL", argv[0]))
	{
		perror(SH_NAME);
		sh_state_destroy();
		return (-1);
	}
	return (0);
}

void	sh_state_destroy(void)
{
	ft_lstclear(&g_sh_state.envlst, (t_lft_delfn)env_destroy);
}
