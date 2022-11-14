/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 03:49:02 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/14 12:50:21 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parser.h"
#include "./execution/execution.h"
#include "utils/utils.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/errno.h>
#include <signal.h>
#include <sys/signal.h>

t_glb_v	g_lbv;

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
	intialize_signal();
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
		printf("exit\n");
		return (free_env_list(), 0);
	}
}
