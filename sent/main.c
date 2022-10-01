/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:23:22 by syakoubi          #+#    #+#             */
/*   Updated: 2022/10/01 20:03:08 by zmoussam         ###   ########.fr       */
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

void    echo(t_node *root)
{
    printf("%s\n ", root->argv[1]);     
    //printf("%s\n", root->argv[2]);     
}
void    execution_cmd(t_node *root)
{
    if (!ft_strcmp(root->argv[0], "echo"))
        echo(root);
}
// void    execution(t_node    *node)
// {
//     if (root == NULL)
//         return;
//     if (node->type == SIMPLE_CMD)
//     {
//         execution_cmd(node->argv, node->argc);
//         return ;
//     }
//     if (node->type == PIPE)
//     {
//         execution(node->left);
//         execution(node->right);
//         return ;
//     }
// }
void printtabs(int numtabs){
    for (int i = 0; i < numtabs; i++){
        printf("\t");
    }   
}
void    printtree_rec(t_node *root, int level){
    if (root == NULL){
       // printtabs(level);
        printf("\t----<empty>----\n");
        return;
    }
    printtabs(level);
    if (root->type == PIPE)
    {
        printtree_rec(root->left, level + 1);
        printtree_rec(root->right, level + 1);
        printf("done\n");   
    }
    else
    {
        execution_cmd(root);  
    }
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
