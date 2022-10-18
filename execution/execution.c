/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:11:40 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/18 22:16:54 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/execution.h"

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
				waitpid(pid, NULL, 0);
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
						waitpid(pid, NULL, 0);
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
	int	pid;
	int	fd[2];

    if (pipe(fd) == -1)
        return ;
    if (root == NULL){
        return;
    }
    if (root->type == PIPE)
    {
        pid = fork();
        if (pid == 0)
        {
            close(STDOUT_FILENO);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execution(root->left);
            exit(0);
        }
        waitpid(pid, NULL, 0);
        pid = fork();
        if (pid == 0)
        {
            close(STDIN_FILENO);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            execution(root->right);
            exit(0);  
        }
        close(fd[0]);
        close(fd[1]);
        waitpid(pid, NULL, 0);
	}
    else
        execution_cmd(root);
}
