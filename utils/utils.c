/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:29:06 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/14 14:36:03 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../parsing/parser.h"
#include "../execution/execution.h"

int	readline_hook(void)
{
	return (0);
}

void	handler(int signum)
{
	if (signum == SIGQUIT)
	{
		g_lbv.check_sigquit = 1;
		return ;
	}
	if (signum == SIGINT)
	{
		g_lbv.exit_status = 256;
		g_lbv.check_signal = 1;
		rl_done = 1;
	}
}

void	intialize_signal(void)
{
	g_lbv.check_sigquit = 0;
	rl_catch_signals = 0;
	rl_event_hook = readline_hook;
	if (signal(SIGINT, &handler) == SIG_ERR \
		|| signal(SIGQUIT, &handler) == SIG_ERR)
		printf("minishell: %s\n", strerror(errno));
}

void	free_env_list(void)
{
	t_env_node	*head;

	head = g_lbv.list;
	while (head)
	{
		delone_env(head);
		head = head->next;
	}
}

const char	*get_wd(char *path)
{
	char	*working_directory;
	char	*cwd;

	cwd = NULL;
	if (path)
	{
		working_directory = ft_strrchr(path, '/');
		working_directory = ft_strjoin("\e[0;35m➜", working_directory);
		cwd = ft_strjoin(working_directory, "\e[0m\e[0;35m => \e[0m ");
		free(path);
		free(working_directory);
	}
	else
		cwd = ft_strdup("\e[0;35m!!➜/N.A.D => \e[0m ");
	return (cwd);
}
