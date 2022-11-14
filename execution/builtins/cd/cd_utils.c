/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 23:25:01 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/13 22:59:18 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	set_pwd(char **pwd)
{
	if (pwd)
	{
		free(*pwd);
		*pwd = getcwd(NULL, 0);
	}
}

void	set_oldpwd(char **oldpwd, char *new_oldpwd, int msg)
{
	if (msg)
		printf("%s\n", *oldpwd);
	free(*oldpwd);
	*oldpwd = new_oldpwd;
}

void	go_to_oldpath(char **oldpwd, char **pwd)
{
	char	*tmp_cwd;

	tmp_cwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		g_lbv.exit_status = 256;
		return (printf("minishell: cd: OLDPWD not set\n"), free(tmp_cwd));
	}
	else
	{
		if (chdir(*oldpwd) == -1)
		{
			g_lbv.exit_status = 256;
			return (printf("minishell: cd: %s:%s\n", tmp_cwd, \
				strerror(errno)), free(tmp_cwd));
		}
		else
			set_oldpwd(oldpwd, tmp_cwd, 1);
		set_pwd(pwd);
		g_lbv.exit_status = 0;
	}
}

void	go_to_home(char **oldpwd, char **pwd, t_env_node *tmp_home, char *old_d)
{
	char		*home;

	home = NULL;
	if (tmp_home)
		home = tmp_home->content;
	if (home)
	{
		if (chdir(home) == -1)
		{
			g_lbv.exit_status = 256;
			return (printf("minishell: cd: %s:%s\n", home, \
				strerror(errno)), free(old_d));
		}
		else if (oldpwd == NULL)
			add_back(&g_lbv.list, new_node(old_d, ft_strdup("OLDPWD"), 6));
		else
			set_oldpwd(oldpwd, old_d, 0);
		set_pwd(pwd);
		g_lbv.exit_status = 0;
	}
	else
	{
		g_lbv.exit_status = 256;
		return (printf("minishell: cd: HOME not set\n"), free(old_d));
	}
}
