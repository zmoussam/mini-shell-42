/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:13:41 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/13 22:54:47 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "./builtins/builtins.h"
# include <sys/types.h>
# include <unistd.h>

int		check_path(char *path);
void	*launch_executabl(t_parser_node *root);
void	execution_cmd(t_parser_node *root);
void	execution(t_parser_node *root);
char	**copy_env(int size, int index);
void	free_env(char **env, int index);
void	copy_argv_for_execve(char **root_argv, char **args, char *first_arg);
int		execute_file(char *path, char **argv, char **env, int v);
void	*searsh_in_path(char *path, char **argv, char **env, char **args);
void	str_tolower(char *str);

#endif
