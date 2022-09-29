/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:23:22 by syakoubi          #+#    #+#             */
/*   Updated: 2022/09/30 00:24:17 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"
#include "include/parser.h"
#include "include/shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/signal.h>

void    execution_cmd(char **cmd, int nbr_of_option)
{
    if (cmd[0] == "echo")
        echo();
    if (cmd[0] == "cd")
        cd();
    if (cmd[0] == "pwd")
        pwd();
    if (cmd[0] == "export")
        export();
    if (cmd[0] == "unset")
        unset();
    if (cmd[0] == "env")
        env();
    if (cmd[0] == "exit")
        exit();
}
void    execution(t_node    *node)
{
    if (root == NULL)
        return;
    if (node->type == SIMPLE_CMD)
    {
        execution_cmd(node->argv, node->argc);
        return ;
    }
    if (node->type == PIPE)
        execution(node->left);
    execution(node->right);
}
void printtabs(int numtabs){
    for (int i = 0; i < numtabs; i++){
        printf("\t");
    }   
}
void    printtree_rec(t_node *root, int level){
    if (root == NULL){
        printtabs(level);
        printf("----<empty>----\n");
        return;
    }
    printtabs(level);
    printf("-----> type = %d\n", root->type);
    printf("-----> argc = %d\n", root->argc);
	int i = 0;
	while(root->argv[i])
	{
		printf("----> argv[%d] == %s\t", i, root->argv[i]);
		i++;
	}
	printf("\n");
    printtabs(level);
    printf("  : left\n");
    printtree_rec(root->left, level + 1);
    printtabs(level);
    printf("  : right\n ");
    printtree_rec(root->right, level + 1);
    printtabs(level);
    printf("done\n");   
}
void printtree(t_node * root){
    printtree_rec(root, 0);
}
t_sh_state	g_sh_state = {0};

int	main()
{
	char	*line;
	t_node	*tree;

	line = readline(SH_PS1);
	while (line)
	{
		if (ft_strspn(line, " \n\t") < ft_strlen(line))
			add_history(line);
		tree = parse(line);
		printtree(tree);
		node_tree_clear(&tree);
		free(line);
		line = readline(SH_PS1);
	}
}
