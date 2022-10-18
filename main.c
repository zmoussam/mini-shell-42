
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:23:22 by syakoubi          #+#    #+#             */
/*   Updated: 2022/10/04 20:06:58 by zmoussam         ###   ########.fr       */
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
#include<sys/wait.h>

t_sh_state	g_sh_state = {0};
t_env_node *env_list;

int	check_path(char *path)
{
	int	i;

	i = 0;
	while(path[i])
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
void	launch_executabl(t_node *root)
{
	int pid;
	int	i;
	char **path_content;
	char *tmp_path;
	char *tmp2_path;
	char **args;

	args = (char **)malloc(sizeof(char *) * root->argc + 1);

	if (check_path(root->argv[0]))
	{
		if (!access(root->argv[0], X_OK))
		{
			pid = fork();
			if (pid == 0)
				execve(root->argv[0],root->argv ,NULL);
			else 
				wait(NULL);
		}
		else 
			printf("bash: %s: No such file or directory\n", root->argv[0]);
	}
	else
	{
		if (env_find(env_list, "PATH", 4))
		{
			path_content = ft_split(env_find(env_list , "PATH", 4)->content, ":");
			i = 0;
			while (path_content[i])
			{
				tmp2_path = ft_strjoin("/", root->argv[0]);
				tmp_path = ft_strjoin(path_content[i], tmp2_path);
				free(tmp2_path);
				if (!access(tmp_path, X_OK))
				{
					pid = fork();
					if (pid == 0)
					{
						args[0] = tmp_path;
						i = 1;
						while (root->argv[i])
						{
							args[i] = root->argv[i];
							i++;
						}
						args[i] = NULL;
						execve(tmp_path, args ,NULL);
					}
					else
						wait(NULL);
				}
				free(tmp_path);
				//free path_content!!
				i++;
			}
		}
		else 
			printf("bash: %s: No such file or directory\n", root->argv[0]);
	}
}
void    execution_cmd(t_node *root)
{
	char	*copy;

	copy = ft_strdup(root->argv[0]);
	ft_strtolower(copy);
    if (ft_strcmp(copy, "echo") == 0)
        echo(root);
   else if (ft_strcmp(copy, "env") == 0)
        env_cmd(root->argc);
	else if (ft_strcmp(root->argv[0], "cd") == 0)
		cd(root);
	else if (ft_strcmp(copy, "pwd") == 0)
		pwd(root);
	else if (ft_strcmp(root->argv[0], "unset") == 0)
		unset(root);
	else if (ft_strcmp(root->argv[0], "exit") == 0)
		exit_cmd();
	else if (ft_strcmp(root->argv[0], "export") == 0)
		export(root);
	else
		launch_executabl(root); 
}

void    execution(t_node *root)
{
	// int	fd1[2];
	// int	pid;

	// if (pipe(fd) == -1)
    //     return ;
    // if (root == NULL){
    //     return;
    // }
    // if (root->type == PIPE)
    // {
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{	
	// 		dup2(fd1[1], STDOUT_FILENO);
	// 		execution(root->left, fd1[1]);
	// 		exit(1);
	// 	}
	// 	else
    //     execution(root->right, fd1[0]);   
    //     // execution(root->left);
    // }
    // else
        execution_cmd(root);
}


char	*get_wd(char *path)
{
	char	*working_directory;
	char	*cwd;
	char	*dup;

	working_directory = ft_strrchr(path, '/');
	if (working_directory[1] == '\0')
	{
		cwd = ft_strjoin(working_directory, "\033[0;31m :: \033[0;37m");
		free(path);
		return (cwd);
	}
	else
	{
		dup = ft_strdup(working_directory + 1);
		cwd = ft_strjoin(dup, "\033[0;31m :: \033[0;37m");
		free(dup);
		free(path);
		return (cwd);
	}	
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_node	*tree;

	char		*prompt;
	(void)argc;
	(void)argv;
	
	prompt = get_wd(getcwd(NULL, 0));
	env_list = create_env(env);

	if (sh_state_init(argc, argv, env))
		return (1);	
	ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
	printf("\033[0;33m➜  \033[0;36m");	
	line = readline(prompt);
	free(prompt);
	while (line)
	{
		if (ft_strspn(line, " \n\t") < ft_strlen(line))
			add_history(line);
		tree = parse(line);
		// printf("left = %s\n", tree->right->right->argv[0]);
		execution(tree);

		node_tree_clear(&tree);
		free(line);
		printf("\033[0;33m➜  \033[0;36m");
		prompt = get_wd(getcwd(NULL, 0));
		line = readline(prompt);
		free(prompt);
	}
}