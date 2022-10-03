/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:46 by syakoubi          #+#    #+#             */
/*   Updated: 2022/01/04 01:02:10 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPEC_H
# define SPEC_H

# define FLAG_MASK			(0x001f)
# define FLAG_HASHTAG		(0x0001)
# define FLAG_ZERO			(0x0002)
# define FLAG_MINUS			(0x0004)
# define FLAG_SPACE			(0x0008)
# define FLAG_PLUS			(0x0010)

# define SPECIFIER_MASK		(0xffe0)
# define SPECIFIER_D		(0x0020)
# define SPECIFIER_I		(0x0040)
# define SPECIFIER_U		(0x0080)
# define SPECIFIER_X		(0x0100)
# define SPECIFIER_UPPER_X	(0x0200)
# define SPECIFIER_C		(0x0400)
# define SPECIFIER_S		(0x0800)
# define SPECIFIER_P		(0x1000)
# define SPECIFIER_PERCENT	(0x2000)

#endif /* SPEC_H */
