/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:45 by syakoubi          #+#    #+#             */
/*   Updated: 2022/01/04 01:01:42 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <sys/types.h>

/*
 * Adds `bytes_written` to `*writec`.
 * If either of them is initially -1, `*writec` is set to -1.
 */
void	ft_acc_writec(ssize_t bytes_written, ssize_t *writec);

/*
 * Outputs at most `n` characters from the string `s` to stdout.
 * Adds the number of bytes written to `writec` or sets it to -1 on failure.
 * If `writec` is initially -1 no operation is performed.
 */
void	ft_putnstr_acc(const char *s, size_t n, ssize_t *writec);

/*
 * Outputs the string `s` to stdout.
 * Adds the number of bytes written to `writec` or sets it to -1 on failure.
 * If `writec` is initially -1 no operation is performed.
 */
void	ft_putstr_acc(const char *s, ssize_t *writec);

/*
 * Outputs the character `c` to stdout.
 * Adds the number of bytes written to `writec` or sets it to -1 on failure.
 * If `writec` is initially -1 no operation is performed.
 */
void	ft_putchar_acc(char c, ssize_t *writec);

/*
 * Outputs the string representation of an unsigned long
 * in a given `base` to stdout, where `precision` is the minimum number
 * of digits to be printed.
 * If `n` and `precision` are both zero, no operation is performed.
 * Adds the number of bytes written to `writec` or sets it to -1 on failure.
 * If `writec` is initially -1 no operation is performed.
 */
void	ft_putul_acc(
			unsigned long n,
			const char *base,
			int precision,
			ssize_t *writec
			);

#endif /* COMMON_H */
