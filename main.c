/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 03:49:02 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/12 18:13:24 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "./execution/execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/errno.h>
#include <signal.h>
#include <sys/signal.h>

t_glb_v g_lbv;

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_strchr(accept, s[i]))
		i++;
	return (i);
}

void	print_node_argv(t_parser_node *node)
{
	char	**argv = node->av;

	if(node->type == PIPE)
	{
		print_node_argv(node->left);
		print_node_argv(node->right);
	}
	else
	{
		while (argv && *argv)
			printf("%s\n", *argv++);
		if(node->rdrlst)
			printf("file = %s\n", node->rdrlst->file);
	}
}
int readline_hook()
{
	return 0;
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
int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_parser_node	*tree = NULL;
	const	char	*prompt;

	rl_catch_signals = 0;
	rl_event_hook = readline_hook;
	if (signal(SIGINT, &handler) == SIG_ERR || signal(SIGQUIT, &handler) == SIG_ERR)
		printf("minishell: %s\n", strerror(errno));
	if (argc < 2 && !argv[1])
	{
		g_lbv.list =  create_env(envp);
		ft_list_remove_if(&g_lbv.list, "OLDPWD");
		while (true)
		{
			prompt =  get_wd(getcwd(NULL, 0));
			line = readline(prompt);
			free((void *)prompt);
			if (line == NULL)
					break;
			if (ft_strspn(line, " \n\t") < ft_strlen(line))
				add_history(line);
			tree = parse(line);
			if (tree)
			{
				if (g_lbv.check_signal == 0)
				// printf("file == %s\n", tree->rdrlst->next->next->file);
				    execution(tree);
				g_lbv.check_signal = 0;
				node_del(&tree);
			}
			free(line);
		}
		return (printf("exit\n"));
	}
	// sh_state_destroy();
}