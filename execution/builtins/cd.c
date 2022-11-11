/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:26:54 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/11 18:02:28 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <unistd.h>

void	go_to_newpath(char **oldpwd, char *path, char **pwd)
{
	char	*tmp_cwd;

	tmp_cwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
		return (printf("minishell: cd: %s:%s\n", path, \
			strerror(errno)), free(tmp_cwd));
	else
	{
		if (oldpwd == NULL)
			add_back(&g_lbv.list, new_node(tmp_cwd, ft_strdup("OLDPWD"), 6));
		else
		{
			free(*oldpwd);
			*oldpwd = tmp_cwd;
		}
		if (pwd)
		{
			free(*pwd);
			*pwd = getcwd(NULL, 0);
		}
	}
}

void	go_to_oldpath(char **oldpwd, char **pwd)
{
	char	*tmp_cwd;

	tmp_cwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (printf("minishell: cd: OLDPWD not set\n"), free(tmp_cwd));
	else
	{
		if (chdir(*oldpwd) == -1)
			return (printf("minishell: cd: %s:%s\n", tmp_cwd, \
				strerror(errno)), free(tmp_cwd));
		else
		{
			printf("%s\n", tmp_cwd);
			free(*oldpwd);
			*oldpwd = tmp_cwd;
		}
		if (pwd)
		{
			free(*pwd);
			*pwd = getcwd(NULL, 0);
		}
	}
}

void	go_to_home(char **oldpwd, char **pwd)
{
	char		*tmp_old;
	char		*home;
	t_env_node	*tmp_env_home;

	home = NULL;
	tmp_env_home = env_find(g_lbv.list, "HOME", 4);
	if (tmp_env_home)
		home = tmp_env_home->content;
	tmp_old = getcwd(NULL, 0);
	if (home)
	{
		if (chdir(home) == -1)
			return (printf("minishell: cd: %s:%s\n", home, \
				strerror(errno)), free(tmp_old));
		else if (oldpwd == NULL)
			add_back(&g_lbv.list, new_node(tmp_old, ft_strdup("OLDPWD"), 6));
		else
		{
			free(*oldpwd);
			*oldpwd = tmp_old;
		}
		if (pwd)
		{
			free(*pwd);
			*pwd = getcwd(NULL, 0);
		}
	}
	else
		printf("minishell: cd: HOME not set\n");
}

void	cd(t_parser_node *root)
{
	char		**oldpwd;
	t_env_node	*tmp_env_oldpwd;
	t_env_node	*tmp_env_pwd;
	char		**pwd;

	oldpwd = NULL;
	pwd = NULL;
	tmp_env_oldpwd = env_find(g_lbv.list, "OLDPWD", 6);
	if (tmp_env_oldpwd)
		oldpwd = &(tmp_env_oldpwd->content);
	tmp_env_pwd = env_find(g_lbv.list, "PWD", 3);
	if (tmp_env_pwd)
		pwd = &(tmp_env_pwd->content);
	if (root->ac == 1 || ft_strcmp(root->av[1], "~" ) == 0 \
	|| ft_strcmp(root->av[1], "--" ) == 0)
		go_to_home(oldpwd, pwd);
	else if (root->ac > 1)
	{
		if (ft_strcmp(root->av[1], "-") == 0)
			go_to_oldpath(oldpwd, pwd);
		else
			go_to_newpath(oldpwd, root->av[1], pwd);
	}
}
