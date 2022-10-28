
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
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/signal.h>
#include<sys/wait.h>
#include <sys/errno.h>

t_sh_state	g_sh_state = {0};
t_env_node *env_list;

// extern char **environ;

const char	*get_wd(char *path)
{
	char	*working_directory;
	char	*cwd;

	working_directory = ft_strrchr(path, '/');
	working_directory = ft_strjoin("\e[1;41m➜\e[0m\e[1;41m", working_directory);
	cwd = ft_strjoin(working_directory, "\e[0m\e[1;41m => \e[0m ");
	free(path);
	free(working_directory);
	return (cwd);	
}

void	handler(int signum)
{

	if (signum == SIGQUIT)
		return ;
	if (signum == SIGINT)
		rl_done = 1;
}

int get_c()
{
	return 0;
}
// 
int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_node	*tree;
	struct sigaction sa;
	t_env_node *copy;
	sa.sa_handler = &handler;
	sa.sa_flags = SA_RESTART;
	//initialize_readline();
	rl_catch_signals = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGQUIT, &sa, NULL) == -1)
		printf("%s\n", strerror(errno));
	const	char	*prompt;
	(void)argc;
	(void)argv;
	prompt = get_wd(getcwd(NULL, 0));
	env_list = create_env(env);
	copy = env_list;

	if (sh_state_init(argc, argv, env))
		return (1);	
	ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
	rl_event_hook = get_c;
	line = readline(prompt);
	free((void *)prompt);
	while (line)
	{
		if (ft_strspn(line, " \n\t") < ft_strlen(line))
			add_history(line);
		tree = parse(line);
		execution(tree);
		free(line);
		prompt = get_wd(getcwd(NULL, 0));
		line = readline(prompt);
		// printf("%d", rl_end);
		free((void *)prompt);
	}
	return (printf("exit\n"));
}
