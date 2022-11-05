/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:49 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/30 21:09:59 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

unsigned long long	ft_llatoi(const char *str)
{
	unsigned long long	nombre;
	int				signe;
	int				i;

	i = 0;
	nombre = 0;
	signe = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nombre = nombre * 10;
		nombre = nombre + (int)(str[i] - '0');
		i++;
	}
	if (nombre > 9223372036854775807)
		return (255);
	return (nombre * signe);
}

int	check_if_all_digit(char *arg)
{
	int	i;

	i = 0;
	while(arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

void	exit_cmd(t_node *root)
{
	unsigned long long	result;

	printf("exit\n");
	if (root->argc == 1)
		exit(1);
	else if ((root->argc > 1 && !check_if_all_digit(root->argv[1])) \
	|| (check_if_all_digit(root->argv[1]) && ft_strlen(root->argv[1]) > 19))
	{
		printf("minishell: exit: %s: numeric argument require\n", root->argv[1]);
		exit(255);
	}
	else if (root->argc == 2 && check_if_all_digit(root->argv[1]))
	{
		result = ft_llatoi(root->argv[1]);
		printf("result  = %lld\n", result);
		if (result < 0)
			exit(256 - ((result * -1) % 256));	
		exit(result % 256);
	}
	else if (root->argc > 2 && check_if_all_digit(root->argv[1]))
	{
		printf("minishell: exit: %s: too many arguments\n", root->argv[1]);
	}
	//u should free data;
}