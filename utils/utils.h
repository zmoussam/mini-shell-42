/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:53:24 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/02 13:34:48 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

typedef struct s_wc_node
{
	char				*d_name;
	int					len;
	struct s_wc_node	*next;
}		t_wc_node;

typedef struct s_cmd
{
	t_wc_node				*wc;
	char					*word;
	struct s_cmd				*next;
}			t_cmd;

t_cmd	*ft_new_cmd(char *content, t_wc_node **list);
void	cmd_addback(t_cmd **lst, t_cmd *new);
t_cmd	*cmd_lstlast(t_cmd *lst);
t_wc_node	*lstlast_dir(t_wc_node *lst);
void	lstadd_back_dir(t_wc_node **lst, t_wc_node *new_ld);
t_wc_node	*lstnew_dir(char *content, int   len);
int	wc_size(t_wc_node *lst);
int	cmd_size(t_cmd *lst);
void	wc_clear(t_wc_node **lst);
void	cmd_clear(t_cmd **lst);
char    *remove_q(char *s);
#endif