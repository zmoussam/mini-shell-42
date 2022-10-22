
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
#include "./include/execution.h"
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

char	*get_wd(char *path)
{
	char	*working_directory;
	char	*cwd;

	working_directory = ft_strrchr(path, '/');
	working_directory = ft_strjoin("\033[0;33m➜  \033[0;36m", working_directory);
	cwd = ft_strjoin(working_directory, "\033[0;31m :: \033[0;37m");
	free(path);
	free(working_directory);
	return (cwd);	
}
void	handler(int signum)
{
	if (signum == SIGQUIT)
		return ;
}
int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_node	*tree;
	struct sigaction sa;
	sa.sa_handler = &handler;
	// sa.sa_flags = SA_RESTART;
	rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	char		*prompt;
	(void)argc;
	(void)argv;
	
	prompt = get_wd(getcwd(NULL, 0));
	env_list = create_env(env);

	if (sh_state_init(argc, argv, env))
		return (1);	
	ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
	printf("promt = %s\n", prompt);	
	line = readline(prompt);
	free(prompt);
	while (line)
	{
		// rl_redisplay();
		if (ft_strspn(line, " \n\t") < ft_strlen(line))
			add_history(line);
		tree = parse(line);
		execution(tree);
		node_tree_clear(&tree);
		free(line);
		// printf("\001\033[0;33m➜  \001\033[0;36m");
		prompt = get_wd(getcwd(NULL, 0));
		line = readline(prompt);
		free(prompt);
	}
	return (printf("exit\n"));
}