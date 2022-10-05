
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



void    execution_cmd(t_node *root, t_env_node *env, t_env_node *export_list)
{
	int i;
	
	i = 0;
	if (ft_strcmp(root->argv[0], "CD") && ft_strcmp(root->argv[0], "UNSET") && 
		ft_strcmp(root->argv[0], "EXPORT"))
		ft_strtolower(root->argv[0]);
    if (ft_strcmp(root->argv[0], "echo") == 0)
        echo(root);
    if (ft_strcmp(root->argv[0], "env") == 0)
        env_cmd(env, root->argc);
	if (ft_strcmp(root->argv[0], "cd") == 0)
		cd(root, env);
	if (ft_strcmp(root->argv[0], "pwd") == 0)
		pwd(root);
	if (ft_strcmp(root->argv[0], "unset") == 0)
		unset(root, env);
	if (ft_strcmp(root->argv[0], "exit") == 0)
		exit_cmd();
	if (ft_strcmp(root->argv[0], "export") == 0)
		export(root, export_list);
}

void    execution(t_node *root, t_env_node *env, t_env_node *export){
    if (root == NULL){
        return;
    }
    if (root->type == PIPE)
    {
        execution(root->left, env, export);
        execution(root->right, env, export);   
    }
    else
        execution_cmd(root, env, export);
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

void	print_node_argv(t_node *node)
{
	char	**argv = node->argv;

	while (argv && *argv)
		printf("%s\n", *argv++);
}
void	sort_export_list(t_env_node *export_list)
{
	t_env_node *head;

	char *tmp_content;
	char *tmp_name;

	head = export_list;

	while (export_list && export_list->next)
	{
		if (ft_strcmp(export_list->name, export_list->next->name) > 0)
		{
			tmp_content = export_list->content;
			tmp_name = export_list->name;
			export_list->content = export_list->next->content;
			export_list->name = export_list->next->name;
			export_list->next->content = tmp_content;
			export_list->next->name = tmp_name;
			export_list = head;
		}
		else
		export_list = export_list->next;
	}
}
int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_node	*tree;
	t_env_node  *export_list;
	t_env_node  *env_list;
	char		*prompt;
	(void)argc;
	(void)argv;
	// get the prompt like name of the workin directory
	prompt = get_wd(getcwd(NULL, 0));
	// set the env in linked list 
	env_list = create_env(env);
	export_list = create_env(env);
	sort_export_list(export_list);
	// printf("hi\n");
	// print_list(export_list);
	if (sh_state_init(argc, argv, env))
		return (1);	
	// remove the OLDPWD
	ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
	// get CMDS
	printf("\033[0;33m➜  \033[0;36m");
	line = readline(prompt);
	free(prompt);
	while (line)
	{
		if (ft_strspn(line, " \n\t") < ft_strlen(line))
			add_history(line);
		tree = parse(line);
		// print_node_argv(tree);
		execution(tree, env_list, export_list);
		node_tree_clear(&tree);
		free(line);
		printf("\033[0;33m➜  \033[0;36m");
		prompt = get_wd(getcwd(NULL, 0));
		line = readline(prompt);
		free(prompt);
	}
}
// void	print_node_argv(t_node *node)
// {
// 	char	**argv = node->argv;

// 	while (argv && *argv)
// 		printf("%s\n", *argv++);
// }

// int main(int argc, char **argv, char **envp)
// {
// 	char	*line;
// 	t_node	*tree;

// 	if (sh_state_init(argc, argv, envp))
// 		return (1);
// 	line = readline(SH_PS1);
// 	while (line)
// 	{
// 		if (ft_strspn(line, " \n\t") < ft_strlen(line))
// 			add_history(line);
// 		tree = parse(line);
// 		print_node_argv(tree);
// 		node_tree_clear(&tree);
// 		free(line);
// 		line = readline(SH_PS1);
// 	}
// 	sh_state_destroy();
// }
