/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:23:22 by syakoubi          #+#    #+#             */
/*   Updated: 2022/10/03 02:17:47 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "shell.h"
#include "./include/builtins.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/signal.h>

void    execution_cmd(t_node *root, t_env_node *env)
{
    if (ft_strcmp(root->argv[0], "echo") == 0)
        echo(root);
    if (ft_strcmp(root->argv[0], "env") == 0)
        env_cmd(env, root->argc);
	if (ft_strcmp(root->argv[0], "cd") == 0)
		cd(root, env);
	
}

void    execution(t_node *root, t_env_node *env){
    if (root == NULL){
        return;
    }
    if (root->type == PIPE)
    {
        execution(root->left, env);
        execution(root->right, env);   
    }
    else
        execution_cmd(root, env);
}
t_sh_state	g_sh_state = {0};

char	*get_wd(char *path)
{
	char	*working_directory;
	char	*cwd;
	char	*dup;
	working_directory = ft_strrchr(path, '/');
	if (working_directory[1] == '\0')
	{
		cwd = ft_strjoin(working_directory, " :: ");
		free(path);
		return (cwd);
	}
	else
	{
		dup = ft_strdup(working_directory + 1);
		cwd = ft_strjoin(dup, " :: ");
		free(dup);
		free(path);
		return (cwd);
	}	
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_node	*tree;
	t_env_node  *env_list;
	char		*prompt;
	(void)argc;
	(void)argv;
	// get the prompt like name of the workin directory
	prompt = get_wd(getcwd(NULL, 0));
	// set the env in linked list 
	env_list = create_env(env);
	// remove the OLDPWD
	ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
	// get CMDS
	line = readline(prompt);
	free(prompt);
	while (line)
	{
		if (ft_strspn(line, " \n\t") < ft_strlen(line))
			add_history(line);
		tree = parse(line);
		execution(tree, env_list);
		node_tree_clear(&tree);
		free(line);
		prompt = get_wd(getcwd(NULL, 0));
		line = readline(prompt);
		free(prompt);
	}
}
