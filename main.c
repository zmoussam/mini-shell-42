/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 03:49:02 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/13 17:19:33 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parser.h"
#include "./execution/execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/errno.h>
#include <signal.h>
#include <sys/signal.h>

t_glb_v	g_lbv;

int	readline_hook(void)
{
	return (0);
}

const char	*get_wd(char *path)
{
	char	*working_directory;
	char	*cwd;

	cwd = NULL;
	if (path)
	{
		working_directory = ft_strrchr(path, '/');
		working_directory = ft_strjoin("\e[1;41m➜", working_directory);
		cwd = ft_strjoin(working_directory, "\e[0m\e[1;41m => \e[0m ");
		free(path);
		free(working_directory);
	}
	else
		cwd = ft_strdup("\e[1;41m!!➜/N.A.D => \e[0m ");
	return (cwd);
}

void	handler(int signum)
{
	if (signum == SIGQUIT)
		return ;
	if (signum == SIGINT)
	{
		g_lbv.check_signal = 1;
		rl_done = 1;
	}
}

void	minishell(t_parser_node *tree, char *line)
{
	if (ft_strcmp(line, "") != 0)
		add_history(line);
	if (g_lbv.check_signal == 0)
	{
		tree = parse(line);
		if (tree)
		{
			if (g_lbv.check_signal == 0)
				execution(tree);
			node_del(&tree);
		}
	}
	g_lbv.check_signal = 0;
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_parser_node	*tree;
	const char		*prompt;

	tree = NULL;
	rl_catch_signals = 0;
	rl_event_hook = readline_hook;
	if (signal(SIGINT, &handler) == SIG_ERR \
		|| signal(SIGQUIT, &handler) == SIG_ERR)
		printf("minishell: %s\n", strerror(errno));
	if (argc < 2 && !argv[1])
	{
		g_lbv.list = create_env(env);
		ft_list_remove_if(&g_lbv.list, "OLDPWD");
		while (true)
		{
			prompt = get_wd(getcwd(NULL, 0));
			line = readline(prompt);
			free((void *)prompt);
			if (line == NULL)
				break ;
			minishell(tree, line);
		}
		return (printf("exit\n"));
	}
}
