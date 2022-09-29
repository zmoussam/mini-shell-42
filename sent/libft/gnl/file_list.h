/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:49:33 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_LIST_H
# define FILE_LIST_H

# include "libft.h"
# include "file.h"

/*
 * Locates a node where its content is a `t_file`
 * instance with an `fd` member that equals the provided `fd`,
 * and returns it.
 * Returns NULL if such a node is not found.
 */
t_list	*ft_file_find(t_list *lst, int fd);

/*
 * Locates a node where its content is a `t_file`
 * instance with an `fd` member that equals the provided `fd`,
 * and returns that `t_file` instance.
 * Returns NULL if such a node is not found.
 */
t_file	*ft_file_get(t_list *lst, int fd);

/*
 * Locates a node where its content is a `t_file`
 * instance with an `fd` member that equals the provided `fd`,
 * and returns that `t_file` instance.
 * If such a node is not found,
 * a new one is created and added to the front of `*lst`,
 * and the newly created `t_file` instance is returned.
 * Returns NULL on allocation failure.
 */
t_file	*ft_file_get_or_create(t_list **lst, int fd);

/*
 * Locates a `t_list` node where its content is a `t_file`
 * instance with an `fd` member that equals the provided `fd`,
 * removes it from the list then frees its content.
 * If such a node is not found, `*lst` is untouched.
 */
void	ft_file_delete(t_list **lst, int fd);

#endif /* FILE_LIST_H */
