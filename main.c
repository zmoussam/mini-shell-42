/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:05:28 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/08 00:32:23 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"
#include "./execution/execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/errno.h>
#include <signal.h>
#include <sys/signal.h>

t_glb_v glb_v;

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
int get_c()
{
	return 0;
}

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
	{
		*glb_v.check_signal = 1;
		rl_done = 1;
	}
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_parser_node	*tree = NULL;
	struct sigaction sa;
	const	char	*prompt;
	int		x = 0;

	glb_v.check_signal = &x;
	sa.sa_handler = &handler;
	sa.sa_flags = SA_RESTART;
	
	rl_catch_signals = 0;
  
	if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGQUIT, &sa, NULL) == -1)
		printf("%s\n", strerror(errno));


	if (argc < 2 && !argv[1])
	{
		glb_v.list = create_env(envp);
		ft_list_remove_if(&glb_v.list, "OLDPWD");
		rl_event_hook = get_c;
		
		prompt = get_wd(getcwd(NULL, 0));
		line = readline(prompt);
		free((void *)prompt);
		while (line)
		{
			// printf("%zu\n"    , ft_strspn(line, " \n\t"));
			
			if (ft_strspn(line, " \n\t") < ft_strlen(line))
				add_history(line);
			tree = parse(line);
			if (tree)
			{
				if (x == 0)
				    execution(tree);//  print_node_argv(tree);
				x = 0;
				node_del(&tree);
			}
			free(line);
			prompt = get_wd(getcwd(NULL, 0));
			line = readline(prompt);
			free((void *)prompt);
		}
		return (printf("exit\n"));
	}
	// sh_state_destroy();
}